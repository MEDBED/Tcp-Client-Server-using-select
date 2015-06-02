/*
Copyright@Mohamed Bouhamed
Email: med.bouhamed@live.fr
Phone:+216 26 198 178  
*/

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char **argv){
/*---------variable declaration---------------*/
	struct sockaddr_in servaddr;
/*---------this is our socket in order to send our message---------------*/
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
/*---------this a test allow us to know if On error, the socket () function returns -1 and set the global variable errno.---------------*/
	if (sock == -1) 
		perror("Socket");
/*---------The bzero() function sets the first n=sizeof(servaddr) bytes of the area starting at vide
       to zero (bytes containing '\0')---------------*/
	bzero((void *) &servaddr, sizeof(servaddr));
/*---------sticking with AF_INET for socket programming over a network is the safest option---------------*/
  //AF_INET is the address family that is used for the socket we are creating
	servaddr.sin_family = AF_INET;
/*---------htons is the port that is used for the socket we are creating---------------*/
	servaddr.sin_port = htons(6782);
/*---------this the adress of the server---------------*/
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
/*---------test connection to the server if =-1 than there are a error---------------*/
  /*If the socket is in online mode (SOCK_STREAM), connect (), used by clients process causes a connection
   request to the server whose address and size of the address are 
   indicated in the serv_addr and addrlen parameters.
   If the socket is connectionless (SOCK_DGRAM), connect (), used by clients process causes a pseudo-connection:
   the system stores the recipient's address, which will be sent to all datagrams sent
   on this socket descriptor (for send () or write ()) to another pseudo-connection.*/
   if (-1 == connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)))
   	perror("Connect");
/*---------after connection, the client still connected to the server and send their own message---------------*/
   while(1){
   //variable to put the message in
   	char message[500];
    //get the message typing in the terminal
    fgets(message, 50, stdin);
    //the message must be end by \0 end of buffer NULL is consatnt ponit on \0
    message[50] = '\0';
    //send the message 4 param (int socket, const void * buffer, size_t length, int flags)
    send(sock, message, 50, 0);
}
close(sock);
}



















/*
Copyright@Mohamed Bouhamed
Email: med.bouhamed@live.fr
Phone:+216 26 198 178  
*/
