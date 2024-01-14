/*
*	types.hpp
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#ifndef TEST_CPP_SYSTEM_TYPES_H_
#define TEST_CPP_SYSTEM_TYPES_H_

typedef unsigned char ui8;
typedef unsigned short ui16;
typedef unsigned int ui32;
typedef unsigned long ui64;

typedef float f32;
typedef double f64;

typedef const char* string_t;

typedef f32 Pressure_t;
typedef f32 Temperature_t;
typedef Pressure_t HightPressure_t;
typedef Pressure_t LowPressure_t;
typedef ui8 FanSpeed_t;
typedef ui8 PumpFlow_t;

typedef struct {
	HightPressure_t hightPressure;
	LowPressure_t lowPressure;
} PressureValue_t;

#define USER_TEMPERATURE_MIN 18.0
#define USER_TEMPERATURE_MAX 30.0
#define STANDBY_PRESSURE 5.0
#define PRESSURE_MIN 0.5
#define PRESSURE_MAX 25.0

#define FAN_SPEED_MIN 0
#define FAN_SPEED_MAX 100

#define WATER_PUMP_FLOW_MIN 0
#define WATER_PUMP_FLOW_MAX 100

typedef enum {
	CompressorStatus_Off,
	CompressorStatus_Min,
	CompressorStatus_Med,
	CompressorStatus_Max
} CompressorStatus;
typedef enum {
	ElectricResistanceStatus_Off,
	ElectricResistanceStatus_Min,
	ElectricResistanceStatus_Med,
	ElectricResistanceStatus_Max
} ElectricResistanceStatus;

#endif // TEST_CPP_SYSTEM_TYPES_H_
