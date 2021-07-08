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
int main() {
	fd_set reads, tmps;
	int result, strlen;
	char buf[30] = {0};
	struct timeval timeout;
	timeout.tv_sec=5;
	timeout.tv_usec = 0;
	FD_ZERO(&reads);
	FD_SET(0,&reads);
	while (1) {
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		tmps = reads;
		int ret = select(1, &tmps, 0, 0, &timeout);
		if (ret == -1) {
			std::cout << "ret:" << ret << "\n";
			break;
		}
		else if (ret == 0) {
			std::cout << "ret:" << ret << "\n";
			
		}
		else {
			if (FD_ISSET(0, &tmps)) {
				int len = read(ret, buf, 30);
				buf[len] = 0;
				printf("buf:%s \n", buf);
			}
		}
	}
	return 0;
}