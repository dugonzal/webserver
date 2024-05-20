/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:48:39 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/05/20 12:40:49 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/server/Request.hpp"

template <typename T>
string toString(T val) {
  stringstream oss;
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

static string adjustRoute(const string &locationRoot, string &route) {
  size_t pos = 0;
  while ((pos = route.find("//", pos)) != string::npos) {
      route.replace(pos, 2, "/");
  }
  if (!locationRoot.empty() && *locationRoot.end() == '/' && !route.empty() && *route.begin() == '/') {
      route.erase(0, 1);
  }
  return route;
}

static string adjustRoute(string route) {
  size_t pos = 0;
  while ((pos = route.find("//", pos)) != string::npos) {
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

void  Request::setEnviroment( char** _environ ) {
  environ = _environ;
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

  if (setRouteAndVersion(trim(Utils::lastWord(header.substr(0, pos))))) {
    logger.Log("error version");
  }
  setLocation();
  if (setMethod(trim(Utils::firstWord(header.substr(0, pos))))) {
    logger.Log("error method no allowed");
  }
}

string checkContentType(const string& routeToFile) {
    // Mapeo de extensiones a tipos de contenido
    map<string, string> extensionsMap;
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
        map<string, string>::iterator it = extensionsMap.find(extension);
        if (it != extensionsMap.end()) {
            return it->second;  // Devuelve el tipo de contenido correspondiente si se encuentra la extensión
        }
    }

    // Si no se encuentra la extensión en el mapa o no hay extensión, se asigna 'text/plain'
    return "text/html";
}

string checkAllowedMethods(const vector<string>& methods) {
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

string generate_autoindex(const string& directoryPath, string autoindex, string route, string host, int port) {
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
          autoindex += "<li><a href=\"" "http://" + host + ":" +toString(port) + route + "/" + string(entry->d_name) + "\">" + string(entry->d_name) + "</a></li>\n"; // http://" + host + ":" + toString(locationRoot.getPort()) + "/" + location[route] + "\r\n";
        else
          autoindex += "<li><a href=\"" "http://" + host + ":" +toString(port) + "/" + route + "/" + string(entry->d_name) + "\">" + string(entry->d_name) + "</a></li>\n"; // http://" + host + ":" + toString(locationRoot.getPort()) + "/" + location[route] + "\r\n";
      } else
        autoindex += "<li><a href=\"" "http://" + host + ":" +toString(port) + "/" + string(entry->d_name) + "\">" + string(entry->d_name) + "</a></li>\n"; // http://" + host + ":" + toString(locationRoot.getPort()) + "/" + location[route] + "\r\n";
    }
    autoindex += "</ul><hr></body></html>\n";
    // Cierra el directorio
    closedir(dir);
    return autoindex;
}

string personalizeErrorPage(map<size_t, string> errorPages, size_t errorCode, const string rootPath, string httpResponse)
{
  string filePath = adjustRoute(rootPath, errorPages[errorCode]).c_str();
  stringstream totalPath;
  
  totalPath << rootPath << filePath;
  ifstream archivo(totalPath.str().c_str());
  if (archivo.is_open()) {
    ostringstream oss;
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
	string contentType = checkContentType(route);
	string httpResponse;
	size_t bodyStart = header.find("\r\n\r\n");
	string postBody = header.substr(bodyStart + 4);
	if (!postBody.empty()) /* Return 500 if any body is given */
    	resHttpErr(true, INTERNAL_ERROR, "text/html", "<h2>Error 500: Internal Server Error</h2>");
	else if (!checkMethod("GET"))
    resHttpErr(true, METHOD_NOT_ALLOWED, "text/html", "");
	else
	{
    string directoryPath = locationRoot.getRoot() + route;
		if (!locationRoot.getReturn().second.empty())
		{
			if (isAbsolutePath(locationRoot.getReturn().second))
        resHttpErr(true, FOUND, "", "");
			else if (!locationRoot.getReturn().second.empty() && route != locationRoot.getReturn().second)
        resHttpErr(true, MOVED, "", "");
			else
        resHttpErr(true, INTERNAL_ERROR, "text/html", "<h2>Error 500: Internal Server Error</h2>");
	  }
		else
		{
      stringstream totalPath;
      string directoryPath;
      
      totalPath << locationRoot.getRoot() << route;
      directoryPath = locationRoot.getRoot() + route;
      if (isDirectory(locationRoot.getRoot() + route)) { /* is Directory & Index specified */
        if (!locationRoot.getIndex().empty()) { /* This is the case where index should apply */
          totalPath.str("");
          if (route[route.size() - 1] != '/' && locationRoot.getIndex()[locationRoot.getIndex().size() - 1] != '/')
              route.append("/");
          totalPath << locationRoot.getRoot() << route << locationRoot.getIndex();
          directoryPath = locationRoot.getRoot() + route + locationRoot.getIndex();
        }
      }
      ifstream archivo(totalPath.str().c_str());
      ostringstream oss;
      if (isCgi)
        resHttpCGI(contentType);
      else if (isDirectory(directoryPath)) { /* Directory */
        if ((locationRoot.getAutoIndex() == 1 || locationRoot.getAutoIndex() == -1) && locationRoot.getIndex().empty()) /* Autoindex on / Non-defined */
        {
          string autoindex;
          if (route == "/")
            route = "";
          autoindex = generate_autoindex(directoryPath, autoindex, route, host, port);
          resHttpCustom(OK, contentType, autoindex);
        }
        else /* Autoindex manually off */
        {
          if (locationRoot.getErrorPages().find(404) != locationRoot.getErrorPages().end()) {
            map<size_t, string>::iterator it = locationRoot.getErrorPages().find(404);
            string filePath = adjustRoute(locationRoot.getRoot(), it->second);
            stringstream totalPath;
            totalPath << locationRoot.getRoot() << filePath;
            ifstream archivo(totalPath.str().c_str());
            if (archivo.is_open()) {
              ostringstream oss;
              oss << archivo.rdbuf();
              resHttpCustom(NOT_FOUND, checkContentType(it->second), oss.str());
            }
            else
              resHttpErr(false, INTERNAL_ERROR, "text/html", "<h2>Error 500: Internal Server Error</h2>");
          }
          else /* No error pages for 404 code */
            resHttpErr(false, INTERNAL_ERROR, "text/html", "<h2>Error 500: Internal Server Error</h2>");
        }
      } else if (archivo.is_open()) { /* File OR Index */
        oss << archivo.rdbuf();
        string httpResponse;
        if (locationRoot.getClientBodySize() == -1)
          locationRoot.setClientBodySize("1m");
        if (static_cast<long>(oss.str().size()) > (locationRoot.getClientBodySize()))
          resHttpErr(true, ENTITY_TOO_LARGE, "text/html", "<h2>Error 413: Request Entity Too Large</h2>");
        else
          resHttpCustom(OK, contentType, oss.str());
      }
      else /* Not found */
      {
        if (locationRoot.getErrorPages().find(404) != locationRoot.getErrorPages().end()) {
          map<size_t, string>::iterator it = locationRoot.getErrorPages().find(404);
          string filePath = adjustRoute(locationRoot.getRoot(), it->second);
          stringstream totalPath;
          totalPath << locationRoot.getRoot() << filePath;
          ifstream archivo(totalPath.str().c_str());
          if (archivo.is_open()) {
            ostringstream oss;
            oss << archivo.rdbuf();
            resHttpCustom(NOT_FOUND, checkContentType(it->second), oss.str());
          }
          else
          {
            ifstream archivo("resources/GET/404.html");
            if (archivo.is_open()) {
              ostringstream oss;
              oss << archivo.rdbuf();
              resHttpCustom(NOT_FOUND, "text/html", oss.str());
            }
            else
              resHttpErr(true, INTERNAL_ERROR, "text/html", "<h2>Error 500: Internal Server Error</h2>");
          }
        }
        else
          resHttpErr(true, INTERNAL_ERROR, "text/html", "<h2>Error 500: Internal Server Error</h2>");
      }
    }
  }
}

void Request::postMethod( void )
{
	string httpResponse;
	string contentType = checkContentType(route);
	string allowed_methods = checkAllowedMethods(locationRoot.getmethods());
	if (!checkMethod("POST"))
		resHttpErr(true, METHOD_NOT_ALLOWED, "text/html", "");
	else
	{
    if (isCgi) {
      resHttpCGI( contentType );
      return ;
    }
		string msgString(header);
		size_t bodyStart = msgString.find("\r\n\r\n");
		string postBody = msgString.substr(bodyStart + 4);
		ifstream verificarArchivo((locationRoot.getRoot() + route).c_str());
		bool archivoExiste = verificarArchivo.good();
		verificarArchivo.close();
		ofstream archivo((locationRoot.getRoot() + route).c_str(), ios::app);
		if (archivo.is_open()) {
			if (archivoExiste)
				resHttpCustom(OK, checkContentType(route), postBody);
			else
				resHttpCustom(CREATED, contentType, postBody);
		}
		else
		  resHttpErr(true, INTERNAL_ERROR, "text/html", "<h2>Error 500: Internal Server Error</h2>");
	}
}

void Request::deleteMethod( void )
{
  string httpResponse;
  if (!checkMethod("DELETE"))
    resHttpErr(true, METHOD_NOT_ALLOWED, "text/html", "");
  else
  {
    // Intentar eliminar el archivo
    if (remove((locationRoot.getRoot() + route).c_str()) != 0)
    {
      if (locationRoot.getErrorPages().find(404) != locationRoot.getErrorPages().end()) {
        map<size_t, string>::iterator it = locationRoot.getErrorPages().find(404);
        string filePath = adjustRoute(locationRoot.getRoot(), it->second);
        stringstream totalPath;
        totalPath << locationRoot.getRoot() << filePath;
        ifstream archivo(totalPath.str().c_str());
        if (archivo.is_open()) {
          ostringstream oss;
          oss << archivo.rdbuf();
          resHttpCustom(NOT_FOUND, checkContentType(it->second), oss.str());
        }
        else
        {
          ifstream archivo("resources/GET/404.html");
          if (archivo.is_open()) {
            ostringstream oss;
            oss << archivo.rdbuf();
            resHttpCustom(NOT_FOUND, "text/html", oss.str());
          }
          else
            resHttpErr(true, INTERNAL_ERROR, "text/html", "<h2>Error 500: Internal Server Error</h2>");
        }
      }
    } 
    else
		  resHttpCustom(OK, "", "");
  }
}

void  Request::resHttpCustom( int httpCode, const string& contentType, const string& body ) {
  string httpResponse;
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
      break ;
    case FOUND:
      httpResponse = "HTTP/1.1 302 Found\r\n";
      httpResponse += "Location: " + locationRoot.getReturn().second + "\r\n";
      break ;
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
    case INTERNAL_ERROR:
      httpResponse = "HTTP/1.1 500 Internal Server Error\r\n";
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
  Response::sendResponse(httpResponse, clientFd);
}

void  Request::resHttpCGI( const string& contentType ) {
	string httpResponse;
  httpResponse.clear();
	string tmp;
	if (locationRoot.getRoot()[locationRoot.getRoot().size() - 1] != '/') {
		tmp = locationRoot.getRoot();
		tmp.append("/");
	}
  if (method == "POST" && checkQueryPost(header))
    handleQueryPost(header);
	cgi.setCgi(locationRoot.getCgiPath(), tmp + locationRoot.getIndex(), environ);
  cgi.handlerCgi();
  //std::cout << cgi.getCgi() << std::endl;
  resHttpCustom(OK, contentType, cgi.getCgi());
}

void  Request::resHttpErr( bool checkErrPg, int _httpCode,const string& _contentType, const string& _body ) {
  string httpResponse;
  if ( checkErrPg && locationRoot.getErrorPages().find(_httpCode) != locationRoot.getErrorPages().end()) {
		httpResponse = personalizeErrorPage(locationRoot.getErrorPages(), _httpCode, locationRoot.getRoot(), httpResponse);
		Response::sendResponse(httpResponse ,clientFd);
	}
  else
    resHttpCustom( _httpCode, _contentType, _body );
}

string Request::replaceAlias(const string& path) {
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
  map<string, string> alias;
  ss >> method >> route;
	route = replaceAlias(route);
  route = adjustRoute(locationRoot.getRoot(), route);
  if (version != "HTTP/1.1") {
    resHttpErr(true, VERSION_NOT_SUPPORTED, "text/html", "");
  } else if (method == "GET")
	  getMethod();
  else if (method == "POST")
	  postMethod();
  else if (method == "DELETE")
		deleteMethod();
  else
    resHttpErr(true, INTERNAL_ERROR, "text/html", "<h2>Error 500: Internal Server Error</h2>");
}

bool  Request::checkQueryPost( const string& msgClient ) {
  size_t bodyStart = msgClient.find("Content-Length: ");
  if (bodyStart == string::npos)
    return false;
	size_t bodyEnd = msgClient.find("\r\n" ,bodyStart);
  string ret = msgClient.substr(bodyStart + 16, bodyEnd - bodyStart - 16);
  if (!ret.compare("0"))
    return false;
  else
    return true;
}

void  Request::handleQueryPost( const string& msgClient ) {
  size_t bodyStart = msgClient.find("\r\n\r\n");
  string query = msgClient.substr(bodyStart + 4);

  size_t it;
  char envLine[100] = "QUERY_STRING=";
  for (it = 0; environ[it]; it++)
    ;
  strcat(envLine, query.c_str());
  environ[0] = envLine;

  if (setenv("QUERY_STRING", query.c_str(), 1) != 0)
    logger.Log("error: setenv() did not work");
  string query_value(getenv("QUERY_STRING"));
  if (!query_value.empty()) {
      logger.Log(query_value.c_str());
  } else {
      logger.Log("QUERY_STRING environment variable not set");
  }
}
