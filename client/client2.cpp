// client.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#else 
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif
int main(int argc, char** argv)
{
    int server_sock;
    int client_sock;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    std::string message(30,0);
    if (argc != 3) {
        std::cout << "port:" << argv[0] << "\n";
        return 0;
    }
    client_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (client_sock == -1) {
        std::cout << "socket error \n";
    }
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(argv[1]);
    client_addr.sin_port = htons(atoi(argv[2]));
    if (connect(client_sock, (struct sockaddr*)&client_addr, sizeof(client_addr)) == -1) {
        std::cout << "connect error \n";
    }
    int str_len = 0;
    int read_len = 0;
    int index = 0;
    
    while (read_len=read(client_sock, (void*)(message.c_str()+index++), 1)) {
        if (read_len == -1) {
            std::cout << "read error \n";
        }
        str_len += read_len;
    }

    std::cout << "message from server: " << message << " str_len:"<< str_len<< "\n";

    close(client_sock);
    std::cout << "Hello World!\n";
}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
