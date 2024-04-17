TODO :

@dugonzal:
    el parseo tiene buena pinta cosas por hacer:

    [x] checkerar que toda la configuracion siempre este dentro del \
        scope de un servidor si esta afuera es un error
  std::string response = "HTTP/1.1 200  OK\r\n\r\n <h1 align=\"center\"> Hello, World! </h1>";

@JOKITON:
    - Comando para verificar multiples puertos al mismo tiempo:
        - curl http://localhost:404 & curl http://localhost:80 &
        (Se puede usar BurpSuite también para ver HTTP GET)
        In the configuration file, you should be able to:
        • Choose the port and host of each ’server’. -> [ host / port ] : 127.0.0.1:80 / localhost:80 / 80 (assume its localhost)
        • Setup the server_names or not. -> [ server_name ] : Compare with clients HEAD & select server block
        • The first server for a host:port will be the default for this host:port (that means it will answer to all the requests that don’t belong to an other server). -> Hierarchy
        • Setup default error pages. -> [ error_page 404 403 500 503 /error-page.html; ]
        • Limit client body size. -> [client_max_body_size 1m;]

```c
  for (vector<string>::iterator it = data.begin(); it != data.end(); it++) {
    if (it->find("server") != string::npos) {
      while (it->find("}") == string::npos) {
        it++;
        if (it->find("location") != string::npos) {
          Location location;
          it++;
          while (it->find("}") == string::npos) {
            if (it->find("root") != string::npos) {
              location.setRoot(it->substr(it->find("root") + 5));
            } else if (it->find("path") != string::npos) {
              location.setPath(it->substr(it->find("path") + 5));
            } else if (it->find("index") != string::npos) {
              location.setIndex(it->substr(it->find("index") + 6));
            } else if (it->find("autoindex") != string::npos) {
              location.setAutoIndex(it->substr(it->find("autoindex") + 10));
            } else if (it->find("cgi_path") != string::npos) {
              location.setCgiPath(it->substr(it->find("cgi_path") + 9));
            } else if (it->find("methods") != string::npos) {
              location.setMethods(it->substr(it->find("methods") + 8));
            } else if (it->find("error_page") != string::npos) {
              location.setErrorPages(it->substr(it->find("error_page") + 11));
            }
            it++;
          }
          locations.insert(pair<string, Location>(location.getPath(), location));
        }
      }
    }
  }

```
