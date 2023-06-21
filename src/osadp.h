#ifndef OSADP_H
#define OSADP_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT_1 8888
#define PORT_2 8889
#define PORT_3 8880

#define SERVICE_TYPE_NOT_DEFINED -1
#define SERVICE_TYPE_STORAGE 0
#define SERVICE_TYPE_DOWNLOAD 1

#define BUFFER_SIZE 100

#define OSADP_PROT_NUMBER 1

#define PUBLISHING_PERIOD 10
#define OSADP_PROTOCOL_SLEEP 0.5

#define HOP_LIMIT 5

#define SERVICE_LIFETIME 600

typedef struct
{
    int id_satellite;   /* id of the satellite that send the packet */
    int id_satellite_forward;  /* id of the satellite that send the service  */
    int service;
    int protocol_number;
    int hop_limit;
    long creation_date;
} Packet;

typedef struct{
    int available_service;
    int type_of_service_available;
    int m_service_type_interest;
    int id_satellite;

}Satellite;

/**
* Triggers the execution of the OSADP protocol. This fuction is the main function
* of the protocol execution. It starts the algorithm. 
*/
void start_osadp(Satellite sat, int port);

/**
* Transfers a PUBLISH message through a socket. It fills the different fields of the 
* packet and trasnfer it through a UDP socket. 
*/
void send_publish(int sock, Satellite sat);

/**
* Retrieves the packet from the socket. It stores the received packet into a structure,
* and also evaluates if the packet follows the OSADP protocol. 
*/
int check_received_packet(int sock, bool *cont, Satellite sat);

/**
* Propagates the received PUBLISH packet. After modifying the corresponding fields of
* the packet, it sends it through a UDP socket.
*/
void forward_publish(int sock, Satellite sat);

/**
* Provides the system time in UTC.
*/
long get_current_time();

/**
* Cleans the structure of the packet. The packets are stored in the same structure
* to recycle memory. In this case, this function cleans this structure and ensures
* that no old values may interfere.
*/
void reset_rx_packet();

/**
* Insert the item at the beginning of the service table.
*/
void insertFirst(int key, int data);

/**
* Delete the first item of the service table.
*/
struct node* deleteFirst();

/**
* Find the service associated to the key
*/
struct node* find(int key);

/**
* Prints statistics and configuration of the OSDAP. This print is currently done 
* through the stdout.
*/
void printList();

#endif