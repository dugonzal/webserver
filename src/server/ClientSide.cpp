/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSide.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:00:28 by jaizpuru          #+#    #+#             */
/*   Updated: 2024/03/19 12:30:54 by jaizpuru         ###   ########.fr       */
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
		if (errno == EAGAIN || errno == EWOULDBLOCK) { // No data available, handle accordingly (e.g., retry later)
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			std::cout << "No data available, retry later." << std::endl;
		} else { // Other error occurred
			close(_serverFd);
			close(clientFd);
			throw std::logic_error("recv error");
		}
	} else if (returnedBytes == 0) { // Connection closed by the client
		close(_serverFd);
		close(clientFd);
		throw std::runtime_error("client closed connection");
	} else // Data received, process it
		std::cout << "Bytes received: " << returnedBytes << std::endl;

	setRoute();
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

void	ClientSide::setRoute( void ) {
	std::string str(clientMsg);
	std::stringstream ss;

	size_t start = str.find("/", 0);
	for (start = str.find("/", 0); clientMsg[start] != ' '; start++)
		ss << clientMsg[start];
	askedRoute = ss.str();
	std::cout << "Route : " << askedRoute << std::endl;
}

int ClientSide::openFile( const std::string& _route ) {
	if ( open(_route.c_str(), O_RDONLY) == -1 ) {
		// return 404 page
		throw (errno);
	}
	return 0;
}
