/*
 * IOMMUFD Device
 *
 * Copyright (C) 2024 Intel Corporation.
 *
 * Authors: Yi Liu <yi.l.liu@intel.com>
 *          Zhenzhong Duan <zhenzhong.duan@intel.com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef SYSEMU_IOMMUFD_DEVICE_H
#define SYSEMU_IOMMUFD_DEVICE_H

#include <linux/iommufd.h>
#include "sysemu/iommufd.h"

typedef struct IOMMUFDDevice IOMMUFDDevice;
typedef struct IOMMUFDViommu IOMMUFDViommu;

typedef struct IOMMUFDDeviceOps {
    int (*attach_hwpt)(IOMMUFDDevice *idev, uint32_t hwpt_id);
    int (*detach_hwpt)(IOMMUFDDevice *idev);
} IOMMUFDDeviceOps;

/* This is an abstraction of host IOMMUFD device */
struct IOMMUFDDevice {
    IOMMUFDBackend *iommufd;
    uint32_t dev_id;
    uint32_t ioas_id;
    IOMMUFDDeviceOps *ops;
};

struct IOMMUFDViommu {
    IOMMUFDBackend *iommufd;
    uint32_t s2_hwpt_id;
    uint32_t viommu_id;
};

int iommufd_device_attach_hwpt(IOMMUFDDevice *idev, uint32_t hwpt_id);
int iommufd_device_detach_hwpt(IOMMUFDDevice *idev);
int iommufd_device_get_info(IOMMUFDDevice *idev,
                            enum iommu_hw_info_type *type,
                            uint32_t len, void *data);
int iommufd_device_invalidate_cache(IOMMUFDDevice *ideve,
                                    uint32_t req_type, uint32_t req_len,
                                    uint32_t *req_num, void *reqs_ptr);
void iommufd_device_init(void *_idev, size_t instance_size,
                         IOMMUFDBackend *iommufd, uint32_t dev_id,
                         uint32_t ioas_id, IOMMUFDDeviceOps *ops);
struct IOMMUFDViommu *iommufd_device_alloc_viommu(IOMMUFDDevice *idev,
                                                  uint32_t hwpt_id);
int iommufd_viommu_set_data(IOMMUFDViommu *viommu,
                            uint32_t data_type, uint32_t len, void *data_ptr);
#endif
