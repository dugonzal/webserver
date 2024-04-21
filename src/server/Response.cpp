/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:48:59 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 19:30:35 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Response.hpp"

Response::Response( void ) {
	ptrData = NULL;
	response = "";
}

void	Response::setPtrRequest( Request* ptr ) { ptrData = ptr; }

Response::~Response( void ) { }

Response::Response( const Response& ref ) {
	this->ptrData = ref.getPtrData();
	this->response = ref.getResponse();
}

Response	Response::operator=(const Response& ref) {
	this->ptrData = ref.getPtrData();
	this->response = ref.getResponse();
	return *this;
}

Request*	Response::getPtrData( void ) const {
	return ptrData;
}

std::string	Response::getResponse( void ) const {
	return response;
}
