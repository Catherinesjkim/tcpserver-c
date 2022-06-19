// https://github.com/nikhilroxtomar/tcp-client-server-in-C

// All the headers that we need - identical to the UDP server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// hardcoded port 8801
#define PORT 8801

// we are going to need socket file descriptor as usual - it's just a number, the more, the more memory you need
// we need server address (me) and new address (destination server)
// create socket the same as udp
// AF_INET == IPv4
// SOCK_STREAM == TCP; the only thing different from UDP
// the only different is with binding - any packet that is received, go ahead, and deliver the datagrams of the segments to me
// you have to listen to the incoming request  "listen(sockfd, 5);"
// "listen" is what performs the TCP handshake. Backlog == 5
// Queue, maximum number of connections that can set in your queue
// Only accepts one TCP connection. If you want more, you need to create an array
// Accepting is the most important concept in TCP

int main()
{

    int sockfd;
    struct sockaddr_in serverAddr;

    int newSocket;
    struct sockaddr_in newAddr;

    socklen_t addr_size;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Server Socket Created Successfully.\n");
    memset(&serverAddr, '\0', sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    printf("[+]Bind to Port number %d.\n", PORT);

    listen(sockfd, 5);
    printf("[+]Listening...\n");

    newSocket = accept(sockfd, (struct sockaddr *)&newAddr, &addr_size);

    strcpy(buffer, "Hello");
    send(newSocket, buffer, strlen(buffer), 0);
    printf("[+]Closing the connection.\n");

    return 0;
}
