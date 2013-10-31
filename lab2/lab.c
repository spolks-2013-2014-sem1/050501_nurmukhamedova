#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int sock(char* port,const char *transp);

int main(int argc, char** argv)
{
	int sock_s,sock_c;
	struct sockaddr_in addr_in;
	unsigned int addr_ins = sizeof(addr_in);
	char msg[2048];
	int r_byte;
	char *port = argv[1];
	 
	sock_s = sock(port,"TCP");
	memset(&msg,0,sizeof(msg));

	if(sock_s <0)
		return -1;
	while(1)
	{
		sock_c = accept(sock_s, (struct sockaddr*)&addr_in, &addr_ins);
		if(sock_c < 0)
			printf("Error of connection");
		else
		{
			while(1)
			{
			 	r_byte = read(sock_c,msg, sizeof(msg));
				if(r_byte == 2)
				{
					close(sock_c); 
					break;
				}
				write(sock_c,msg,sizeof(msg));
				memset(&msg,0,sizeof(msg));
			
			}
		}
	}
	close(sock_s);
	return 0;
}

int sock(char* port, const char *transp)
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
	
	if(listen(s,5) < 0)
	{
		printf("Error of listen\n");
		return -1;
	}

	return s;
}
