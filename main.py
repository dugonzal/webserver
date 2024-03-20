# create an INET, STREAMing socket
import  socket
from  time import sleep
import  sys, os, time

import http.server
import socketserver

""" 
        Handler = http.server.SimpleHTTPRequestHandler

        with socketserver.TCPServer(("0.0.0.0", 8081), Handler) as httpd:
            print("serving at port", 8080)
            httpd.serve_forever()
            print (http.HTTPStatus.OK)
            # create an [ipv4/tcp] INET AF_INET (IPv4), SOCK_STREAM (TCP) socket
   """  
def test():
       with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
           s.bind(("0.0.0.0", 3000))
           s.listen(5)
           pos = True 
           while pos:
              print ("Esperando conexion")
              sleep(1)
              clientSocket, adress =  s.accept() 
              print ("Conexion desde \n\n", adress)
              print (f"{clientSocket.recv(1024)}")
              clientSocket.sendall(bytes("HTTP/1.3 200 OK; <h1> hello<\h1>\r\n\r\n", "utf-8"))
              print("HECHO\n")
              pos = False
           sleep(10)
                
def main():
    test()

main()
