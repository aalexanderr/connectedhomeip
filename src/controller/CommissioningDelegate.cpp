/*
 * SPDX-FileCopyrightText: (c) 2021 Project CHIP Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <controller/CommissioningDelegate.h>

namespace chip {
namespace Controller {

const char * StageToString(CommissioningStage stage)
{
    switch (stage)
    {
    case kError:
        return "Error";
        break;

    case kSecurePairing:
        return "SecurePairing";
        break;

    case kReadCommissioningInfo:
        return "ReadCommissioningInfo";
        break;

    case kArmFailsafe:
        return "ArmFailSafe";
        break;

    case kScanNetworks:
        return "ScanNetworks";
        break;

    case kConfigRegulatory:
        return "ConfigRegulatory";
        break;

    case kSendPAICertificateRequest:
        return "SendPAICertificateRequest";
        break;

    case kSendDACCertificateRequest:
        return "SendDACCertificateRequest";
        break;

    case kSendAttestationRequest:
        return "SendAttestationRequest";
        break;

    case kAttestationVerification:
        return "AttestationVerification";
        break;

    case kSendOpCertSigningRequest:
        return "SendOpCertSigningRequest";
        break;

    case kValidateCSR:
        return "ValidateCSR";
        break;

    case kGenerateNOCChain:
        return "GenerateNOCChain";
        break;

    case kSendTrustedRootCert:
        return "SendTrustedRootCert";
        break;

    case kSendNOC:
        return "SendNOC";
        break;

    case kWiFiNetworkSetup:
        return "WiFiNetworkSetup";
        break;

    case kThreadNetworkSetup:
        return "ThreadNetworkSetup";
        break;

    case kWiFiNetworkEnable:
        return "WiFiNetworkEnable";
        break;

    case kThreadNetworkEnable:
        return "ThreadNetworkEnable";
        break;

    case kFindOperational:
        return "FindOperational";
        break;

    case kSendComplete:
        return "SendComplete";
        break;

    case kCleanup:
        return "Cleanup";
        break;

    case kNeedsNetworkCreds:
        return "NeedsNetworkCreds";
        break;

    default:
        return "???";
        break;
    }
}

} // namespace Controller
} // namespace chip
