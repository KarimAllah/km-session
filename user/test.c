#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>

int main()
{
	int fd, rc;

	/* Open the character device */
	fd = open("km-session", O_RDONLY);
	if (fd < 0) {
		perror("opening device node failed\n");
		return -1;
	}

	/* Now speak to it */
	rc = ioctl(fd, 0);
	if (rc) {
		perror("ioctl failed\n");
		return -1;
	}

	/* ... and again */
	rc = ioctl(fd, 1);
	if (rc) {
		perror("ioctl failed\n");
		return -1;
	}

	return 0;
}
