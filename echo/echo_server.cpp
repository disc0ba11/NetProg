#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

int main()
{
    sockaddr_in * addr = new (sockaddr_in);
    addr->sin_family = AF_INET;
    addr->sin_port = htons(7777);
    addr->sin_addr.s_addr = inet_addr("127.0.0.1");
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1) {
        perror("couldn't create socket");
		exit(1);
    }
    int rc = bind(s, (const sockaddr *) addr, sizeof(sockaddr_in));
    if (rc == -1) {
        perror("couldn't bind address");
        exit(1);
    }
    rc = listen(s, 100);
    if (rc == -1) {
        perror("couldn't set up listener");
        close(s);
        exit(1);
    }
    sockaddr_in * client_addr = new sockaddr_in;
    socklen_t len = sizeof(sockaddr_in);
    while(1) {
        int work_sock = accept(s, (sockaddr *)(client_addr), &len);
        if (work_sock == -1) {
            perror("couldn't accept connection");
            close(work_sock);
        }
        size_t len = 1024;
        char * data = new char[len];
        while (recv(work_sock, (void*)data, len, MSG_PEEK) == len) {
            delete[] data;
            len *= 2;
            data = new char[len];
        }
        recv(work_sock, (void*)data, len, 0);
        rc = send(work_sock, data, len, 0);
        close(work_sock);
        delete[] data;
    }
}