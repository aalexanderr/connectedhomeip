/*
 * SPDX-FileCopyrightText: (c) 2021 Project CHIP Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */
package com.matter.tv.server.tvapp;

/*
 *   This class is provides the JNI interface to the linux layer of the ContentAppPlatform
 */
public class AppPlatform {
  private static final String TAG = "AppPlatform";

  public AppPlatform(ContentAppEndpointManager manager) {
    nativeInit(manager);
  }

  // Initializes the ContentAppPlatform on startup
  public native void nativeInit(ContentAppEndpointManager manager);

  // Method to add a content app as a new endpoint
  public native int addContentApp(
      String vendorName,
      int vendorId,
      String appName,
      int productId,
      String appVersion,
      ContentAppEndpointManager manager);

  // Method to add a content app at an existing endpoint after restart of the matter server
  public native int addContentAppAtEndpoint(
      String vendorName,
      int vendorId,
      String appName,
      int productId,
      String appVersion,
      int endpointId,
      ContentAppEndpointManager manager);

  // Method to remove content app as endpoint (happens when the app is uninstalled)
  public native int removeContentApp(int endpointId);

  // Method to report attribute change for content app endpoints to the SDK
  public native void reportAttributeChange(int endpointId, int clusterId, int attributeId);

  static {
    System.loadLibrary("TvApp");
  }
}
