/*
 * common.cpp
 *
 *  Created on: Oct 01, 2025
 *      Author: Daniel Lee
 */

#include "common.h"


extern uint32_t millisec ;
extern TIM_HandleTypeDef  htim8  ;


uint32_t millis()
{
	return millisec ;
}


uint32_t DelayMs( uint32_t const ms )
{
	if( 1 > ms )
	{
		return 0 ;
	}

	uint32_t totalRemain = 0 ;

	for( uint32_t pos = 0 ; pos < ms ; ++pos )
	{
		uint32_t remain = DelayUs( 1000 ) ;
		totalRemain += remain ;
	}

	if( 1000 <= totalRemain )
	{
		uint32_t extraMs = totalRemain / 1000 ;
		totalRemain %= 1000 ;

		for( uint32_t pos = 0 ; pos < extraMs ; ++pos )
		{
			DelayUs( 1000 ) ;
		}
	}

	return totalRemain ;
}


uint32_t DelayUs( uint32_t const delayUs )
{
	if( 1 > delayUs )
	{
		return 0 ;
	}

	uint32_t start  = __HAL_TIM_GET_COUNTER( & htim8 ) ;
	uint32_t remain = delayUs ;

	while( 0 < remain )
	{
		uint32_t current = __HAL_TIM_GET_COUNTER( & htim8 ) ;
		uint32_t elapsed ;

		if( start <= current )
		{
			elapsed = current - start ;
		}
		else
		{
			elapsed = ( 0xFFFFU - start ) + current + 1 ;
		}

		if( remain <= elapsed )
		{
			break ;
		}

		remain -= elapsed ;
		start = current ;
	}

	return remain ; // reduce
}
