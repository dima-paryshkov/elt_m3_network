#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_CLIENT 10

struct client
{
    int flag;
    int n;
    int sockfd;
    int len;
    struct sockaddr_in cliaddr;
    pthread_t thread;
};

struct client clients[MAX_CLIENT];

void *routine()
{
}

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        return 1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(51000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        perror("bind");
        close(sockfd);
        return 2;
    }

    if (listen(sockfd, 5) < 0)
    {
        perror("listen");
        close(sockfd);
        return 3;
    }

    for (int i = 0; i < MAX_CLIENT; i++)
        clients[i].flag = 0;

    int curN;

    while (1)
    {
        curN = -1;
        for (int i = 0; i < MAX_CLIENT; i++)
            if (clients[i].flag == 0)
                curN = i;

        if (curN == MAX_CLIENT)
        {
            printf("Max count of conection, new connection is break");
            continue;
        }

        if ((clients[curN].sockfd = accept(sockfd, (struct sockaddr *)&clients[curN].cliaddr, &clients[curN].len)) < 0)
        {
            perror("accept");
            close(sockfd);
            return 4;
        }

        clients[curN].n = curN;
        if (pthread_create(clients[curN].thread, NULL, routine, (void *)&clients[curN].n) == -1)
        {
            perror("pthread_create");
            close(sockfd);
            return 5;
        }
        clients[curN].flag = 1;
    }

    return 0;
}