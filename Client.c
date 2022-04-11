#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LENGHT 100

int main(int argc, char **argv)
{
    int sockfd;
    int n;
    char buf[MAX_LENGHT];

    struct sockaddr_in servaddr;

    if (argc != 2)
    {
        printf("Usage: bin/Client <IP address>\n");
        return 1;
    }

    bzero(buf, MAX_LENGHT);

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(51000);

    if (inet_aton(argv[1], &servaddr.sin_addr) == 0)
    {
        fprintf(stderr, "Invalid IP address\n");
        close(sockfd);
        return 2;
    }

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        close(sockfd);
        return 2;
    }
    /* Три раза в цикле вводим строку с клавиатуры, отправляем
    ее серверу и читаем полученный ответ */

    printf("String => ");
    
    if (fflush(stdin) == -1)
    {
        perror("fflush");
        close(sockfd);
        return 3;
    }

    fgets(buf, 1000, stdin);

    if ((n = write(sockfd, buf, strlen(buf) + 1)) == -1)
    {
        perror("write");
        close(sockfd);
        return 4;
    }
    
    bzero(buf, MAX_LENGHT);

    if ((n = read(sockfd, buf, MAX_LENGHT)) == -1)
    {
        perror("read");
        close(sockfd);
        return 5;
    }

    printf("%s", buf);

    close(sockfd);
}