#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <bitset>

using std::cout;
using std::flush;
using std::this_thread::sleep_for;
using std::chrono::seconds;

void DisplayCriticalIdicator() {
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
    cout << std::endl;
}

bool CheckValueOutOfRange(float MinValue, float MaxValue, float value) {
    if (value < MinValue || value > MaxValue) {
        return true;
    }
    return false;
}

bool IsTemperatureInFarenheitCritical(float temperature) {
    if (CheckValueOutOfRange(Min_Normal_Temperature_F, Max_Normal_Temperature_F, temperature)) {
        cout << "Temperature is critical!\n";
        return true;
    }
    return false;
}

bool IsPulseRateCritical(float pulseRate) {
    if (CheckValueOutOfRange(Min_Normal_PulseRange, Max_Normal_PulseRange, pulseRate)) {
        cout << "Pulse Rate is critical!\n";
        return true;
    }
    return false;
}

bool IsOxygenSaturationCritical(float spo2) {
    if (CheckValueOutOfRange(Min_Normal_SPO2, Max_Normal_SPO2, spo2)) {
        cout << "Oxygen Saturation is critical!\n";
        return true;
    }
    return false;
}

bool isPatientCritical(float temperature, float pulseRate, float spo2) {
    std::bitset<Vitals::count> vitalsStatus{};

    vitalsStatus[Temperature] = IsTemperatureInFarenheitCritical(temperature);
    vitalsStatus[PulseRate] = IsPulseRateCritical(pulseRate);
    vitalsStatus[OxygenSaturation] = IsOxygenSaturationCritical(spo2);
    return vitalsStatus.any();
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    if (isPatientCritical(temperature, pulseRate, spo2)) {
        DisplayCriticalIdicator();
        return 0;
    }
    return 1;
}
