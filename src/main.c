#include <stdio.h>
#include <stdlib.h>
#include "client_create.h"

int main(int argc, char** argv)
{
    /* if(argc < 3)
    {
        printf("Usage: %s [ip addr] [port number]\n", argv[0]);
        return -1;
    } */

    char ip_addr[32], portnum[8];;

    printf("Server IP address: ");
    fgets(ip_addr, sizeof(ip_addr)-1, stdin);

    printf("Server port number: ");
    fgets(portnum, sizeof(portnum)-1, stdin);

    CLIENT client;
    __init_client(&client);

    client.set_server(&client, ip_addr, atoi(portnum));

    client.load_file(&client);
    client.send_file(&client);

    printf("File name: %s\n", client.filename);
    printf("File content: %s\n", client.filecontent);

    return 0;
}
