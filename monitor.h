#pragma once

constexpr const float Min_Normal_Temperature_F = 95.0F;
constexpr const float Max_Normal_Temperature_F = 102.0F;
constexpr const float Min_Normal_PulseRange = 60.0F;
constexpr const float Max_Normal_PulseRange = 100.0F;
constexpr const float Min_Normal_SPO2 = 90.0F;

bool IsTemperatureInFarenheitCritical(float temperature);
bool IsPulseRateCritical(float pulseRate);
bool IsOxygenSaturationCritical(float spo2);
int vitalsOk(float temperature, float pulseRate, float spo2);
