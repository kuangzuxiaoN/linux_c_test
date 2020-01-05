#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP	"125.217.48.36"
#define SERVER_PORT	37777

int main(int argc, char* argv[])
{
	int ret = 0;
    char buffer[64];
	
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);  //具体的IP地址
    serv_addr.sin_port = htons(SERVER_PORT);  //端口
	
	while(1)
	{
		//创建套接字
		int sock = socket(AF_INET, SOCK_STREAM, 0);
		if(sock < 0)
		{
			printf("[%s][%d]: socket faild !\r\n", __FUNCTION__, __LINE__);
			return -1;
		}
		
		ret = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
		if(ret == 0)
		{
			printf("[%s][%d]: connect success !\r\n", __FUNCTION__, __LINE__);
		}
		else
		{
			printf("[%s][%d]: connect faild !\r\n", __FUNCTION__, __LINE__);
			//关闭套接字
			close(sock);
			return -1;
		}
	   
		//读取服务器传回的数据
		read(sock, buffer, sizeof(buffer));
	   
		printf("Message form server: %s\n", buffer);
	   
		//发送服务器传回的数据
	    write(sock, buffer, sizeof(buffer));
		
		memset(buffer, 0, sizeof(buffer));
		
		//关闭套接字
		close(sock);
	}

    return 0;
}