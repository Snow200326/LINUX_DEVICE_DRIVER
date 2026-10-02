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
	{ 0x9f222e1e, "alloc_chrdev_region" },
	{ 0xd9324140, "cdev_init" },
	{ 0x45d300cd, "cdev_add" },
	{ 0xfad798b2, "class_create" },
	{ 0x02106a3d, "device_create" },
	{ 0xca31368d, "kthread_create_on_node" },
	{ 0x42baf079, "wake_up_process" },
	{ 0x8b881dc5, "const_current_task" },
	{ 0x7ec472ba, "cpu_number" },
	{ 0xd7442be0, "class_destroy" },
	{ 0x73634a54, "cdev_del" },
	{ 0x0bc5fb0d, "unregister_chrdev_region" },
	{ 0x2794f3c0, "kthread_stop" },
	{ 0x408a0738, "device_destroy" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x5e505530, "kthread_should_stop" },
	{ 0x67628f51, "msleep" },
	{ 0xe9196a28, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x9f222e1e,
	0xd9324140,
	0x45d300cd,
	0xfad798b2,
	0x02106a3d,
	0xca31368d,
	0x42baf079,
	0x8b881dc5,
	0x7ec472ba,
	0xd7442be0,
	0x73634a54,
	0x0bc5fb0d,
	0x2794f3c0,
	0x408a0738,
	0xd272d446,
	0xe8213e80,
	0xd272d446,
	0x5e505530,
	0x67628f51,
	0xe9196a28,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"alloc_chrdev_region\0"
	"cdev_init\0"
	"cdev_add\0"
	"class_create\0"
	"device_create\0"
	"kthread_create_on_node\0"
	"wake_up_process\0"
	"const_current_task\0"
	"cpu_number\0"
	"class_destroy\0"
	"cdev_del\0"
	"unregister_chrdev_region\0"
	"kthread_stop\0"
	"device_destroy\0"
	"__fentry__\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"kthread_should_stop\0"
	"msleep\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "14441AE1EC1B0C3DEB49FB7");
