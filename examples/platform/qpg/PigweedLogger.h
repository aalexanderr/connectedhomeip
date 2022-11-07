/*
 * SPDX-FileCopyrightText: (c) 2021 Project CHIP Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <FreeRTOS.h>

#include "semphr.h"
#include <cstdint>

namespace PigweedLogger {

void init(void);
int putString(const char * buffer, size_t size);
void lock(void);
void unlock(void);

} // namespace PigweedLogger
