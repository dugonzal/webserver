/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:48:39 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/29 10:35:17 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Request.hpp"

Request::Request(void) { }

Request::~Request(void) { }

Request::Request(const Request &copy) {
  if (this != &copy) {
    header = copy.header;
  }
}

Request &Request::operator=(const Request &copy) {
  if (this != &copy) {
    header = copy.header;
  }
  return (*this);
}

void Request::setHeader(const char *_header) {
  header = _header;
}

void  Request::setLocation(const map<string, Location> &tmp) {
    locations = tmp;
}

bool  Request::setMethod(const string &_method) {
  vector<string> tmp = locationRoot.getmethods();
  for (size_t i = 0; i < tmp.size(); i++) {
    if (!tmp[i].compare(_method)) {
      method = _method;
      return (false);
    }
  }

  if (_method.compare("GET") && _method.compare("DELETE") \
    && _method.compare("POST")) {
      return (true);
  }
  return (true);
}

void  Request::setLocation(void) {
  map<string, Location>::iterator it = locations.find(route);
  if (it != locations.end()) {
    locationRoot = it->second;
    isCgi =  it->second.getIsCgi();
  } else {
    locationRoot = locations.find("root")->second;
    isCgi = false;
  }
}

bool  Request::setRouteAndVersion(const string &tmp) {
  route = firstWord(tmp);
  version = lastWord(tmp);
  if (version.compare("HTTP/1.1"))
    return (true);
  return(false);
}

void  Request::parserData(void) {
  int pos = header.find_first_of('\n');

  // set route and version
  if (setRouteAndVersion(trim(lastWord(header.substr(0, pos))))) {
    logger.Log("error version");
  }
  // set location:
  setLocation();
  // set method
  if (setMethod(trim(firstWord(header.substr(0, pos))))) {
    logger.Log("error method no allowed");
  }
  if (isCgi) {
    string tmp;
    if (locationRoot.getRoot()[locationRoot.getRoot().size() - 1] != '/') {
      tmp = locationRoot.getRoot();
      tmp.append("/");
    }
    tmp.append(locationRoot.getIndex());
    ifstream f(tmp.c_str());
    std::cout << tmp.c_str() << std::endl;
    if (f.fail()) {
      isCgi = false;
      std::cout << "(warning: bad Cgi route)" << std::endl;
      return ;
    }
    cgi.setCgi(locationRoot.getCgiPath(), tmp);
    cgi.handlerCgi();
    logger.Log("hay que lanzar cgi para esta location");
  }
}

//FUNCIONES IKER

int  Request::checkMethod(const string &_method) {
  vector<string> tmp = locationRoot.getmethods();
  for (size_t i = 0; i < tmp.size(); i++) {
    if (!tmp[i].compare(_method)) {
      return (1);
    }
  }
  return (0);
}

bool isAbsolutePath(const std::string& path) {
    // Verifica si la ruta comienza con "http://" o "https://"
    return (path.find("http://") == 0 || path.find("https://") == 0);
}

std::string generate_autoindex(const std::string& directoryPath, string autoindex, string route) {
    cout << "ey mi route es " << route << endl;
    // Abre el directorio
    DIR* dir = opendir(directoryPath.c_str());
    if (!dir) {
        return autoindex; // Error al abrir el directorio
    }

    autoindex += "<html><head><title>Index of " + directoryPath + "</title></head>\n";
    autoindex += "<body><h1>Index of " + directoryPath + "</h1><hr><ul>\n";

    // Lee el contenido del directorio
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        autoindex += "<li><a href=\"" + route + "/" + std::string(entry->d_name) + "\">" + std::string(entry->d_name) + "</a></li>\n";
        
    }

    autoindex += "</ul><hr></body></html>\n";

    // Cierra el directorio
    closedir(dir);

    return autoindex;
}

void Request::getMethod( void )
{
	std::map<std::string, std::string> location;
	//std::map<std::string, std::string> alias;
	//unsigned long max_length = 3000;
	location["GET/web2.html"] = "GET/web.html";
	location["/web3.html"] = "http://localhost:405/extra/web3.html";
	location["/Extra/hola.html"] = "https://www.youtube.com";
	//alias["/kapouet"] = "/mi_carpeta";
	std::string allowed_methods = "GET POST";
	std::cout << "GETMETHOD" << std::endl;
	std::string httpResponse;
	if (!checkMethod("GET"))
	{
		std::string httpResponse = "HTTP/1.1 405 Method Not Allowed\r\n";
    httpResponse += "Allow: " + allowed_methods + "\r\n";
    httpResponse += "\r\n";
		std::cout << "Error allowed methods" << std::endl;
		send(clientFd, httpResponse.data(), httpResponse.size(), 0);
	}
	else
	{
		if (location.find(route) != location.end())
		{
			if (isAbsolutePath(location[route]))
			{
    			// Redirección 301
				  std::cout << "AQUI VA" << std::endl;
    			httpResponse = "HTTP/1.1 302 Found\r\n";
    			httpResponse += "Location: " + location[route] + "\r\n";
				httpResponse += "\r\n";
				send(clientFd, httpResponse.data(), httpResponse.size(), 0);
			}
			else if (!location[route].empty())
			{
				httpResponse = "HTTP/1.1 301 Moved Permanently\r\n";
        
				  std::string host = locationRoot.getHost();
          std::stringstream locationRoute;
          locationRoute << locationRoot.getPort() << "/" << location[route];
          cout << "Location: " + host + ":" + locationRoute.str() << endl;
    			httpResponse += "Location: " + host + ":" + locationRoute.str() + "\r\n";//+ location[route] + "\r\n";//+ host + ":" + std::to_string(locationRoot.getPort()) + "/" + location[route] + "\r\n";
    			httpResponse += "\r\n";
    			send(clientFd, httpResponse.data(), httpResponse.size(), 0);
			}
			else
			{
				httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
				send(clientFd, httpResponse.data(), httpResponse.size(), 0);
			}
	  }
		else
		{
      std::cout << "Hola estoy aqui " << locationRoot.getRoot() + route << std::endl;
			std::stringstream fileRoute;
      fileRoute << locationRoot.getRoot() << route;
      std::ifstream archivo(fileRoute.str().c_str());
			std::ostringstream oss;
			std::string directoryPath = locationRoot.getRoot() + route;
			if (isDirectory(directoryPath)) {
          // Generar autoindex
          std::string autoindex;
          autoindex = generate_autoindex(directoryPath, autoindex, route);
          // Respuesta 200 OK con el autoindex
          httpResponse = "HTTP/1.1 200 OK\r\n";
          httpResponse += "Content-Type: text/html\r\n";
          std::stringstream strContentLength;
          strContentLength << autoindex.size();
          httpResponse += "Content-Length: " + strContentLength.str() + "\r\n";
          httpResponse += "\r\n";
          if (isCgi) {
            httpResponse += cgi.getCgi();
          }
          else
            httpResponse += autoindex;
          autoDirectory = route;
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
            } else if (archivo.is_open()){
				std::cout << "y" << std::endl;
				oss << archivo.rdbuf();
				std::string httpResponse;
				if (static_cast<long>(oss.str().size()) > locationRoot.getClientBodySize())
				{
					httpResponse = "HTTP/1.1 413 Request Entity Too Large\r\n";
					httpResponse += "\r\n";
					send(clientFd, httpResponse.data(), httpResponse.size(), 0);
				}
				else
				{
					// Respuesta 200 OK
	    			httpResponse = "HTTP/1.1 200 OK\r\n";
					httpResponse += "Content-Type: text/html\r\n";
          std::stringstream strContentLen;
          strContentLen << oss.str().size();
					httpResponse += "Content-Length: " + strContentLen.str() + "\r\n";
					httpResponse += "\r\n";
          httpResponse += oss.str();
					send(clientFd, httpResponse.data(), httpResponse.size(), 0);
				}
	    	}
			else
			{
				std::ifstream archivo("resources/GET/404.html");
	    		oss << archivo.rdbuf();
				std::string httpResponse = "HTTP/1.1 404 Not Found\r\n";
				httpResponse += "Content-Type: text/html\r\n";
        std::stringstream strContentLen;
        strContentLen << oss.str().size();
				httpResponse += "Content-Length: " + strContentLen.str() + "\r\n";
				httpResponse += "\r\n";
				httpResponse += oss.str();
				send(clientFd, httpResponse.data(), httpResponse.size(), 0);
			}
		}
	}
	
	std::cout << "TERMINO" << std::endl;
	close(clientFd);
}

std::string replaceAlias(const std::string& file, const std::map<std::string, std::string>& alias) {
    std::string result = file;
    
    for (std::map<std::string, std::string>::const_iterator it = alias.begin(); it != alias.end(); ++it) {
        const std::string& aliasPath = it->first;
        const std::string& replacement = it->second;
        
        size_t pos = result.find(aliasPath);
        
        // Si se encuentra el alias, reemplazarlo
        while (pos != std::string::npos) {
            result.replace(pos, aliasPath.length(), replacement);
            pos = result.find(aliasPath, pos + replacement.length());
        }
    }
    std::cout << "result = " << result << std::endl;
    return result;
}

string adjustRoute(const std::string &locationRoot, std::string &route) {
    // Verificar si locationRoot termina en "/" y route comienza con "/"
    if (!locationRoot.empty() && locationRoot[locationRoot.length() - 1] == '/' && !route.empty() && route[0] == '/') {
        // Eliminar la barra diagonal de inicio de route
        route = route.substr(1);
    }
    return route;
}

void  Request::serverToClient(const string &_header, size_t fd) {
  header = _header;
  parserData();
  cout << fd << header << endl;
  clientFd = fd;
  std::istringstream ss(header);
	std::map<std::string, std::string> alias;
  //alias["micuenta"] = "Extra";
	
	ss >> method >> route;
  cout << "locationRoot: " << locationRoot.getRoot() << endl;
  cout << "route: " << route << endl;
  cout << method << endl;
	route = replaceAlias(route, alias);
  route = adjustRoute(locationRoot.getRoot(), route);
	if (method == "GET")
		getMethod();
	/*else if (method == "POST")
		postMethod();
	else if (method == "DELETE")
		deleteMethod();*/
}

/* void  Request::serverToClient(const string &_header, size_t fd) {
  header = _header;
  parserData();
  string response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";
  if (::send(fd, response.data(), response.size(), 0) < 0)
     logger.Log("error al enviar [%d]", fd);
  std::string redirect_response = "HTTP/1.1 301 Moved Permanently\r\n";
  redirect_response += "Location:" + locationRoot.getReturn().second  + "\r\n"; // Cambia la URL según sea necesario
  redirect_response += "Connection: close\r\n\r\n";
  std::string redirect_response = "HTTP/1.1 301 Moved Permanently\r\n";
   redirect_response += "Location: http:0.0.0.0:3008/nueva_pagina\r\n";
   redirect_response += "Connection: close\r\n\r\n";
  if (::send(fd, redirect_response.data(), redirect_response.size(), 0) < 0)
    logger.Log("error al enviar [%d]", fd);
  
}*/
