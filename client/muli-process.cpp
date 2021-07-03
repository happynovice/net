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


// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
