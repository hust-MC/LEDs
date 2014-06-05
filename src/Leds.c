//#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/pci.h>
#include <asm/uaccess.h>
//#include <mach/map.h>
//#include <mach/regs-gpio.h>
//#include <mach/gpio-bank-m.h>

#define DEVIECE_NAME	"tiny210_leds"		//设备名称
#define DEVICE_COUNT	1					//设备文件数量
#define tiny210_LEDS_MAJOR	0				//默认主设备号
#define tiny210_LEDS_MINOR	234				//默认次设备号

static int major = tiny210_LEDS_MAJOR;		//主设备号
static int minor = tiny210_LEDS_MINOR;		//次设备号
static dev_t dev_number;					//设备号

static struct class *leds_class = NULL;									//创建class
static struct file_operations dev_fops = { .owner = THIS_MODULE };		//设置fops
static struct cdev leds_cdev;											//设备描述

static int leds_create_device(void)
{
	int ret = 0;
	int err = 0;

	//1.初始化cdev的成员，建立cdev和fops之间的连接
	cdev_init(leds_cdev, dev_fops);
	leds_cdev.owner = THIS_MODULE;

	//2.主设备号大于0，通过指定设备号注册字符设备区域
	if (major > 0)
	{
		dev_number = MKDEV(major, minor);
		err = register_chrdev_region(dev_number, DEVICE_COUNT, DEVIECE_NAME);
		if (err < 0)
		{
			printk(KERN_WARNING "register_chrdev_region failed\n");
			return err;
		}
	} else  //主设备号为0，随即分配设备号这册字符设备区域
	{
		err = alloc_chrdev_region(*leds_cdev.dev, 10, DEVICE_COUNT,
		DEVIECE_NAME);
		if (err < 0)
		{
			printk("alloc_chrdev_region failed\n");
			return err;
		}

		major = MAJOR(leds_cdev.dev);
		minor = MINOR(leds_cdev.dev);
		dev_number = leds_cdev.dev;
	}
	//3.将字符设备添加到内核中的字符数组中
	ret = cdev_add(&leds_cdev,leds_cdev.dev,DEVICE_COUNT);
	//4.创建struct class
	leds_class = class_create(THIS_MODULE,DEVIECE_NAME);
	//5.创建设备文件
	device_create(&leds_class,NULL,dev_number,NULL,DEVIECE_NAME);
	return ret;
}

static int leds_init(void)
{
	int ret;
	//创建设备文件
	ret = leds_create_device();
	printk(DEVIECE_NAME"\tinitialized\n");
	return ret;
}

module_init(leds_init);
