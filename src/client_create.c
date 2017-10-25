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
    printf(">>> ");
    fgets(this->filename, sizeof(this->filename)-1, stdin);
    this->filename[strlen(this->filename)-1] = '\0';
    this->load_filecontent(this);
}

void CLIENT_send_file(CLIENT* this)
{
    
}





/* Private funcs */
void CLIENT_load_filecontent(CLIENT* this)
{
    FILE* fp = fopen(this->filename, "rb");
    if(fp != NULL)
    {
        int size;
        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        fread(this->filecontent, 1, size, fp);
        fclose(fp);
    }
}

