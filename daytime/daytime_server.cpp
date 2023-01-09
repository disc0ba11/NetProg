#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
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
    char buf[100];
    std::string dateTime;
    int n;
    socklen_t len;
    // sockaddr_in * saddr = new (sockaddr_in);
    // sockaddr_in * caddr = new (sockaddr_in);
    struct sockaddr_in saddr, caddr;
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(7777);
    saddr.sin_addr.s_addr = inet_addr(INADDR_ANY);
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1) {
        perror("couldn't create socket");
		exit(1);
    }
    bind(s, (struct sockaddr *) &saddr, sizeof(saddr));
    len = sizeof(caddr);
    while (1) {
        n = recvfrom(s, buf, sizeof(buf), MSG_WAITALL, (struct sockaddr *) &caddr, &len);
        buf[n] = '\0';
        printf("Client: %s", buf);
        dateTime = currentDateTime();
        sendto(s, dateTime.c_str(), 1024, MSG_CONFIRM, (struct sockaddr *) &caddr, sizeof(caddr));
        printf("Sent date/time\n");
    }
}