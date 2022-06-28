#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <signal.h>

typedef struct clients {
	int id;
	int fd;
}	clients;

clients client[1024];
char buff[1000000], msg[1000000];
int sockfd, fdmax, gid;
fd_set memS, rS, wS;

void fatal(int err) 
{
	printf("%d\n", err);
	write(2, "Fatal Error \n", 12);
	exit(1);	
}

void send_to_all(int fromId)
{
	for (int i = 0; i < gid; i++)
		if (client[i].id != fromId && client[i].fd > 0 && FD_ISSET(client[i].fd, &wS))
			 (send(client[i].fd, msg, strlen(msg), 0));
				// fatal(6);
	bzero(msg, sizeof(msg));
}

void add_client()
{
	int i = 0;
	while(i < 1024 && client[i].fd > 0)
		i++;
	struct sockaddr_in cliaddr;
	socklen_t len;
	if ((client[i].fd = accept(sockfd, (struct sockaddr *)&cliaddr, &len)) < 0)
		fatal(0);
	FD_SET(client[i].fd, &memS);
	client[i].id = gid++;
	if(client[i].fd > fdmax)
		fdmax = client[i].fd;
	sprintf(msg, "server: client %d just arrived\n", client[i].id);
	send_to_all(client[i].id);
}

void send_msg(fromId)
{
	int i = 0, j = 0;
	int len = strlen(buff);
	char tmp[100000] = {0};
	while (i < len)
	{
		tmp[j++] = buff[i];
		if (buff[i++] == '\n')
		{
			sprintf(msg + strlen(msg), "client %d: %s", fromId, tmp);
			bzero(tmp, sizeof(tmp));
			j = 0;
		}
	}
	send_to_all(fromId);
}

int main(int ac, char** av) 
{
	signal(SIGPIPE, SIG_IGN);

	if (ac != 2)
		return(write(2, "Wrong number of arguments\n", 26));
	struct sockaddr_in servaddr; 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1)
	   fatal(1);	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1])); 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		fatal(2);
	if (listen(sockfd, 128) != 0)
		fatal(3);
	fdmax = sockfd;
	FD_ZERO(&memS);
	FD_SET(sockfd, &memS);
	while(1)
	{
		rS = wS = memS;
		if (select(fdmax + 1, &rS, &wS, NULL, NULL) < 0)
			fatal(4);
		if (FD_ISSET(sockfd, &rS))
			add_client();	
		for (int i = 0; i < gid; i++)
		{
			if (client[i].fd < sockfd || !FD_ISSET(client[i].fd, &rS))
					continue;
			int rval = 1;
			bzero(buff, sizeof(buff));
			while(rval == 1 && client[i].fd)
			{
				rval = recv(client[i].fd, buff + strlen(buff), 1, 0);
				if (buff[strlen(buff) - 1] == '\n')
					break;
			}
			// printf("buff=[%s]\n", buff);
			if (rval == 0)
			{
				sprintf(msg, "server: client %d just left\n", client[i].id);
				send_to_all(client[i].id);
				close(client[i].fd);
				FD_CLR(client[i].fd, &memS);
				client[i].fd = -1;
				client[i].id = -1;
			}
			else if (rval)
				send_msg(client[i].id);
		}
	}
}