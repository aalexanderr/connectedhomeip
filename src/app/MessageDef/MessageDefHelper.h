/*
 * SPDX-FileCopyrightText: (c) 2020-2021 Project CHIP Authors
 * SPDX-FileCopyrightText: (c) 2018 Google LLC.
 * SPDX-FileCopyrightText: (c) 2016-2017 Nest Labs, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
/**
 *    @file
 *      This file defines message helper functions in CHIP interaction model
 *
 */

#pragma once

#include <algorithm>
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>

#include <app/AppBuildConfig.h>

// We need CHIPLogging.h to get the right value for CHIP_DETAIL_LOGGING here.
#include <lib/support/logging/CHIPLogging.h>

#include <lib/core/CHIPError.h>
#include <lib/core/CHIPTLV.h>

namespace chip {
namespace app {
#if CHIP_CONFIG_IM_ENABLE_SCHEMA_CHECK && CHIP_DETAIL_LOGGING
/**
 * Start a new "blank" line.  This will actually print out whitespace to the
 * current indent level, which can be followed with PRETTY_PRINT_SAMELINE calls.
 */
void PrettyPrintIMBlankLine();
void PrettyPrintIM(bool aIsNewLine, const char * aFmt, ...) ENFORCE_FORMAT(2, 3);
void IncreaseDepth();
void DecreaseDepth();
#define PRETTY_PRINT_BLANK_LINE()                                                                                                  \
    do                                                                                                                             \
    {                                                                                                                              \
        PrettyPrintIMBlankLine();                                                                                                  \
    } while (0)
#define PRETTY_PRINT(fmt, ...)                                                                                                     \
    do                                                                                                                             \
    {                                                                                                                              \
        PrettyPrintIM(true, fmt, ##__VA_ARGS__);                                                                                   \
    } while (0)
#define PRETTY_PRINT_SAMELINE(fmt, ...)                                                                                            \
    do                                                                                                                             \
    {                                                                                                                              \
        PrettyPrintIM(false, fmt, ##__VA_ARGS__);                                                                                  \
    } while (0)
#define PRETTY_PRINT_INCDEPTH()                                                                                                    \
    do                                                                                                                             \
    {                                                                                                                              \
        IncreaseDepth();                                                                                                           \
    } while (0)
#define PRETTY_PRINT_DECDEPTH()                                                                                                    \
    do                                                                                                                             \
    {                                                                                                                              \
        DecreaseDepth();                                                                                                           \
    } while (0)
#else
#define PRETTY_PRINT_BLANK_LINE()
#define PRETTY_PRINT(fmt, ...)
#define PRETTY_PRINT(fmt, ...)
#define PRETTY_PRINT_SAMELINE(fmt, ...)
#define PRETTY_PRINT_INCDEPTH()
#define PRETTY_PRINT_DECDEPTH()
#endif

#if CHIP_CONFIG_IM_ENABLE_SCHEMA_CHECK
// Parse an IM payload (attribute value, command fields, event fields,
// recursively parsing any complex types encountered.
CHIP_ERROR CheckIMPayload(TLV::TLVReader & aReader, int aDepth, const char * aLabel);
#endif // CHIP_CONFIG_IM_ENABLE_SCHEMA_CHECK

}; // namespace app
}; // namespace chip
