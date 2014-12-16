#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

void WriteBad(int nsockfd);
void WriteOk(int nsockfd);
int ReceiveFileName(int nsockfd, char **fileName);
int ReadHeader(int nsockfd);

int main()
{
	struct sockaddr_in sAddr, cAddr;
	int port = 10830;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		printf("Socket creation failed\n");
		exit(1);
	}

	bzero((char *) &sAddr, sizeof(sAddr));
	sAddr.sin_family = AF_INET;
	sAddr.sin_addr.s_addr = INADDR_ANY;
	sAddr.sin_port = htons(port);	
	int result = bind(sockfd, (struct sockaddr *) &sAddr, sizeof(sAddr));
	if(result != 0)
	{
		printf("Error: %s\n", strerror(errno));
		exit(1);
	}
	result = listen(sockfd, 5);
	if(result != 0)
	{
		printf("Error: %s\n", strerror(errno));
		exit(1);
	}

	socklen_t cLen = sizeof(cAddr);
	while(1)
	{
		printf("Waiting for accept\n");
		int nsockfd = accept(sockfd, (struct sockaddr *) &cAddr, &cLen);
		printf("Reading new filename\n");
		if(nsockfd < 0)
		{
			printf("Socket accept failed\n");
			exit(1);
		}
		char *fileName;
		if(ReceiveFileName(nsockfd, &fileName) == 0)
		{
			printf("Good filename: %s\n", fileName);
			WriteOk(nsockfd);
		}
		else
		{
			printf("Bad filename\n");
			WriteBad(nsockfd);
			continue;
		}
		FILE *imgFile = fopen(fileName, "wb");
		close(nsockfd);
		nsockfd = accept(sockfd, (struct sockaddr *) &cAddr, &cLen);
		if(nsockfd < 0)
		{
			printf("Socket accept failed\n");
			exit(1);
		}
		int cntLength = ReadHeader(nsockfd);
		unsigned char buffer[4096];
		bzero(buffer, 4096);
		int read2 = 0;
		printf("Reading %s - %i\n", fileName, cntLength);
		while(read2 < cntLength)
		{
			//fprintf(stderr, "%i ", read2);
			int n = recv(nsockfd, buffer, 4095, 0);
			if(n <= 0)
			{
				printf("No message from sock\n");
				break;
			}
			read2 += n;
			int current;
			for(current = 0; current < n; current++)
			{
				fputc(buffer[current], imgFile);
			}
		}
		printf("\n");
		WriteOk(nsockfd);
		close(nsockfd);
	}
	close(sockfd);
}

void WriteOk(int nsockfd)
{
	char *msg2 = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 2\nConnection: Close\n\nOK";
	int n = send(nsockfd, msg2, strlen(msg2), 0);
	if(n < 0)
	{
		printf("Error writing to sock\n");
		exit(1);
	}
}

void WriteBad(int nsockfd)
{
	char *msg2 = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 3\nConnection: Close\n\nBad";
	int n = send(nsockfd, msg2, strlen(msg2), 0);
	if(n < 0)
	{
		printf("Error writing to sock\n");
		exit(1);
	}
}

int ReceiveFileName(int nsockfd, char **fileName)
{
	int nameLen = ReadHeader(nsockfd);
	if(nameLen <= 0)
	{
		printf("No content length\n");
		return -1;
	}
	*fileName = malloc(nameLen + 1);
	int n = read(nsockfd, *fileName, nameLen);
	if(n < 0)
	{
		printf("No message from sock\n");
		return -1;
	}
	return 0;
}

int ReadHeader(int nsockfd)
{
	unsigned char header[4096];
	bzero(header, 4096);
	int n = read(nsockfd, header, 4095);
	if(n < 0)
	{
		printf("No message from sock\n");
		return -1;
	}
	printf("Header: %s\nEnd-Header\n", header);
	char *lengthStr = strstr(header, "Content-Length: ");
	if(lengthStr == NULL)
	{
		printf("Could not read content length\n");
		return -1;
	}
	lengthStr += strlen("Content-Length: ");
	char bfr[100];
	int index = 0;
	while(lengthStr[index] != '\n')
	{
		bfr[index] = lengthStr[index];
		index++;
	}
	bfr[index] = '\0';
	return atoi(bfr);
}

