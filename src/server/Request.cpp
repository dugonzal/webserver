/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:48:39 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/15 23:29:22 by jaizpuru         ###   ########.fr       */
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
	std::string httpResponse;
	size_t bodyStart = header.find("\r\n\r\n");
	std::string postBody = header.substr(bodyStart + 4);
	if (!postBody.empty()) /* Return 500 if any body is given */
    	resHttp500(true);
	else if (!checkMethod("GET"))
	{
		if (locationRoot.getErrorPages().find(405) != locationRoot.getErrorPages().end()) {
			httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 405, locationRoot.getRoot(), httpResponse);
			send(clientFd, httpResponse.data(), httpResponse.size(), 0);
		}
    else
      restHttpCustom(405, "text/html", "");
	}
	else
	{
    std::string directoryPath = locationRoot.getRoot() + route;
		if (!locationRoot.getReturn().second.empty())
		{
			if (isAbsolutePath(locationRoot.getReturn().second))
			{
        if (locationRoot.getErrorPages().find(302) != locationRoot.getErrorPages().end()) {
          httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 302, locationRoot.getRoot(), httpResponse);
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        }
        else
          restHttpCustom(302, "", "");
			}
			else if (!locationRoot.getReturn().second.empty() && route != locationRoot.getReturn().second)
			{
        if (locationRoot.getErrorPages().find(301) != locationRoot.getErrorPages().end()) {
          httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 301, locationRoot.getRoot(), httpResponse);
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        }
        else
          restHttpCustom(301, "", "");
			}
			else
        resHttp500(true);
	  }
		else
		{
      std::stringstream totalPath;
      std::string directoryPath;
      if (locationRoot.getAutoIndex() == 1 || locationRoot.getAutoIndex() == -1) { 
        totalPath << locationRoot.getRoot() << route;
        directoryPath = locationRoot.getRoot() + route;
      }
      else { /* Inserts index */
        if (route[route.size() - 1] != '/' && locationRoot.getIndex()[locationRoot.getIndex().size() - 1] != '/')
          route.append("/");
        totalPath << locationRoot.getRoot() << route << locationRoot.getIndex();
        directoryPath = locationRoot.getRoot() + route + locationRoot.getIndex();
      }
        //totalPath << locationRoot.getRoot() << route; Old ones
	      //directoryPath = locationRoot.getRoot() + route;
        std::ifstream archivo(totalPath.str().c_str());
		    std::ostringstream oss;
		    if (isCgi)
          resHttpCGI(contentType);
		    else if (isDirectory(directoryPath)) {
			    if (locationRoot.getAutoIndex() == 1 || locationRoot.getAutoIndex() == -1) /* Autoindex on / Non-defined */
			    {
				    std::string autoindex;
				    if (route == "/")
					    route = "";
				    autoindex = generate_autoindex(directoryPath, autoindex, route, host, port);
            restHttpCustom(200, contentType, autoindex);
			    }
			    else /* Autoindex manually off */
			    {
				    if (locationRoot.getErrorPages().find(404) != locationRoot.getErrorPages().end()) {
					  std::map<size_t, std::string>::iterator it = locationRoot.getErrorPages().find(404);
					  string filePath = adjustRoute(locationRoot.getRoot(), it->second);
					  std::stringstream totalPath;
					  totalPath << locationRoot.getRoot() << filePath;
					  std::ifstream archivo(totalPath.str().c_str());
					  if (archivo.is_open()) {
						  std::ostringstream oss;
					  	oss << archivo.rdbuf();
              restHttpCustom(404, checkContentType(it->second), oss.str());
					  }
					  else /* File could not be opened */
						  resHttp500(false);
				  }
				  else /* There are no error pages associated with 404 code */
					  resHttp500(false);
			    }
        } else if (archivo.is_open()){
          oss << archivo.rdbuf();
          std::string httpResponse;
          if (locationRoot.getClientBodySize() == -1)
            locationRoot.setClientBodySize("1m");
          if (static_cast<long>(oss.str().size()) > (locationRoot.getClientBodySize()))//OJOOO
          {
            if (locationRoot.getErrorPages().find(413) != locationRoot.getErrorPages().end()) {
              httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 413, locationRoot.getRoot(), httpResponse);
              send(clientFd, httpResponse.data(), httpResponse.size(), 0);
            }
            else
              restHttpCustom(413, "text/html", "");
          }
          else
            restHttpCustom(200, contentType, oss.str());
        }
        else
        {
          if (locationRoot.getErrorPages().find(404) != locationRoot.getErrorPages().end()) {
            std::map<size_t, std::string>::iterator it = locationRoot.getErrorPages().find(404);
            string filePath = adjustRoute(locationRoot.getRoot(), it->second);
            std::stringstream totalPath;
            totalPath << locationRoot.getRoot() << filePath;
            std::ifstream archivo(totalPath.str().c_str());
            if (archivo.is_open()) {
              std::ostringstream oss;
              oss << archivo.rdbuf();
              restHttpCustom(404, checkContentType(it->second), oss.str());
            }
            else
            {
              std::ifstream archivo("resources/GET/404.html");
              if (archivo.is_open()) {
                std::ostringstream oss;
                oss << archivo.rdbuf();
                restHttpCustom(404, "text/html", oss.str());
              }
              else
                resHttp500(true);
            }
          } else {
            resHttp500(true);
          }
        }
    }
  }
}

void Request::postMethod( void )
{
	std::string httpResponse;
	std::string contentType = checkContentType(route);
	std::string allowed_methods = checkAllowedMethods(locationRoot.getmethods());
	if (!checkMethod("POST")) {
		if (locationRoot.getErrorPages().find(405) != locationRoot.getErrorPages().end()) {
			httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 405, locationRoot.getRoot(), httpResponse);
			send(clientFd, httpResponse.data(), httpResponse.size(), 0);
		}
    else
			restHttpCustom(405, "text/html", "");
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
				if (isCgi)
					resHttpCGI( contentType );
				else
          restHttpCustom(200, checkContentType(route), postBody);
			}
			else
			{
				if (isCgi)
					resHttpCGI( contentType );
				else
          restHttpCustom(201, contentType, postBody);
			}
		}
		else
		  resHttp500(true);
	}
}

void Request::deleteMethod( void )
{
  std::string httpResponse;
  if (!checkMethod("DELETE")) {
    if (locationRoot.getErrorPages().find(405) != locationRoot.getErrorPages().end()) {
      httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 405, locationRoot.getRoot(), httpResponse);
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
    }
    else
      restHttpCustom(405, "text/html", "");
  }
  else
  {
    // Intentar eliminar el archivo
    if (std::remove((locationRoot.getRoot() + route).c_str()) != 0)
    {
      if (locationRoot.getErrorPages().find(404) != locationRoot.getErrorPages().end()) {
        std::map<size_t, std::string>::iterator it = locationRoot.getErrorPages().find(404);
        string filePath = adjustRoute(locationRoot.getRoot(), it->second);
        std::stringstream totalPath;
        totalPath << locationRoot.getRoot() << filePath;
        std::ifstream archivo(totalPath.str().c_str());
        if (archivo.is_open()) {
          std::ostringstream oss;
          oss << archivo.rdbuf();
          restHttpCustom(404, checkContentType(it->second), oss.str());
        }
        else
        {
          std::ifstream archivo("resources/GET/404.html");
          if (archivo.is_open()) {
            std::ostringstream oss;
            oss << archivo.rdbuf();
            restHttpCustom(404, "text/html", oss.str());
          }
          else
            resHttp500(true);
        }
      }
    }
	  else
		  restHttpCustom(200, "", "");
  }
}

void  Request::restHttpCustom( int httpCode, const std::string& contentType, const std::string& body ) {
  std::string httpResponse;
  switch (httpCode)
  {
    case OK:
      httpResponse = "HTTP/1.1 200 OK\r\n";
      break;
    case CREATED:
      httpResponse = "HTTP/1.1 201 CREATED\r\n";
      break;
    case MOVED:
      httpResponse = "HTTP/1.1 301 Moved Permanently\r\n";
      if (locationRoot.getReturn().second[0] == '/')
          httpResponse += "Location: http://" + host + ":" + toString(port) + locationRoot.getReturn().second + "\r\n";
        else
    		  httpResponse += "Location: http://" + host + ":" + toString(port) + "/" + locationRoot.getReturn().second + "\r\n";
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
      return ;
    case FOUND:
      httpResponse = "HTTP/1.1 302 Found\r\n";
      httpResponse += "Location: " + locationRoot.getReturn().second + "\r\n";
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
      return ;
    case NOT_FOUND:
      httpResponse = "HTTP/1.1 404 Not Found\r\n";
      break ;
    case METHOD_NOT_ALLOWED:
      httpResponse = "HTTP/1.1 405 Method Not Allowed\r\n";
      httpResponse += "Allow: " + checkAllowedMethods(locationRoot.getmethods()) + "\r\n";
      break ;
    case ENTITY_TOO_LARGE:
      httpResponse = "HTTP/1.1 413 Request Entity Too Large\r\n";
      break ;
    case VERSION_NOT_SUPPORTED:
      httpResponse = "HTTP/1.1 505 HTTP Version Not Supported\r\n";
      break ;
    default:
      break;
  }
  if (cookie)
    httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
  if (!contentType.empty())
    httpResponse += "Content-Type: " + contentType + "\r\n";
  httpResponse += "Content-Length: " + toString(body.size()) + "\r\n";
  httpResponse += "Server: " + locationRoot.getServerName() + "\r\n";
  httpResponse += "\r\n";
  if (!body.empty())
    httpResponse += body;
  httpResponse.push_back('\0');
  send(clientFd, httpResponse.data(), httpResponse.size(), 0);
}

void  Request::resHttpCGI( const std::string& contentType ) {
	string httpResponse;
  httpResponse.clear();
	string tmp;
	if (locationRoot.getRoot()[locationRoot.getRoot().size() - 1] != '/') {
		tmp = locationRoot.getRoot();
		tmp.append("/");
	}
	cgi.setCgi(locationRoot.getCgiPath(), tmp + locationRoot.getIndex());
	cgi.handlerCgi();
  restHttpCustom(200, contentType, convertHTML(cgi.getCgi()));
}

void  Request::resHttp500( bool checkErrorPages ) {
	std::string httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
	if (cookie)
		httpResponse += "Set-Cookie: session_id=" + setCookie + "\r\n";
	if ( checkErrorPages && locationRoot.getErrorPages().find(500) != locationRoot.getErrorPages().end()) {
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
    if (locationRoot.getErrorPages().find(505) != locationRoot.getErrorPages().end()) {
      std::string httpResponse;
      httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), 505, locationRoot.getRoot(), httpResponse);
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
    }
    else
      restHttpCustom(505, "text/html", "");
  } else if (method == "GET")
		getMethod();
	else if (method == "POST")
		postMethod();
	else if (method == "DELETE")
		deleteMethod();
  else
    resHttp500(true);
}
