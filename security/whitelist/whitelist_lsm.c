#include <linux/xattr.h>
#include <linux/binfmts.h>
#include <linux/lsm_hooks.h>
#include <linux/cred.h>

static int whitelist_bprm_check_security(struct linux_binprm *bprm)
{
       const struct task_struct *task = current;
       kuid_t uid = task->cred->uid;

       struct dentry *dentry = bprm->file->f_path.dentry;
       struct inode *inode = d_backing_inode(dentry);

       int size = 0;

       if ( uid.val == 0 )
          return 0;

       size = __vfs_getxattr(dentry, inode, "security.whitelisted", NULL, 0);
       if ( size > 0 )
           return 0;

       printk(KERN_INFO "whitelist LSM check of %s denying access for UID %d [ERRO:%d] \n", bprm->filename, uid.val, size );
       return -EPERM;
}

static struct security_hook_list whitelist_hooks[] __lsm_ro_after_init = {
	LSM_HOOK_INIT(bprm_check_security, whitelist_bprm_check_security),
};

void __init whitelist_add_hooks(void)
{
	security_add_hooks(whitelist_hooks, ARRAY_SIZE(whitelist_hooks), "whitelist");
	printk(KERN_INFO "whitelist LSM initialized\n");
}