// client.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
int main(int argc,char **argv )
{
    int server_sock;
    int client_sock;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    
    //message.reserve(50);
        // = "hello world!";
    if (argc != 3) {
        std::cout << "port:"<<argv[0]<<"\n";
        return 0;
    }
    client_sock = socket(PF_INET,SOCK_STREAM,0);
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
    std::string message(20,0);
    pid_t pid=fork();
    if (pid == 0) {
        while (1) {
            std::cin >> message;
            std::cout << "client_sock:" << client_sock << "\n";
            int ret = write(client_sock, (void*)message.c_str(), message.length());
            if (ret < 0 || message == "quit") {
                break;
            }
            std::cout << "message from client to server : " << message << "\n";
        }
        close(client_sock);
    }
    else {
        while (1) {
            int str_len = read(client_sock, (void*)message.c_str(), message.length());
            std::cout << "message from server to client : " << message << "\n";
            if (str_len < 0 || message == "quit") {
                break;
            }
            message.clear();
        }
    }
    

    //int str_len = read(client_sock, (void*)message.c_str(), message.length());
    //if (str_len == -1) {
    //    std::cout << "read error \n";
    //}
    

    close(client_sock);
    //std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
