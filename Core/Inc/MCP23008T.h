/*
 * MCP23008T.h
 *
 *  Created on: Aug 4, 2026
 *      Author: Daniel Lee
 */

#pragma once


#include "common.h"
#include "stm32f1xx_hal_i2c.h"


namespace daniel
{

class MCP23008T // MCP23008T-E/ML
{

private :
	static constexpr uint16_t const devAddr = 0x20 ;
	static constexpr uint16_t const tryCnt  =    3 ;
	static constexpr uint16_t const delayMs =  100 ;

	static constexpr uint8_t const REG_DDR      = 0x00 ;
	static constexpr uint8_t const REG_POLARITY = 0x01 ;
	static constexpr uint8_t const REG_PULLUP   = 0x06 ;
	static constexpr uint8_t const REG_GPIO     = 0x09 ;
	static constexpr uint8_t const REG_OLAT     = 0x0A ;

private :
	I2C_HandleTypeDef * pHandle ;

private :
	bool Set( uint8_t const & reg , uint8_t const & value ) ;
	bool Get( uint8_t const & reg , uint8_t       & value ) ;

public :
	void SetHandle( I2C_HandleTypeDef * pTypeDef ) ;

public :
	bool Init() ;

	bool SetDir( uint8_t const & dir ) ;
	bool GetDir( uint8_t       & dir ) ;

	bool SetPolarity( uint8_t const & pol ) ;
	bool GetPolarity( uint8_t       & pol ) ;

	bool SetPullUp( uint8_t const & pol ) ;
	bool GetPullUp( uint8_t       & pol ) ;

	bool Write( uint8_t const & value ) ;
	bool Read ( uint8_t       & value ) ;

public :
	MCP23008T( I2C_HandleTypeDef * pTypeDef ) ;
	MCP23008T() ;

} ;

} // namespace daniel
