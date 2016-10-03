#include <linux/module.h>

/* Called during initilization of the kernel module */
static int __init initialize(void)
{
	printk("Hello world\n");

	return 0;
}

/* Called during deinitialization of the kernel module */
static void __exit finalize(void)
{
	printk("Bye world!\n");
}

/* Tell the kernel which function should be called during initialization */
module_init(initialize);
/* Tell the kernel which function should be called during deinitialization */
module_exit(finalize);
