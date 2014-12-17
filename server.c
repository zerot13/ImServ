#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <syslog.h>

void WriteBad(int nsockfd);
int WriteOk(int nsockfd);
int ReadData(int nsockfd, FILE *imgFile);
int ReadFileName(int nsockfd, char **fileName);
int ReadHeader(unsigned char *header);

int main()
{
	struct sockaddr_in sAddr, cAddr;
	int port = 10830;

	openlog("slog", LOG_PID|LOG_CONS, LOG_USER);
	syslog(LOG_INFO, "TestTest");

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
		if(nsockfd < 0)
		{
			printf("Socket accept failed\n");
			continue;
		}
		char *fileName;
		if(ReadFileName(nsockfd, &fileName) == 0)
		{
			printf("Current filename: %s\n", fileName);
			if(WriteOk(nsockfd) == -1)
			{
				continue;	
			}
		}
		else
		{
			printf("Error: Bad filename\n");
			WriteBad(nsockfd);
			if(fileName)
			{
				free(fileName);
			}
			continue;
		}
		char *filePath = malloc(strlen("images/") + strlen(fileName) + 1);
		filePath = strcpy(filePath, "images/");
		filePath = strcat(filePath, fileName);
		FILE *imgFile = fopen(filePath, "wb");
		close(nsockfd);
		nsockfd = accept(sockfd, (struct sockaddr *) &cAddr, &cLen);
		if(nsockfd < 0)
		{
			printf("Socket accept failed\n");
			continue;
		}
		if(ReadData(nsockfd, imgFile) == 0)
		{
			printf("Successful transfer: %s\n", fileName);
			if(WriteOk(nsockfd) == -1)
			{
				continue;	
			}
		}
		else
		{
			printf("Failed transfer: %s\n", fileName);
			WriteBad(nsockfd);
		}

		fclose(imgFile);
		free(fileName);
		free(filePath);
		close(nsockfd);
	}
	close(sockfd);
	closelog();
}

int WriteOk(int nsockfd)
{
	char *msg2 = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 2\nConnection: Close\n\nOK";
	int n = send(nsockfd, msg2, strlen(msg2), 0);
	if(n < 0)
	{
		printf("Error writing to sock\n");
		return -1;
	}
	return 0;
}

void WriteBad(int nsockfd)
{
	char *msg2 = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 3\nConnection: Close\n\nBad";
	int n = send(nsockfd, msg2, strlen(msg2), 0);
	if(n < 0)
	{
		printf("Error writing to sock\n");
	}
}

int ReadData(int nsockfd, FILE *imgFile)
{
	int dataRead = 0;
	int contLen;
	unsigned char buffer[4096];
	bzero(buffer, 4096);
	int n = recv(nsockfd, buffer, 4095, 0);
	if(n <= 0)
	{
		printf("No message from sock\n");
		return -1;
	}
	contLen = ReadHeader(buffer);
	if(contLen <= 0)
	{
		printf("No content length\n");
		return -1;
	}
	unsigned char *dataStr = strstr(buffer, "\r\n\r\n");
	if(dataStr == NULL)
	{
		printf("Could not read content data\n");
		return -1;
	}
	dataStr += 4;
	int offset = dataStr - buffer;
	n -= offset;
	while(dataRead < contLen)
	{
		if(offset == 0)
		{
			n = recv(nsockfd, buffer, 4095, 0);
			if(n <= 0)
			{
				printf("No message from sock\n");
				return -1;
			}
		}
		int current;
		for(current = 0; current < n; current++)
		{
			fputc(buffer[current + offset], imgFile);
		}
		dataRead += n;
		offset = 0;
	}
	printf("%i\n", dataRead);
	return 0;
}

int ReadFileName(int nsockfd, char **fileName)
{
	unsigned char buffer[4096];
	bzero(buffer, 4096);
	int n = read(nsockfd, buffer, 4095);
	if(n < 0)
	{
		printf("No message from sock\n");
		return -1;
	}
	int nameLen = ReadHeader(buffer);
	if(nameLen <= 0)
	{
		printf("No content length\n");
		return -1;
	}
	*fileName = malloc(nameLen + 1);

	unsigned char *dataStr = strstr(buffer, "\r\n\r\n");
	if(dataStr == NULL)
	{
		printf("Could not read content data\n");
		return -1;
	}
	dataStr += 4;
	int offset = dataStr - buffer;
	int dataRead = n - offset;
	memcpy(*fileName, dataStr, n - offset);
	while(dataRead < nameLen)
	{
		int n = recv(nsockfd, buffer, 4095, 0);
		if(n <= 0)
		{
			printf("No message from sock\n");
			return -1;
		}
		memcpy(&((*fileName)[dataRead]), buffer, n);
		dataRead += n;
	}
	(*fileName)[nameLen] = '\0';
	return 0;
}

int ReadHeader(unsigned char *header)
{
	char *lengthStr = strstr(header, "Content-Length: ");
	if(lengthStr == NULL)
	{
		printf("Could not read content length\n");
		return -1;
	}
	lengthStr += strlen("Content-Length: ");
	char bfr[100];
	int index = 0;

	while(lengthStr[index] != '\r')
	{
		bfr[index] = lengthStr[index];
		index++;
	}

	bfr[index] = '\0';
	return atoi(bfr);
}

