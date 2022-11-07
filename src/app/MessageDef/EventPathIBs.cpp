/*
 * SPDX-FileCopyrightText: (c) 2020 Project CHIP Authors
 * SPDX-FileCopyrightText: (c) 2018 Google LLC.
 * SPDX-FileCopyrightText: (c) 2016-2017 Nest Labs, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "EventPathIBs.h"

#include "MessageDefHelper.h"

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>

#include <app/AppConfig.h>

namespace chip {
namespace app {
#if CHIP_CONFIG_IM_ENABLE_SCHEMA_CHECK
CHIP_ERROR EventPathIBs::Parser::CheckSchemaValidity() const
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    size_t NumPath = 0;
    TLV::TLVReader reader;

    PRETTY_PRINT("EventPathIBs =");
    PRETTY_PRINT("[");

    // make a copy of the EventPathIBs reader
    reader.Init(mReader);

    while (CHIP_NO_ERROR == (err = reader.Next()))
    {
        VerifyOrReturnError(TLV::AnonymousTag() == reader.GetTag(), CHIP_ERROR_INVALID_TLV_TAG);
        VerifyOrReturnError(TLV::kTLVType_List == reader.GetType(), CHIP_ERROR_WRONG_TLV_TYPE);

        {
            EventPathIB::Parser path;
            ReturnErrorOnFailure(path.Init(reader));

            PRETTY_PRINT_INCDEPTH();
            ReturnErrorOnFailure(path.CheckSchemaValidity());
            PRETTY_PRINT_DECDEPTH();
        }

        ++NumPath;
    }

    PRETTY_PRINT("],");
    PRETTY_PRINT_BLANK_LINE();

    // if we have exhausted this container
    if (CHIP_END_OF_TLV == err)
    {
        err = CHIP_NO_ERROR;
    }
    ReturnErrorOnFailure(err);
    return reader.ExitContainer(mOuterContainerType);
}
#endif // CHIP_CONFIG_IM_ENABLE_SCHEMA_CHECK

EventPathIB::Builder & EventPathIBs::Builder::CreatePath()
{
    if (mError == CHIP_NO_ERROR)
    {
        mError = mEventPath.Init(mpWriter);
    }
    return mEventPath;
}

EventPathIBs::Builder & EventPathIBs::Builder::EndOfEventPaths()
{
    EndOfContainer();
    return *this;
}
}; // namespace app
}; // namespace chip
