/*
* CS 176A Programming Assignment 3
*
* The command line arguments should be:
* ./EmailSender <recipient address>
*
* NOTE:
* 1- I would like you to hardcode the following:
*	a- Sender address: "MAIL FROM".
*	b- Message you are sending.
* 2- Pass the recipient address "RCPT TO" as a command line argument.
* 3- INCLUDE comments in the code to show what is going on (not too detailed).
* 4- INCLUDE a README file if something did not run properly. That will help you receive partial credit.
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include <netdb.h>
#include <string.h>

#define SMTP_PORT 25
#define MAXLINE 1024 			// NOTE: Can be modified to any size you want.

char *Server_IP = "128.111.41.14"; 	// NOTE: IP of the mail server after running "nslookup -type=MX cs.ucsb.edu".  Hence you will need to change this value.

void main (int argc, char ** argv)
{
	char sendline[MAXLINE], recvline[MAXLINE];
	char recipient_address[MAXLINE]; // "RCPT TO" address.
	char sender_address[MAXLINE];	 // "MAIL FROM" adress.
	char *temp;
	
	if (argc != 2)
	{
		printf("usage: ./EmailSender <recipient address,\"RCPT TO\">\n");
		exit(0);
	}
	strcpy(recipient_address, argv[1]);
			
	/* Establish a TCP connection with the main server */
	int sockfd;
	struct sockaddr_in serveraddr;

	
	
	
	
	
	
	/* Read greeting from the server */
	read(sockfd, recvline, MAXLINE);
	printf("%s\n", recvline);	
	temp = strtok(recvline, " ");
	if (strcmp(temp, "220")!=0)
	{
		printf("220 reply ont received from server.\n");
		exit(0);
	}
	
	/* Send HELO command and get server response */
	strcpy(sendline, "HELO alice\r\n");
	printf("%s\n", sendline);
	write(sockfd, sendline, MAXLINE);
	
	read(sockfd, recvline, MAXLINE);
	printf("%s\n", recvline);
	temp = strtok(recvline, " ");
	if (strcmp(temp, "250")!=0)
	{
		printf("250 reply not received from server.\n");
		exit(0);
	}
	
	// Send MAIL FROM command.
	strcpy(sender_address, "youraddress@cs.ucsb.edu"); 	// NOTE: replace address with your own.
		
	// Send RCPT TO command.
	
	// Send DATA command.
	
	// Send message data.
	
	// End with a single period.
	// Send QUIT command.

	exit(0);	
}  
