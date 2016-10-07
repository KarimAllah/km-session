#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/uaccess.h>

/* Include the data-structures shared between user and kernel */
#include "km-session.h"

/* Called when ioctl(fd, cmd, data) is called from user-space */
static long
km_session_ioctl(struct file *file, unsigned int cmd, unsigned long data)
{
	/* In real-life you should not blindly trust data coming from user-space! */

	printk("Dispatching for cmd 0x%x\n", cmd);

	/*
	 * The proper way to encode cmd values is through _IO*(type,nr,size)
	 * family, but for the sake of simplicity just hard-code it
	 */
	switch (cmd) {
	case 0x10: {
		struct cmd_0_data cmd_data;

		if (copy_from_user(&cmd_data, (void *)data, sizeof(cmd_data)))
			return -EFAULT;

		printk("value: %x\n", cmd_data.value);

		break;
	}
	case 0x20: {
		struct cmd_1_data cmd_data;

		if (copy_from_user(&cmd_data, (void *)data, sizeof(cmd_data)))
			return -EFAULT;

		printk("value: %lx\n", cmd_data.value);

		break;
	}
	case 0x30: {
		struct cmd_2_data cmd_data;

		if (copy_from_user(&cmd_data, (void *)data, sizeof(cmd_data)))
			return -EFAULT;

		printk("name: %s\n", cmd_data.name);

		break;
	}
	default:
		printk("Unknown command\n");
		return -EINVAL;
	}

	return 0;
}

/* File system operations against the misc device */
const struct file_operations km_session_fops = {
	.unlocked_ioctl = km_session_ioctl,
};

/*
 * Character device with major number at 10 and minor at 100
 *
 * Create a device node in user-space with:
 * # mknod km-session c 10 100
 *
 */
static struct miscdevice km_session_miscdev = {
	.minor = 100,
	.name = "km-session",
	.fops = &km_session_fops,
};

/* Called during initilization of the kernel module */
static int __init initialize(void)
{
	printk("Hello world!\n");

	return misc_register(&km_session_miscdev);
}

/* Called during deinitialization of the kernel module */
static void __exit finalize(void)
{
	misc_deregister(&km_session_miscdev);

	printk("Bye world!\n");
}

/* Tell the kernel which function should be called during initialization */
module_init(initialize);
/* Tell the kernel which function should be called during deinitialization */
module_exit(finalize);
