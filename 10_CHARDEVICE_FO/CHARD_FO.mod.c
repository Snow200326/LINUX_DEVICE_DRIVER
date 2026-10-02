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
	{ 0x45d300cd, "cdev_add" },
	{ 0xfad798b2, "class_create" },
	{ 0x02106a3d, "device_create" },
	{ 0xd7442be0, "class_destroy" },
	{ 0x0bc5fb0d, "unregister_chrdev_region" },
	{ 0x5cb46e6d, "validate_usercopy_range" },
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0x90a48d82, "__ubsan_handle_out_of_bounds" },
	{ 0xf64ac983, "__copy_overflow" },
	{ 0x092a35a2, "_copy_to_user" },
	{ 0x408a0738, "device_destroy" },
	{ 0x73634a54, "cdev_del" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x9f222e1e, "alloc_chrdev_region" },
	{ 0xd9324140, "cdev_init" },
	{ 0xe9196a28, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x45d300cd,
	0xfad798b2,
	0x02106a3d,
	0xd7442be0,
	0x0bc5fb0d,
	0x5cb46e6d,
	0xa61fd7aa,
	0x092a35a2,
	0x90a48d82,
	0xf64ac983,
	0x092a35a2,
	0x408a0738,
	0x73634a54,
	0xd272d446,
	0xe8213e80,
	0xd272d446,
	0x9f222e1e,
	0xd9324140,
	0xe9196a28,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"cdev_add\0"
	"class_create\0"
	"device_create\0"
	"class_destroy\0"
	"unregister_chrdev_region\0"
	"validate_usercopy_range\0"
	"__check_object_size\0"
	"_copy_from_user\0"
	"__ubsan_handle_out_of_bounds\0"
	"__copy_overflow\0"
	"_copy_to_user\0"
	"device_destroy\0"
	"cdev_del\0"
	"__fentry__\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"alloc_chrdev_region\0"
	"cdev_init\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "EB00C0FF74361CCECAC4870");
