/*
 * GPIO.cpp
 *
 *  Created on: Feb 24, 2025
 *      Author: Daniel Lee
 */


#include "GPIO.h"


extern I2C_HandleTypeDef hi2c1 ;


daniel::GPIO::GPIO()
	: isExpAble( false )
{
	HAL_GPIO_WritePin( GPIOB , GPIO_PIN_14 , GPIO_PIN_SET ) ;
	HAL_GPIO_WritePin( GPIOB , GPIO_PIN_15 , GPIO_PIN_SET ) ;
	HAL_GPIO_WritePin( GPIOC , GPIO_PIN_6  , GPIO_PIN_SET ) ;
}


daniel::GPIO::GPIO( I2C_HandleTypeDef * pTypeDef )
	: isExpAble( false )
{
	HAL_GPIO_WritePin( GPIOB , GPIO_PIN_14 , GPIO_PIN_SET ) ;
	HAL_GPIO_WritePin( GPIOB , GPIO_PIN_15 , GPIO_PIN_SET ) ;
	HAL_GPIO_WritePin( GPIOC , GPIO_PIN_6  , GPIO_PIN_SET ) ;

	exp.SetHandle( pTypeDef ) ;
	bool is = exp.Init() ;

	if( true == is )
	{
		isExpAble = true ;
		exp.SetDir( 0xFF ) ;      // read mode
		exp.SetPullUp( 0x00 ) ;   // disable all internal pull-up
		exp.SetPolarity( 0xFF ) ; // inverse all pin's polarity
	}
	else
	{
		isExpAble = false ;
	}
}


void daniel::GPIO::SetHandle( I2C_HandleTypeDef * pTypeDef )
{
	exp.SetHandle( pTypeDef ) ;
	bool is = exp.Init() ;

	if( true == is )
	{
		isExpAble = true ;
		exp.SetDir( 0xFF ) ;      // read mode
		exp.SetPullUp( 0x00 ) ;   // disable all internal pull-up
		exp.SetPolarity( 0xFF ) ; // inverse all pin's polarity
	}
	else
	{
		isExpAble = false ;
	}
}


void daniel::GPIO::SetDbgLed1( bool const & isOn )
{
	HAL_GPIO_WritePin( GPIOB , GPIO_PIN_14 , ( true == isOn ) ? GPIO_PIN_RESET : GPIO_PIN_SET ) ;
}


void daniel::GPIO::SetDbgLed2( bool const & isOn )
{
	HAL_GPIO_WritePin( GPIOB , GPIO_PIN_15 , ( true == isOn ) ? GPIO_PIN_RESET : GPIO_PIN_SET ) ;
}


void daniel::GPIO::SetDbgLed3( bool const & isOn )
{
	HAL_GPIO_WritePin( GPIOC , GPIO_PIN_6  , ( true == isOn ) ? GPIO_PIN_RESET : GPIO_PIN_SET ) ;
}


void daniel::GPIO::SetNKROLed( bool const & isOn )
{
	HAL_GPIO_WritePin( GPIOC , GPIO_PIN_3  , ( true == isOn ) ? GPIO_PIN_RESET : GPIO_PIN_SET ) ;
}

void daniel::GPIO::Set6KROLed( bool const & isOn )
{
	HAL_GPIO_WritePin( GPIOC , GPIO_PIN_2  , ( true == isOn ) ? GPIO_PIN_RESET : GPIO_PIN_SET ) ;
}


void daniel::GPIO::ToggleDbgLed1()
{
	HAL_GPIO_TogglePin( GPIOB , GPIO_PIN_14 ) ;
}


void daniel::GPIO::ToggleDbgLed2()
{
	HAL_GPIO_TogglePin( GPIOB , GPIO_PIN_15 ) ;
}


void daniel::GPIO::ToggleDbgLed3()
{
	HAL_GPIO_TogglePin( GPIOC , GPIO_PIN_6  ) ;
}


bool daniel::GPIO::GetSwStatus( bool & sw , uint8_t const & pos )
{
	if( 0 == pos || 8 < pos || false == isExpAble )
	{
		return false ;
	}

	uint8_t value ;
	bool is = exp.Read( value ) ;
	if( false == is )
	{
		return false ;
	}

	sw = 0 < ( value & ( 0x80 >> ( pos - 1 ) ) ) ? true : false ;

	return true ;
}


bool daniel::GPIO::GetSwValue( uint8_t & value )
{
	if( false == isExpAble )
	{
		return false ;
	}

	bool is = exp.Read( value ) ;
	if( false == is )
	{
		return false ;
	}

	return true ;
}

