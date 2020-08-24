#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#define FIFO_SERVER "myfifo"
#define FIFO_MODE O_CREAT|O_NONBLOCK|O_RDWR
#define FILE_MODE O_WRONLY | O_NONBLOCK
int main(int argc, char** argv)
{
	int fd;
	char w_buf[100];
	char w_t_buf[50];
	const char *hstr = "hello world";
	if(mkfifo(FIFO_SERVER, FIFO_MODE<0)&& (errno != EEXIST))
	{
		perror("failed to create fifo server");
		exit(1);
	}
	char cmd[100];
	sprintf(cmd, "chmod 704 %s", FIFO_SERVER);
	system(cmd);
	int nwrite;
	fd = open(FIFO_SERVER, FILE_MODE);
	if (fd == -1)
	{
		if (errno == ENXIO)
		{
			printf("open errop;no reading process\n");
		} else {
			perror("open error");
			exit(EXIT_FAILURE);
		}
	}
	if (argc >= 2)
	{
		strcpy(w_t_buf, argv[1]);
	} else {
		strcpy(w_t_buf, hstr);
	}
	int i=0;
	int n;
	time_t tp;
	while(i  <20)
	{
		time(&tp);
		n=sprintf(w_buf, "Harry Process %d is sending %s at %s", getpid(), w_t_buf, ctime(&tp));
	if ((nwrite = write(fd, w_buf, n)) < 0)
	{
		if (errno == EAGAIN)
		{
			printf("the fifo has not been read yet.Please try later\n");
		} else {
			exit(1);
		}
		}
		printf("Send Message to FIFO: %s \n", w_buf);
		sleep(1);
	}
	close(fd);
	return 0;
}
