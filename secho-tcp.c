#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include "inet.h"

main() {
    int sockfd,newsockfd,clilen,n;
	struct sockaddr_in   	cli_addr,serv_addr ;
	char 	             		buffer[1024];

	if ((sockfd = socket(AF_INET, SOCK_STREAM,0)) < 0){
		perror("server: can't open stream socket") ;
		return -1;
		}
  	serv_addr.sin_family        	= AF_INET ;
  	serv_addr.sin_addr.s_addr   	= htonl(0) ;
	serv_addr.sin_port          	= htons(SERV_TCP_PORT) ;
	if (bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) <0) {
		perror("server: can't bind local address") ;
    	return -1;
	}
	listen(sockfd, 5);
	for (;;)  {
	  clilen = sizeof(cli_addr);
	  newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
	  if (newsockfd < 0) {
	    perror("servidor: accept error") ;
	    return -1 ;
	    }
	  bzero(buffer, sizeof(buffer));
     if ((n=recv(newsockfd,buffer,sizeof(buffer),0))<0){
	    perror("ERROR: recv");
	    return -1;
	    }
	  if ((n=send(newsockfd,buffer,strlen(buffer),0))!=strlen(buffer)) {
	    perror("ERROR: send");
	    return -1;
	    }
	  close(newsockfd);
	}
}
