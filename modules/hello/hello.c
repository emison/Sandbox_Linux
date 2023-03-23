#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_DESCRIPTION("Hello world kernel module");
MODULE_AUTHOR("Joe");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");

static int __init hello(void)
{
        printk(KERN_INFO "hello: Hi\n");
        return 0;
}

static void __exit goodbye(void)
{
        printk(KERN_INFO "hello: Bye\n");
}

module_init(hello);
module_exit(goodbye);
