// udp client driver program
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#define PORT 5000
#define MAXLINE 1000

int main()
{   
    char buffer[100];
    char *message = "Hello";
    int s, n;
    struct sockaddr_in saddr;
    bzero(&saddr, sizeof(saddr));
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(PORT);
    saddr.sin_family = AF_INET;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    connect(s, (struct sockaddr *)&saddr, sizeof(saddr));
    sendto(s, message, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(saddr));
    recvfrom(s, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL);
    puts(buffer);
    close(s);
}