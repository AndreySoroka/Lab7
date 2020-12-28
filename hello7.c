
/*
 * Copyright (c) 2017, GlobalLogic Ukraine LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the GlobalLogic.
 * 4. Neither the name of the GlobalLogic nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY GLOBALLOGIC UKRAINE LLC ``AS IS`` AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC UKRAINE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/ktime.h>

struct head_list {
  struct head_list *next;
  ktime_t time;
};

MODULE_AUTHOR("Soroka Andrey");
MODULE_DESCRIPTION("Lab7_hello_world_output");
MODULE_LICENSE("Dual BSD/GPL");

static struct head_list *head;

static uint count = 1;
module_param(count,uint,S_IRUGO);
MODULE_PARM_DESC(count, "variable for quantity of hello world output");

static int __init init(void)
{
  uint i = 0;
  struct head_list *var_1, *var_2, *m, *var;

  head = kmalloc(sizeof(struct head_list *), GFP_KERNEL);

  var_1 = head;


  if(count == 0) {
    pr_warn("Parametr=0");
  }else if(count >=5 && count <= 10) {
    pr_warn("Parametr is between 5 and 10");
  }
  BUG_ON(count>10);

  for(i = 0; i < count; i++){
    m = kmalloc(sizeof(struct head_list), GFP_KERNEL);
    if (i == 7){
        m = NULL;
    }
    if (ZERO_OR_NULL_PTR(m)){
        pr_err("No memory available");
        while (head != NULL && count != 0) {
            var = head;
            head = var->next;
            kfree(var);
        }
        BUG_ON(!m);
        return -ENOMEM;
    }
    var_1->time = ktime_get();
    pr_info("Hello, world!\n");
    var_2 = var_1;
    var_1 = m;
  }
  if (count != 0) {
    kfree(var_2->next);
    var_2->next = NULL;
  }
  pr_info("count: %d\n", count);
  return 0;
}

static void __exit exit(void)
{
  struct head_list *var;

  while (head != NULL && count != 0) {
    var = head;
    pr_info("Time: %lld", var->time);
    head = var->next;
    kfree(var);
  }
  pr_info("");
}


module_init(init);
module_exit(exit);
