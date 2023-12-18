/*
*	DataExporter.hpp
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#ifndef TEST_CPP_IO_DATAEXPORTER_HPP_
#define TEST_CPP_IO_DATAEXPORTER_HPP_

#include "../system/types.hpp"

namespace test {
namespace system {
class Cooler;
class Heater;
class System;
enum class CompressorStatus : ui8;
enum class ElectricResistanceStatus : ui8;
} /* namespace system */

namespace io {

/*!
*	@brief Parses an enum into a string
* 
*	Using c++17 or newer version, we can use "Magic Enum C++" that parses in compilation
*	time all enums and gives a lot of funtions to enums
*	This function could be removed and replaced with a magic enum function
*
*	@param[in] status Compressor status value
*
*	@return Enum in string format (string_t or const char*)
*
*	@sa @ref data_parser
*
*	@since Added in version 1.0.
*
*	@ingroup io
*/
__NO_DISCARD__ system::string_t parseEnum(const system::CompressorStatus status);
/*!
*	@brief Parses an enum into a string
* 
*	Using c++17 or newer version, we can use "Magic Enum C++" that parses in compilation
*	time all enums and gives a lot of funtions to enums
*	This function could be removed and replaced with a magic enum function
*
*	@param[in] status Electric resistance status value
*
*	@return Enum in string format (string_t or const char*)
*
*	@sa @ref data_parser
*
*	@since Added in version 1.0.
*
*	@ingroup io
*/
__NO_DISCARD__ system::string_t parseEnum(const system::ElectricResistanceStatus status);

/*!
*	@brief Exportes a system control data into a CSV file
* 
*	If file already exists, this function will add new rows of data without deleting any data
*
*	@param[in] system System data to export
*	@param[in] filename File name to export data
*
*	@return False on error (this time error will be printed in stderr)
*
*	@sa @ref data_parser
*
*	@since Added in version 1.0.
*
*	@ingroup io
*/
__NO_DISCARD__ bool exportToCSV(const system::System& system, system::string_t filename);

__NO_DISCARD__ bool print(const system::System& system);

} /* namespace io */
} /* namespace test */

#endif /* TEST_CPP_IO_DATAEXPORTER_HPP_ */
