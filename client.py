import socket

HEADER = 64
PORT = 8080
FORMAT = "utf-8"
DISCONNECT_MESSAGE = "!DISCONNECT"
SERVER = "http://localhost"

# create new socket for client which only accepts IPV4 addresses
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# connect with the server socket
client.connect((SERVER,PORT))

message = 'GET http://localhost:8080/ HTTP/1.1\r\n\r\n'.encode();

client.send(message)

while True:
     data = client.recv(512)
     if len(data) < 1:
          break;
     print(data.decode(), end='')
     
client.close()

