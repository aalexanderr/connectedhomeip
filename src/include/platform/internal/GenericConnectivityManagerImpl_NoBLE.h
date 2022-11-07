/*
 * SPDX-FileCopyrightText: (c) 2020 Project CHIP Authors
 * SPDX-FileCopyrightText: (c) 2019 Nest Labs, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 *    @file
 *          Provides an generic implementation of ConnectivityManager features
 *          for use on platforms that don't have BLE.
 */

#pragma once

namespace chip {
namespace DeviceLayer {
namespace Internal {

/**
 * Provides a generic implementation of BLE-specific ConnectivityManager features for
 * platforms that don't support BLE.
 *
 * This class is intended to be inherited (directly or indirectly) by the ConnectivityManagerImpl
 * class, which also appears as the template's ImplClass parameter.
 *
 * The members of this class are all inlined methods that do nothing, and return static return
 * values.  This allows the compiler to optimize away dead code without the use of \#ifdef's.
 */
template <class ImplClass>
class GenericConnectivityManagerImpl_NoBLE
{
public:
    // ===== Methods that implement the ConnectivityManager abstract interface.

    Ble::BleLayer * _GetBleLayer(void);
    bool _IsBLEAdvertisingEnabled(void);
    CHIP_ERROR _SetBLEAdvertisingEnabled(bool val);
    bool _IsBLEAdvertising(void);
    CHIP_ERROR _SetBLEAdvertisingMode(ConnectivityManager::BLEAdvertisingMode mode);
    CHIP_ERROR _GetBLEDeviceName(char * buf, size_t bufSize);
    CHIP_ERROR _SetBLEDeviceName(const char * deviceName);
    uint16_t _NumBLEConnections(void);
    static const char * _CHIPoBLEServiceModeToStr(ConnectivityManager::CHIPoBLEServiceMode mode);

private:
    ImplClass * Impl() { return static_cast<ImplClass *>(this); }
};

template <class ImplClass>
inline Ble::BleLayer * GenericConnectivityManagerImpl_NoBLE<ImplClass>::_GetBleLayer(void)
{
    return nullptr;
}

template <class ImplClass>
inline bool GenericConnectivityManagerImpl_NoBLE<ImplClass>::_IsBLEAdvertisingEnabled(void)
{
    return false;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_NoBLE<ImplClass>::_SetBLEAdvertisingEnabled(bool val)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline bool GenericConnectivityManagerImpl_NoBLE<ImplClass>::_IsBLEAdvertising(void)
{
    return false;
}

template <class ImplClass>
inline CHIP_ERROR
GenericConnectivityManagerImpl_NoBLE<ImplClass>::_SetBLEAdvertisingMode(ConnectivityManager::BLEAdvertisingMode mode)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_NoBLE<ImplClass>::_GetBLEDeviceName(char * buf, size_t bufSize)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline CHIP_ERROR GenericConnectivityManagerImpl_NoBLE<ImplClass>::_SetBLEDeviceName(const char * deviceName)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

template <class ImplClass>
inline uint16_t GenericConnectivityManagerImpl_NoBLE<ImplClass>::_NumBLEConnections(void)
{
    return false;
}

template <class ImplClass>
inline const char *
GenericConnectivityManagerImpl_NoBLE<ImplClass>::_CHIPoBLEServiceModeToStr(ConnectivityManager::CHIPoBLEServiceMode mode)
{
    return NULL;
}

} // namespace Internal
} // namespace DeviceLayer
} // namespace chip
