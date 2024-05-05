/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:48:39 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/05 15:19:48 by jaizpuru         ###   ########.fr       */
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
}

//FUNCIONES IKER

std::string checkContentType(const std::string& routeToFile) {
    // Mapeo de extensiones a tipos de contenido
    std::map<std::string, std::string> extensionsMap;
    extensionsMap[".html"] = "text/html";
    extensionsMap[".css"] = "text/css";
    extensionsMap[".js"] = "application/javascript";
    extensionsMap[".jpg"] = "image/jpeg";
    extensionsMap[".jpeg"] = "image/jpeg";
    extensionsMap[".png"] = "image/png";
    extensionsMap[".gif"] = "image/gif";
    extensionsMap[".txt"] = "text/plain";

    // Obtener la extensión del archivo
    std::string extension;
    size_t puntoPos = routeToFile.find_last_of('.');
    if (puntoPos != std::string::npos) {
        extension = routeToFile.substr(puntoPos);
        // Convertir la extensión a minúsculas para comparar
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
        std::map<std::string, std::string>::iterator it = extensionsMap.find(extension);
        if (it != extensionsMap.end()) {
            return it->second;  // Devuelve el tipo de contenido correspondiente si se encuentra la extensión
        }
    }

    // Si no se encuentra la extensión en el mapa o no hay extensión, se asigna 'text/plain'
    return "text/html";
}

std::string checkAllowedMethods(const std::vector<std::string>& methods) {
    std::string result;
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

bool isAbsolutePath(const std::string& path) {
    // Verifica si la ruta comienza con "http://" o "https://"
    return (path.find("http://") == 0 || path.find("https://") == 0);
}

std::string generate_autoindex(const std::string& directoryPath, string autoindex, string route, string host, int port) {
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
      if (!route.empty()) {
        if (*route.begin() == '/')
          autoindex += "<li><a href=\"" "http://" + host + ":" +std::to_string(port) + route + "/" + std::string(entry->d_name) + "\">" + std::string(entry->d_name) + "</a></li>\n"; // http://" + host + ":" + std::to_string(locationRoot.getPort()) + "/" + location[route] + "\r\n";
        else
          autoindex += "<li><a href=\"" "http://" + host + ":" +std::to_string(port) + "/" + route + "/" + std::string(entry->d_name) + "\">" + std::string(entry->d_name) + "</a></li>\n"; // http://" + host + ":" + std::to_string(locationRoot.getPort()) + "/" + location[route] + "\r\n";
      } else
        autoindex += "<li><a href=\"" "http://" + host + ":" +std::to_string(port) + "/" + std::string(entry->d_name) + "\">" + std::string(entry->d_name) + "</a></li>\n"; // http://" + host + ":" + std::to_string(locationRoot.getPort()) + "/" + location[route] + "\r\n";

    }

    autoindex += "</ul><hr></body></html>\n";

    // Cierra el directorio
    closedir(dir);

    return autoindex;
}

std::string adjustRoute(const std::string &locationRoot, std::string &route) {
  size_t pos = 0;
  while ((pos = route.find("//", pos)) != std::string::npos) {
      // Reemplaza la secuencia "//" con una sola "/"
      route.replace(pos, 2, "/");
  }
  // Verificar si locationRoot termina en "/" y route comienza con "/"
  if (!locationRoot.empty() && locationRoot.back() == '/' && !route.empty() && route.front() == '/') {
      // Eliminar la barra diagonal de inicio de route
      route.erase(0, 1);
  }
  // Eliminar barras diagonales duplicadas


  return route;
}

std::string personalizeErrorPage(std::map<size_t, std::string> errorPages, size_t errorCode, const std::string rootPath, string httpResponse)
{
  string filePath = adjustRoute(rootPath, errorPages[errorCode]).c_str();
  std::ifstream archivo(rootPath + filePath);
  std::cout << rootPath + filePath << endl;
  if (archivo.is_open()) {
    cout << "error perso" << endl;
    std::ostringstream oss;
    oss << archivo.rdbuf();

    httpResponse += "Content-Type: " + checkContentType(errorPages[errorCode].c_str()) + "\r\n";
    httpResponse += "Content-Length: " + std::to_string(oss.str().size()) + "\r\n";
    httpResponse += "\r\n";
    httpResponse += oss.str();
  }
  else
  {
    cout << "error perso fallido" << endl;
    httpResponse += "Content-Type: text/html\r\n";
    httpResponse += "Content-Length: 0\r\n";
    httpResponse += "\r\n";
  }
  return (httpResponse);
}

void printErrorPages(const std::map<size_t, std::string>& errorPages) {
  cout << "DENTROOOOOOOOO" << endl;
    for (std::map<size_t, std::string>::const_iterator it = errorPages.begin(); it != errorPages.end(); ++it) {
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    }
}

void Request::getMethod( void )
{
  std::string contentType = checkContentType(route);
	std::string allowed_methods = checkAllowedMethods(locationRoot.getmethods());
	std::cout << "GETMETHOD" << std::endl;
  cout << "ContentType " << contentType << endl;
  cout << "Allowed_methods " << allowed_methods << endl;
	std::string httpResponse;
  cout << "RUTA ACTUAL: " << route << endl;
  size_t bodyStart = header.find("\r\n\r\n");
	std::string postBody = header.substr(bodyStart + 4);
  if (!postBody.empty())
  {
    cout << "BODY= " << postBody << endl;
    cout << "INTERNAL2.2" << endl;
		httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
    httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
    if (locationRoot.getErrorPages().find(500) != locationRoot.getErrorPages().end()) {
      httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 500, locationRoot.getRoot(), httpResponse);
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
    }
    else
    {
      // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
      httpResponse += "Content-Type: text/html\r\n";
      httpResponse += "Content-Length: 0\r\n";
      httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
      httpResponse += "\r\n";
      httpResponse.push_back('\0');
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
    }
  }
	else if (!checkMethod("GET"))
	{
    std::string httpResponse = "HTTP/1.1 405 Method Not Allowed\r\n";
    httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
    httpResponse += "Allow: " + allowed_methods + "\r\n";
		if (locationRoot.getErrorPages().find(405) != locationRoot.getErrorPages().end()) {
      httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 405, locationRoot.getRoot(), httpResponse);
      std::cout << "Error allowed methods" << std::endl;
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
    } else {
      // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
      httpResponse += "Content-Type: text/html\r\n";
      httpResponse += "Content-Length: 0\r\n";
      httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
      httpResponse += "\r\n";
      std::cout << "Error allowed methods" << std::endl;
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
    }
	}
	else
	{
    std::string directoryPath = locationRoot.getRoot() + route;
    std::cout << "DIRECTORY PATH= " << directoryPath << endl;
    std::cout << "ESTO= " << !isDirectory(directoryPath) << endl;
    cout << locationRoot.getReturn().second << endl;
		if (!locationRoot.getReturn().second.empty())
		{
			if (isAbsolutePath(locationRoot.getReturn().second))
			{
        httpResponse = "HTTP/1.1 302 Found\r\n";
        httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
        httpResponse += "Location: " + locationRoot.getReturn().second + "\r\n";
        if (locationRoot.getErrorPages().find(302) != locationRoot.getErrorPages().end()) {
          httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 302, locationRoot.getRoot(), httpResponse);
          std::cout << "302 Found" << std::endl;
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        } else {
          // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
          httpResponse += "Content-Type: text/html\r\n";
          httpResponse += "Content-Length: 0\r\n";
          httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
          httpResponse += "\r\n";
          std::cout << "302 Found" << std::endl;
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        }
			}
			else if (!locationRoot.getReturn().second.empty() && route != locationRoot.getReturn().second)
			{

        httpResponse = "HTTP/1.1 301 Moved Permanently\r\n";
        httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
        if (locationRoot.getReturn().second[0] == '/')
          httpResponse += "Location: http://" + host + ":" + std::to_string(port) + locationRoot.getReturn().second + "\r\n";
        else
    		  httpResponse += "Location: http://" + host + ":" + std::to_string(port) + "/" + locationRoot.getReturn().second + "\r\n";
        cout << "301 Moved Permanently" << endl;
        if (locationRoot.getErrorPages().find(301) != locationRoot.getErrorPages().end()) {
          httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 301, locationRoot.getRoot(), httpResponse);
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        } else {
          // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
          httpResponse += "\r\n";
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        }
			}
			else
			{
        httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
        httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
        std::cout << "500 Internal Server Error" << std::endl;
        if (locationRoot.getErrorPages().find(500) != locationRoot.getErrorPages().end()) {
          httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 500, locationRoot.getRoot(), httpResponse);
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        } else {
          // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
          httpResponse += "Content-Type: text/html\r\n";
          httpResponse += "Content-Length: 0\r\n";
          httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
          httpResponse += "\r\n";
          httpResponse.push_back('\0');
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        }
			}
	  }
		else
		{
      std::cout << "Hola estoy aqui " << locationRoot.getRoot() + route << std::endl;
			std::ifstream archivo(locationRoot.getRoot() + route);
			std::ostringstream oss;
      std::string directoryPath = locationRoot.getRoot() + route;
      std::cout << "Hola estoy aqui " << directoryPath << std::endl;
      std::cout << "HOST: " << host << endl;
      std::cout << "PORT: " << port << endl;
      std::cout << "AUTOINDEX: " << locationRoot.getAutoIndex() << std::endl;
      if (isCgi) {
        string tmp;
        if (locationRoot.getRoot()[locationRoot.getRoot().size() - 1] != '/') {
          tmp = locationRoot.getRoot();
          tmp.append("/");
        }
        cgi.setCgi(locationRoot.getCgiPath(), tmp + locationRoot.getIndex());
        cgi.handlerCgi();
        logger.Log("hay que lanzar cgi para esta location");
        httpResponse = "HTTP/1.1 200 OK\r\n";
        httpResponse += "Content-Type: " + contentType + "\r\n";
        std::stringstream ss;
        ss << convertHTML(cgi.getCgi()).size();
        httpResponse += "Content-Length: " + ss.str() + "\r\n";
        httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
        httpResponse += "\r\n";
        httpResponse += convertHTML(cgi.getCgi());
        send(clientFd, httpResponse.data(), httpResponse.size(), 0);
      }
			else if (isDirectory(directoryPath)) {
        if (locationRoot.getAutoIndex() == 1 || locationRoot.getAutoIndex() == -1)
        {
          cout << "AUTOINDEX" << endl;
          // Generar autoindex
          std::string autoindex;
          if (route == "/")
            route = "";
          autoindex = generate_autoindex(directoryPath, autoindex, route, host, port);
          httpResponse = "HTTP/1.1 200 OK\r\n";
          httpResponse += "Content-Type: " + contentType + "\r\n";
          httpResponse += "Content-Length: " + std::to_string(autoindex.size()) + "\r\n";
          httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
          httpResponse += "\r\n";
          httpResponse += autoindex;
          autoDirectory = route;
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        }
        else
        {
          httpResponse = "HTTP/1.1 404 Not Found\r\n";
          if (locationRoot.getErrorPages().find(404) != locationRoot.getErrorPages().end()) {
            std::cout << "404 Not Found" << std::endl;
            std::map<size_t, std::string>::iterator it = locationRoot.getErrorPages().find(404);
            string filePath = adjustRoute(locationRoot.getRoot(), it->second);
            std::cout << "FILE404PATH = " << locationRoot.getRoot() + filePath << endl;
            std::ifstream archivo(locationRoot.getRoot() + filePath);
            if (archivo.is_open()) {
              std::ostringstream oss;
              oss << archivo.rdbuf();
              httpResponse += "Content-Type: " + checkContentType(it->second) + "\r\n";
              httpResponse += "Content-Length: " + std::to_string(oss.str().size()) + "\r\n";
              httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
              httpResponse += "\r\n";
              httpResponse += oss.str();
              send(clientFd, httpResponse.data(), httpResponse.size(), 0);
            }
            else
            {
              cout << "INTERNAL1.1" << endl;
				      httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
              httpResponse += "Content-Type: " + contentType + "\r\n";
              httpResponse += "Content-Length: 0\r\n";  // Longitud del contenido (en este caso, 0)
              httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
              httpResponse += "\r\n";
              // Asegúrate de agregar un carácter nulo al final de la cadena
              httpResponse.push_back('\0');
				      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
			      }
          } else {
            cout << "INTERNAL1.2" << endl;
				    httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
            httpResponse += "Content-Type: " + contentType + "\r\n";
            httpResponse += "Content-Length: 0\r\n";  // Longitud del contenido (en este caso, 0)
            httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
            httpResponse += "\r\n";
            // Asegúrate de agregar un carácter nulo al final de la cadena
            httpResponse.push_back('\0');
				    send(clientFd, httpResponse.data(), httpResponse.size(), 0);
          }
        }
      } else if (archivo.is_open()){
				std::cout << "y" << std::endl;
				oss << archivo.rdbuf();
				std::string httpResponse;
        if (locationRoot.getClientBodySize() == -1)
          locationRoot.setClientBodySize("1m");
        cout << static_cast<long>(oss.str().size()) << endl;
        cout << locationRoot.getClientBodySize() << endl;
				if (static_cast<long>(oss.str().size()) > (locationRoot.getClientBodySize()))//OJOOO
				{
          cout << "TOO LARGE" << endl;
          httpResponse = "HTTP/1.1 413 Request Entity Too Large\r\n";
          httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
          if (locationRoot.getErrorPages().find(413) != locationRoot.getErrorPages().end()) {
            httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 413, locationRoot.getRoot(), httpResponse);
            send(clientFd, httpResponse.data(), httpResponse.size(), 0);
          } else {
            // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
            httpResponse += "Content-Type: text/html\r\n";
            httpResponse += "Content-Length: 0\r\n";
            httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
            httpResponse += "\r\n";
            send(clientFd, httpResponse.data(), httpResponse.size(), 0);
          }
				}
				else
				{
				  // Respuesta 200 OK
          cout << "200 OK" << endl;
	    	  httpResponse = "HTTP/1.1 200 OK\r\n";
				  httpResponse += "Content-Type: " + contentType + "\r\n";
				  httpResponse += "Content-Length: " + std::to_string(oss.str().size()) + "\r\n";
          httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
				  httpResponse += "\r\n";
				  httpResponse += oss.str();
				  send(clientFd, httpResponse.data(), httpResponse.size(), 0);
				}
	    }
			else
			{
        httpResponse = "HTTP/1.1 404 Not Found\r\n";
        std::cout << "404 Not Found" << std::endl;
        if (locationRoot.getErrorPages().find(404) != locationRoot.getErrorPages().end()) {
          std::map<size_t, std::string>::iterator it = locationRoot.getErrorPages().find(404);
          string filePath = adjustRoute(locationRoot.getRoot(), it->second);
          std::ifstream archivo(locationRoot.getRoot() + filePath);
          cout << "ESTO: " << locationRoot.getRoot() + filePath << endl;
          if (archivo.is_open()) {
            std::ostringstream oss;
            oss << archivo.rdbuf();
            httpResponse += "Content-Type: " + checkContentType(it->second) + "\r\n";
            httpResponse += "Content-Length: " + std::to_string(oss.str().size()) + "\r\n";
            httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
            httpResponse += "\r\n";
            httpResponse += oss.str();
            cout << "TEXTO: " << oss.str() << endl;
            send(clientFd, httpResponse.data(), httpResponse.size(), 0);
          }
          else
          {
            std::ifstream archivo("resources/GET/404.html");
            if (archivo.is_open()) {
              std::ostringstream oss;
              oss << archivo.rdbuf();
              httpResponse += "Content-Type: text/html\r\n";
              httpResponse += "Content-Length: " + std::to_string(oss.str().size()) + "\r\n";
              httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
              httpResponse += "\r\n";
              httpResponse += oss.str();
              cout << "TEXTO: " << oss.str() << endl;
              send(clientFd, httpResponse.data(), httpResponse.size(), 0);
            }
            else
            {
              httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
              std::cout << "500 Internal Server Error" << std::endl;
              httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
              if (locationRoot.getErrorPages().find(500) != locationRoot.getErrorPages().end()) {
                httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 500, locationRoot.getRoot(), httpResponse);
                send(clientFd, httpResponse.data(), httpResponse.size(), 0);
              }
              else
              {
                // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
                httpResponse += "Content-Type: text/html\r\n";
                httpResponse += "Content-Length: 0\r\n";
                httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
                httpResponse += "\r\n";
                httpResponse.push_back('\0');
                send(clientFd, httpResponse.data(), httpResponse.size(), 0);
              }
            }
          }
        } else {
          cout << "INTERNAL2.2" << endl;
				  httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
          httpResponse += "Content-Type: " + contentType + "\r\n";
          if (locationRoot.getErrorPages().find(500) != locationRoot.getErrorPages().end()) {
            httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 500, locationRoot.getRoot(), httpResponse);
            send(clientFd, httpResponse.data(), httpResponse.size(), 0);
          }
          else
          {
            // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
            httpResponse += "Content-Type: text/html\r\n";
            httpResponse += "Content-Length: 0\r\n";
            httpResponse += "\r\n";
            httpResponse.push_back('\0');
            send(clientFd, httpResponse.data(), httpResponse.size(), 0);
          }
        }
      }
    }
  }
	std::cout << "TERMINO" << std::endl;
}

void Request::postMethod( void )
{
	std::cout << "ENTRO AL METODO POST" << std::endl;
	std::string httpResponse;
	std::string allowed_methods = checkAllowedMethods(locationRoot.getmethods());
  if (!checkMethod("POST")) {
    std::string httpResponse = "HTTP/1.1 405 Method Not Allowed\r\n";
    httpResponse += "Allow: " + allowed_methods + "\r\n";
    httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
	  if (locationRoot.getErrorPages().find(405) != locationRoot.getErrorPages().end()) {
      httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 405, locationRoot.getRoot(), httpResponse);
      std::cout << "Error allowed methods" << std::endl;
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
    } else {
      // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
      httpResponse += "Content-Type: text/html\r\n";
      httpResponse += "Content-Length: 0\r\n";
      httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
      httpResponse += "\r\n";
      std::cout << "Error allowed methods" << std::endl;
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
    }
  }
  else
  {
	  std::string msgString(header);
	  size_t bodyStart = msgString.find("\r\n\r\n");
	  std::string postBody = msgString.substr(bodyStart + 4);
	  std::cout << "Body: " << postBody << std::endl;
	  std::ifstream verificarArchivo((locationRoot.getRoot() + route).c_str());
  	bool archivoExiste = verificarArchivo.good();
  	verificarArchivo.close();
	  std::ofstream archivo((locationRoot.getRoot() + route).c_str(), std::ios::app);
	  if (archivo.is_open()) {
      if (archivoExiste) {
        archivo << postBody << std::endl;
        std::cout << "Contenido escrito exitosamente al final del archivo." << std::endl;
        std::cout << "HTTP/1.1 200 OK\r\n" << std::endl;
        httpResponse = "HTTP/1.1 200 OK\r\n";
        httpResponse += "Content-Type: " + checkContentType(route) + "\r\n";
        httpResponse += "Content-Length: " + std::to_string(postBody.size()) + "\r\n";
        httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
	      httpResponse += "\r\n";
        httpResponse += postBody;
	      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
      } else {
        archivo << postBody << std::endl;
        std::cout << "Contenido escrito exitosamente en el archivo nuevo." << std::endl;
        std::cout << "HTTP/1.1 201 Created\r\n" << std::endl;
        httpResponse = "HTTP/1.1 201 CREATED\r\n";
	      httpResponse += "Content-Type: " + checkContentType(route) + "\r\n";
        httpResponse += "Content-Length: " + std::to_string(postBody.size()) + "\r\n";
        httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
	      httpResponse += "\r\n";
        httpResponse += postBody;
	      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
      }
    }
    else {
      std::cout << "500 Internal Server Error" << std::endl;
      httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
      httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
      if (locationRoot.getErrorPages().find(500) != locationRoot.getErrorPages().end()) {
        httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 500, locationRoot.getRoot(), httpResponse);
        send(clientFd, httpResponse.data(), httpResponse.size(), 0);
      }
      else
      {
        // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
        httpResponse += "Content-Type: text/html\r\n";
        httpResponse += "Content-Length: " + std::to_string(postBody.size()) + "\r\n";
        httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
	      httpResponse += "\r\n";
        httpResponse += postBody;
        send(clientFd, httpResponse.data(), httpResponse.size(), 0);
      }
	  }
	}
}

void Request::deleteMethod( void )
{
  std::string allowed_methods = "GET POST"; // Métodos permitidos
	std::cout << "DELETEMETHOD" << std::endl;
	std::string httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
  if (!checkMethod("DELETE")) {
    std::string httpResponse = "HTTP/1.1 405 Method Not Allowed\r\n";
    httpResponse += "Allow: " + allowed_methods + "\r\n";
	  if (locationRoot.getErrorPages().find(405) != locationRoot.getErrorPages().end()) {
      httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 405, locationRoot.getRoot(), httpResponse);
      std::cout << "Error allowed methods" << std::endl;
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
    } else {
      // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
      httpResponse += "Content-Type: text/html\r\n";
      httpResponse += "Content-Length: 0\r\n";
      httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
      httpResponse += "\r\n";
      std::cout << "Error allowed methods" << std::endl;
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
    }
  }
  else
  {
    // Intentar eliminar el archivo
    if (std::remove((locationRoot.getRoot() + route).c_str()) != 0)
    {
		  httpResponse = "HTTP/1.1 404 Not Found\r\n";
      std::cout << "404 Not Found" << std::endl;
      if (locationRoot.getErrorPages().find(404) != locationRoot.getErrorPages().end()) {
        std::map<size_t, std::string>::iterator it = locationRoot.getErrorPages().find(404);
        string filePath = adjustRoute(locationRoot.getRoot(), it->second);
        std::ifstream archivo(locationRoot.getRoot() + filePath);
        cout << "ESTO: " << locationRoot.getRoot() + filePath << endl;
        if (archivo.is_open()) {
          std::ostringstream oss;
          oss << archivo.rdbuf();
          httpResponse += "Content-Type: " + checkContentType(it->second) + "\r\n";
          httpResponse += "Content-Length: " + std::to_string(oss.str().size()) + "\r\n";
          httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
          httpResponse += "\r\n";
          httpResponse += oss.str();
          cout << "TEXTO: " << oss.str() << endl;
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        }
        else
        {
          std::ifstream archivo("resources/GET/404.html");
          if (archivo.is_open()) {
            std::ostringstream oss;
            oss << archivo.rdbuf();
            httpResponse += "Content-Type: text/html\r\n";
            httpResponse += "Content-Length: " + std::to_string(oss.str().size()) + "\r\n";
            httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
            httpResponse += "\r\n";
            httpResponse += oss.str();
            cout << "TEXTO: " << oss.str() << endl;
            send(clientFd, httpResponse.data(), httpResponse.size(), 0);
          }
          else
          {
            httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
            httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
            std::cout << "500 Internal Server Error" << std::endl;
            if (locationRoot.getErrorPages().find(500) != locationRoot.getErrorPages().end()) {
              httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 500, locationRoot.getRoot(), httpResponse);
              send(clientFd, httpResponse.data(), httpResponse.size(), 0);
            }
            else
            {
              // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
              httpResponse += "Content-Type: text/html\r\n";
              httpResponse += "Content-Length: 0\r\n";
              httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
              httpResponse += "\r\n";
              httpResponse.push_back('\0');
              send(clientFd, httpResponse.data(), httpResponse.size(), 0);
            }
          }
        }
      }
    }
	  else
		  httpResponse = "HTTP/1.1 200 OK\r\n";
      httpResponse += "Content-Length: 0\r\n";
      httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
      httpResponse += "\r\n";
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
  }
	std::cout << "TERMINO" << std::endl;
	//close(clientFd);
}


std::string Request::replaceAlias(const std::string& path) {
  std::string result = path;
  for (std::map<std::string, Location>::const_iterator it = locations.begin(); it != locations.end(); ++it) {
    const std::string& aliasPath = it->first;
    const std::string& replacement = it->second.getAlias();

    size_t pos = result.find(aliasPath);

    // Si se encuentra el alias, reemplazarlo
    while (pos != std::string::npos) {
      if (replacement != "\0")
      {
        result.replace(pos, aliasPath.length(), replacement);
        pos = result.find(aliasPath, pos + replacement.length());
      }
      else
        break; // Si el reemplazo es nulo, sal del bucle para evitar bucles infinitos
    }
  }
  std::cout << "result = " << result << std::endl;
  return result;
}

/*string adjustRoute(const std::string &locationRoot, std::string &route) {
  // Verificar si locationRoot termina en "/" y route comienza con "/"
  if (!locationRoot.empty() && locationRoot[locationRoot.length() - 1] == '/' && !route.empty() && route[0] == '/') {
      // Eliminar la barra diagonal de inicio de route
      route = route.substr(1);
  }
  return route;
}*/

void  Request::serverToClient(const string &_header, size_t fd) {
  header = _header;
  parserData();
  cout << fd << header << endl;
  clientFd = fd;
  std::istringstream ss(header);
	std::map<std::string, std::string> alias;

	ss >> method >> route;
  cout << "locationRoot: " << locationRoot.getRoot() << endl;
  cout << "route: " << route << endl;
  cout << method << endl;
	route = replaceAlias(route);
  route = adjustRoute(locationRoot.getRoot(), route);
  cout << "ROUTE FINAL: " << route << endl;
  cout << version << endl;
	if (version != "HTTP/1.1") {
    cout << version << endl;
    std::string httpResponse = "HTTP/1.1 505 HTTP Version Not Supported\r\n";
    httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
    std::cout << "505 Internal Server Error" << std::endl;
    if (locationRoot.getErrorPages().find(505) != locationRoot.getErrorPages().end()) {
      httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 505, locationRoot.getRoot(), httpResponse);
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
    }
    else
    {
      // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
      httpResponse += "Content-Type: text/html\r\n";
      httpResponse += "Content-Length: 0\r\n";
      httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
      httpResponse += "\r\n";
      httpResponse.push_back('\0');
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
    }
  } else if (method == "GET")
		getMethod();
	else if (method == "POST")
		postMethod();
	else if (method == "DELETE")
		deleteMethod();
  else
  {
    std::string httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
    httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
    std::cout << "500 Internal Server Error" << std::endl;
    if (locationRoot.getErrorPages().find(500) != locationRoot.getErrorPages().end()) {
      httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 500, locationRoot.getRoot(), httpResponse);
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
    }
    else
    {
      // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
      httpResponse += "Content-Type: text/html\r\n";
      httpResponse += "Content-Length: 0\r\n";
      httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
      httpResponse += "\r\n";
      httpResponse.push_back('\0');
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
    }
  }
}
