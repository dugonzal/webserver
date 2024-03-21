/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:00:28 by jaizpuru          #+#    #+#             */
/*   Updated: 2024/03/21 17:54:03 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/Request.hpp"

Request::Request( void ) {}

Request::Request( int _serverFd ) {
	timeout.tv_sec = 5; // 5 seconds for Client
	timeout.tv_usec = 0;
	serverFd = _serverFd;
	bzero(clientMsg, sizeof(clientMsg));
	std::cout << std::endl << "------------INPUT_DATA----------------" << std::endl;
	if ((clientFd = accept(_serverFd, (sockaddr *)&clientAddr, &addrClientLen)) < 0)
		perror("error: accept");

	if (setsockopt(clientFd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0)
		perror("error: setsockopt()");

	//! Recieve message
	returnedBytes = recv(clientFd, clientMsg, sizeof(clientMsg), 0);
	if (returnedBytes < 0) {
		close(clientFd);
		perror("recv error");
		return ;
	} else if (returnedBytes == 0) { // Connection closed by the client
		close(clientFd);
		perror("client closed connection");
		return ;
	} else // Data received, process it
		std::cout << "Bytes received: " << returnedBytes << std::endl;
	inputIsGood = true;
	inputMethod = getMethod();
	if (inputIsGood == true) {
		inputRoute = getRoute();
		if (inputIsGood == true)
			checkHttpVersion();
	}
	std::cout << std::endl << "--------------INPUT--------------" << std::endl;
	std::cout << std::endl << clientMsg << std::endl;

	//! Response
	if (inputRoute.empty()) // No file is asked
		responseFile = readFile("resources/default.html");
	else // Any file is asked
		responseFile = readFile(inputRoute);

	if (responseFile == "" || inputIsGood == false) { // File is not found
		responseHeader = "HTTP/1.1 404 Not found\r\n";
		responseFile = readFile("resources/404.html");
	}
	else // File is found
		responseHeader = "HTTP/1.1 200  OK\r\n";
	responseHeader += "Content-Type: text/html\r\n";
	responseHeader += "Content-Length:  \r\n";
	responseHeader += "\r\n";
	responseHeader += responseFile;
	std::cout << "--------------OUTPUT--------------" << std::endl << responseHeader << std::endl << "---------------------------------" << std::endl;
	send(clientFd, responseHeader.data(), responseHeader.size(), 0);


	close(clientFd); // After server has replied, close connection
}

Request::~Request( void ) {}

std::string	Request::getRoute( void ) {
	std::string str(clientMsg);
	std::stringstream ss;
	size_t start;


	for (start = 0; str[start]; start++) {
		if (start > 0 && str[start - 1] == ' ')
			break;
		else if (str[start] == '\n') {
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
			inputIsGood = false;
			return "";
		}
	}
	else {
		inputIsGood = false;
		return "";
	}
	
	std::cout << "Route : " << ss.str() << std::endl;
	std::string ret(ss.str());
	return (ret);
}

int		Request::getMethod( void ) {
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
		return 0;
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
		perror("error: HTTP version is erroneus");
		return ;
	}
	while (firstLine[pos] && firstLine[pos] < '0' && firstLine[pos] > '9') {
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
		inputIsGood = false;
		perror("error: HTTP version is erroneus");
	}
	ss.clear();
	std::cout << std::endl;
}
