#include <stdio.h>
#include <stdlib.h>
#include "client_create.h"

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        printf("Usage: %s [ip addr] [port number]\n", argv[0]);
        return -1;
    }

    CLIENT client;
    __init_client(&client);

    client.set_server(&client, argv[1], atoi(argv[2]));
    client.load_file(&client);
    client.send_file(&client);

    printf("File name: %s\n", client.filename);
    printf("File content: %s\n", client.filecontent);

    return 0;
}
