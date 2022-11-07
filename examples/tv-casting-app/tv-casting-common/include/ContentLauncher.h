/*
 * SPDX-FileCopyrightText: (c) 2022 Project CHIP Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "MediaCommandBase.h"
#include "MediaSubscriptionBase.h"

#include <functional>
#include <zap-generated/CHIPClusters.h>

// COMMAND CLASSES
class LaunchURLCommand : public MediaCommandBase<chip::app::Clusters::ContentLauncher::Commands::LaunchURL::Type,
                                                 chip::app::Clusters::ContentLauncher::Commands::LaunchResponse::DecodableType>
{
public:
    LaunchURLCommand() : MediaCommandBase(chip::app::Clusters::ContentLauncher::Id) {}

    CHIP_ERROR Invoke(const char * contentUrl, const char * contentDisplayStr,
                      chip::Optional<chip::app::Clusters::ContentLauncher::Structs::BrandingInformation::Type> brandingInformation,
                      std::function<void(CHIP_ERROR)> responseCallback);
};

class LaunchContentCommand : public MediaCommandBase<chip::app::Clusters::ContentLauncher::Commands::LaunchContent::Type,
                                                     chip::app::Clusters::ContentLauncher::Commands::LaunchResponse::DecodableType>
{
public:
    LaunchContentCommand() : MediaCommandBase(chip::app::Clusters::ContentLauncher::Id) {}

    CHIP_ERROR Invoke(chip::app::Clusters::ContentLauncher::Structs::ContentSearch::Type search, bool autoPlay,
                      chip::Optional<chip::CharSpan> data, std::function<void(CHIP_ERROR)> responseCallback);
};

// SUBSCRIBER CLASSES
class AcceptHeaderSubscriber
    : public MediaSubscriptionBase<chip::app::Clusters::ContentLauncher::Attributes::AcceptHeader::TypeInfo>
{
public:
    AcceptHeaderSubscriber() : MediaSubscriptionBase(chip::app::Clusters::ContentLauncher::Id) {}
};

class SupportedStreamingProtocolsSubscriber
    : public MediaSubscriptionBase<chip::app::Clusters::ContentLauncher::Attributes::SupportedStreamingProtocols::TypeInfo>
{
public:
    SupportedStreamingProtocolsSubscriber() : MediaSubscriptionBase(chip::app::Clusters::ContentLauncher::Id) {}
};
