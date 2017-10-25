#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

/* Will clear dest and store the contents of source to dest */
void set_str(char* dest, const char* source);

int main(int argc, char** argv)
{
    int clientfd;
    struct sockaddr_in server_addr;
    char buffer[1024];

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("192.168.43.4");
    server_addr.sin_port = htons(8000);

    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(connect(clientfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Error connecting to server\n");
        return -1;
    }

    set_str(buffer, "autotext.txt");
    send(clientfd, buffer, strlen(buffer)+1, 0);
    memset(buffer, 0, strlen(buffer));
    recv(clientfd, buffer, sizeof(buffer)-1, 0);
    printf("Confirmation: %s\n", buffer);
    set_str(buffer, "Example String");
    send(clientfd, buffer, strlen(buffer)+1, 0);
    memset(buffer, 0, strlen(buffer));
    recv(clientfd, buffer, sizeof(buffer)-1, 0);
    printf("Confirmation: %s\n", buffer);
    shutdown(clientfd, SHUT_RDWR);
    close(clientfd);

    return 0;
}

void set_str(char* dest, const char* source)
{
    memset(dest, 0, sizeof(dest));
    strcpy(dest, source);
}
