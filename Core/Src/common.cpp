/*
 * common.cpp
 *
 *  Created on: Oct 01, 2025
 *      Author: Daniel Lee
 */

#include "common.h"

namespace
{
	TIM_HandleTypeDef * pHtim = nullptr ;
	volatile uint32_t * pMillisec ;
}


void RegisterDelayTimer( TIM_HandleTypeDef * p )
{
	pHtim = p ;
}


void RegisterMillisCounter( volatile uint32_t * p )
{
	pMillisec = p ;
}


uint32_t millis()
{
	if( nullptr == pMillisec )
	{
		return 0 ;
	}

	return *pMillisec ;
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
	if( 1 > delayUs || nullptr == pHtim )
	{
		return 0 ;
	}

	uint32_t start  = __HAL_TIM_GET_COUNTER( pHtim ) ;
	uint32_t remain = delayUs ;

	while( 0 < remain )
	{
		uint32_t current = __HAL_TIM_GET_COUNTER( pHtim ) ;
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
