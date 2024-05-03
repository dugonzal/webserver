/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:48:39 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/03 17:37:08 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Request.hpp"

template<class T>
static string toString(const T& value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

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

void  Request::setHostAndPort(const string &_host, size_t _port) {
  host = _host;
  port = _port;
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
    cgi.setCgi(locationRoot.getCgiPath(), tmp + locationRoot.getIndex());
    cgi.handlerCgi();
    logger.Log("hay que lanzar cgi para esta location");
  }
}

//FUNCIONES IKER

string checkContentType(const std::string& routeToFile) {
    // Mapeo de extensiones a tipos de contenido
    map<std::string, std::string> extensionsMap;
    extensionsMap[".html"] = "text/html";
    extensionsMap[".css"] = "text/css";
    extensionsMap[".js"] = "application/javascript";
    extensionsMap[".jpg"] = "image/jpeg";
    extensionsMap[".jpeg"] = "image/jpeg";
    extensionsMap[".png"] = "image/png";
    extensionsMap[".gif"] = "image/gif";
    extensionsMap[".txt"] = "text/plain";

    // Obtener la extensión del archivo
    string extension;
    size_t puntoPos = routeToFile.find_last_of('.');
    if (puntoPos != string::npos) {
        extension = routeToFile.substr(puntoPos);
        // Convertir la extensión a minúsculas para comparar
        transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
        map<std::string, std::string>::iterator it = extensionsMap.find(extension);
        if (it != extensionsMap.end()) {
            return it->second;  // Devuelve el tipo de contenido correspondiente si se encuentra la extensión
        }
    }
    
    // Si no se encuentra la extensión en el mapa o no hay extensión, se asigna 'text/plain'
    return "text/plain";
}

string checkAllowedMethods(const std::vector<std::string>& methods) {
    string result;
    for (size_t i = 0; i < methods.size(); ++i) {
        if (i != 0) {
            result += " ";  // Agrega un espacio antes de cada método excepto el primero
        }
        result += methods[i];
    }
    return result;
}

int  Request::checkMethod(const string &_method) {
  vector<string> tmp = locationRoot.getmethods();
  for (size_t i = 0; i < tmp.size(); i++) {
    cout << tmp[i] << endl;
    if (!tmp[i].compare(_method)) {
      return (1);
    }
  }
  return (0);
}

bool isAbsolutePath(const string& path) {
    // Verifica si la ruta comienza con "http://" o "https://"
    return (path.find("http://") == 0 || path.find("https://") == 0);
}

static string generate_autoindex(const std::string& directoryPath, string autoindex, string route, string host, int port) {
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
        autoindex += "<li><a href=\"" "http://" + host + ":" +toString(port) + "/" + route + "/" + std::string(entry->d_name) + "\">" + std::string(entry->d_name) + "</a></li>\n"; // http://" + host + ":" + std::toString(locationRoot.getPort()) + "/" + location[route] + "\r\n";
        
    }

    autoindex += "</ul><hr></body></html>\n";

    // Cierra el directorio
    closedir(dir);

    return autoindex;
}

void Request::getMethod( void )
{
	//map<std::string, std::string> location;
	//alias["/kapouet"] = "/mi_carpeta";
  string contentType = checkContentType(route);
	string allowed_methods = checkAllowedMethods(locationRoot.getmethods());
	cout << "GETMETHOD" << std::endl;
  cout << "ContentType " << contentType << endl;
  cout << "Allowed_methods " << allowed_methods << endl;
  //cout << locations["/a"].getReturn().second << endl;
	string httpResponse;
	if (!checkMethod("GET"))
	{
		string httpResponse = "HTTP/1.1 405 Method Not Allowed\r\n";
    httpResponse += "Allow: " + allowed_methods + "\r\n";
    httpResponse += "\r\n";
		cout << "Error allowed methods" << std::endl;
		send(clientFd, httpResponse.data(), httpResponse.size(), 0);
	}
	else
	{
		if (locations.find(route) != locations.end())
		{
			if (isAbsolutePath(locations[route].getReturn().second))
			{
    		// Redirección 301
				cout << "AQUI VA" << std::endl;
    		httpResponse = "HTTP/1.1 302 Found\r\n";
    		httpResponse += "Location: " + locations[route].getReturn().second + "\r\n";
				httpResponse += "\r\n";
				send(clientFd, httpResponse.data(), httpResponse.size(), 0);
			}
			else if (!locations[route].getReturn().second.empty() && route != locations[route].getReturn().second)
			{
				httpResponse = "HTTP/1.1 301 Moved Permanently\r\n";
        cout << "LO CONSEGUI" << endl;
        cout << "Location: " + locationRoot.getReturn().second << endl;//+ host + ":" + toString(locationRoot.getPort()) + "/" +location[route] << endl;
        if (locations[route].getReturn().second[0] == '/')
          httpResponse += "Location: http://" + host + ":" + toString(port) + locations[route].getReturn().second + "\r\n";
        else
    		  httpResponse += "Location: http://" + host + ":" + toString(port) + "/" + locations[route].getReturn().second + "\r\n";//+ locationRoot.getReturn().second + "\r\n"; //"Location: " + host + ":" + std::toString(locationRoot.getPort()) + "/" + location[route] + "\r\n";//+ location[route] + "\r\n";//+ host + ":" + std::toString(locationRoot.getPort()) + "/" + location[route] + "\r\n";
    		httpResponse += "\r\n";
    		send(clientFd, httpResponse.data(), httpResponse.size(), 0);
			}
			else
			{
        cout << "INTERNAL" << endl;
				httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
        httpResponse += "Content-Type: text/html\r\n";
        httpResponse += "Content-Length: 0\r\n";  // Longitud del contenido (en este caso, 0)
        httpResponse += "\r\n";
        // Asegúrate de agregar un carácter nulo al final de la cadena
        httpResponse.push_back('\0');
				send(clientFd, httpResponse.data(), httpResponse.size(), 0);
			}
	  }
		else
		{
      cout << "Hola estoy aqui " << locationRoot.getRoot() + route << endl;
			ifstream archivo((locationRoot.getRoot() + route).data());
			ostringstream oss;    
      string directoryPath = locationRoot.getRoot() + route;
      cout << "Hola estoy aqui " << directoryPath << endl;
      cout << "HOST: " << locationRoot.getHost() << endl;
      cout << "PORT: " << locationRoot.getPort() << endl;
			if (isDirectory(directoryPath)) {
        cout << "AUTOINDEX" << endl;
        // Generar autoindex
        string autoindex;
        if (route == "/")
          route = ""; 
        autoindex = generate_autoindex(directoryPath, autoindex, route, locationRoot.getHost(), locationRoot.getPort());
        // Respuesta 200 OK con el autoindex
        httpResponse = "HTTP/1.1 200 OK\r\n";
        httpResponse += "Content-Type: " + contentType + "\r\n";
        httpResponse += "Content-Length: " + toString(autoindex.size()) + "\r\n";
        httpResponse += "\r\n";
        httpResponse += autoindex;
        autoDirectory = route;
        send(clientFd, httpResponse.data(), httpResponse.size(), 0);
      } else if (archivo.is_open()){
				cout << "y" << std::endl;
				oss << archivo.rdbuf();
				string httpResponse;
        cout << static_cast<long>(oss.str().size()) << endl;
        cout << locationRoot.getClientBodySize() << endl;
				if (static_cast<long>(oss.str().size()) > (locationRoot.getClientBodySize()))//OJOOO
				{
          cout << "TOO LARGE" << endl;
				  httpResponse = "HTTP/1.1 413 Request Entity Too Large\r\n";
				  httpResponse += "\r\n";
				  send(clientFd, httpResponse.data(), httpResponse.size(), 0);
				}
				else
				{
				  // Respuesta 200 OK
          cout << "200 OK" << endl;
	    	  httpResponse = "HTTP/1.1 200 OK\r\n";
				  httpResponse += "Content-Type: " + contentType + "\r\n";
				  httpResponse += "Content-Length: " + toString(oss.str().size()) + "\r\n";
				  httpResponse += "\r\n";
				  httpResponse += oss.str();
				  send(clientFd, httpResponse.data(), httpResponse.size(), 0);
				}
	    }
			else
			{
				ifstream archivo("resources/GET/404.html");
        if (archivo.is_open()) {
          ostringstream oss;
          oss << archivo.rdbuf();
          cout << "NOT FOUND" << endl;
          string httpResponse = "HTTP/1.1 404 Not Found\r\n";
          httpResponse += "Content-Type: " + contentType + "\r\n";
          httpResponse += "Content-Length: " + toString(oss.str().size()) + "\r\n";
          httpResponse += "\r\n";
          httpResponse += oss.str();
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        } else {
          cout << "INTERNAL2" << endl;
				  httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
          httpResponse += "Content-Type: " + contentType + "\r\n";
          httpResponse += "Content-Length: 0\r\n";  // Longitud del contenido (en este caso, 0)
          httpResponse += "\r\n";
          // Asegúrate de agregar un carácter nulo al final de la cadena
          httpResponse.push_back('\0');
				  send(clientFd, httpResponse.data(), httpResponse.size(), 0);
			  }
			}
		}
	}
	
	cout << "TERMINO" << std::endl;
	close(clientFd);
}

void Request::postMethod( void )
{
	cout << "ENTRO AL METODO POST" << std::endl;
	string httpResponse;
	string allowed_methods = "GET POST"; // Métodos permitidos
    if (!checkMethod("POST")) {
        httpResponse = "HTTP/1.1 405 Method Not Allowed\r\n";
        httpResponse += "Allow: " + allowed_methods + "\r\n";
        httpResponse += "\r\n";
        cout << "Error: Método no permitido" << std::endl;
        send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        return;
    } else {
		string msgString(header);
	    size_t bodyStart = msgString.find("\r\n\r\n");
		string postBody = msgString.substr(bodyStart + 4);
	    if (postBody.empty()) {
	        cout << "HTTP/1.1 204 No Content\r\n" << std::endl;
	        httpResponse = "HTTP/1.1 204 No Content\r\n";
	        httpResponse += "\r\n";
	        send(clientFd, httpResponse.data(), httpResponse.size(), 0);
	        return;
	    }
	    cout << "Body: " << postBody << std::endl;
		ifstream verificarArchivo((locationRoot.getRoot() + route).c_str());
    	bool archivoExiste = verificarArchivo.good();
    	verificarArchivo.close();

	    ofstream archivo((locationRoot.getRoot() + route).c_str(), std::ios::app);
	    if (archivo.is_open()) {
        	if (archivoExiste) {
            	archivo << postBody << endl;
            	cout << "Contenido escrito exitosamente al final del archivo." << std::endl;
            	cout << "HTTP/1.1 200 OK\r\n" << std::endl;
              httpResponse = "HTTP/1.1 200 OK\r\n";
	            httpResponse += "\r\n";
	            send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        	} else {
            	archivo << postBody << endl;
            	cout << "Contenido escrito exitosamente en el archivo nuevo." << std::endl;
            	cout << "HTTP/1.1 201 Created\r\n" << std::endl;
              httpResponse = "HTTP/1.1 201 CREATED\r\n";
	            httpResponse += "\r\n";
	            send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        	}
	    } else {
	        cerr << "HTTP/1.1 500 Internal Server Error\n" << std::endl;
	        httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
	        httpResponse += "\r\n";
	        send(clientFd, httpResponse.data(), httpResponse.size(), 0);
	    }
	}
}

void Request::deleteMethod( void )
{
  string allowed_methods = "GET POST"; // Métodos permitidos
	cout << "DELETEMETHOD" << std::endl;
	string httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
  if (!checkMethod("DELETE")) {
        httpResponse = "HTTP/1.1 405 Method Not Allowed\r\n";
        httpResponse += "Allow: " + allowed_methods + "\r\n";
        httpResponse += "\r\n";
        cout << "Error: Método no permitido" << std::endl;
        send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        return;
  }
  else
  {
    // Intentar eliminar el archivo
    if (remove((locationRoot.getRoot() + route).c_str()) != 0)
		  httpResponse = "HTTP/1.1 404 Not Found\r\n";
	  else
		  httpResponse = "HTTP/1.1 200 OK\r\n";
  }
	send(clientFd, httpResponse.data(), httpResponse.size(), 0);
	cout << "TERMINO" << std::endl;
	close(clientFd);
}


string Request::replaceAlias(const std::string& path) {
    string result = path;
    for (map<std::string, Location>::const_iterator it = locations.begin(); it != locations.end(); ++it) {
        const string& aliasPath = it->first;
        const string& replacement = it->second.getAlias();
        
        size_t pos = path.find(aliasPath);
        
        // Si se encuentra el alias, reemplazarlo
        while (pos != string::npos) {
            result.replace(pos, aliasPath.length(), replacement);
            pos = result.find(aliasPath, pos + replacement.length());
        }
    }
    cout << "result = " << result << std::endl;
    return result;
}

/*string adjustRoute(const string &locationRoot, std::string &route) {
    // Verificar si locationRoot termina en "/" y route comienza con "/"
    if (!locationRoot.empty() && locationRoot[locationRoot.length() - 1] == '/' && !route.empty() && route[0] == '/') {
        // Eliminar la barra diagonal de inicio de route
        route = route.substr(1);
    }
    return route;
}*/
string adjustRoute(const std::string &locationRoot, std::string &route) {
  size_t pos = 0;
  while ((pos = route.find("//", pos)) != string::npos) {
      // Reemplaza la secuencia "//" con una sola "/"
      route.replace(pos, 2, "/");
  }
  // Verificar si locationRoot termina en "/" y route comienza con "/"
  if (!locationRoot.empty() && locationRoot[locationRoot.size() - 1] == '/' \
    && !route.empty() && route[0] == '/') {
      // Eliminar la barra diagonal de inicio de route
      route.erase(0, 1);
  }
  // Eliminar barras diagonales duplicadas
  return route;
}

void  Request::serverToClient(const string &_header, size_t fd) {
  header = _header;
  parserData();
  cout << fd << header << endl;
  clientFd = fd;
  istringstream ss(header);
	map<std::string, std::string> alias;
  //alias["micuenta"] = "Extra";
  //alias["micuenta2"] = "Extra2";
	
	ss >> method >> route;
  cout << "locationRoot: " << locationRoot.getRoot() << endl;
  cout << "route: " << route << endl;
  cout << method << endl;
	route = replaceAlias(route);
  route = adjustRoute(locationRoot.getRoot(), route);
  cout << "ROUTE FINAL: " << route << endl;
	if (method == "GET")
		getMethod();
	else if (method == "POST")
		postMethod();
	else if (method == "DELETE")
		deleteMethod();
}



/* void  Request::serverToClient(const string &_header, size_t fd) {
  header = _header;
  parserData();
  string response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";
  if (::send(fd, response.data(), response.size(), 0) < 0)
     logger.Log("error al enviar [%d]", fd);
  string redirect_response = "HTTP/1.1 301 Moved Permanently\r\n";
  redirect_response += "Location:" + locationRoot.getReturn().second  + "\r\n"; // Cambia la URL según sea necesario
  redirect_response += "Connection: close\r\n\r\n";
  string redirect_response = "HTTP/1.1 301 Moved Permanently\r\n";
   redirect_response += "Location: http:0.0.0.0:3008/nueva_pagina\r\n";
   redirect_response += "Connection: close\r\n\r\n";
  if (::send(fd, redirect_response.data(), redirect_response.size(), 0) < 0)
    logger.Log("error al enviar [%d]", fd);
  
}*/


