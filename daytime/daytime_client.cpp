#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string.h>

int main()
{
    char *msg = "hello\n";
    char buf[1024];
    int n;
    socklen_t len;
    sockaddr_in * saddr = new (sockaddr_in);
    saddr->sin_family = AF_INET;
    saddr->sin_port = htons(7777);
    saddr->sin_addr.s_addr = inet_addr("127.0.0.1");
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1) {
        perror("couldn't create socket");
		exit(1);
    }
    // sockaddr_in * self_addr = new(sockaddr_in);
    // addr->sin_family = AF_INET;
    // addr->sin_port = 0;
    // addr->sin_addr.s_addr = 0;
    // int rc = bind(s, (const sockaddr *) self_addr, sizeof(sockaddr_in));
    // if (rc == -1) {
    //     perror("couldn't bind address");
    //     exit(1);
    // }
    // rc = connect(s, (const sockaddr *) addr, sizeof(sockaddr_in));
    // if (rc == -1) {
    //     perror("couldn't connect");
    //     close(s);
    //     exit(1);
    // }
    connect(s, (sockaddr *) &saddr, sizeof(saddr));
    sendto(s, msg, strlen(msg), 0, (sockaddr *) NULL, sizeof(saddr));
    printf("sent");
    n = recvfrom(s, (char *) buf, 1024, 0, (sockaddr *) NULL, NULL);
    buf[n] = '\0';
    printf(buf);
    close(s);
    // sockaddr_in * client_addr = new sockaddr_in;
    // socklen_t len = sizeof(sockaddr_in);
    // while(1) {
    //     int work_sock = accept(s, (sockaddr *)(client_addr), &len);
    //     if (work_sock == -1) {
    //         perror("couldn't accept connection");
    //         close(work_sock);
    //     }
    //     std::string dateTime = currentDateTime();
    //     rc = send(work_sock, dateTime.c_str(), dateTime.length(), 0);
    //     close(work_sock);
    // }
}