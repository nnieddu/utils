#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

typedef struct client
{
	int id;
	int fd;
}	client;

client clients[10000];
int sockfd;
int gid = 0;
int maxfd = 1;
fd_set s_set, w_set, r_set;
char buff[1000000];
char msg[42];

void fatal()
{
	write(2, "Fatal error\n", 12);
	close(sockfd);
	exit(1);
}


void send_all(int ufd, char *str_req)
{
	int i = 0;
    while (i <= gid)
    {
        if (ufd != clients[i].fd && clients[i].fd > 0 && FD_ISSET(clients[i].fd, &w_set))
        {
            if (send(clients[i].fd, str_req, strlen(str_req), 0) < 0)
                fatal();
        }
      	i++;
		printf("i send all ===%d\n", i);
    }
}

void parse_msg(char *usr_msg)
{
	return;
}

int main(int ac, char **av) 
{
	struct sockaddr_in servaddr, cli; 
	int connfd = -1;

	if (ac != 2)
		return (write(2, "Wrong number of arguments\n", 26) && 1);
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1)
		fatal();
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1])); 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		fatal(); 
	if (listen(sockfd, 10) != 0)
		fatal();
	FD_ZERO(&s_set);
	FD_SET(sockfd, &s_set);
	maxfd = sockfd;
	while(1)
	{	
		w_set = r_set = s_set;
		select(maxfd + 1, &r_set, &w_set, NULL, NULL);
		for (int i = 0; i <= gid; i++)
		{
			if(FD_ISSET(sockfd, &r_set))
			{
				int j = 0; 
				while (j <= gid && clients[j].fd > 0)
				   	j++;
				socklen_t len = sizeof(cli);
				connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
				if (connfd < 0)
					fatal();
				clients[j].fd = connfd;
				clients[j].id = gid;
				gid++;
				FD_SET(connfd, &s_set);
				if (connfd > 0 && maxfd < connfd)
					maxfd = connfd;
				connfd = -1;
				sprintf(msg, "server: client %d just arrived\n", gid);
				send_all(gid, msg);
				bzero(&msg, sizeof(msg));
				break;
			}
			/*else
			{
				int ret = 0;
				ret = recv(clients[i].fd, buff, 1000000, 0);
				if (ret <=0)
				{
                    sprintf(msg, "server: client %d just left\n", clients[i].id);
					FD_CLR(clients[i].fd, &s_set);
					send_all(clients[i].fd, msg);
					close(clients[i].fd);
					clients[i].fd = -1;
					bzero(&msg, sizeof(msg));
					clients[i].id = -1;
					break;
				}
			}
			parse_msg(buff);
		*/
		}
	}
}
