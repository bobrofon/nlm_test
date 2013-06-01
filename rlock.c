#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#ifndef SLEEP_TIME
#define SLEEP_TIME 5
#endif 

int main(int argc, char *argv[]) {
	struct flock lock;
	int fd = -1;
	int ret_code = 0;

	if(argc != 2) {
		fprintf(stderr, "Use: %s file_to_lock\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	fd = open(argv[1], O_RDONLY);
	if(fd == -1) {
		fprintf(stderr, "Open file %s: %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}

	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	ret_code = fcntl(fd, F_SETLKW, &lock);
	if(ret_code == -1) {
		printf("access denied\n exit\n");
		exit(EXIT_SUCCESS);
	}
	printf("access granted\n sleep %d sec\n", SLEEP_TIME);
	sleep(SLEEP_TIME);
	printf("exit\n");

	exit(EXIT_SUCCESS);
}
