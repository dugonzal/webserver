/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:48:39 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/04 18:56:00 by inunez-g         ###   ########.fr       */
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
        autoindex += "<li><a href=\"" "http://" + host + ":" +std::to_string(port) + "/" + route + "/" + std::string(entry->d_name) + "\">" + std::string(entry->d_name) + "</a></li>\n"; // http://" + host + ":" + std::to_string(locationRoot.getPort()) + "/" + location[route] + "\r\n";
        
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
	//std::map<std::string, std::string> location;
	//alias["/kapouet"] = "/mi_carpeta";
  std::string contentType = checkContentType(route);
	std::string allowed_methods = checkAllowedMethods(locationRoot.getmethods());
	std::cout << "GETMETHOD" << std::endl;
  cout << "ContentType " << contentType << endl;
  cout << "Allowed_methods " << allowed_methods << endl;
  //cout << locations["/a"].getReturn().second << endl;
	std::string httpResponse;
  bool loc = false;
  /*std::map<size_t, std::string> errorPages;
  std::map<std::string, Location>::iterator locationIterator = locations.find(route);
  printErrorPages(errorPages);
  if (locationIterator != locations.end())
  {
    cout << "Existe la loc" << endl;
    loc = true;
    errorPages = locationIterator->second.getErrorPages();  
  }*/
  std::map<size_t, std::string> errorPages;
  //std::map<std::string, Location>::iterator locationIterator = locations.find(route);
  printErrorPages(errorPages);
  cout << "RUTA ACTUAL: " << route << endl;
  if (locations.find(route) != locations.end())
  {
      cout << "Existe la loc" << endl;
      loc = true;

      // Obtenemos las páginas de error de la ubicación actual
      std::map<size_t, std::string> locationErrorPages = locations.find(route)->second.getErrorPages();

      // Fusionamos las páginas de error nuevas con las antiguas
      errorPages.insert(locationErrorPages.begin(), locationErrorPages.end());
  }
	if (!checkMethod("GET"))
	{
    std::string httpResponse = "HTTP/1.1 405 Method Not Allowed\r\n";
    httpResponse += "Allow: " + allowed_methods + "\r\n";
		if (loc && (errorPages.find(405) != errorPages.end())) {
      httpResponse = personalizeErrorPage(errorPages, 405, locationRoot.getRoot(), httpResponse);
      std::cout << "Error allowed methods" << std::endl;
      send(clientFd, httpResponse.data(), httpResponse.size(), 0);
    } else {
      // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
      httpResponse += "Content-Type: text/html\r\n";
      httpResponse += "Content-Length: 0\r\n";
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
    
		if ((locations.find(route) != locations.end()) && locations[route].getReturn().second != "\0")
		{
			if (isAbsolutePath(locations[route].getReturn().second))
			{
        httpResponse = "HTTP/1.1 302 Found\r\n";
        httpResponse += "Location: " + locations[route].getReturn().second + "\r\n";
        if (loc && (errorPages.find(302) != errorPages.end())) {
          httpResponse = personalizeErrorPage(errorPages, 302, locationRoot.getRoot(), httpResponse);
          std::cout << "302 Found" << std::endl;
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        } else {
          // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
          httpResponse += "Content-Type: text/html\r\n";
          httpResponse += "Content-Length: 0\r\n";
          httpResponse += "\r\n";
          std::cout << "302 Found" << std::endl;
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        }
			}
			else if (!locations[route].getReturn().second.empty() && route != locations[route].getReturn().second)
			{

        httpResponse = "HTTP/1.1 301 Moved Permanently\r\n";
        if (locations[route].getReturn().second[0] == '/')
          httpResponse += "Location: http://" + host + ":" + std::to_string(port) + locations[route].getReturn().second + "\r\n";
        else
    		  httpResponse += "Location: http://" + host + ":" + std::to_string(port) + "/" + locations[route].getReturn().second + "\r\n";
        cout << "301 Moved Permanently" << endl;
        if (loc && (errorPages.find(301) != errorPages.end())) {
          httpResponse = personalizeErrorPage(errorPages, 301, locationRoot.getRoot(), httpResponse);
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
        std::cout << "500 Internal Server Error" << std::endl;
        if (loc && (errorPages.find(500) != errorPages.end())) {
          httpResponse = personalizeErrorPage(errorPages, 500, locationRoot.getRoot(), httpResponse);
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        } else {
          // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
          httpResponse += "Content-Type: text/html\r\n";
          httpResponse += "Content-Length: 0\r\n";
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
      std::cout << "AUTOINDEX: " << locations[route].getAutoIndex() << std::endl;
			if (isDirectory(directoryPath)) {
        if (locations[route].getAutoIndex() == 1 || locations[route].getAutoIndex() == -1)
        {
          /*cout << "AUTOINDEX" << endl;
          std::string autoindex;
          if (route == "/")
            route = ""; 
          autoindex = generate_autoindex(directoryPath, autoindex, route, host, port);
          httpResponse = "HTTP/1.1 200 OK\r\n";
          if (loc && (errorPages.find(200) != errorPages.end())) {
            httpResponse = personalizeErrorPage(errorPages, 200, httpResponse);
            send(clientFd, httpResponse.data(), httpResponse.size(), 0);
          } else {
            // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
            httpResponse += "Content-Type: text/html\r\n";
            httpResponse += "Content-Length: " + std::to_string(autoindex.size()) + "\r\n";
            httpResponse += "\r\n";
            httpResponse += autoindex;
            autoDirectory = route;
            send(clientFd, httpResponse.data(), httpResponse.size(), 0);
          }*/
          cout << "AUTOINDEX" << endl;
          // Generar autoindex
          std::string autoindex;
          if (route == "/")
            route = ""; 
          autoindex = generate_autoindex(directoryPath, autoindex, route, host, port);
          // Respuesta 200 OK con el autoindex
          httpResponse = "HTTP/1.1 200 OK\r\n";
          httpResponse += "Content-Type: " + contentType + "\r\n";
          httpResponse += "Content-Length: " + std::to_string(autoindex.size()) + "\r\n";
          httpResponse += "\r\n";
          httpResponse += autoindex;
          autoDirectory = route;
          send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        }
        else
        {
          httpResponse = "HTTP/1.1 404 Not Found\r\n";
          if (loc && (errorPages.find(404) != errorPages.end())) {
            std::cout << "404 Not Found" << std::endl;
            string filePath = adjustRoute(locationRoot.getRoot(), errorPages[404]).c_str();
            std::cout << "FILE404PATH = " << locationRoot.getRoot() + filePath << endl;
            std::ifstream archivo(locationRoot.getRoot() + filePath);
            std::string httpResponse = "";
            if (archivo.is_open()) {
              std::ostringstream oss;
              oss << archivo.rdbuf();
              httpResponse += "Content-Type: " + checkContentType(errorPages[404].c_str()) + "\r\n";
              httpResponse += "Content-Length: " + std::to_string(oss.str().size()) + "\r\n";
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
        cout << static_cast<long>(oss.str().size()) << endl;
        cout << locationRoot.getClientBodySize() << endl;
				if (static_cast<long>(oss.str().size()) > (locationRoot.getClientBodySize()))//OJOOO
				{
          cout << "TOO LARGE" << endl;
          httpResponse = "HTTP/1.1 413 Request Entity Too Large\r\n";
          if (loc && (errorPages.find(413) != errorPages.end())) {
            httpResponse = personalizeErrorPage(errorPages, 413, locationRoot.getRoot(), httpResponse);
            send(clientFd, httpResponse.data(), httpResponse.size(), 0);
          } else {
            // Si no hay una página de error definida, responder con el código de estado 405 predeterminado
            httpResponse += "Content-Type: text/html\r\n";
            httpResponse += "Content-Length: 0\r\n";
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
				  httpResponse += "\r\n";
				  httpResponse += oss.str();
				  send(clientFd, httpResponse.data(), httpResponse.size(), 0);
				}
	    }
			else
			{
        httpResponse = "HTTP/1.1 404 Not Found\r\n";
        std::cout << "404 Not Found" << std::endl;
        if (loc && (errorPages.find(404) != errorPages.end())) {
          string filePath = adjustRoute(locationRoot.getRoot(), errorPages[404]).c_str();
          std::ifstream archivo(filePath);
          std::string httpResponse = "";
          if (archivo.is_open()) {
            std::ostringstream oss;
            oss << archivo.rdbuf();
            httpResponse += "Content-Type: " + checkContentType(errorPages[404].c_str()) + "\r\n";
            httpResponse += "Content-Length: " + std::to_string(oss.str().size()) + "\r\n";
            httpResponse += "\r\n";
            httpResponse += oss.str();
            send(clientFd, httpResponse.data(), httpResponse.size(), 0);
          }
          else
          {
            cout << "INTERNAL2.1" << endl;
				    httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
            httpResponse += "Content-Type: " + contentType + "\r\n";
            httpResponse += "Content-Length: 0\r\n";  // Longitud del contenido (en este caso, 0)
            httpResponse += "\r\n";
            // Asegúrate de agregar un carácter nulo al final de la cadena
            httpResponse.push_back('\0');
				    send(clientFd, httpResponse.data(), httpResponse.size(), 0);
			    }
        } else {
          
         
          cout << "INTERNAL2.2" << endl;
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
	std::cout << "TERMINO" << std::endl;
	//close(clientFd);
}

void Request::postMethod( void )
{
	std::cout << "ENTRO AL METODO POST" << std::endl;
	std::string httpResponse;
	std::string allowed_methods = "GET POST"; // Métodos permitidos
    if (!checkMethod("POST")) {
        httpResponse = "HTTP/1.1 405 Method Not Allowed\r\n";
        httpResponse += "Allow: " + allowed_methods + "\r\n";
        httpResponse += "\r\n";
        std::cout << "Error: Método no permitido" << std::endl;
        send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        return;
    } else {
		std::string msgString(header);
	  size_t bodyStart = msgString.find("\r\n\r\n");
		std::string postBody = msgString.substr(bodyStart + 4);
	    if (postBody.empty()) {
	        std::cout << "HTTP/1.1 204 No Content\r\n" << std::endl;
	        httpResponse = "HTTP/1.1 204 No Content\r\n";
	        httpResponse += "\r\n";
	        send(clientFd, httpResponse.data(), httpResponse.size(), 0);
	        return;
	    }
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
	            httpResponse += "\r\n";
	            send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        	} else {
            	archivo << postBody << std::endl;
            	std::cout << "Contenido escrito exitosamente en el archivo nuevo." << std::endl;
            	std::cout << "HTTP/1.1 201 Created\r\n" << std::endl;
              httpResponse = "HTTP/1.1 201 CREATED\r\n";
	            httpResponse += "\r\n";
	            send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        	}
	    } else {
	        std::cerr << "HTTP/1.1 500 Internal Server Error\n" << std::endl;
	        httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
	        httpResponse += "\r\n";
	        send(clientFd, httpResponse.data(), httpResponse.size(), 0);
	    }
	}
}

void Request::deleteMethod( void )
{
  std::string allowed_methods = "GET POST"; // Métodos permitidos
	std::cout << "DELETEMETHOD" << std::endl;
	std::string httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
  if (!checkMethod("DELETE")) {
        httpResponse = "HTTP/1.1 405 Method Not Allowed\r\n";
        httpResponse += "Allow: " + allowed_methods + "\r\n";
        httpResponse += "\r\n";
        std::cout << "Error: Método no permitido" << std::endl;
        send(clientFd, httpResponse.data(), httpResponse.size(), 0);
        return;
  }
  else
  {
    // Intentar eliminar el archivo
    if (std::remove((locationRoot.getRoot() + route).c_str()) != 0)
		  httpResponse = "HTTP/1.1 404 Not Found\r\n";
	  else
		  httpResponse = "HTTP/1.1 200 OK\r\n";
  }
	send(clientFd, httpResponse.data(), httpResponse.size(), 0);
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
	if (method == "GET")
		getMethod();
	else if (method == "POST")
		postMethod();
	else if (method == "DELETE")
		deleteMethod();
  else
    return;
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


