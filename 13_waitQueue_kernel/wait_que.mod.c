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
	{ 0xc281f1fb, "prepare_to_wait_event" },
	{ 0xd272d446, "schedule" },
	{ 0xb730487b, "finish_wait" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0x68a1b6c6, "__wake_up" },
	{ 0x9f222e1e, "alloc_chrdev_region" },
	{ 0xd9324140, "cdev_init" },
	{ 0x45d300cd, "cdev_add" },
	{ 0xfad798b2, "class_create" },
	{ 0x02106a3d, "device_create" },
	{ 0xd7442be0, "class_destroy" },
	{ 0xe804603d, "__init_waitqueue_head" },
	{ 0xca31368d, "kthread_create_on_node" },
	{ 0x42baf079, "wake_up_process" },
	{ 0x73634a54, "cdev_del" },
	{ 0x0bc5fb0d, "unregister_chrdev_region" },
	{ 0x408a0738, "device_destroy" },
	{ 0xd272d446, "__fentry__" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xbd03ed67, "__ref_stack_chk_guard" },
	{ 0xe8213e80, "_printk" },
	{ 0x7851be11, "__SCT__might_resched" },
	{ 0x7a5ffe84, "init_wait_entry" },
	{ 0xe9196a28, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xc281f1fb,
	0xd272d446,
	0xb730487b,
	0xd272d446,
	0x68a1b6c6,
	0x9f222e1e,
	0xd9324140,
	0x45d300cd,
	0xfad798b2,
	0x02106a3d,
	0xd7442be0,
	0xe804603d,
	0xca31368d,
	0x42baf079,
	0x73634a54,
	0x0bc5fb0d,
	0x408a0738,
	0xd272d446,
	0xd272d446,
	0xbd03ed67,
	0xe8213e80,
	0x7851be11,
	0x7a5ffe84,
	0xe9196a28,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"prepare_to_wait_event\0"
	"schedule\0"
	"finish_wait\0"
	"__stack_chk_fail\0"
	"__wake_up\0"
	"alloc_chrdev_region\0"
	"cdev_init\0"
	"cdev_add\0"
	"class_create\0"
	"device_create\0"
	"class_destroy\0"
	"__init_waitqueue_head\0"
	"kthread_create_on_node\0"
	"wake_up_process\0"
	"cdev_del\0"
	"unregister_chrdev_region\0"
	"device_destroy\0"
	"__fentry__\0"
	"__x86_return_thunk\0"
	"__ref_stack_chk_guard\0"
	"_printk\0"
	"__SCT__might_resched\0"
	"init_wait_entry\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "0404F7957267E518A3754A5");
