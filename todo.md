TODO :

@dugonzal:
    el parseo tiene buena pinta cosas por hacer:

    [x] checkerar que toda la configuracion siempre este dentro del \
        scope de un servidor si esta afuera es un error

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
