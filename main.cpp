
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <fstream>

// Función para leer un archivo y devolver su contenido como una cadena
std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    return content;
}

int main() {
    // Crear el socket del servidor
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error al crear el socket del servidor\n";
        return 1;
    }

    // Configurar opciones del socket para reutilizar la dirección y puerto del servidor
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
        std::cerr << "Error al configurar las opciones del socket\n";
        return 1;
    }

    // Configurar la dirección del servidor
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

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

    // Crear un conjunto de descriptores de archivos para select
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(serverSocket, &readSet);
    int maxFd = serverSocket;

    while (true) {
        fd_set tmpSet = readSet;
        
        // Llamar a select para esperar actividad en los sockets
        int activity = select(maxFd + 1, &tmpSet, NULL, NULL, NULL);
        if (activity == -1) {
            std::cerr << "Error en select\n";
            return 1;
        }

        // Comprobar si hay actividad en el socket del servidor
        if (FD_ISSET(serverSocket, &tmpSet)) {
            // Aceptar la conexión entrante
            struct sockaddr_in clientAddr;
            socklen_t clientAddrLen = sizeof(clientAddr);
            int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
            if (clientSocket == -1) {
                std::cerr << "Error al aceptar la conexión entrante\n";
                continue;
            }

            // Imprimir información sobre el cliente conectado
/*            char clientIP[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
            std::cout << "Nuevo cliente conectado desde: " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;
*/
            // Recibir la solicitud del cliente
            char buffer[1024];
            int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesRead <= 0) {
                std::cerr << "Error al recibir la solicitud del cliente\n";
                close(clientSocket);
                continue;
            }

            // Analizar la solicitud HTTP
            std::string request(buffer, bytesRead);
            size_t pos = request.find("GET");
            if (pos != std::string::npos) {
                size_t endPos = request.find(" ", pos + 4);
                if (endPos != std::string::npos) {
                    std::string filePath = request.substr(pos + 4, endPos - pos - 4);
                    if (filePath == "/") {
                        filePath = "/index.html"; // Servir index.html por defecto si no se especifica un archivo
                    }

                    // Leer el archivo solicitado
                    std::string fileContent = readFile("public" + filePath);
                    if (fileContent.empty()) {
                        // Archivo no encontrado, enviar respuesta 404 Not Found
                        std::string response = "HTTP/1.1 404 Not Found\r\n\r\n";
                        send(clientSocket, response.c_str(), response.length(), 0);
                    } else {
                        // Archivo encontrado, enviar respuesta 200 OK con el contenido del archivo
                        std::string response = "HTTP/1.1 200 OK\r\nContent-Length: " + std::to_string(fileContent.length()) + "\r\n\r\n" + fileContent;
                        send(clientSocket, response.c_str(), response.length(), 0);
                    }
                }
            }

            // Cerrar la conexión con el cliente
            close(clientSocket);
            std::cout << "Cliente desconectado\n";
        }
    }

    // Cerrar el socket del servidor (nunca llegaremos aquí en este ejemplo)
    close(serverSocket);

    return 0;
}
