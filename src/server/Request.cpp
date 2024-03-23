/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:00:28 by jaizpuru          #+#    #+#             */
/*   Updated: 2024/03/23 09:59:58 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/Request.hpp"

Request::Request(void) {
  timeout.tv_sec = 5;
  timeout.tv_usec = 0;
  addrClientLen = sizeof(clientAddr);
}

Request::Request(int _serverFd): inputIsGood(true) {
  bzero(clientMsg, sizeof(clientMsg));
	std::cout << std::endl << "------------INPUT_DATA----------------" << std::endl;
	if ((clientFd = accept(_serverFd, (sockaddr *)&clientAddr, &addrClientLen)) < 0)
    perror("error: accept");

	if (setsockopt(clientFd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0)
    perror("error: setsockopt()");

  //! Recieve message
	if (parseClientMsg() == EXIT_FAILURE)
     return ;

	// Message from the client
	/* std::cout << std::endl << "--------------INPUT--------------" << std::endl;
	std::cout << std::endl << clientMsg << std::endl; */

	//! Response
	// Manage file
	if (inputRoute.empty()) // No file is asked
		responseFile = readFile("resources/default.html");
	else // Any file is asked
		responseFile = readFile(inputRoute);

	//! Differing method types should divide here!
	switch (inputMethod) {
		case GET:
			methodGet();
			break ;
		case POST:
			methodPost();
			break ;
		case DELETE:
			methodDelete();
			break ;
		default:
			// Erroneus Method, 405 Error (@inunez-g)
			break ;
}

	//! Message for the client
	/* std::cout << "--------------OUTPUT--------------" << std::endl << responseHeader << std::endl << "---------------------------------" << std::endl; */

	close(clientFd); // After server has replied, close connection
}

Request::~Request( void ) {}

/* Parse Client Message */
int	Request::parseClientMsg( void ) {
	returnedBytes = recv(clientFd, clientMsg, sizeof(clientMsg), 0);
	if (returnedBytes < 0) {
		close(clientFd);
		perror("recv error");
		return (EXIT_FAILURE);
	} else if (returnedBytes == 0) { // Connection closed by the client
		close(clientFd);
		perror("client closed connection");
		return (EXIT_FAILURE);
	} else // Data received, process it
		std::cout << "Bytes received: " << returnedBytes << std::endl;

	inputMethod = getMethodType();
	if (inputIsGood == true) {
		inputRoute = getRoute();
		if (inputIsGood == true)
			checkHttpVersion();
	}
	else
		inputRoute = "";
	return (0);
}

std::string	Request::getRoute( void ) {
	std::string str(clientMsg);
	std::stringstream ss;
	size_t start;


	for (start = 0; str[start]; start++) {
		if (str[start] == '/' && str[start - 1] == ' ')
			break;
		else if (str[start] == '\n') {
			perror("error: Route is non existent");
			inputIsGood = false;
			return ("");
		}
	}
	if (str[start] && str[start + 1]) {
		if (str[start] == '/' && isspace(str[start + 1])) {
			std::cout << "Route : " << "/" << std::endl;
			return ("");
		}
		else if (str[start] == '/' && isalnum(str[start + 1])) {
			for (start = start + 1; str[start] != ' '; start++) {
				ss << str[start];
			}
		}
		else {
			perror("error: Route has special characters");
			inputIsGood = false;
			return "";
		}
	}
	else {
		perror("error: Route is erroneus");
		inputIsGood = false;
		return "";
	}
	
	std::cout << "Route : " << ss.str() << std::endl;
	std::string ret(ss.str());
	return (ret);
}

int		Request::getMethodType( void ) {
	std::stringstream ss;

	for ( int i = 0; !isspace(clientMsg[i]) && clientMsg[i]; i++)
		ss << clientMsg[i];

	std::cout << "Method : " << ss.str() << std::endl;
	if (!ss.str().compare("GET"))
		return GET;
	else if (!ss.str().compare("DELETE"))
		return DELETE;
	else if (!ss.str().compare("POST"))
		return POST;
	else {
		inputIsGood = false;
		perror("error: Method is erroneus OR non-handled");
		return (EXIT_FAILURE);
	}
}

void	Request::checkHttpVersion( void ) {
	std::string str(clientMsg);
	std::string firstLine;
	std::stringstream ss;

	firstLine = str.substr(0, str.find("\n", 0));
	size_t pos = firstLine.find("HTTP/", 0);
	if (pos == std::string::npos) {
		inputIsGood = false;
		perror("error: HTTP is not present in the header");
		return ;
	}
	while (firstLine[pos] && !isdigit(firstLine[pos])) {
		if (!firstLine[pos + 1] || isspace(firstLine[pos + 1])) {
			inputIsGood = false;
			perror("error: HTTP version: bad format");
			return ;
		}
		pos++;
	}
	while (firstLine[pos] && !isspace(firstLine[pos]))
		ss << firstLine[pos++];
	
	if (!ss.str().compare("1.1"))
		std::cout << "Version : " << ss.str() << std::endl;
	else {
		// Error 505 (@inunez-g)
		inputIsGood = false;
		perror("error: HTTP version is erroneus");
	}
	ss.clear();
	std::cout << std::endl;
}

/* Methods */
void Request::methodGet( void )
{
	std::stringstream ss;
	// Insert first line
	if (responseFile == "" || inputIsGood == false) { // File is not found
		responseHeader = "HTTP/1.1 404 Not found\r\n";
		responseFile = readFile("resources/404.html");
	}
	else // File is found
		responseHeader = "HTTP/1.1 200  OK\r\n";
	// Insert content
	responseHeader += "Content-Type: text/html\r\n";
	ss << responseFile.size() << "\r\n";
	responseHeader += "Content-Length: " + ss.str();
	responseHeader += "\r\n";
	responseHeader += responseFile;
	send(clientFd, responseHeader.data(), responseHeader.size(), 0);
}


void Request::methodPost( void )
{
	/*std::string msgRet(clientMsg);
	if (msgRet.find("favicon.ico", 0) != std::string::npos) {
		//msgRet = readFaviconFile("resources/favicon.ico");
		std::string httpResponse = "HTTP/1.1 200 OK\r\n";
		httpResponse += "Content-Type: text/html\r\n";
		httpResponse += "Content-Length: " + std::to_string(msgRet.size()) + "\r\n";
		httpResponse += "\r\n";
		httpResponse += msgRet;
		send(clientFd, httpResponse.data(), httpResponse.size(), 0);
	}*/
}

void Request::methodDelete( void )
{
	std::cout << "DELETEMETHOD" << std::endl;
	std::string httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
    // Intentar eliminar el archivo
    if (std::remove(("resources/GET/" + file).c_str()) != 0)
		httpResponse = "HTTP/1.1 404 Not Found\r\n";
	else
		httpResponse = "HTTP/1.1 200 OK\r\n";
	send(clientFd, httpResponse.data(), httpResponse.size(), 0);
	std::cout << "TERMINO" << std::endl;
	close(clientFd);
}
