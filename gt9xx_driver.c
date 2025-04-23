#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/property.h> // for property reading

// 1. Define matching compatible strings
static const struct of_device_id goodix_of_match[] = {
    { .compatible = "goodix,gt9xx" },
    { /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, goodix_of_match);

// 2. Probe function
static int goodix_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    struct device_node *np = client->dev.of_node;
    u32 x_size, y_size;
    int ret;

    printk(KERN_INFO "Goodix driver: Probing device 🛠️\n");

    // Example: Read properties from device tree
    ret = of_property_read_u32(np, "touchscreen-size-x", &x_size);
    if (ret)
        printk(KERN_ERR "Failed to read touchscreen-size-x property\n");
    else
        printk(KERN_INFO "Touchscreen X Size: %u\n", x_size);

    ret = of_property_read_u32(np, "touchscreen-size-y", &y_size);
    if (ret)
        printk(KERN_ERR "Failed to read touchscreen-size-y property\n");
    else
        printk(KERN_INFO "Touchscreen Y Size: %u\n", y_size);

    return 0;
}

// 3. Remove function
static int goodix_remove(struct i2c_client *client)
{
    printk(KERN_INFO "Goodix driver: Removing device 🧹\n");
    
    return 0;
}

// 4. i2c_driver structure
static struct i2c_driver goodix_driver = {
    .driver = {
        .name = "goodix_ts",
        .of_match_table = goodix_of_match,
    },
    .probe = goodix_probe,
    .remove = goodix_remove,
};

// 5. Init function
static int __init goodix_init(void)
{
    printk(KERN_INFO "Goodix driver: Initializing driver 🚀\n");
    return i2c_add_driver(&goodix_driver);
}

// 6. Exit function
static void __exit goodix_exit(void)
{
    printk(KERN_INFO "Goodix driver: Exiting driver 🧹\n");
    i2c_del_driver(&goodix_driver);
}

// 7. Connect init/exit to kernel
module_init(goodix_init);
module_exit(goodix_exit);

// 8. Meta information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Deepak");
MODULE_DESCRIPTION("Goodix GT9xx Touchscreen Driver");
