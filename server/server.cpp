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
#include <sys/epoll.h>
#endif
int main(int argc, char** argv)
{
    int server_sock;
    int client_sock;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    // = "hello world!";
    if (argc != 2) {
        std::cout << "port:" << argv[0] << "\n";
        return 0;
    }
    server_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        std::cout << "socket error \n";
        return 0;
    }
    std::cout <<" server_sock:" << server_sock << "\n";
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        std::cout << "bind error \n";
        return 0;
    }
    if (listen(server_sock, 5) == -1) {
        std::cout << "listen error \n";
        close(server_sock);
        return 0;
    }
    socklen_t client_addr_size = sizeof(client_addr);
    int str_len = 0;
    std::string str (30,0);
    int epoll_size = 50;

    int epfd=epoll_create(epoll_size);
    int event_cnt = 0;
    struct epoll_event epevent;
    struct epoll_event* p_epevents;
    p_epevents = (struct epoll_event*)malloc(sizeof(epoll_event)* epoll_size);
    epevent.events = EPOLLIN;
    epevent.data.fd = server_sock;
    epoll_ctl(epfd,EPOLL_CTL_ADD,server_sock,&epevent);

    while (1) {
        int event_cnt =epoll_wait(epfd, p_epevents, epoll_size,5000000);
        if (event_cnt == 0) {
            std::cout << "time out:"  << " \n";
            continue;
        }
        else if(event_cnt == -1){
            std::cout << "event_cnt:" << event_cnt << " \n";
            break;
        }
        std::cout << "selectret:"<< event_cnt  <<" \n";
        
        for (int i = 0; i < event_cnt; i++) {
            
            if (p_epevents[i].data.fd==server_sock) {
                client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);
                epevent.events = EPOLLIN;
                epevent.data.fd = client_sock;
                epoll_ctl(epfd,EPOLL_CTL_ADD,client_sock,&epevent);
                std::cout << "accept success client_sock:" << client_sock << " \n";
            }
            else {
                if ((str_len = read(p_epevents[i].data.fd, (void*)str.c_str(), str.size())) != 0) {
                    std::cout << "client_sock:" << p_epevents[i].data.fd << " str:" << str << "\n";
                    write(p_epevents[i].data.fd, str.c_str(), str_len);
                    memset((void*)str.c_str(), 0, str.size());
                }
                else
                {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, p_epevents[i].data.fd, NULL);
                    close(p_epevents[i].data.fd);
                    std::cout << "close client_sock:" << client_sock << " \n";
                }
                //pid_t pid = fork();
                //if (pid == 0) {
                //    close(server_sock);

                //    exit(0);
                //}
                //else {
                //    //close(p_epevents[i].data.fd);
                //}
            }
            
        }
    }
    close(server_sock);
    close(epfd);
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
