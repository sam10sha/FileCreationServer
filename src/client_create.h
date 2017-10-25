#ifndef CLIENT_CREATE_H
#define CLIENT_CREATE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

typedef struct CLIENT_struct CLIENT;

struct CLIENT_struct{
    int clientfd;
    struct sockaddr_in server_addr;
    char filename[128];
    char filecontent[1024];

    /* public funcs */
    void (*set_server)(CLIENT* this, char* ip_addr, int portnum);
    void (*load_file)(CLIENT* this);
    void (*send_file)(CLIENT* this);

    /* private funcs */
    void (*load_filecontent)(CLIENT* this);
};





/* Constructor for the CLIENT struct */
void __init_client(CLIENT* this);


/* Public funcs */
/* Sets the address of the server */
void CLIENT_set_server(CLIENT* this, char* ip_addr, int portnum);

/* Get the file name */
void CLIENT_load_file(CLIENT* this);

/* Sends the file to the server */
void CLIENT_send_file(CLIENT* this);




/* Private funcs */
/* Loads the contents of the specified file into the filecontents buffer */
void CLIENT_load_filecontent(CLIENT* this);

#endif
