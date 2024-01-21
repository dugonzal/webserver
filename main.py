# create an INET, STREAMing socket
import  socket
from  time import sleep
import  sys, os, time

import http.server
import socketserver

def test():
        Handler = http.server.SimpleHTTPRequestHandler

        with socketserver.TCPServer(("0.0.0.0", 8081), Handler) as httpd:
            print("serving at port", 8080)
            httpd.serve_forever()
            print (http.HTTPStatus.OK)
            # create an [ipv4/tcp] INET AF_INET (IPv4), SOCK_STREAM (TCP) socket
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.bind(("0.0.0.0", 8080))
            s.listen(5)
            pos = True 
            while pos:
                print ("Esperando conexion")
                sleep(1)
                clientSocket, adress =  s.accept() 
                print ("Conexion desde ", adress)
                print (f"Recibido {clientSocket.recv(1024)}")
                clientSocket.sendall(b"HTTP/1.1 200 OK\r\n\r\n")
                pos = False
# Echo client program

HOST = 'www.google.com'    # The remote host
PORT = 50007              # The same port as used by the server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b'Hello, world')
    data = s.recv(1024)
    print('Received', repr(data))
# hasta aqui solo creamoos el sockewt, ahora lo tenemos que conectar a un puerto

# now connect to the web server on port 80 - the normal http port

