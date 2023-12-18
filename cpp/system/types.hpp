/*
*	types.hpp
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#ifndef TEST_CPP_SYSTEM_TYPES_HPP_
#define TEST_CPP_SYSTEM_TYPES_HPP_

#include <utility>

namespace test {
namespace system {

typedef unsigned char ui8;
typedef unsigned short ui16;
typedef unsigned int ui32;
typedef unsigned long ui64;

typedef float f32;
typedef double f64;

typedef const char* string_t;

typedef f64 Pressure;
typedef f64 Temperature;
typedef Pressure HightPressure;
typedef Pressure LowPressure;
typedef ui8 FanSpeed;
typedef ui8 PumpFlow;

typedef std::pair<HightPressure, LowPressure> PressureValue;

constexpr Temperature USER_TEMPERATURE_MIN = 18.0;
constexpr Temperature USER_TEMPERATURE_MAX = 30.0;
constexpr Pressure STANDBY_PRESSURE = 5.0;
constexpr Pressure PRESSURE_MIN = 0.5;
constexpr Pressure PRESSURE_MAX = 25.0;

constexpr FanSpeed FAN_SPEED_MIN = 0;
constexpr FanSpeed FAN_SPEED_MAX = 100;

constexpr PumpFlow WATER_PUMP_FLOW_MIN = 0;
constexpr PumpFlow WATER_PUMP_FLOW_MAX = 100;

enum class CompressorStatus : ui8 { Off, Min, Med, Max };
enum class ElectricResistanceStatus : ui8 { Off, Min, Med, Max };

} /* namespace system */
} /* namespace test */


// Do not let anyone ignore function result without analyzing if it could be ignored
#define __NO_DISCARD__ [[nodiscard]]

#endif /* TEST_CPP_SYSTEM_TYPES_HPP_ */
