#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>

#include <signal.h>

typedef struct client {
	int id;
	int fd;
}	client;

client clients[10000];
char buf[1000000], msg[1000000];
int sockfd, id, fd_max;
fd_set mem_s, r_s, w_s;

void fatal(int err) {
	printf("%d\n", err);
	write(1, "Fatal error\n", 12);
	exit(1);
}

int init_server(int port)
{
	struct sockaddr_in serv_addr;
	serv_addr.sin_family		= AF_INET;
	serv_addr.sin_addr.s_addr	= 16777343; 
	serv_addr.sin_port			= htons(port);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ||\
		 bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0 ||\
		 listen(sockfd, 128) < 0)
		fatal(0);
	
	return sockfd;
}

void send_all(int id_from)
{
	for (int i = 0; i < id; i++)
		if (clients[i].id != id_from  && clients[i].fd > sockfd && FD_ISSET(clients[i].fd, &w_s))
			send(clients[i].fd, msg, strlen(msg), 0);
	bzero(msg, sizeof(msg));
}

void add_client()
{
	int i = 0;
	while (clients[i].fd > 0 && i < 100000)
		i++;
	struct sockaddr_in client_addr;
	socklen_t len;
	if ((clients[i].fd = accept(sockfd, (struct sockaddr*)&client_addr, &len)) < 0)
		fatal(1);
	FD_SET(clients[i].fd, &mem_s);
	clients[i].id = id++;
	if (clients[i].fd > fd_max)
		fd_max = clients[i].fd;
	sprintf(msg, "server: client %d just arrived\n", clients[i].id);
	send_all(clients[i].id);
}

void send_msg(int id_from)
{
	int i = 0, j = 0;
	int len = strlen(buf);
	char tmp[100000] = {0};
	while (i < len)
	{
		tmp[j++] = buf[i];
		if (buf[i++] == '\n')
		{
			sprintf(msg + strlen(msg), "client %d: %s", id_from, tmp);
			bzero(tmp, sizeof(tmp));
			j = 0;
		}
	}
	//add or don't add the '\n' here
	send_all(id_from);
}

int main(int argc, char **argv)
{
	signal(SIGPIPE, SIG_IGN);
	if (argc != 2)
		return (write(1, "Wrong number of arguments\n", 26) && 1);

	fd_max = sockfd = init_server(atoi(argv[1]));
	FD_ZERO(&mem_s);
	FD_SET(sockfd, &mem_s);

	while (1)
	{
		r_s = w_s = mem_s;
		if (select(fd_max + 1, &r_s, &w_s, NULL, NULL) < 0)
			fatal(2);
		if (FD_ISSET(sockfd, &r_s))
			add_client();
		for (int i = 0; i < id; i++)
		{
			if (clients[i].fd < sockfd || !FD_ISSET(clients[i].fd, &r_s))
				continue ;
			int rval = 1;
			bzero(buf, sizeof(buf));
			while (rval == 1)
			{
				rval = recv(clients[i].fd, buf + strlen(buf), 1, 0);
				if (buf[strlen(buf) - 1] == '\n')
					break;
			}
			if (rval == 0)
			{
				sprintf(msg, "server: client %d just left\n", clients[i].id);
				send_all(clients[i].id);
				close(clients[i].fd);
				FD_CLR(clients[i].fd, &mem_s);
				clients[i].id = -1;
				clients[i].fd = -1;
			}
			else if (rval)
				send_msg(clients[i].id);
			break;
		}
	}
}