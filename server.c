#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_IP	"127.0.0.1"
#define SERVER_PORT	37777

int main(int argc, char* argv[])
{
	char str[] = {"Hello, I'm Server !"};
	
    //创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);  //具体的IP地址
    serv_addr.sin_port = htons(SERVER_PORT);  //端口
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    //进入监听状态，等待用户发起请求
    if(listen(serv_sock, 20) != 0)
	{
		printf("listen() Error : %s\r\n", stderror(errno));
		return -1;
	}

	while(1)
	{
		//接收客户端请求
		struct sockaddr_in clnt_addr;
		bzero(&clnt_addr, sizeof(clnt_addr));
		socklen_t clnt_addr_size = sizeof(clnt_addr);
		int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
		if(clnt_sock < 0)
		{
			printf("accept() Error : %s\r\n", stderror(errno));
			return -1;
		}

		//向客户端发送数据
		write(clnt_sock, str, sizeof(str));
	   
		//关闭套接字
		close(clnt_sock);
	}
	
	
    close(serv_sock);

    return 0;
}





