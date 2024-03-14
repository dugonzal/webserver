TODO :

@dugonzal:
    el parseo tiene buena pinta cosas por hacer:

    [x] checkerar que toda la configuracion siempre este dentro del \
        scope de un servidor si esta afuera es un error

@JOKITON:
    - Comando para verificar multiples puertos al mismo tiempo:
        - curl http://localhost:404 & curl http://localhost:80 &
        (Se puede usar BurpSuite también para ver HTTP GET)
    - Manejar los FDs relativos a escritura que se dan en select().
    - Crear una pagina HTTP de error, 404.
    - Crear los metodos GET, POST, DELETE...
