/*
 * getSensorData.c
 *
 *  Created on: 20 Apr 2018
 *      Author: ralfh
 */

#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */

/* Global variable */
char data[1000];


char* getSensorData (char* hostAddress, int port, char* uri)
{
	    char *host = hostAddress;
	    int portno = port;

	    char message_fmt[1024];

	    strcpy (message_fmt,"GET ");
	    strcat(message_fmt, uri);
	    strcat(message_fmt," HTTP/1.0\r\n\r\n");

	    struct hostent *server;
	    struct sockaddr_in serv_addr;
	    int sockfd, bytes, sent, received, total;
	    char message[1024],response[4096];

	    /* fill in the parameters */
	    sprintf(message,message_fmt,hostAddress,port);
	    //printf("Request:\n%s\n",message);

	    /* create the socket */
	    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	    if (sockfd < 0) error("ERROR opening socket");

	    /* lookup the ip address */
	    server = gethostbyname(host);
	    if (server == NULL) error("ERROR, no such host");

	    /* fill in the structure */
	    memset(&serv_addr,0,sizeof(serv_addr));
	    serv_addr.sin_family = AF_INET;
	    serv_addr.sin_port = htons(portno);
	    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

	    /* connect the socket */
	    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
	        error("ERROR connecting");

	    /* send the request */
	    total = strlen(message);
	    sent = 0;
	    do {
	        bytes = write(sockfd,message+sent,total-sent);
	        if (bytes < 0)
	            error("ERROR writing message to socket");
	        if (bytes == 0)
	            break;
	        sent+=bytes;
	    } while (sent < total);

	    /* receive the response */
	    memset(response,0,sizeof(response));
	    total = sizeof(response)-1;
	    received = 0;
	    do {
	        bytes = read(sockfd,response+received,total-received);
	        if (bytes < 0)
	            error("ERROR reading response from socket");
	        if (bytes == 0)
	            break;
	        received+=bytes;
	    } while (received < total);

	    if (received == total)
	        error("ERROR storing complete response from socket");

	    /* close the socket */
	    close(sockfd);

	    /* process response */
	    //printf("Response:\n%s\n",response);

	    strcpy(data,response);

	return data;
}
