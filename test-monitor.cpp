#include "./monitor.h"

#include "gtest/gtest.h"

TEST(Monitor, IndividualVital) {
    ASSERT_TRUE(IsTemperatureInFarenheitCritical(93.0F));  // Less than Min Temperature
    ASSERT_TRUE(IsTemperatureInFarenheitCritical(105.0F));  // Greater than Max Temperature
    ASSERT_FALSE(IsTemperatureInFarenheitCritical(98.0F));  // Normal Temperature
    ASSERT_FALSE(IsTemperatureInFarenheitCritical(Min_Normal_Temperature_F)); 
    ASSERT_FALSE(IsTemperatureInFarenheitCritical(Max_Normal_Temperature_F)); 
    ASSERT_TRUE(IsPulseRateCritical(50));  // Less than Min PulseRate
    ASSERT_TRUE(IsPulseRateCritical(110));  // Greater than Max PulseRate
    ASSERT_FALSE(IsPulseRateCritical(72));  // Normal PulseRate
    ASSERT_FALSE(IsPulseRateCritical(Min_Normal_PulseRange));
    ASSERT_FALSE(IsPulseRateCritical(Max_Normal_PulseRange));
    ASSERT_TRUE(IsOxygenSaturationCritical(88));  // Less than Min
    ASSERT_FALSE(IsOxygenSaturationCritical(97));  // More than Min
    ASSERT_FALSE(IsOxygenSaturationCritical(Min_Normal_SPO2));
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
  ASSERT_FALSE(vitalsOk(103, 99, 70));  // Temperature and saturation critical
  ASSERT_FALSE(vitalsOk(99, 102, 70));  // Pulse rate and saturation critical
  ASSERT_FALSE(vitalsOk(99, 70, 89));  // Only saturation is critical
  ASSERT_TRUE(vitalsOk(98.1, 70, 98));  // All is ok
}
