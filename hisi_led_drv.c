#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/cdev.h>
#include <linux/device.h>

#include <asm/uaccess.h>
#include <asm/system.h>
#include <asm/io.h>


// 硬件连接
// ------------------------------------------
//  dev |  chip   | pin  | name  |  func0
// ------------------------------------------
//  LED | Hi3531A | AH23 | IR_IN | GPIO20_5
// ------------------------------------------


#define GPIO20_BASE           (0x12290000) 

#define GPIO20_DATA_OFFSET    (0x3FC)        // 对bit0~bit7操作全部有效，这里和其他芯片的区别大，建议去认真看datasheet
#define GPIO20_5_DATA_OFFSET  (0x20 << 2)    // 仅对bit5操作有效

#define PIN_AH23_MUXCTRL      *((volatile unsigned int *)(IO_ADDRESS(0x120F0270)))                         // 管脚复用，0：GPIO20_5   1：IR_IN
#define GPIO20_DATA           *((volatile unsigned int *)(IO_ADDRESS(GPIO20_BASE + GPIO20_5_DATA_OFFSET))) // GPIO数据寄存器，这里去看手册理解偏移地址
#define GPIO20_DIR            *((volatile unsigned int *)(IO_ADDRESS(GPIO20_BASE + 0x400)))                // GPIO方向控制寄存器，0：输入  1：输出
#define GPIO20_IE             *((volatile unsigned int *)(IO_ADDRESS(GPIO20_BASE + 0x410)))                // GPIO中断屏蔽寄存器，0：屏蔽  1：不屏蔽
 

#define DEVICE_NAME "hisi_led"
 
dev_t dev_id;                      // 设备号                    
struct cdev led_cdev;              // 每个字符设备对应一个cdev结构
static struct class *led_class;    // 设备类


static int led_drv_open(struct inode *inode, struct file *file)
{
	printk(KERN_ALERT "Hisi led driver open!\n");
	
	PIN_AH23_MUXCTRL = 0x0;        // PIN AH23 as GPIO
	GPIO20_DIR |= (0x01 << 5);     // GPIO20_5 as output
	GPIO20_IE &= ~(0x01 << 5);     // 关闭中断功能
	
	GPIO20_DATA &= ~(0x01 << 5);   // 输出低
	
	return 0;
}


ssize_t led_drv_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	printk(KERN_ALERT "Hisi led driver read!\n");
	
    return 0;	
}


static ssize_t led_drv_write(struct file *file, const char __user *buffer, size_t count, loff_t *ppos)
{
	int val;
	
	printk(KERN_ALERT "Hisi led driver write!\n");
		
	if(count > 4)
	{
		printk(KERN_ALERT "led driver write count error!\n");
		
		return -1;
	}
	
	copy_from_user(&val, buffer, count); //	copy_to_user();

	if (val == 1)
	{
		// 点灯
		GPIO20_DATA |= (0x01 << 5);      // 输出高
	}
	else
	{
		// 灭灯
		GPIO20_DATA &= ~(0x01 << 5);     // 输出低
	}	
	
    return 0;	
}


static const struct file_operations led_drv_fops = 
{
	.owner = THIS_MODULE,
	.open  = led_drv_open,
	.read  = led_drv_read,
	.write = led_drv_write,
};


static int __init led_drv_init(void)
{
	int err;
	
	printk(KERN_ALERT "Hisi led driver init!\n");
		
	alloc_chrdev_region(&dev_id, 0, 1, DEVICE_NAME);            
	
	cdev_init(&led_cdev, &led_drv_fops);                        
    led_cdev.owner = THIS_MODULE;	
	err = cdev_add(&led_cdev, dev_id, 1);                       
    if (err) 
	{
		printk("Cannot add Hisi led device!\n");
	}
	
	led_class = class_create(THIS_MODULE, "led_class");         
	device_create(led_class, NULL, dev_id, NULL, DEVICE_NAME); 
	
    return 0;
}


static void __exit led_drv_exit(void)
{
	printk(KERN_ALERT "Hisi led driver exit!\n");
	
	cdev_del(&led_cdev);
    unregister_chrdev_region(dev_id, 1);
	
	device_destroy(led_class, dev_id);
	class_destroy(led_class);  
}


module_init(led_drv_init);
module_exit(led_drv_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("wang");
MODULE_DESCRIPTION("Hisi led driver");