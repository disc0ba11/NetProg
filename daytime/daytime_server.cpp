#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#define PORT 5000
#define MAXLINE 1000

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

int main()
{   
    char buffer[100];
    std::string message;
    int s;
    socklen_t len;
    struct sockaddr_in saddr, caddr;
    bzero(&saddr, sizeof(saddr));
    s = socket(AF_INET, SOCK_DGRAM, 0);        
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(PORT);
    saddr.sin_family = AF_INET; 
    bind(s, (struct sockaddr*)&saddr, sizeof(saddr));
    while (1) {
        len = sizeof(caddr);
        int n = recvfrom(s, buffer, sizeof(buffer),
                0, (struct sockaddr*) &caddr, &len);
        buffer[n] = '\0';
        puts(buffer);
        message = currentDateTime();
        sendto(s, message.c_str(), MAXLINE, 0,
            (struct sockaddr*) &caddr, sizeof(caddr));
    }
}