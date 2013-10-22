#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int sock(const char *port,const char *transp, int qlen);

int main()
{
	int sock1,sock2;
	struct sockaddr_in addr_in;
	unsigned int addr_ins = sizeof(addr_in);
	char msg[21];
	int t, i;
	sock1 = sock("2300","TCP",5);
	
	if(sock1 <0)
		return -1;
	while(1)
	{
		sock2 = accept(sock1, (struct sockaddr*)&addr_in, &addr_ins);
		if(sock2 < 0)
			printf("Error of connection");
		else
		{

			while(1)
			{
			 	read(sock2,msg, sizeof(msg));
				write(sock2,msg,sizeof(msg));
				memset(&msg,0,sizeof(msg));
			
			}
			close(sock2);
		}
	}
	close(sock1);
	return 0;
}

int sock(const char *port, const char *transp, int qlen)
{
	struct sockaddr_in sin;
	int s;
	memset(&sin,0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons((unsigned short)atoi(port));
	s = socket(PF_INET, SOCK_STREAM,0);
	
	if(s < 0) 
	{	
		printf("Error of create socket\n");
		return -1;
	}
	if(bind(s,(struct sockaddr*)&sin,sizeof(sin))<0)
	{
		printf("Error of bind\n");
		return -1;
	}
	
	if(listen(s,qlen) < 0)
	{
		printf("Error of listen\n");
		return -1;
	}

	return s;
}
