#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FIFO_SERVER "myfifo"
#define OPEN_MODE O_RDONLY | O_NONBLOCK
#define FIFO_MODE O_CREAT|O_RDWR|O_NONBLOCK
int main(int argc, char** argv) {
char buf_r[100];
int fd;
int nread;
int res;
if (((res=mkfifo(FIFO_SERVER, FIFO_MODE)) < 0) && (errno != EEXIST))
{
printf("can not creat fifoserver %d :\n", res, errno);
exit(1);
}
printf("preparing for reading bytes...\n");
char cmd[100];
sprintf(cmd, "chmod 704 %s", FIFO_SERVER);
system(cmd);
fd = open(FIFO_SERVER, OPEN_MODE);
if (fd == -1) {
perror("error in openning fifo server");
exit(1);
}
int i=0;
int len;
while (i  <21)
{
memset(buf_r, 0, sizeof(buf_r));
if ((nread = read(fd, buf_r, sizeof(buf_r))) < 0) {
if (errno == EAGAIN)
{
printf("no data yet\n");
sleep(1);
}
} else {
if(nread > 0)
{
printf("read %s from FIFO %d \n", buf_r, i);
}
sleep(1);
}
}
//    pause();
close(fd);
unlink(FIFO_SERVER);
return 0;
}
