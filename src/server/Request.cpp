/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:48:39 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/14 10:48:01 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Request.hpp"

template <typename T>
std::string toString(T val) {
  std::stringstream oss;
  oss << val;
  return oss.str();
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

static std::string adjustRoute(const std::string &locationRoot, std::string &route) {
  size_t pos = 0;
  while ((pos = route.find("//", pos)) != std::string::npos) {
      route.replace(pos, 2, "/");
  }
  if (!locationRoot.empty() && *locationRoot.end() == '/' && !route.empty() && *route.begin() == '/') {
      route.erase(0, 1);
  }
  return route;
}

static string adjustRoute(string route) {
  size_t pos = 0;
  while ((pos = route.find("//", pos)) != std::string::npos) {
      // Reemplaza la secuencia "//" con una sola "/"
      route.replace(pos, 2, "/");
  }
  return route;
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
  route = adjustRoute(firstWord(tmp));
  version = lastWord(tmp);
  return(false);
}

void  Request::parserData(void) {
  int pos = header.find_first_of('\n');

  if (setRouteAndVersion(trim(lastWord(header.substr(0, pos))))) {
    logger.Log("error version");
  }
  setLocation();
  if (setMethod(trim(firstWord(header.substr(0, pos))))) {
    logger.Log("error method no allowed");
  }
}

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
          autoindex += "<li><a href=\"" "http://" + host + ":" +toString(port) + route + "/" + std::string(entry->d_name) + "\">" + std::string(entry->d_name) + "</a></li>\n"; // http://" + host + ":" + toString(locationRoot.getPort()) + "/" + location[route] + "\r\n";
        else
          autoindex += "<li><a href=\"" "http://" + host + ":" +toString(port) + "/" + route + "/" + std::string(entry->d_name) + "\">" + std::string(entry->d_name) + "</a></li>\n"; // http://" + host + ":" + toString(locationRoot.getPort()) + "/" + location[route] + "\r\n";
      } else
        autoindex += "<li><a href=\"" "http://" + host + ":" +toString(port) + "/" + std::string(entry->d_name) + "\">" + std::string(entry->d_name) + "</a></li>\n"; // http://" + host + ":" + toString(locationRoot.getPort()) + "/" + location[route] + "\r\n";
    }
    autoindex += "</ul><hr></body></html>\n";
    // Cierra el directorio
    closedir(dir);
    return autoindex;
}



std::string personalizeErrorPage(std::map<size_t, std::string> errorPages, size_t errorCode, const std::string rootPath, string httpResponse)
{
  string filePath = adjustRoute(rootPath, errorPages[errorCode]).c_str();
  std::stringstream totalPath;
  totalPath << rootPath << filePath;
  std::ifstream archivo(totalPath.str().c_str());
  if (archivo.is_open()) {
    std::ostringstream oss;
    oss << archivo.rdbuf();

    httpResponse += "Content-Type: " + checkContentType(errorPages[errorCode].c_str()) + "\r\n";
    httpResponse += "Content-Length: " + toString(oss.str().size()) + "\r\n";
    httpResponse += "\r\n";
    httpResponse += oss.str();
  }
  else
  {
    httpResponse += "Content-Type: text/html\r\n";
    httpResponse += "Content-Length: 0\r\n";
    httpResponse += "\r\n";
  }
  return (httpResponse);
}

void Request::getMethod( void )
{
  std::string contentType = checkContentType(route);
	std::string allowed_methods = checkAllowedMethods(locationRoot.getmethods());
	std::string httpResponse;
  size_t bodyStart = header.find("\r\n\r\n");
	std::string postBody = header.substr(bodyStart + 4);
  if (!postBody.empty())
  {
		httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
    if (cookie)
      httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
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
    if (cookie)
      httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
    httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
    httpResponse += "Allow: " + allowed_methods + "\r\n";
		if (locationRoot.getErrorPages().find(405) != locationRoot.getErrorPages().end()) {
      httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 405, locationRoot.getRoot(), httpResponse);
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
    std::string directoryPath = locationRoot.getRoot() + route;
		if (!locationRoot.getReturn().second.empty())
		{
			if (isAbsolutePath(locationRoot.getReturn().second))
			{
        httpResponse = "HTTP/1.1 302 Found\r\n";
        if (cookie)
          httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
        httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
        httpResponse += "Location: " + locationRoot.getReturn().second + "\r\n";
        if (locationRoot.getErrorPages().find(302) != locationRoot.getErrorPages().end()) {
          httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 302, locationRoot.getRoot(), httpResponse);
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
			else if (!locationRoot.getReturn().second.empty() && route != locationRoot.getReturn().second)
			{

        httpResponse = "HTTP/1.1 301 Moved Permanently\r\n";
        if (cookie)
          httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
        httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
        if (locationRoot.getReturn().second[0] == '/')
          httpResponse += "Location: http://" + host + ":" + toString(port) + locationRoot.getReturn().second + "\r\n";
        else
    		  httpResponse += "Location: http://" + host + ":" + toString(port) + "/" + locationRoot.getReturn().second + "\r\n";
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
        if (cookie)
          httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
        httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
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
      std::stringstream totalPath;
      totalPath << locationRoot.getRoot() << route;
      //totalPath << locationRoot.getRoot() << route << locationRoot.getIndex();
      //std::cout << "Total Path : " << totalPath.str() << std::endl;
      std::ifstream archivo(totalPath.str().c_str());
			std::ostringstream oss;
      std::string directoryPath = locationRoot.getRoot() + route;
      //std::cout << "Directory Path : " << directoryPath << std::endl;
      if (isCgi) {
        string tmp;
        if (locationRoot.getRoot()[locationRoot.getRoot().size() - 1] != '/') {
          tmp = locationRoot.getRoot();
          tmp.append("/");
        }
        cgi.setCgi(locationRoot.getCgiPath(), tmp + locationRoot.getIndex());
        cgi.handlerCgi();
        httpResponse = "HTTP/1.1 200 OK\r\n";
        if (cookie)
          httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
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
          std::string autoindex;
          if (route == "/")
            route = "";
          autoindex = generate_autoindex(directoryPath, autoindex, route, host, port);
          httpResponse = "HTTP/1.1 200 OK\r\n";
          if (cookie)
            httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
          httpResponse += "Content-Type: " + contentType + "\r\n";
          httpResponse += "Content-Length: " + toString(autoindex.size()) + "\r\n";
          httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
          httpResponse += "\r\n";
          httpResponse += autoindex;
          autoDirectory = route;
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        }
        else
        {
          httpResponse = "HTTP/1.1 404 Not Found\r\n";
          if (cookie)
            httpResponse += "Set-Cookie: session_id=" +setCookie + "\r\n";
          if (locationRoot.getErrorPages().find(404) != locationRoot.getErrorPages().end()) {
            std::map<size_t, std::string>::iterator it = locationRoot.getErrorPages().find(404);
            string filePath = adjustRoute(locationRoot.getRoot(), it->second);
            std::stringstream totalPath;
            totalPath << locationRoot.getRoot() << filePath;
            std::ifstream archivo(totalPath.str().c_str());
            if (archivo.is_open()) {
              std::ostringstream oss;
              oss << archivo.rdbuf();
              httpResponse += "Content-Type: " + checkContentType(it->second) + "\r\n";
              httpResponse += "Content-Length: " + toString(oss.str().size()) + "\r\n";
              httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
              httpResponse += "\r\n";
              httpResponse += oss.str();
              send(clientFd, httpResponse.data(), httpResponse.size(), 0);
            }
            else
            {
				      httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
              if (cookie)
                httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
              httpResponse += "Content-Type: " + contentType + "\r\n";
              httpResponse += "Content-Length: 0\r\n";  // Longitud del contenido (en este caso, 0)
              httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
              httpResponse += "\r\n";
              // Asegúrate de agregar un carácter nulo al final de la cadena
              httpResponse.push_back('\0');
				      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
			      }
          } else {
				    httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
            if (cookie)
              httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
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
				oss << archivo.rdbuf();
				std::string httpResponse;
        if (locationRoot.getClientBodySize() == -1)
          locationRoot.setClientBodySize("1m");
				if (static_cast<long>(oss.str().size()) > (locationRoot.getClientBodySize()))//OJOOO
				{
          httpResponse = "HTTP/1.1 413 Request Entity Too Large\r\n";
          if (cookie)
             httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
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
	    	  httpResponse = "HTTP/1.1 200 OK\r\n";
          if (cookie)
            httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
				  httpResponse += "Content-Type: " + contentType + "\r\n";
				  httpResponse += "Content-Length: " + toString(oss.str().size()) + "\r\n";
          httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
				  httpResponse += "\r\n";
				  httpResponse += oss.str();
				  send(clientFd, httpResponse.data(), httpResponse.size(), 0);
				}
	    }
			else
			{
        httpResponse = "HTTP/1.1 404 Not Found\r\n";
        if (cookie)
          httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
        if (locationRoot.getErrorPages().find(404) != locationRoot.getErrorPages().end()) {
          std::map<size_t, std::string>::iterator it = locationRoot.getErrorPages().find(404);
          string filePath = adjustRoute(locationRoot.getRoot(), it->second);
          std::stringstream totalPath;
          totalPath << locationRoot.getRoot() << filePath;
          std::ifstream archivo(totalPath.str().c_str());
          if (archivo.is_open()) {
            std::ostringstream oss;
            oss << archivo.rdbuf();
            httpResponse += "Content-Type: " + checkContentType(it->second) + "\r\n";
            httpResponse += "Content-Length: " + toString(oss.str().size()) + "\r\n";
            httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
            httpResponse += "\r\n";
            httpResponse += oss.str();
            send(clientFd, httpResponse.data(), httpResponse.size(), 0);
          }
          else
          {
            std::ifstream archivo("resources/GET/404.html");
            if (archivo.is_open()) {
              std::ostringstream oss;
              oss << archivo.rdbuf();
              httpResponse += "Content-Type: text/html\r\n";
              httpResponse += "Content-Length: " + toString(oss.str().size()) + "\r\n";
              httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
              httpResponse += "\r\n";
              httpResponse += oss.str();
              send(clientFd, httpResponse.data(), httpResponse.size(), 0);
            }
            else
            {
              httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
              if (cookie)
                httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
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
				  httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
          if (cookie)
            httpResponse += "Set-Cookie: session_id=" +  setCookie + "\r\n";
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
}

void Request::postMethod( void )
{
	std::string httpResponse;
	std::string allowed_methods = checkAllowedMethods(locationRoot.getmethods());
  if (!checkMethod("POST")) {
    std::string httpResponse = "HTTP/1.1 405 Method Not Allowed\r\n";
    if (cookie)
      httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
    httpResponse += "Allow: " + allowed_methods + "\r\n";
    httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
	  if (locationRoot.getErrorPages().find(405) != locationRoot.getErrorPages().end()) {
      httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 405, locationRoot.getRoot(), httpResponse);
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
	  std::string msgString(header);
	  size_t bodyStart = msgString.find("\r\n\r\n");
	  std::string postBody = msgString.substr(bodyStart + 4);
	  std::ifstream verificarArchivo((locationRoot.getRoot() + route).c_str());
  	bool archivoExiste = verificarArchivo.good();
  	verificarArchivo.close();
	  std::ofstream archivo((locationRoot.getRoot() + route).c_str(), std::ios::app);
	  if (archivo.is_open()) {
      if (archivoExiste) {
        archivo << postBody << std::endl;
        httpResponse = "HTTP/1.1 200 OK\r\n";
        if (cookie)
          httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
        httpResponse += "Content-Type: " + checkContentType(route) + "\r\n";
        if (isCgi) {
          string tmp;
          if (locationRoot.getRoot()[locationRoot.getRoot().size() - 1] != '/') {
            tmp = locationRoot.getRoot();
            tmp.append("/");
          }
          cgi.setCgi(locationRoot.getCgiPath(), tmp + locationRoot.getIndex());
          cgi.handlerCgi();
          std::stringstream ss;
          ss << convertHTML(cgi.getCgi()).size();
          httpResponse += "Content-Length: " + ss.str() + "\r\n";
          httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
          httpResponse += "\r\n";
          httpResponse += convertHTML(cgi.getCgi());
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        }
        else {
          httpResponse += "Content-Length: " + toString(postBody.size()) + "\r\n";
          httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
          httpResponse += "\r\n";
          httpResponse += postBody;
          send(clientFd, httpResponse.data(), httpResponse.size(), 0); }
      } else {
        archivo << postBody << std::endl;
        httpResponse = "HTTP/1.1 201 CREATED\r\n";
        if (cookie)
          httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
	      httpResponse += "Content-Type: " + checkContentType(route) + "\r\n";
        if (isCgi) {
          string tmp;
          if (locationRoot.getRoot()[locationRoot.getRoot().size() - 1] != '/') {
            tmp = locationRoot.getRoot();
            tmp.append("/");
          }
          cgi.setCgi(locationRoot.getCgiPath(), tmp + locationRoot.getIndex());
          cgi.handlerCgi();
          std::stringstream ss;
          ss << convertHTML(cgi.getCgi()).size();
          httpResponse += "Content-Length: " + ss.str() + "\r\n";
          httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
          httpResponse += "\r\n";
          httpResponse += convertHTML(cgi.getCgi());
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        }
        else {
          httpResponse += "Content-Length: " + toString(postBody.size()) + "\r\n";
          httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
	        httpResponse += "\r\n";
          httpResponse += postBody;
	        send(clientFd, httpResponse.data(), httpResponse.size(), 0); }
      }
    }
    else {
      httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
      if (cookie)
        httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
      httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
      if (locationRoot.getErrorPages().find(500) != locationRoot.getErrorPages().end()) {
        httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 500, locationRoot.getRoot(), httpResponse);
        send(clientFd, httpResponse.data(), httpResponse.size(), 0);
      }
      else
      {
        // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
        httpResponse += "Content-Type: text/html\r\n";
        httpResponse += "Content-Length: " + toString(postBody.size()) + "\r\n";
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
  string allowed_methods = checkAllowedMethods(locationRoot.getmethods());
	std::string httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
  if (cookie)
    httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
  if (!checkMethod("DELETE")) {
    std::string httpResponse = "HTTP/1.1 405 Method Not Allowed\r\n";
    if (cookie)
      httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
    httpResponse += "Allow: " + allowed_methods + "\r\n";
	  if (locationRoot.getErrorPages().find(405) != locationRoot.getErrorPages().end()) {
      httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 405, locationRoot.getRoot(), httpResponse);
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
    // Intentar eliminar el archivo
    if (std::remove((locationRoot.getRoot() + route).c_str()) != 0)
    {
		  httpResponse = "HTTP/1.1 404 Not Found\r\n";
      if (cookie)
        httpResponse += "Set-Cookie: session_id=" +setCookie + "\r\n";
      if (locationRoot.getErrorPages().find(404) != locationRoot.getErrorPages().end()) {
        std::map<size_t, std::string>::iterator it = locationRoot.getErrorPages().find(404);
        string filePath = adjustRoute(locationRoot.getRoot(), it->second);
        std::stringstream totalPath;
        totalPath << locationRoot.getRoot() << filePath;
        std::ifstream archivo(totalPath.str().c_str());
        if (archivo.is_open()) {
          std::ostringstream oss;
          oss << archivo.rdbuf();
          httpResponse += "Content-Type: " + checkContentType(it->second) + "\r\n";
          httpResponse += "Content-Length: " + toString(oss.str().size()) + "\r\n";
          httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
          httpResponse += "\r\n";
          httpResponse += oss.str();
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        }
        else
        {
          std::ifstream archivo("resources/GET/404.html");
          if (archivo.is_open()) {
            std::ostringstream oss;
            oss << archivo.rdbuf();
            httpResponse += "Content-Type: text/html\r\n";
            httpResponse += "Content-Length: " + toString(oss.str().size()) + "\r\n";
            httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
            httpResponse += "\r\n";
            httpResponse += oss.str();
            send(clientFd, httpResponse.data(), httpResponse.size(), 0);
          }
          else
          {
            httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
            httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
            if (cookie)
              httpResponse += "Set-Cookie: session_id=" +setCookie + "\r\n";
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
      if (cookie)
        httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
      httpResponse += "Content-Length: 0\r\n";
      httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
      httpResponse += "\r\n";
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
  }
}


std::string Request::replaceAlias(const std::string& path) {
  string remplacement = locationRoot.getAlias();
  if (!remplacement.empty())
    return (remplacement);
  return (path);
}


void  Request::serverToClient(const string &_header, size_t fd) {
  string coo;
  header.clear();
  header = _header;
  cookie = 1;
  parserData();
  clientFd = fd;
  size_t pos = header.find("session_id=");
  size_t end = pos + 10 + 11;
  while (pos != string::npos && header[end]) {
    pos += 11; // Go to the end of the string
    coo = header.substr(pos, end - pos);
    vector<string>::const_iterator it = listCookie.begin();
    while (it != listCookie.end()) {
      string tmp = *it;
      if (!tmp.compare(coo)) {
        cookie = 0;
        break;
      }
      it++;
    }
    pos = header.find("session_id=", end);
    end = pos + 10 + 11;
  }
  if (cookie) {
    setCookie = generate_random_session_id();
    listCookie.push_back(setCookie);
  }
  istringstream ss(header);
  map<std::string, std::string> alias;
  ss >> method >> route;
	route = replaceAlias(route);
  route = adjustRoute(locationRoot.getRoot(), route);
  if (version != "HTTP/1.1") {
    std::string httpResponse = "HTTP/1.1 505 HTTP Version Not Supported\r\n";
    httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
    if (cookie)
      httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
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
    if (cookie)
      httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
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
