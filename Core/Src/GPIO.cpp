/*
 * GPIO.cpp
 *
 *  Created on: Feb 24, 2025
 *      Author: Daniel Lee
 */


#include "GPIO.h"


daniel::GPIO::GPIO()
{
	HAL_GPIO_WritePin( GPIOB , GPIO_PIN_14 , GPIO_PIN_SET ) ;
	HAL_GPIO_WritePin( GPIOB , GPIO_PIN_15 , GPIO_PIN_SET ) ;
	HAL_GPIO_WritePin( GPIOC , GPIO_PIN_6  , GPIO_PIN_SET ) ;
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
