/*
 * SPDX-FileCopyrightText: (c) 2022 Project CHIP Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */
package chip.devicecontroller;

import javax.annotation.Nullable;

/** JNI wrapper callback class for {@link ReportCallback}. */
public class ReportEventCallbackJni {
  @Nullable private SubscriptionEstablishedCallback wrappedSubscriptionEstablishedCallback;
  @Nullable private ResubscriptionAttemptCallback wrappedResubscriptionAttemptCallback;
  private ReportEventCallback wrappedReportCallback;
  private long callbackHandle;

  public ReportEventCallbackJni(
      @Nullable SubscriptionEstablishedCallback subscriptionEstablishedCallback,
      ReportEventCallback reportCallback,
      ResubscriptionAttemptCallback resubscriptionAttemptCallback) {
    this.wrappedSubscriptionEstablishedCallback = subscriptionEstablishedCallback;
    this.wrappedReportCallback = reportCallback;
    this.wrappedResubscriptionAttemptCallback = resubscriptionAttemptCallback;
    this.callbackHandle =
        newCallback(subscriptionEstablishedCallback, reportCallback, resubscriptionAttemptCallback);
  }

  long getCallbackHandle() {
    return callbackHandle;
  }

  private native long newCallback(
      @Nullable SubscriptionEstablishedCallback subscriptionEstablishedCallback,
      ReportEventCallback wrappedCallback,
      @Nullable ResubscriptionAttemptCallback resubscriptionAttemptCallback);

  private native void deleteCallback(long callbackHandle);

  // TODO(#8578): Replace finalizer with PhantomReference.
  @SuppressWarnings("deprecation")
  protected void finalize() throws Throwable {
    super.finalize();

    if (callbackHandle != 0) {
      deleteCallback(callbackHandle);
      callbackHandle = 0;
    }
  }
}
