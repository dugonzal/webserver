
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include <arpa/inet.h> // Incluir esta cabecera para inet_ntop

int main() {
    // Crear el socket del servidor
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error al crear el socket del servidor\n";
        return 1;
    }

    // Configurar la dirección del servidor
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8082);

    // Enlazar el socket a la dirección y puerto
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error al enlazar el socket\n";
        return 1;
    }

    // Escuchar conexiones entrantes
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error al escuchar conexiones entrantes\n";
        return 1;
    }

    // Crear estructura de eventos para poll
    struct pollfd fds[1];
    fds[0].fd = serverSocket;
    fds[0].events = POLLIN;

    while (true) {
        // Llamar a poll para esperar actividad en los sockets
        int activity = poll(fds, 1, -1);
        if (activity == -1) {
            std::cerr << "Error en poll\n";
            return 1;
        }

        // Comprobar si hay actividad en el socket del servidor
        if (fds[0].revents & POLLIN) {
            // Aceptar la conexión entrante
            struct sockaddr_in clientAddr;
            socklen_t clientAddrLen = sizeof(clientAddr);
            int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
            if (clientSocket == -1) {
                std::cerr << "Error al aceptar la conexión entrante\n";
                continue;
            }

            // Imprimir información sobre el cliente conectado
            char clientIP[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
            std::cout << "Nuevo cliente conectado desde: " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;

            std::string response = "HTTP/1.1 200  OK\r\n\r\n <h1 align=\"center\"> Hello, World! </h1>";
            // Enviar "Hello, World!" al cliente
            send(clientSocket, response.data(), response.size(), 0);

            // Cerrar la conexión con el cliente
            close(clientSocket);
            std::cout << "Cliente desconectado\n";
        }
    }

    // Cerrar el socket del servidor (nunca llegaremos aquí en este ejemplo)
    close(serverSocket);

    return 0;
}
