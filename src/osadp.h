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

void start_osadp(Satellite sat, int port);
void send_publish(int sock, Satellite sat);
int check_received_packet(int sock, bool *cont, Satellite sat);
void forward_publish(int sock, Satellite sat);
long get_current_time();
void reset_rx_packet();

void insertFirst(int key, int data);
struct node* deleteFirst();
struct node* find(int key);
void printList();

#endif