#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xd9324140, "cdev_init" },
	{ 0x45d300cd, "cdev_add" },
	{ 0xfad798b2, "class_create" },
	{ 0x02106a3d, "device_create" },
	{ 0x95ac83d3, "kernel_kobj" },
	{ 0x7bc2c7ea, "kobject_create_and_add" },
	{ 0xd08a1472, "sysfs_create_file_ns" },
	{ 0x955c7048, "kobject_put" },
	{ 0x9e3ce042, "sysfs_remove_file_ns" },
	{ 0xd7442be0, "class_destroy" },
	{ 0x73634a54, "cdev_del" },
	{ 0x0bc5fb0d, "unregister_chrdev_region" },
	{ 0x408a0738, "device_destroy" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x173ec8da, "sscanf" },
	{ 0xdd6830c7, "sprintf" },
	{ 0x9f222e1e, "alloc_chrdev_region" },
	{ 0xe9196a28, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xd9324140,
	0x45d300cd,
	0xfad798b2,
	0x02106a3d,
	0x95ac83d3,
	0x7bc2c7ea,
	0xd08a1472,
	0x955c7048,
	0x9e3ce042,
	0xd7442be0,
	0x73634a54,
	0x0bc5fb0d,
	0x408a0738,
	0xd272d446,
	0xe8213e80,
	0xd272d446,
	0x173ec8da,
	0xdd6830c7,
	0x9f222e1e,
	0xe9196a28,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"cdev_init\0"
	"cdev_add\0"
	"class_create\0"
	"device_create\0"
	"kernel_kobj\0"
	"kobject_create_and_add\0"
	"sysfs_create_file_ns\0"
	"kobject_put\0"
	"sysfs_remove_file_ns\0"
	"class_destroy\0"
	"cdev_del\0"
	"unregister_chrdev_region\0"
	"device_destroy\0"
	"__fentry__\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"sscanf\0"
	"sprintf\0"
	"alloc_chrdev_region\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "4BA7F83327006DFBC54DCA3");
