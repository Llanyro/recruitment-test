/*
*	DataExporter.h
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#ifndef TEST_CPP_IO_DATAEXPORTER_H_
#define TEST_CPP_IO_DATAEXPORTER_H_

#include "../system/System.h"

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
int exportToCSV(const System_t* system, string_t filename);

int print(const System_t* system);

#endif // TEST_CPP_IO_DATAEXPORTER_H_
