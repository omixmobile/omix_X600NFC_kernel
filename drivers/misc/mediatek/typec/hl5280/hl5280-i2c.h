// SPDX-License-Identifier: GPL-2.0-only
/* Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */
 
#ifndef FSA4480_I2C_H
#define FSA4480_I2C_H

#include <linux/of.h>
#include <linux/notifier.h>

enum fsa_function {
	FSA_MIC_GND_SWAP,
	FSA_USBC_ORIENTATION_CC1,
	FSA_USBC_ORIENTATION_CC2,
	FSA_USBC_DISPLAYPORT_DISCONNECTED,
	FSA_EVENT_MAX,
};
#define CONFIG_MTK_FSA4480_I2C
#ifdef CONFIG_MTK_FSA4480_I2C
int fsa4480_switch_event(struct device_node *node,
					enum fsa_function event);
int fsa4480_reg_notifier(struct notifier_block *nb,
					struct device_node *node);
int fsa4480_unreg_notifier(struct notifier_block *nb,
					struct device_node *node);
#else
static inline int fsa4480_switch_event(struct device_node *node,
								enum fsa_function event)
{
		return 0;
}

static inline int fsa4480_reg_notifier(struct notifier_block *node,
								enum device_node event)
{
		return 0;
}

static inline int fsa4480_unreg_notifier(struct notifier_block *node,
								enum device_node event)
{
		return 0;
}
#endif /* CONFIG_MTK_FSA4480_I2C */
#endif /* FSA4480_I2C_H */