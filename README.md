# goodix-gt9xx-i2c-driver
A simple Linux kernel I2C driver for Goodix GT9xx touchscreen controllers.  Covers complete flow: device tree matching, driver registration, probe/remove functions, property reading, and clean module loading/unloading. Written in an easy-to-understand format for learning and reference purposes.


Setup:
=========

Imagine we are writing a simple I2C driver for a touchscreen connected to the I2C bus.

Device Tree gives us: compatible = "goodix,gt9xx"

We want our driver to probe, read reg values, setup, and remove correctly.

We will register manually using module_init() and module_exit(), no shortcut!


⚙️ Kernel Driver Flow
=======================


Step	Action	Purpose
1	Create match table (of_device_id)	Tells kernel "match me with goodix,gt9xx"
2	Create probe()	Called when matching device found
3	Create remove()	Called when device removed
4	Create i2c_driver structure	Connects probe, remove, match table
5	Create init() and exit() functions	To register/unregister driver
6	Use module_init and module_exit	Connect init/exit to kernel loading

In Short:
============


Point	Summary
.compatible	Links DTS entry and driver
probe()	Happens when device found
remove()	Cleanup when device removed
of_property_read_u32()	Read reg-like values from DT
module_init/exit	Tells kernel how to load/unload module

