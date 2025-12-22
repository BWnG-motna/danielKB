/*
 * common.h
 *
 *  Created on: Feb 24, 2025
 *      Author: Daniel Lee
 */

#pragma once

#include <stdint.h>
#include "stm32f1xx_hal.h"

#ifdef __cplusplus
 extern "C" {
#endif


uint32_t millis() ;

uint32_t DelayMs( uint32_t const ms ) ;
uint32_t DelayUs( uint32_t const us ) ;

#ifdef __cplusplus
}
#endif
