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
	{ 0x5af09d8b, "_raw_spin_unlock" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x1ac124bd, "tasklet_setup" },
	{ 0x5c9888a2, "__tasklet_schedule" },
	{ 0x5c9888a2, "tasklet_kill" },
	{ 0xd272d446, "__fentry__" },
	{ 0x5af09d8b, "_raw_spin_lock" },
	{ 0xe8213e80, "_printk" },
	{ 0xe9196a28, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x5af09d8b,
	0xd272d446,
	0x1ac124bd,
	0x5c9888a2,
	0x5c9888a2,
	0xd272d446,
	0x5af09d8b,
	0xe8213e80,
	0xe9196a28,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"_raw_spin_unlock\0"
	"__x86_return_thunk\0"
	"tasklet_setup\0"
	"__tasklet_schedule\0"
	"tasklet_kill\0"
	"__fentry__\0"
	"_raw_spin_lock\0"
	"_printk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "5B641D1316C3B37E97CF023");
