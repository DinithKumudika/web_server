# web_server
simple web server with multi-threading written in C language for 2nd year of my university Networking course module. So far the web server can only handle GET requests from the clients and only works with linux operating system. hope to imporve this to works with windows operating system and POST, PUT, PATCH, DELETE http methods in future :)


## Getting started

1. clone the repository (host OS must be a linux distro. If your pc is not running a linux OS you can use a virtualBox)
2. cd web_server
3. compile the program using `make` command
4. run web server using `bin/server` PORT command. PORT is the port which you want to run the server (ex-:8080)
5. open a web browser and go to http://localhost:PORT

## Compile

`make`

## Usage

`bin/server` PORT

## Reference 
https://bruinsslot.jp/post/simple-http-webserver-in-c/
<br>
https://www.jmarshall.com/easy/http/
<br>
https://www.geeksforgeeks.org/http-headers-content-type/
<br>
https://dzone.com/articles/parallel-tcpip-socket-server-with-multi-threading
<br>
https://www.geeksforgeeks.org/thread-functions-in-c-c/
<br>
https://stackoverflow.com/questions/34510/what-is-a-race-condition
