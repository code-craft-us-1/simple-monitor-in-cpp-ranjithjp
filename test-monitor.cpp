#include "./monitor.h"

#include "gtest/gtest.h"

TEST(Monitor, IndividualVital) {
    ASSERT_TRUE(IsTemperatureInFarenheitCritical(93.0F));
    ASSERT_TRUE(IsTemperatureInFarenheitCritical(105.0F));
    ASSERT_FALSE(IsTemperatureInFarenheitCritical(95.0F));
    ASSERT_FALSE(IsPulseRateCritical(70));
    ASSERT_FALSE(IsPulseRateCritical(100));
    ASSERT_TRUE(IsPulseRateCritical(110));
    ASSERT_FALSE(IsOxygenSaturationCritical(90));
    ASSERT_TRUE(IsOxygenSaturationCritical(88));
    ASSERT_FALSE(IsOxygenSaturationCritical(97));
}

TEST(Monitor, IndividualVitalForPrecision) {
    ASSERT_FALSE(IsTemperatureInFarenheitCritical(101.99999));
    ASSERT_TRUE(IsPulseRateCritical(59.99999));
    ASSERT_FALSE(IsPulseRateCritical(59.9999999));
    ASSERT_TRUE(IsPulseRateCritical(100.00001));
    ASSERT_FALSE(IsPulseRateCritical(100.0000001));
    ASSERT_TRUE(IsOxygenSaturationCritical(89.9999));
    ASSERT_FALSE(IsOxygenSaturationCritical(89.999999));
}

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  ASSERT_FALSE(vitalsOk(103, 99, 70));
  ASSERT_FALSE(vitalsOk(99, 102, 70));
  ASSERT_FALSE(vitalsOk(99, 70, 89));
  ASSERT_TRUE(vitalsOk(98.1, 70, 98));
}
