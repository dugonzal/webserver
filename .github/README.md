<h1 align="center">
	🌐  Web Server HTTP en C++98
</h1>

<p align="center">
	<b><i>
	Web Server es un proyecto desarrollado en la escuela 42. Permite comprender el funcionamiento de un servidor HTTP y cómo se comunican los clientes y los servidores en la red.

  </i></b><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/dugonzal/webserver" />
	<img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/dugonzal/webserver" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/dugonzal/libft">
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/dugonzal/werbserver?color=green" />
	<img alt="GitHub closed issues" src="https://img.shields.io/github/issues-closed/dugonzal/webserver" />
	<img alt="GitHub pull requests" src="https://img.shields.io/github/issues-pr/dugonzal/webserver" />
	<img alt="GitHub closed pull requests" src="https://img.shields.io/github/issues-pr-closed/dugonzal/webserver" />
</p>

---
[HTTP/1.1 RFC 9112!](https://www.rfc-editor.org/rfc/rfc9112.html)

# webserv

<p align="center">
  <img src="img/matrix.jpg" alt="Matrix interconectada ¡¡Nodos!!" width="1000"/>
</p>


## HTTP

**HTTP (Protocolo de Transferencia de Hipertexto)** es un protocolo utilizado para transferir hipertexto en la World Wide Web. Facilita la comunicación entre clientes (como navegadores web) y servidores (donde se almacenan y sirven los recursos web).

### Términos clave

- **Navegador**: Aplicación utilizada para acceder y navegar entre documentos HTML.
- **Agente de usuario**: Aplicación que actúa en nombre del usuario, típicamente un navegador.
- **TCP (Protocolo de Control de Transmisión)**: Protocolo de internet utilizado para la comunicación en la web.
- **IP (Protocolo de Internet)**: Protocolo utilizado para transferir datos entre computadoras en una red.
- **URL (Localizador de recursos uniforme)**: Dirección que apunta a un recurso en la web.
- **DNS (Servidor de nombres de dominio)**: Cataloga todas las URL de nombres de dominio y las direcciona a las direcciones IP de los servidores.
- **Sesión**: Comunicación persistente entre un cliente y un servidor.
- **Cookie**: Datos intercambiados entre el cliente y el servidor para mantener una sesión.

### Flujo de HTTP

1. El navegador establece una conexión TCP con el servidor.
2. El navegador envía un mensaje HTTP al servidor, solicitando un recurso.
3. El servidor procesa la solicitud y envía una respuesta al navegador.
4. Una vez recibida la respuesta, la conexión TCP se cierra.

### Métodos HTTP

Los métodos HTTP especifican la acción que el remitente desea realizar en el recurso solicitado.

- **GET**: Obtener el recurso especificado.
- **POST**: Crear un nuevo recurso y agregarlo a una colección.
- **PUT**: Actualizar un recurso existente.
- **PATCH**: Modificar un recurso existente.
- **DELETE**: Eliminar un recurso.
- **OPTION**: Obtener las opciones disponibles para un recurso.
- **HEAD**: Obtener solo los encabezados de respuesta de un recurso.

## Funciones

Este proyecto incluye implementaciones de funciones clave para crear un servidor web.

- **Socket()**: Crea un socket.
- **Poll()**: permite monitorear múltiples descriptores de archivos para detectar eventos de entrada/salida sin bloquear el proceso.
- **Getaddrinfo()**: Resuelve una dirección IP y un puerto.
- **Bind()**: Asocia un socket con una dirección IP y un puerto.
- **Listen()**: Pone un socket en modo de escucha.
- **Accept()**: Acepta una conexión entrante en un socket.
- **Recv()**: Recibe datos de un socket.
- **Send()**: Envía datos a través de un socket.

## ¿Como se usa?
```bash
git clone https://github.com/dugonzal/webserver && cd webserver
make && ./webserver || ./webserver [archivo de configuracion]
```
##  **Palabras reservadas en la key del archivó de configuracion**
```json
  "server", "location", "include", "server_name",
  "listen", "index", "return", "alias", "root",
  "autoindex", "client_max_body_size" "error_page",
  "cgi_path", "allow_methods"
```
## Ejemplo simple de archivo de configuracion
```nginx
server  {
listen	localhost:4242;
root	/dir;
index	index.html;
client_max_body_size 42;
allow_methods	GET;
};
```

## Ejemplo completo de archivo de configuracion
```nginx
server  {

listen	localhost:4242;
autoindex	on;
server_name	tetaedro;
root	resources;
allow_methods	GET POST;
client_max_body_size 4242;
# archivo de configuracion incluido
include ./conf/location.conf;
location / {
	index	main.py;
	alias	./resources;
	cgi_path	./cgi-bin;
	resources	./resources;
	autoindex	on;
	allow_methods	GET POST;
	error_page	4242 errorPages.html;
}
location /redirect {
	index	index.html;
	allow_methods	GET;
	root	./resources;
	client_max_body_size 42;
	# hace una redireccion
	return	301 http://www.42urduliz.com;
}
error_page 403 /error.html;
error_page 404 /error.html;
error_page 405 /error.html;
error_page 500 /error.html;
};
```

 **pruebas de estres**
  - [Load Testing Web Servers with Siege](https://www.linode.com/docs/guides/load-testing-with-siege/)
```cpp
echo "example"
siege -c 255 -t 1M http://0.0.0.0:3007
```
