/*
 * SPDX-FileCopyrightText: (c) 2022 Project CHIP Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <platform/Tizen/ConfigurationManagerImpl.h>
#include <platform/internal/GenericDeviceInstanceInfoProvider.h>

namespace chip {
namespace DeviceLayer {

class DeviceInstanceInfoProviderImpl : public Internal::GenericDeviceInstanceInfoProvider<Internal::PosixConfig>
{
public:
    CHIP_ERROR GetVendorId(uint16_t & vendorId) override;
    CHIP_ERROR GetProductId(uint16_t & productId) override;

    DeviceInstanceInfoProviderImpl(ConfigurationManagerImpl & configManager) :
        Internal::GenericDeviceInstanceInfoProvider<Internal::PosixConfig>(configManager)
    {}
};

inline DeviceInstanceInfoProviderImpl & DeviceInstanceInfoProviderMgrImpl()
{
    static DeviceInstanceInfoProviderImpl sInstance(ConfigurationManagerImpl::GetDefaultInstance());
    return sInstance;
}
} // namespace DeviceLayer
} // namespace chip
