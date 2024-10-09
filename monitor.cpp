#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <bitset>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

void DisplayCriticalIdicator() {
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
    cout << std::endl;
}

bool IsTemperatureInFarenheitCritical(float temperature) {
    if (temperature < Min_Normal_Temperature_F || temperature > Max_Normal_Temperature_F) {
        cout << "Temperature is critical!\n";
        return true;
    }
    return false;
}

bool IsPulseRateCritical(float pulseRate) {
    if (pulseRate < Min_Normal_PulseRange || pulseRate > Max_Normal_PulseRange) {
        cout << "Pulse Rate is out of range!\n";
        return true;
    }
    return false;
}

bool IsOxygenSaturationCritical(float spo2) {
    if (spo2 < Min_Normal_SPO2) {
        cout << "Oxygen Saturation out of range!\n";
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
