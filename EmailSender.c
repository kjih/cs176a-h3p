/*
* Kevin Jih
* Fall 2015
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
* TCP Client Code Referenced From: "TCP/IP Sockets in C"
* 	Authors: Michael J. Donahoo, Kenneth L. Calvert
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

int main (int argc, char ** argv)
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
	strcpy(recipient_address, argv[1]);		// set "RCPT TO" address.

	/* See if code runs until here */
	//printf("about to establish TCP connection...");

	/* Establish a TCP connection with the main server */
	int sockfd;							// Socket descriptor.
	struct sockaddr_in serveraddr;		// Server address.
	unsigned short serverPort;			// Server Port.
	char *serverIP;						// Server IP.

	serverPort = 25;	// set Port to 25, default SMTP port.
	serverIP = Server_IP;

	/* Create reliable, stream socket using TCP */
	if ((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		printf("socket() failed");
		return 0;
	}

	/* See if code runs until here */
	//printf("socket() successful");

	/* Construct the server address structure */
	memset(&serveraddr, 0, sizeof(serveraddr));			// Zero out structure.
	serveraddr.sin_family 		= AF_INET;				// Internet address family.
	serveraddr.sin_addr.s_addr 	= inet_addr(serverIP);	// Server IP address.
	serveraddr.sin_port 		= htons(serverPort);	// Server port.

	/* Establish the connection to the server */
	if (connect(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) {
		printf("connect() failed");
		return 0;
	}
	
	/* See if code runs until here */
	printf("connect() successful");

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
	strcpy(sendline, "HELO kjih\r\n");
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
	strcpy(sender_address, "kjih@umail.ucsb.edu"); 	// NOTE: replace address with your own.
	
	//strcpy(sendline, "MAIL FROM: <alice@crepes.fr>\r\n");
	//strcpy(sendline, "MAIL FROM: <kjih@umail.ucsb.edu>\r\n");
	strcpy(sendline, "MAIL FROM: <");
	strcat(sendline, sender_address);
	strcat(sendline, ">\r\n");
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
		
	// Send RCPT TO command.
	strcpy(sendline, "RCPT TO: <");
	strcat(sendline, recipient_address);
	strcat(sendline, ">\r\n");
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

	
	// Send DATA command.
	strcpy(sendline, "DATA");
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
	
	// Send message data.
	
	// End with a single period.
	// Send QUIT command.

	exit(0);	
}  
