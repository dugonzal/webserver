/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSide.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:00:28 by jaizpuru          #+#    #+#             */
/*   Updated: 2024/03/19 16:55:34 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/ClientSide.hpp"

ClientSide::ClientSide( void ) {}

ClientSide::ClientSide( int _serverFd ) {
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

	openFile(getRoute());
	std::cout << std::endl << clientMsg << std::endl;

	//! Response
	serverResponse = "HTTP/1.1 200  OK\r\n\r\n <html><head></head><body><h1 text-family=\"Roboto\" align=\"center\"> Hello, Inception42! </h1></body></html>";
		std::string msgRet(clientMsg);
	if (msgRet.find("favicon.ico", 0) != std::string::npos) {
		msgRet = readFaviconFile("resources/favicon.ico");
		std::string httpResponse = "HTTP/1.1 200 OK\r\n";
		httpResponse += "Content-Type: image/x-icon\r\n";
		httpResponse += "Content-Length: " + std::to_string(msgRet.size()) + "\r\n";
		httpResponse += "\r\n";
		httpResponse += msgRet;
		send(clientFd, httpResponse.data(), httpResponse.size(), 0);
	}
	else
	send(clientFd, serverResponse.data(), serverResponse.size(), 0);


	close(clientFd); // After server has replied, close connection
}

ClientSide::~ClientSide( void ) {}

std::string	ClientSide::getRoute( void ) {
	std::string str(clientMsg);
	std::stringstream ss;

	size_t start = str.find("/", 0);
	if (str[start] == '/' && str[start + 1] == ' ')
		;
	else {
		for (start = start + 1; str[start] != ' '; start++) {
			ss << str[start];
		}
	}
	if (ss.str().empty()) // abort open, since user did not ask for any file
		ss << "none";
	std::cout << "Route : " << ss.str() << std::endl;
	std::string ret(ss.str());
	return (ret);
}

int ClientSide::openFile( std::string _route ) {
	if (!_route.compare("none"))
		return 1;
	std::ifstream file;
	file.open(_route.c_str());
	if (file.is_open() > 0 )
		;
	else { // return 404 page
		_route = "resources/404.html";
		file.open(_route.c_str());
	}	
	char ret[1028];
	while (file.getline(ret, 1028)) {
		std::cout << "Size to read : " << file.gcount() << " : ";
		std::cout << ret << std::endl;
	}
	std::cout << ret << std::endl;
	file.close();
	return 0;
}
