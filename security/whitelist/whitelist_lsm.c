 #include <linux/lsm_hooks.h>

 static int steve_bprm_check_security(struct linux_binprm *bprm)
 {
     printk(KERN_INFO "STEVE LSM check of %s\n", bprm->filename);
     return 0;
 }

 static struct security_hook_list steve_hooks[] = {
     LSM_HOOK_INIT(bprm_check_security, steve_bprm_check_security),
 };

 static void __init steve_init(void)
 {
     security_add_hooks(steve_hooks, ARRAY_SIZE(steve_hooks), "steve");
     printk(KERN_INFO "STEVE LSM initialized\n");
 }