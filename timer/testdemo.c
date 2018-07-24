//
// https://www.cnblogs.com/sky-heaven/p/5157653.html
//
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(void){
	int fd, i;
	int data;
	fd = open("/dev/second",O_RDONLY);
	if (fd < 0){
		printf("open /dev/second error\n");
		fflush(stdout);
		return 0;
	}
	printf("\nopen /dev/second SUCCESS fd=%d\n\n", fd);
	for(i = 0; i < 20; i++){
		read(fd, &data, sizeof(data));
		printf("read /dev/second >>> data=%d\n",data);
		fflush(stdout);
		sleep(1);
	}
	close(fd);
	return 0;
}
