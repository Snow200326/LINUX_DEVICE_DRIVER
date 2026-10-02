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
	{ 0x9126ce86, "request_threaded_irq" },
	{ 0xbd03ed67, "random_kmalloc_seed" },
	{ 0xc4fee520, "kmalloc_caches" },
	{ 0x4574d0c7, "__kmalloc_cache_noprof" },
	{ 0x38a4f384, "tasklet_init" },
	{ 0x9dd4105e, "free_irq" },
	{ 0xd7442be0, "class_destroy" },
	{ 0x73634a54, "cdev_del" },
	{ 0x0bc5fb0d, "unregister_chrdev_region" },
	{ 0x5c9888a2, "tasklet_kill" },
	{ 0x408a0738, "device_destroy" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x5c9888a2, "__tasklet_schedule" },
	{ 0xe9196a28, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x9f222e1e,
	0xd9324140,
	0x45d300cd,
	0xfad798b2,
	0x02106a3d,
	0x9126ce86,
	0xbd03ed67,
	0xc4fee520,
	0x4574d0c7,
	0x38a4f384,
	0x9dd4105e,
	0xd7442be0,
	0x73634a54,
	0x0bc5fb0d,
	0x5c9888a2,
	0x408a0738,
	0xd272d446,
	0xe8213e80,
	0xd272d446,
	0x5c9888a2,
	0xe9196a28,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"alloc_chrdev_region\0"
	"cdev_init\0"
	"cdev_add\0"
	"class_create\0"
	"device_create\0"
	"request_threaded_irq\0"
	"random_kmalloc_seed\0"
	"kmalloc_caches\0"
	"__kmalloc_cache_noprof\0"
	"tasklet_init\0"
	"free_irq\0"
	"class_destroy\0"
	"cdev_del\0"
	"unregister_chrdev_region\0"
	"tasklet_kill\0"
	"device_destroy\0"
	"__fentry__\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"__tasklet_schedule\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "C4D4A91F7E2D5D31969D919");
