/*
 * MCP23008T.cpp
 *
 *  Created on: Aug 4, 2026
 *      Author: Daniel Lee
 */


#include "MCP23008T.h"


daniel::MCP23008T::MCP23008T()
	: pHandle( nullptr )
{

}


daniel::MCP23008T::MCP23008T( I2C_HandleTypeDef * pTypeDef )
	: pHandle( pTypeDef )
{

}


void daniel::MCP23008T::SetHandle( I2C_HandleTypeDef * pTypeDef )
{
	pHandle = pTypeDef ;
}


bool daniel::MCP23008T::Init()
{
	if( nullptr == pHandle )
	{
		return false ;
	}


	if( 0x20 > devAddr || 0x27 < devAddr )
	{
		return false ;
	}

	uint8_t const addr = ( devAddr << 1 ) ;
	HAL_StatusTypeDef typeDef = HAL_I2C_IsDeviceReady( pHandle , addr , tryCnt , delayMs ) ;
	if( HAL_OK != typeDef )
	{
		return false ;
	}

	return true ;
}


bool daniel::MCP23008T::Set( uint8_t const & reg , uint8_t const & value )
{
	if( nullptr == pHandle )
	{
		return false ;
	}

	uint8_t dat[ 2 ]   = { reg , value } ;
	uint8_t const addr = ( devAddr << 1 ) ;
	HAL_StatusTypeDef typeDef = HAL_I2C_Master_Transmit( pHandle , addr , dat , 2 , delayMs ) ;
	if( HAL_OK != typeDef )
	{
		return false ;
	}

	return true ;
}


bool daniel::MCP23008T::Get( uint8_t const & reg , uint8_t & value )
{
	if( nullptr == pHandle )
	{
		return false ;
	}

	uint8_t const addr = ( devAddr << 1 ) ;
	HAL_StatusTypeDef typeDef = HAL_I2C_Mem_Read( pHandle , addr , reg , 1 , & value , 1 , delayMs ) ;
	if( HAL_OK != typeDef )
	{
		return false ;
	}

	return true ;
}


bool daniel::MCP23008T::SetDir( uint8_t const & dir )
{
	return Set( REG_DDR , dir ) ;
}


bool daniel::MCP23008T::GetDir( uint8_t & dir )
{
	return Get( REG_DDR , dir ) ;
}


bool daniel::MCP23008T::SetPolarity( uint8_t const & pol )
{
	return Set( REG_POLARITY , pol ) ;
}


bool daniel::MCP23008T::GetPolarity( uint8_t & pol )
{
	return Get( REG_POLARITY , pol ) ;
}


bool daniel::MCP23008T::SetPullUp( uint8_t const & up )
{
	return Set( REG_PULLUP , up ) ;
}


bool daniel::MCP23008T::GetPullUp( uint8_t & up )
{
	return Get( REG_PULLUP , up ) ;
}


bool daniel::MCP23008T::Write( uint8_t const & val )
{
	return Set( REG_OLAT , val ) ;
}


bool daniel::MCP23008T::Read( uint8_t & val )
{
	return Get( REG_GPIO , val ) ;
}


