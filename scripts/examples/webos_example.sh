#!/usr/bin/env bash
#
# SPDX-FileCopyrightText: (c) 2022 Project CHIP Authors
#
# SPDX-License-Identifier: Apache-2.0
#

# Activating connectedhomeip build environment
source scripts/activate.sh

# Clone webos_sdk
echo "##### Cloning webOS OSE SDK #####"
git clone https://github.com/cabin15/webos-ose-ndk third_party/webos_sdk

# Extract webOS SDK
cat third_party/webos_sdk/v2.14.1/webos_sdk.tar* | (
    cd third_party/webos_sdk/v2.14.1/
    tar xvzf -
)

# Grant execute permission for NDK install script
chmod 555 third_party/webos_sdk/v2.14.1/webos-sdk-x86_64-cortexa7t2hf-neon-vfpv4-toolchain-2.14.1.g.sh

# Install webOS OSE NDK
echo "##### Install webOS OSE NDK #####"
third_party/webos_sdk/v2.14.1/webos-sdk-x86_64-cortexa7t2hf-neon-vfpv4-toolchain-2.14.1.g.sh -d third_party/webos_sdk/v2.14.1 -y

# Activating webOS NDK build environment
echo "##### Activating webOS NDK build environment #####"
source third_party/webos_sdk/v2.14.1/environment-setup-cortexa7t2hf-neon-vfpv4-webos-linux-gnueabi
echo ""

# Build webos example
echo "##### Build webos example #####"
echo "##### Performing gn gen #####"
gn gen out/host --args="is_debug=false target_os=\"webos\" target_cpu=\"arm\" chip_enable_python_modules=false ar_webos=\"$AR\" cc_webos=\"$CC -Wno-format-security\" cxx_webos=\"$CXX\" webos_sysroot=\"$PKG_CONFIG_SYSROOT_DIR\" chip_build_tests=false enable_syslog=true treat_warnings_as_errors=false"

echo "##### Building by ninja #####"
ninja -C out/host
