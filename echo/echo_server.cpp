#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

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
    sockaddr_in * addr = new (sockaddr_in);
    addr->sin_family = AF_INET; // интернет протокол IPv4
    addr->sin_port = htons(7777); // порт 7777
    addr->sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost
    int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
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
        std::string dateTime = currentDateTime();
        rc = send(work_sock, dateTime.c_str(), dateTime.length(), 0);
        close(work_sock);
    }
}