/*
 * SPDX-FileCopyrightText: (c) 2022 Project CHIP Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <commands/common/Command.h>

class StorageClearAll : public Command
{
public:
    StorageClearAll() : Command("clear-all") {}

    CHIP_ERROR Run() override;
};
