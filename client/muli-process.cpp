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
#include <sys/wait.h>
#endif
void signal_fun(int sig) {
	int status;
	std::cout << "before waitpid sig:"<< sig <<"\n";
	pid_t id = waitpid(-1,&status,WNOHANG);
	std::cout << "after waitpidsig sig:" << sig <<"\n";
}
void test_signal() {
	int status = 0;
	struct sigaction act;
	act.sa_handler = signal_fun;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGCHLD, &act, 0);
	pid_t  pid = fork();
	if (pid == 0) {
		std::cout << "child process pid:" << pid << " return \n";
		return 0;
	}
	else {
		std::cout << "before parent process pid:" << pid << " return \n";
		sleep(20);
		std::cout << "after parent process pid:" << pid << " return \n";
		sleep(20);
	}
}
int main(int argc, char** argv)
{

	return 0;
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
