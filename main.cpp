#include <iostream>
#include <vector>
#include <stdexcept>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <map>

class Server {
private:
    int port;
    int serverSocket;

public:
    // Constructor que recibe el puerto como argumento
    Server(int port, int socket) : port(port), serverSocket(socket) {
        std::cout << "Descriptor de archivo del socket para el puerto " << port << ": " << serverSocket << std::endl;
        std::cout << "Servidor escuchando en el puerto " << port << std::endl;
    }

    // Destructor
    ~Server() {
        close(serverSocket);
    }
};

int main() {
    std::vector<int> ports = {8000, 8001, 8002};
    std::map<int, int> socketMap; // Mapa que asigna un descriptor de archivo a cada puerto
    std::vector<Server> servers;

    try {
        // Creamos un servidor para cada puerto en el vector
        for (int port : ports) {
            // Creamos el socket
            int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (serverSocket == -1) {
                throw std::runtime_error("Error al crear el socket");
            }

            // Configuramos la dirección del servidor
            sockaddr_in serverAddr;
            serverAddr.sin_family = AF_INET;
            serverAddr.sin_addr.s_addr = INADDR_ANY;
            serverAddr.sin_port = htons(port);

            // Enlazamos el socket a la dirección y puerto especificados
            if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
                throw std::runtime_error("Error al enlazar el socket al puerto");
            }

            // Ponemos el socket en modo de escucha
            if (listen(serverSocket, 5) == -1) {
                throw std::runtime_error("Error al poner el socket en modo de escucha");
            }

            // Agregamos el descriptor de archivo al mapa
            socketMap[port] = serverSocket;

            // Creamos un objeto Server y lo agregamos al vector
            servers.emplace_back(port, serverSocket);
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Cerramos todos los sockets y liberamos la memoria
    for (auto& entry : socketMap) {
        close(entry.second);
    }

    return 0;
}

