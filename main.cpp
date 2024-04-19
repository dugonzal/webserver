
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include <vector>
#include <arpa/inet.h> // Para inet_ntop

constexpr int MAX_CLIENTS = 10;
constexpr int SERVER_PORT_1 = 8005;
constexpr int SERVER_PORT_2 = 8006;

int main() {
    // Crear vector de estructuras de eventos para poll
    std::vector<pollfd> fds;

    // Crear sockets para los servidores
    int serverSocket1 = socket(AF_INET, SOCK_STREAM, 0);
    int serverSocket2 = socket(AF_INET, SOCK_STREAM, 0);

    // Verificar errores en la creación de sockets
    if (serverSocket1 == -1 || serverSocket2 == -1) {
        std::cerr << "Error al crear los sockets del servidor\n";
        return 1;
    }

    // Configurar la dirección del servidor 1
    struct sockaddr_in serverAddr1;
    serverAddr1.sin_family = AF_INET;
    serverAddr1.sin_addr.s_addr = INADDR_ANY;
    serverAddr1.sin_port = htons(SERVER_PORT_1);

    // Configurar la dirección del servidor 2
    struct sockaddr_in serverAddr2;
    serverAddr2.sin_family = AF_INET;
    serverAddr2.sin_addr.s_addr = INADDR_ANY;
    serverAddr2.sin_port = htons(SERVER_PORT_2);

    // Enlazar el socket 1 a la dirección y puerto
    if (bind(serverSocket1, (struct sockaddr *)&serverAddr1, sizeof(serverAddr1)) == -1) {
        std::cerr << "Error al enlazar el socket 1\n";
        return 1;
    }

    // Enlazar el socket 2 a la dirección y puerto
    if (bind(serverSocket2, (struct sockaddr *)&serverAddr2, sizeof(serverAddr2)) == -1) {
        std::cerr << "Error al enlazar el socket 2\n";
        return 1;
    }

    // Escuchar conexiones entrantes en ambos sockets
    if (listen(serverSocket1, MAX_CLIENTS) == -1 || listen(serverSocket2, MAX_CLIENTS) == -1) {
        std::cerr << "Error al escuchar conexiones entrantes\n";
        return 1;
    }

    // Agregar los sockets de los servidores a la estructura de eventos de poll
    fds.push_back({serverSocket1, POLLIN});
    fds.push_back({serverSocket2, POLLIN});

    while (true) {
        // Llamar a poll para esperar actividad en los sockets
        int activity = poll(fds.data(), fds.size(), -1);
        if (activity == -1) {
            std::cerr << "Error en poll\n";
            return 1;
        }

        // Iterar sobre los sockets de servidores para comprobar actividad
        for (size_t i = 0; i < fds.size(); ++i) {
            if (fds[i].revents & POLLIN) {
                if (fds[i].fd == serverSocket1 || fds[i].fd == serverSocket2) {
                    // Aceptar la conexión entrante solo si es un nuevo cliente
                    struct sockaddr_in clientAddr;
                    socklen_t clientAddrLen = sizeof(clientAddr);
                    int clientSocket = accept(fds[i].fd, (struct sockaddr *)&clientAddr, &clientAddrLen);
                    if (clientSocket == -1) {
                        std::cerr << "Error al aceptar la conexión entrante en el socket " << i+1 << "\n";
                        continue;
                    }

                    // Imprimir información sobre el cliente conectado
                    char clientIP[INET_ADDRSTRLEN];
                    inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
                    std::cout << "Nuevo cliente conectado desde: " << clientIP << ":" << ntohs(clientAddr.sin_port) << " en el socket " << i+1 << "\n";

                    const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";
                    // Enviar un mensaje de bienvenida al cliente
                    send(clientSocket, response, strlen(response), 0);

                    // Agregar el nuevo socket de cliente a la estructura de eventos de poll
                    fds.push_back({clientSocket, POLLIN | POLLRDHUP});
                } else {
                    // Recibir datos del cliente
                    // Procesar los datos recibidos del cliente si es necesario
                    // Enviar respuesta al cliente
                }
            }
        }
    }

    return 0;
}
