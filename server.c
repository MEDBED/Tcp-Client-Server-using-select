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

int main(int argc, char **argv) {
	//--------------variable declaration--------------
	fd_set fds, readfds;
	char buf[1024];
	int i, clientaddrlen,rval;
	int clientsock[2], rc, numsocks = 0, maxsocks = 5;
/*---------this is our socket in order to receive our message---------------*/
	int serversock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//--------this a test allow us to know if On error, the socket () function returns -1 and set the global variable errno-----
	if (serversock == -1) 
		perror("Socket");
	//----------tow struct of sockadr_in---------------
	struct sockaddr_in serveraddr, clientaddr;  
	//--------------filling our structure-------------
	bzero(&serveraddr, sizeof(struct sockaddr_in));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(6782);
	//---------test if  the bind is done, It takes three arguments, the socket file descriptor,
	// the address to which is bound, and the size of the address to which it is bound--------
	if (-1 == bind(serversock, (struct sockaddr *)&serveraddr,sizeof(struct sockaddr_in))) 
		perror("Bind");
	//------The listen system call allows the process to listen on the socket for connections. The first argument 
	//is the socket file descriptor, and the second is the size of the backlog queue, 
	//the number of connections that can be waiting while the process is handling a particular connection-------------
	if (-1 == listen(serversock, SOMAXCONN))
		perror("Listen");
    //clears a set.
	FD_ZERO(&fds);
    //add a given file descriptor from a set
    FD_SET(serversock, &fds);
    printf(" Our Server is Listening !\n");
    while(1) {
    	readfds = fds;
    	/*select() and pselect() allow a program to monitor multiple file descriptors, 
        waiting until one or more of the file descriptors become "ready" for some class of 
        I/O operation (e.g., input possible). A file descriptor is considered ready 
        if it is possible to perform the corresponding I/O operation (e.g., read(2)) without blocking. */
        rc = select(FD_SETSIZE, &readfds, NULL, NULL, NULL);
        //test if there are a error
        if (rc == -1) {
        	perror("Select");
        	break;
        }
		//---------------------------------------
        for (i = 0; i < FD_SETSIZE; i++) {
        	//tests to see if a file descriptor is part of the set; this is useful after select() returns. 
        	if (FD_ISSET(i, &readfds)){
        		//test if there are a client is connected and a file descriptor is active
        		if (i == serversock){
        			//test if we got the max number of client
        			if (numsocks < maxsocks){
        				clientsock[numsocks] = accept(serversock,(struct sockaddr *) &clientaddr,(socklen_t *)&clientaddrlen);
        				if (clientsock[numsocks] == -1)
        				 perror("Accept");
        				FD_SET(clientsock[numsocks], &fds);
        				numsocks++;
        			}else{
        				printf("Ran out of socket space.\n");
        				goto out;
        			}
        		}else{
        			bzero(buf, sizeof(buf));
        			if ((rval = read(i, buf, 1024)) < 0){
        				perror("reading stream message");
        				goto out;
        			}
        			else if (rval == 0){
        				printf("Ending connection\n");
        				goto out;
        			}
        			else
        				printf("-->%s\n", buf);
        		}
        	}
        }
    }
    out:close(serversock);
    return 0;
}
























/*
Copyright@Mohamed Bouhamed
Email: med.bouhamed@live.fr
Phone:+216 26 198 178  
*/
