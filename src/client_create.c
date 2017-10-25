#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "client_create.h"

/* Constructor */
void __init_client(CLIENT* this)
{
    this->set_server = CLIENT_set_server;
    this->load_file = CLIENT_load_file;
    this->send_file = CLIENT_send_file;
    this->load_filecontent = CLIENT_load_filecontent;
    this->create_socket = CLIENT_create_socket;
    this->connect_to_server = CLIENT_connect_to_server;
    this->send_data = CLIENT_send_data;

    memset(this->filename, 0, sizeof(this->filename));
    memset(this->filecontent, 0, sizeof(this->filecontent));
}

/* Public funcs */
void CLIENT_set_server(CLIENT* this, char* ip_addr, int portnum)
{
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_addr.s_addr = inet_addr(ip_addr);
    this->server_addr.sin_port = htons(portnum);
}

void CLIENT_load_file(CLIENT* this)
{
    memset(this->filename, 0, sizeof(this->filename));
    memset(this->filecontent, 0, sizeof(this->filecontent));

    printf("File name: ");
    fgets(this->filename, sizeof(this->filename)-1, stdin);
    this->filename[strlen(this->filename)-1] = '\0';
    this->load_filecontent(this);
}

int CLIENT_send_file(CLIENT* this)
{
    this->create_socket(this);
    this->connect_to_server(this);
    if(this->send_data(this, this->filename) == 0)
    {
        return 0;
    }
    if(this->send_data(this, this->filecontent) == 0)
    {
        return 0;
    }
    return 1;
}





/* Private funcs */
void CLIENT_load_filecontent(CLIENT* this)
{
    FILE* fp = fopen(this->filename, "rb");
    if(fp != NULL)
    {
        int size, num_read;
        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        printf("Size: %d\n", size);
        fseek(fp, 0, SEEK_SET);
        num_read = fread(this->filecontent, 1, size, fp);
        printf("Num bytes read: %d\n", num_read);
        fclose(fp);
    }
}

void CLIENT_create_socket(CLIENT* this)
{
    this->clientfd = socket(AF_INET, SOCK_STREAM, 0);
}

int CLIENT_connect_to_server(CLIENT* this)
{
    if(connect(this->clientfd, (struct sockaddr *)&this->server_addr, sizeof(this->server_addr)) >= 0)
    {
        return 1;
    }
    return 0;
}

int CLIENT_send_data(CLIENT* this, char* data)
{
    char recv_buf[32];
    memset(recv_buf, 0, sizeof(recv_buf));

    send(this->clientfd, data, strlen(data)+1, 0);
    recv(this->clientfd, recv_buf, sizeof(recv_buf)-1, 0);
    if(!strcmp(recv_buf, "Received"))
    {
        return 1;
    }
    return 0;
}

