// test/mocks/Arduino.h
#ifndef MOCK_ARDUINO_H
#define MOCK_ARDUINO_H

// Podstawowe typy, jeśli są potrzebne
#include <stdint.h> // dla uint8_t, itp.
#include <stddef.h> // dla size_t

// Jeśli twój kod używa np. HIGH, LOW, INPUT, OUTPUT
// #define HIGH 0x1
// #define LOW  0x0
// #define INPUT 0x0
// #define OUTPUT 0x1

// Jeśli twój kod używa obiektu Serial, zadeklaruj jego mock:
// class MockSerial {
// public:
//     void begin(long speed);
//     int available();
//     int read();
//     size_t write(uint8_t val);
//     // Dodaj inne metody, których używasz
// };
// extern MockSerial Serial; // Udostępnij globalnie

// Deklaracje innych funkcji Arduino, których używa twój kod z src/
// void delay(unsigned long ms);
// unsigned long millis(void);

#endif // MOCK_ARDUINO_H
