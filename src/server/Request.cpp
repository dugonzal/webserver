/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:00:28 by jaizpuru          #+#    #+#             */
/*   Updated: 2024/03/19 16:55:34 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/Request.hpp"

Request::Request( void ) {}

Request::Request( int _serverFd ) {
	timeout.tv_sec = 5; // 5 seconds for Client
	timeout.tv_usec = 0;
	bzero(clientMsg, sizeof(clientMsg));
	if ((clientFd = accept(_serverFd, (sockaddr *)&clientAddr, &addrClientLen)) < 0)
	throw std::logic_error("error: accept");

	if (setsockopt(clientFd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0)
		throw(std::runtime_error("error: setsockopt()"));

	//! Recieve message
	returnedBytes = recv(clientFd, clientMsg, sizeof(clientMsg), 0);
	if (returnedBytes < 0) {
		close(_serverFd);
		close(clientFd);
		throw std::logic_error("recv error");
	} else if (returnedBytes == 0) { // Connection closed by the client
		close(_serverFd);
		close(clientFd);
		throw std::runtime_error("client closed connection");
	} else // Data received, process it
		std::cout << "Bytes received: " << returnedBytes << std::endl;

	method = getMethod();
	_route = getRoute();
	std::cout << std::endl << "--------------INPUT--------------" << std::endl;
	std::cout << std::endl << clientMsg << std::endl;

	//! Response
	if (_route.empty()) // No file is asked
		fileResponse = readFile("resources/default.html");
	else // Any file is asked
		fileResponse = readFile(_route);

	if (fileResponse == "") { // File is not found
		httpResponse = "HTTP/1.1 404 Not found\r\n";
		fileResponse = readFile("resources/404.html");
	}
	else // File is found
		httpResponse = "HTTP/1.1 200  OK\r\n";
	httpResponse += "Content-Type: text/html\r\n";
	httpResponse += "Content-Length: " + std::to_string(fileResponse.size()) + "\r\n";
	httpResponse += "\r\n";
	httpResponse += fileResponse;
	std::cout << "--------------OUTPUT--------------" << std::endl << httpResponse << std::endl << "---------------------------------" << std::endl;
	send(clientFd, httpResponse.data(), httpResponse.size(), 0);


	close(clientFd); // After server has replied, close connection
}

Request::~Request( void ) {}

std::string	Request::getRoute( void ) {
	std::string str(clientMsg);
	std::stringstream ss;

	size_t start = str.find("/", 0);
	if (str[start] == '/' && str[start + 1] == ' ')
		return ("");
	else {
		for (start = start + 1; str[start] != ' '; start++) {
			ss << str[start];
		}
	}
	std::cout << "Route : " << ss.str() << std::endl;
	std::string ret(ss.str());
	return (ret);
}

int		Request::getMethod( void ) {
	std::stringstream ss;

	for ( int i = 0; !isspace(clientMsg[i]); i++)
		ss << clientMsg[i];

	std::cout << "Method : " << ss.str() << std::endl;
	if (!ss.str().compare("GET"))
		return GET;
	else if (!ss.str().compare("DELETE"))
		return DELETE;
	else if (!ss.str().compare("POST"))
		return POST;
	return 0;
}
