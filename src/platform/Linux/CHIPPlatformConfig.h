/*
 * SPDX-FileCopyrightText: (c) 2020-2022 Project CHIP Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 *    @file
 *          Platform-specific configuration overrides for CHIP on
 *          Linux platforms.
 */

#pragma once

// ==================== General Platform Adaptations ====================

#define CHIP_CONFIG_ABORT() abort()

using CHIP_CONFIG_PERSISTED_STORAGE_KEY_TYPE = const char *;
#define CHIP_CONFIG_PERSISTED_STORAGE_MAX_KEY_LENGTH 16

#define CHIP_CONFIG_LIFETIIME_PERSISTED_COUNTER_KEY "life-count"

#define CHIP_CONFIG_ERROR_FORMAT_AS_STRING 1
#define CHIP_CONFIG_ERROR_SOURCE 1

#define CHIP_CONFIG_VERBOSE_VERIFY_OR_DIE 1

#define CHIP_CONFIG_IM_STATUS_CODE_VERBOSE_FORMAT 1

// ==================== Security Adaptations ====================

// If unspecified, assume crypto is fast on Linux
#ifndef CHIP_CONFIG_SLOW_CRYPTO
#define CHIP_CONFIG_SLOW_CRYPTO 0
#endif // CHIP_CONFIG_SLOW_CRYPTO

// ==================== General Configuration Overrides ====================

#ifndef CHIP_CONFIG_MAX_UNSOLICITED_MESSAGE_HANDLERS
#define CHIP_CONFIG_MAX_UNSOLICITED_MESSAGE_HANDLERS 8
#endif // CHIP_CONFIG_MAX_UNSOLICITED_MESSAGE_HANDLERS

#ifndef CHIP_CONFIG_MAX_EXCHANGE_CONTEXTS
#define CHIP_CONFIG_MAX_EXCHANGE_CONTEXTS 8
#endif // CHIP_CONFIG_MAX_EXCHANGE_CONTEXTS

#ifndef CHIP_LOG_FILTERING
#define CHIP_LOG_FILTERING 0
#endif // CHIP_LOG_FILTERING

#ifndef CHIP_CONFIG_BDX_MAX_NUM_TRANSFERS
#define CHIP_CONFIG_BDX_MAX_NUM_TRANSFERS 1
#endif // CHIP_CONFIG_BDX_MAX_NUM_TRANSFERS

// ==================== Security Configuration Overrides ====================

#ifndef CHIP_CONFIG_KVS_PATH
#define CHIP_CONFIG_KVS_PATH "/tmp/chip_kvs"
#endif // CHIP_CONFIG_KVS_PATH
