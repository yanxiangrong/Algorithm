//
// Created by yan on 2021/4/1.
// 时间格式化

#include <windows.h>
#include <ctime>
#include <iostream>

int startTimestamp;

unsigned int millis();

void setup() {
    startTimestamp = 1617296388;
}

void loop() {
    int zone = 8;
    static unsigned int startTime = millis();
    int timestamp = (int) (startTimestamp + (millis() - startTime) / 1000);
    int second = timestamp % 60;
    int minute = timestamp % 3600 / 60;
    int hour = (timestamp + zone * 3600) % 86400 / 3600;

    int year = (timestamp / 126'230'400) * 4 + 1970;
    int rest = timestamp % 126'230'400;
    if (rest < 63'072'400) {
        year += rest / 31'536'000;
    } else if (rest < 94'694'400) {
        year += 2;
    } else {
        year += 3;
    }

    rest = timestamp % 126'230'400 + zone * 3600;
    if (rest < 63'072'400) {
        rest %= 31'536'000;
    } else if (rest < 94'694'400) {
        rest -= 63'072'400;
    } else {
        rest -= 94'694'400;
    }
    int month = 0;
    int day = 0;
    if (rest < 2'678'400) {
        month += 1;
    } else {
        rest -= 2'678'400;
        month += 2;
        if (year % 4) {
            if (rest > 2'419'200) {
                rest -= 2'419'200;
                month += rest / 5'270'400 + 1;
                rest %= 5'270'400;
                if (rest >= 2'678'400) {
                    rest -= 2'678'400;
                    month += 1;
                    day = rest / 86400 + 1;
                }
            }
        } else {
            if (rest > 2'505'600) {
                rest -= 2'505'600;
                month += rest / 5'270'400 + 1;
                rest %= 5'270'400;
                if (rest >= 2'678'400) {
                    rest -= 2'678'400;
                    day = rest / 86400 + 1;
                    month += 1;
                }
            }
        }
    }

    std::printf("%04d-%02d-%02d %02d:%02d:%02d\n", year, month, day, hour, minute, second); // Windows 下的输出
}

int main() {
    setup();
    while (true) {
        loop();
        Sleep(1000);  // 暂停1秒,时间可以随意设定
    }
}

unsigned int millis() {
    clock_t time = clock();
    return time;
}
