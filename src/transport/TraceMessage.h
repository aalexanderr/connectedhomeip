/*
 * SPDX-FileCopyrightText: (c) 2021 Project CHIP Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <core/CHIPBuildConfig.h>
#include <system/SystemPacketBuffer.h>
#include <transport/Session.h>
#include <transport/raw/MessageHeader.h>
#include <transport/raw/PeerAddress.h>

#if CHIP_CONFIG_TRANSPORT_PW_TRACE_ENABLED
#include "pw_trace/trace.h"
#endif // CHIP_CONFIG_TRANSPORT_PW_TRACE_ENABLED

#if CHIP_CONFIG_TRANSPORT_TRACE_ENABLED || CHIP_CONFIG_TRANSPORT_PW_TRACE_ENABLED

#if CHIP_CONFIG_TRANSPORT_TRACE_ENABLED && CHIP_CONFIG_TRANSPORT_PW_TRACE_ENABLED
#define _CHIP_TRACE_MESSAGE_INTERNAL(type, data, size)                                                                             \
    ::chip::trace::internal::HandleTransportTrace(type, data, size);                                                               \
    PW_TRACE_INSTANT_DATA(::chip::trace::kTraceMessageEvent, type, data, size);
#elif CHIP_CONFIG_TRANSPORT_TRACE_ENABLED
#define _CHIP_TRACE_MESSAGE_INTERNAL(type, data, size) ::chip::trace::internal::HandleTransportTrace(type, data, size);
#else // CHIP_CONFIG_TRANSPORT_PW_TRACE_ENABLED
#define _CHIP_TRACE_MESSAGE_INTERNAL(type, data, size) PW_TRACE_INSTANT_DATA(::chip::trace::kTraceMessageEvent, type, data, size);
#endif // CHIP_CONFIG_TRANSPORT_TRACE_ENABLED && CHIP_CONFIG_TRANSPORT_PW_TRACE_ENABLED

#define CHIP_TRACE_MESSAGE_SENT(payloadHeader, packetHeader, data, dataLen)                                                        \
    do                                                                                                                             \
    {                                                                                                                              \
        const ::chip::trace::TraceSecureMessageSentData _trace_data{ &payloadHeader, &packetHeader, data, dataLen };               \
        _CHIP_TRACE_MESSAGE_INTERNAL(::chip::trace::kTraceMessageSentDataFormat, reinterpret_cast<const char *>(&_trace_data),     \
                                     sizeof(_trace_data));                                                                         \
    } while (0)

#define CHIP_TRACE_MESSAGE_RECEIVED(payloadHeader, packetHeader, session, peerAddress, data, dataLen)                              \
    do                                                                                                                             \
    {                                                                                                                              \
        const ::chip::trace::TraceSecureMessageReceivedData _trace_data{ &payloadHeader, &packetHeader, session,                   \
                                                                         &peerAddress,   data,          dataLen };                 \
        _CHIP_TRACE_MESSAGE_INTERNAL(::chip::trace::kTraceMessageReceivedDataFormat, reinterpret_cast<const char *>(&_trace_data), \
                                     sizeof(_trace_data));                                                                         \
    } while (0)

#define CHIP_TRACE_PREPARED_MESSAGE_SENT(destination, packetBuffer)                                                                \
    do                                                                                                                             \
    {                                                                                                                              \
        const ::chip::trace::TracePreparedSecureMessageData _trace_data{ destination, packetBuffer };                              \
        _CHIP_TRACE_MESSAGE_INTERNAL(::chip::trace::kTracePreparedMessageSentDataFormat,                                           \
                                     reinterpret_cast<const char *>(&_trace_data), sizeof(_trace_data));                           \
    } while (0)

#define CHIP_TRACE_PREPARED_MESSAGE_RECEIVED(source, packetBuffer)                                                                 \
    do                                                                                                                             \
    {                                                                                                                              \
        const ::chip::trace::TracePreparedSecureMessageData _trace_data{ source, packetBuffer };                                   \
        _CHIP_TRACE_MESSAGE_INTERNAL(::chip::trace::kTracePreparedMessageReceivedDataFormat,                                       \
                                     reinterpret_cast<const char *>(&_trace_data), sizeof(_trace_data));                           \
    } while (0)

#else // CHIP_CONFIG_TRANSPORT_TRACE_ENABLED || CHIP_CONFIG_TRANSPORT_PW_TRACE_ENABLED
#define CHIP_TRACE_MESSAGE_SENT(payloadHeader, packetHeader, data, dataLen)                                                        \
    do                                                                                                                             \
    {                                                                                                                              \
    } while (0)

#define CHIP_TRACE_MESSAGE_RECEIVED(payloadHeader, packetHeader, session, peerAddress, data, dataLen)                              \
    do                                                                                                                             \
    {                                                                                                                              \
    } while (0)

#define CHIP_TRACE_PREPARED_MESSAGE_SENT(destination, packetBuffer)                                                                \
    do                                                                                                                             \
    {                                                                                                                              \
    } while (0)

#define CHIP_TRACE_PREPARED_MESSAGE_RECEIVED(source, packetBuffer)                                                                 \
    do                                                                                                                             \
    {                                                                                                                              \
    } while (0)
#endif // CHIP_CONFIG_TRANSPORT_TRACE_ENABLED || CHIP_CONFIG_TRANSPORT_PW_TRACE_ENABLED

namespace chip {
namespace trace {

constexpr const char * kTraceMessageEvent                      = "SecureMsg";
constexpr const char * kTraceMessageSentDataFormat             = "SecMsgSent";
constexpr const char * kTraceMessageReceivedDataFormat         = "SecMsgReceived";
constexpr const char * kTracePreparedMessageSentDataFormat     = "PreparedMsgSent";
constexpr const char * kTracePreparedMessageReceivedDataFormat = "PreparedMsgReceived";

struct TraceSecureMessageSentData
{
    const PayloadHeader * payloadHeader;
    const PacketHeader * packetHeader;
    const uint8_t * packetPayload;
    size_t packetSize;
};

struct TraceSecureMessageReceivedData
{
    const PayloadHeader * payloadHeader;
    const PacketHeader * packetHeader;
    const Transport::Session * session;
    const Transport::PeerAddress * peerAddress;
    const uint8_t * packetPayload;
    size_t packetSize;
};

struct TracePreparedSecureMessageData
{
    const Transport::PeerAddress * peerAddress;
    const System::PacketBufferHandle * packetBuffer;
};

#if CHIP_CONFIG_TRANSPORT_TRACE_ENABLED

typedef void (*TransportTraceHandler)(const char * type, const void * data, size_t size);

// Configure the transport trace events to be sent to the provided handler.
void SetTransportTraceHook(TransportTraceHandler);

namespace internal {

void HandleTransportTrace(const char * type, const void * data, size_t size);

} // namespace internal

#endif // CHIP_CONFIG_TRANSPORT_TRACE_ENABLED

} // namespace trace
} // namespace chip
