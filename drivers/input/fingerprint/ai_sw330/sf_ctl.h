/**
 * User space driver API for Sunwave's fingerprint device.
 * ATTENTION: Do NOT edit this file unless the corresponding driver changed.
 *
 * Copyright (C) 2016 Sunwave Corporation. <http://www.sunwavecorp.com>
 * Copyright (C) 2016 Langson Leung <mailto:liangzh@sunwavecorp.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.
**/

#ifndef __SF_CTRL_API_H__
#define __SF_CTRL_API_H__

#include "sf_user.h"
#include "sf_spi.h"
#include "linux/version.h"

#ifdef CONFIG_PM_WAKELOCKS
#include <linux/pm_wakeup.h>
#else
#include <linux/wakelock.h>
#endif

#include <linux/miscdevice.h>
#include <linux/fb.h>

#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
#elif defined(CONFIG_ADF_SPRD)
//#include <mach/gpio.h>
//#include <soc/sprd/sci_glb_regs.h>
//#include <soc/sprd/adi.h>
//#include <soc/sprd/adc.h>
#include <video/adf_notifier.h>
#else
#include <linux/notifier.h>
#endif

#if (SF_POWER_MODE_SEL == PWR_MODE_REGULATOR)
#include <linux/regulator/consumer.h>
#endif

#if SF_TRUSTKERNEL_COMPATIBLE
//#include <tee_fp.h>
#include <linux/tee_fp.h>
#endif

#if SF_BEANPOD_COMPATIBLE_V2
#include <fp_vendor.h>
#endif

#if SF_BEANPOD_COMPATIBLE_V2_7
/**
 * This type contains a Universally Unique Resource Identifier (UUID) type as
 * defined in RFC4122. These UUID values are used to identify Trusted
 * Applications.
 */
struct TEEC_UUID {
    uint32_t timeLow;
    uint16_t timeMid;
    uint16_t timeHiAndVersion;
    uint8_t clockSeqAndNode[8];
};

extern struct TEEC_UUID uuid_fp;
#endif

#if REE_MTK_ANDROID_L
#include <cust_eint.h>
#include <cust_eint_md1.h>
#include "cust_gpio_usage.h"
#include <mach/mt_gpio.h>
#include <mach/mt_spi.h>
#include <mach/eint.h>
#include <cust_eint.h>
#endif

#if SF_SPI_RW_EN
#if (!REE_MTK_ANDROID_L && defined(CONFIG_MTK_SPI))
#include "mt_spi.h"
#include "mt_spi_hal.h"
#endif // end of #if (!REE_MTK_ANDROID_L && defined(CONFIG_MTK_SPI))
typedef struct spi_device sf_device_t;
typedef struct spi_driver sf_driver_t;
#define SW_BUS_NAME "spi bus"
#else
#include <linux/platform_device.h>
typedef struct platform_device sf_device_t;
typedef struct platform_driver sf_driver_t;
#define SW_BUS_NAME "platform bus"
#endif // end of #if SF_SPI_RW_EN

struct sf_ctl_device {
    struct miscdevice miscdev;
    int rst_num;
    int irq_pin;
    int irq_num;
    int pwr_num;
    struct work_struct work_queue;
    struct input_dev *input;
    struct regulator *vdd_reg;
    int  (*gpio_init) (struct sf_ctl_device *ctl_dev);
    int  (*free_gpio) (struct sf_ctl_device *ctl_dev);
    int  (*power_on)  (bool on);
    int  (*spi_clk_on)(bool on);
    int  (*reset)     (bool output);
#ifdef CONFIG_PM_WAKELOCKS
    struct wakeup_source *wakelock;
#else
    struct wake_lock wakelock;
#endif
#ifdef CONFIG_HAS_EARLYSUSPEND
    struct early_suspend early_suspend;
#elif defined(CONFIG_ADF_SPRD)
    struct notifier_block adf_event_block;
#else
    struct notifier_block notifier;
#endif
    char *spi_buffer;
    int attribute;
    sf_device_t *pdev;
#if (defined(CONFIG_MTK_SPI) || SF_TRUSTKERNEL_COMPAT_SPI_MT65XX)
    struct mt_chip_conf mt_conf;
#endif
    int spi_buf_size;
};

/* int event. */
#define SF_INT_EVENT_NAME "SPI_STATE=finger"

/* Device node. */
#define SF_CTL_DEV_NAME   "/dev/sunwave_fp"

/* Max driver version buffer length. */
#define SF_DRV_VERSION_LEN 32

typedef enum {
    SF_KEY_NONE = 0,
    SF_KEY_HOME,
    SF_KEY_MENU,
    SF_KEY_BACK,
    SF_KEY_F11,
    SF_KEY_ENTER,
    SF_KEY_UP,
    SF_KEY_LEFT,
    SF_KEY_RIGHT,
    SF_KEY_DOWN,
    SF_KEY_WAKEUP,
} sf_key_type_t;

typedef struct {
    sf_key_type_t key;
    int value; /* for key type, 0 means up, 1 means down. */
} sf_key_event_t;

#define SF_MAX_VER_INFO_LEN 32

typedef struct {
    char tee_solution[SF_MAX_VER_INFO_LEN];
    char ca_version  [SF_MAX_VER_INFO_LEN * 2];
    char ta_version  [SF_MAX_VER_INFO_LEN * 2];
    char algorithm   [SF_MAX_VER_INFO_LEN];
    char algo_nav    [SF_MAX_VER_INFO_LEN];
    char driver      [SF_MAX_VER_INFO_LEN];
    char firmware    [SF_MAX_VER_INFO_LEN];
    char sunwave_id  [SF_MAX_VER_INFO_LEN];
    char vendor_id   [SF_MAX_VER_INFO_LEN];
} __attribute__((__packed__)) sf_version_info_t;

/* Magic code for IOCTL-subsystem, 's'(0x73) means 'Sunwave'. */
#define SF_IOC_MAGIC 's'

/* Allocate/Release driver resource (GPIO/SPI etc.). */
#define SF_IOC_INIT_DRIVER      _IO(SF_IOC_MAGIC, 0x00)
#define SF_IOC_DEINIT_DRIVER    _IO(SF_IOC_MAGIC, 0x01)

/* HW reset the fingerprint module. */
#define SF_IOC_RESET_DEVICE     _IO(SF_IOC_MAGIC, 0x02)

/* Low-level IRQ control. */
#define SF_IOC_ENABLE_IRQ       _IO(SF_IOC_MAGIC, 0x03)
#define SF_IOC_DISABLE_IRQ      _IO(SF_IOC_MAGIC, 0x04)
#define SF_IOC_REQUEST_IRQ      _IO(SF_IOC_MAGIC, 0x21)

/* SPI bus clock control, for power-saving purpose. */
#define SF_IOC_ENABLE_SPI_CLK   _IO(SF_IOC_MAGIC, 0x05)
#define SF_IOC_DISABLE_SPI_CLK  _IO(SF_IOC_MAGIC, 0x06)

/* Fingerprint module power control. */
#define SF_IOC_ENABLE_POWER     _IO(SF_IOC_MAGIC, 0x07)
#define SF_IOC_DISABLE_POWER    _IO(SF_IOC_MAGIC, 0x08)

/* Androind system-wide key event, for navigation purpose. */
#define SF_IOC_REPORT_KEY_EVENT _IOW(SF_IOC_MAGIC, 0x09, sf_key_event_t *)

/* Sync 'sf_driver_config_t', the driver configuration. */
#define SF_IOC_SYNC_CONFIG      _IOWR(SF_IOC_MAGIC, 0x0a, void *)

/* SPI speed related. */
#define SF_IOC_SPI_SPEED        _IO(SF_IOC_MAGIC, 0x0b)

/* patform attribute */
#define SF_IOC_ATTRIBUTE        _IO(SF_IOC_MAGIC, 0x0d)

/* Query the driver version string. */
#define SF_IOC_GET_VERSION      _IOR(SF_IOC_MAGIC, 0x20, const char *)

/* sunwave hal lib version info set&get. */
#define SF_IOC_SET_LIB_VERSION  _IO(SF_IOC_MAGIC, 0x30)
#define SF_IOC_GET_LIB_VERSION  _IO(SF_IOC_MAGIC, 0x31)

/* sunwave spi transfer buffer size. */
#define SF_IOC_SET_SPI_BUF_SIZE _IO(SF_IOC_MAGIC, 0x40)

/* sunwave reset pin output. */
#define SF_IOC_SET_RESET_OUTPUT _IO(SF_IOC_MAGIC, 0x50)

/* REE emulate TEE*/
#define SPI_IOC_MAGIC           'k'
/* Read / Write SPI device default max speed hz */
#define SPI_IOC_RD_MAX_SPEED_HZ     _IOR(SPI_IOC_MAGIC, 4, __u32)
#define SPI_IOC_WR_MAX_SPEED_HZ     _IOW(SPI_IOC_MAGIC, 4, __u32)
#define SPI_IOC_RST                 _IO(SPI_IOC_MAGIC, 5)
#define SUNWAVE_IOC_ATTRIBUTE       _IOW(SPI_IOC_MAGIC, 17, __u32)
#endif /* __SF_CTRL_API_H__ */
