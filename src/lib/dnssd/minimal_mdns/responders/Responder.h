/*
 * SPDX-FileCopyrightText: (c) 2020 Project CHIP Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <lib/dnssd/minimal_mdns/core/QName.h>
#include <lib/dnssd/minimal_mdns/records/ResourceRecord.h>

#include <inet/IPPacketInfo.h>
#include <lib/core/Optional.h>

namespace mdns {
namespace Minimal {

class ResponderDelegate
{
public:
    virtual ~ResponderDelegate() {}

    /// Add the specified resource record to the response
    virtual void AddResponse(const ResourceRecord & record) = 0;
};

/// Controls specific options for responding to mDNS queries
///
class ResponseConfiguration
{
public:
    ResponseConfiguration() {}
    ~ResponseConfiguration() = default;

    chip::Optional<uint32_t> GetTtlSecondsOverride() const { return mTtlSecondsOverride; }
    ResponseConfiguration & SetTtlSecondsOverride(chip::Optional<uint32_t> override)
    {
        mTtlSecondsOverride = override;
        return *this;
    }

    ResponseConfiguration & SetTtlSecondsOverride(uint32_t value) { return SetTtlSecondsOverride(chip::MakeOptional(value)); }
    ResponseConfiguration & ClearTtlSecondsOverride() { return SetTtlSecondsOverride(chip::NullOptional); }

    /// Applies any adjustments to resource records before they are being serialized
    /// to some form of reply.
    void Adjust(ResourceRecord & record) const
    {
        if (mTtlSecondsOverride.HasValue())
        {
            record.SetTtl(mTtlSecondsOverride.Value());
        }
    }

private:
    chip::Optional<uint32_t> mTtlSecondsOverride;
};

/// Adds ability to respond with specific types of data
class Responder
{
public:
    Responder(QType qType, const FullQName & qName) : mQType(qType), mQName(qName) {}
    virtual ~Responder() {}

    QClass GetQClass() const { return QClass::IN; }
    QType GetQType() const { return mQType; }

    /// Full name as: "Instance"."Servicer"."Domain"
    /// Domain name is generally just 'local'
    FullQName GetQName() const { return mQName; }

    /// Report all reponses maintained by this responder
    ///
    /// Responses are associated with the objects type/class/qname.
    virtual void AddAllResponses(const chip::Inet::IPPacketInfo * source, ResponderDelegate * delegate,
                                 const ResponseConfiguration & configuration) = 0;

private:
    const QType mQType;
    const FullQName mQName;
};

} // namespace Minimal
} // namespace mdns
