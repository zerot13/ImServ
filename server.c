#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <syslog.h>
#include <time.h>
#include <signal.h>

#include "logger.h"
#include "dbops.h"

void WriteBad(int nsockfd);
int WriteOk(int nsockfd);
void GetFilePath(char **filePath, char *fileName);
int ReadData(int nsockfd, FILE *imgFile);
int ReadFileName(int nsockfd, char **fileName);
int ReadHeader(unsigned char *header);

void INThandler(int);
int sockfd;

int main()
{
	struct sockaddr_in sAddr, cAddr;
	int port = 10830;

	openlog("imserv", LOG_PID|LOG_CONS, LOG_LOCAL7);
	LogInfo("Starting file server.");
	
	signal(SIGINT, INThandler);

	CreateDatabase();

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		LogError("Socket creation failed.");
		exit(1);
	}

	bzero((char *) &sAddr, sizeof(sAddr));
	sAddr.sin_family = AF_INET;
	sAddr.sin_addr.s_addr = INADDR_ANY;
	sAddr.sin_port = htons(port);	
	int result = bind(sockfd, (struct sockaddr *) &sAddr, sizeof(sAddr));
	if(result != 0)
	{
		LogError("Error while binding: %s", strerror(errno));
		exit(1);
	}
	result = listen(sockfd, 5);
	if(result != 0)
	{
		LogError("Error on listen: %s", strerror(errno));
		exit(1);
	}

	socklen_t cLen = sizeof(cAddr);
	while(1)
	{
		int nsockfd = accept(sockfd, (struct sockaddr *) &cAddr, &cLen);
		if(nsockfd < 0)
		{
			LogError("Socket accept failed");
			continue;
		}
		char *fileName;
		if(ReadFileName(nsockfd, &fileName) == 0)
		{
			LogInfo("Current filename: %s", fileName);
			if(WriteOk(nsockfd) == -1)
			{
				continue;	
			}
		}
		else
		{
			LogError("Error: Bad filename");
			WriteBad(nsockfd);
			if(fileName)
			{
				free(fileName);
			}
			continue;
		}
		char *filePath;
		GetFilePath(&filePath, fileName);

		FILE *imgFile = fopen(filePath, "wb");
		close(nsockfd);
		nsockfd = accept(sockfd, (struct sockaddr *) &cAddr, &cLen);
		if(nsockfd < 0)
		{
			LogError("Socket accept failed");
			continue;
		}
		if(ReadData(nsockfd, imgFile) == 0)
		{
			LogInfo("Successful transfer: %s", fileName);
			if(WriteOk(nsockfd) == -1)
			{
				continue;	
			}
		}
		else
		{
			LogError("Failed transfer: %s", fileName);
			WriteBad(nsockfd);
		}

		fclose(imgFile);
		free(fileName);
		free(filePath);
		close(nsockfd);
	}
	LogInfo("File Server stopping");
	close(sockfd);
	closelog();
}

void GetFilePath(char **filePath, char *fileName)
{
	char str_date[20];
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	strftime(str_date, sizeof(str_date), "%m-%d-%Y/", t);

	*filePath = malloc(strlen("images/") + strlen(str_date) + strlen(fileName) + 1);

	*filePath = strcpy(*filePath, "images/");
	mkdir(*filePath, 0777);
	*filePath = strcat(*filePath, str_date);
	mkdir(*filePath, 0777);
	*filePath = strcat(*filePath, fileName);
}

int WriteOk(int nsockfd)
{
	char *msg2 = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 2\nConnection: Close\n\nOK";
	int n = send(nsockfd, msg2, strlen(msg2), 0);
	if(n < 0)
	{
		LogError("Error writing to socket");
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
		LogError("Error writing to socket");
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
		LogError("No message from socket");
		return -1;
	}
	contLen = ReadHeader(buffer);
	if(contLen <= 0)
	{
		LogError("No content length");
		return -1;
	}
	unsigned char *dataStr = strstr(buffer, "\r\n\r\n");
	if(dataStr == NULL)
	{
		LogError("Could not read content data");
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
				LogError("No message from socket");
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
	
	LogInfo("Data read: %i", dataRead);
	return 0;
}

int ReadFileName(int nsockfd, char **fileName)
{
	unsigned char buffer[4096];
	bzero(buffer, 4096);
	int n = read(nsockfd, buffer, 4095);
	if(n < 0)
	{
		LogError("No message from sock");
		return -1;
	}
	int nameLen = ReadHeader(buffer);
	if(nameLen <= 0)
	{
		LogError("No content length");
		return -1;
	}
	*fileName = malloc(nameLen + 1);

	unsigned char *dataStr = strstr(buffer, "\r\n\r\n");
	if(dataStr == NULL)
	{
		LogError("Could not read content data");
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
			LogError("No message from sock");
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
		LogError("Could not read content length");
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

void INThandler(int sig)
{
	signal(sig, SIG_IGN);
	close(sockfd);
	closelog();
	exit(1);
}
