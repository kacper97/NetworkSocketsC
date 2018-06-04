/* Cliente de ECO sobre TCP */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include "inet.h"

main() {
	int           		sockfd, n;
	struct sockaddr_in     	serv_addr ;
	char 		 	serv_host_addr[30],buffer[1024];

	printf("Dirección IP del servidor (a.b.c.d) => ");
    	gets(serv_host_addr);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("client: can't open stream socket") ;
		return -1;
		}

	serv_addr.sin_family        	= AF_INET ;
	serv_addr.sin_addr.s_addr   = inet_addr(serv_host_addr);
	serv_addr.sin_port          	= htons(SERV_TCP_PORT) ;
   	if (connect(sockfd, (struct sockaddr *) &serv_addr,
				sizeof(serv_addr)) != 0)  {
		perror("client: can't connect with server") ;
		return -1;
	}
	printf("Bienvenido al Servicio de ECO ==>\n"); 
	gets(buffer);

	if ((n=send(sockfd,buffer,strlen(buffer),0))!=strlen(buffer)) {
	  perror("client: error in send");
	  return -1;
  	}
	printf("Cliente: envie %d bytes\n",n);
    	bzero(buffer,sizeof(buffer));
	if ((n=recv(sockfd,buffer,sizeof(buffer),0)) < 0) {
	  perror("client: error in recv\n");
	  return -1;
	}
	printf("ECO:  %s (%d bytes)\n",buffer,n) ;
	close(sockfd);
}
