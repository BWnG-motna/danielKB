/*
 * GPIO.h
 *
 *  Created on: Feb 24, 2025
 *      Author: Daniel Lee
 */

#pragma once

#include "common.h"
#include "MCP23008T.h"


namespace daniel
{

class GPIO
{

private :
	MCP23008T exp ;

private :
	bool isExpAble ;

public :
	void SetDbgLed1( bool const & isOn ) ;
	void SetDbgLed2( bool const & isOn ) ;
	void SetDbgLed3( bool const & isOn ) ;
	void SetNKROLed( bool const & isOn ) ;
	void Set6KROLed( bool const & isOn ) ;

	void ToggleDbgLed1() ;
	void ToggleDbgLed2() ;
	void ToggleDbgLed3() ;

	bool GetSwStatus( bool    & sw    , uint8_t const & pos ) ;
	bool GetSwValue ( uint8_t & value ) ;

public :
	void SetHandle( I2C_HandleTypeDef * pTypeDef ) ;

public :
	GPIO( I2C_HandleTypeDef * pTypeDef ) ;
	GPIO() ;

} ; // class GPIO

} // namespace daniel
