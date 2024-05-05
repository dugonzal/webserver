/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _Request.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:54:41 by jaizpuru          #+#    #+#             */
/*   Updated: 2024/04/21 08:49:10 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Utils.hpp"

#define GET 101
#define DELETE 201
#define POST 301

class Request {
	private:
    int							returnedBytes;
	  int							inputMethod;
    string					inputRoute;
	  bool						inputIsGood;
	  string					responseFile;
	  string					responseHeader; // Header for Client
	  string          method, file;
	public:
		Request(void);
		~Request(void);

		int		parseClientMsg(void);
		// Parsing input
		int		getMethodType(void);
		string	getRoute(void);
		void	checkHttpVersion(void);
    void  tmp(void);
		// Funciones Iker
		void methodGet(void);
		void methodPost(void);
		void methodDelete(void);
};
