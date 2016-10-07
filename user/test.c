#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

#include "../km-session.h"

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

	struct cmd_0_data data0 = {
		.value = 0xdeadbeef,
	};

	rc = ioctl(fd, 0x10, &data0);
	if (rc) {
		perror("ioctl failed\n");
		return -1;
	}

	/* ... and again */

	struct cmd_1_data data1 = {
		.value = 0xdeadbeefdeadbeefUL,
	};

	rc = ioctl(fd, 0x20, &data1);
	if (rc) {
		perror("ioctl failed\n");
		return -1;
	}

	/* ... and again */

	struct cmd_2_data data2;

	strcpy(data2.name, "test");

	rc = ioctl(fd, 0x30, &data2);
	if (rc) {
		perror("ioctl failed\n");
		return -1;
	}

	return 0;
}
