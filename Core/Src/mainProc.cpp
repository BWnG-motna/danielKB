/*
 * mainProc.cpp
 *
 *  Created on: Feb 24, 2025
 *      Author: Daniel Lee
 */


#include "mainProc.h"
#include "KBD.h"

#include "usb_device.h"
#include "usbd_hid.h"

#include "usart.h"


extern ADC_HandleTypeDef  hadc1  ;
extern TIM_HandleTypeDef  htim7  ;
extern UART_HandleTypeDef huart1 ;
extern USBD_HandleTypeDef hUsbDeviceFS ;

daniel::USART uart ;
daniel::KBD   kbd  ;


void MainProc()
{
	HAL_TIM_Base_Start_IT( & htim7 ) ;

	uart.SetHandle( & huart1 ) ;
	uart.Begin() ;

	kbd.SetAdcHandle( & hadc1 ) ;
	kbd.SetUSBHandle( & hUsbDeviceFS ) ;
	kbd.Run() ;

	while( true ) ;
}



void UartRX( UART_HandleTypeDef * pHandle , uint8_t const port )
{
	uint32_t isrflags = READ_REG( pHandle->Instance->SR  ) ;
	uint32_t cr1its   = READ_REG( pHandle->Instance->CR1 ) ;

	if( ( 0U != ( isrflags & USART_SR_RXNE ) ) && ( 0U != ( cr1its & USART_CR1_RXNEIE ) ) )
	{
		uint32_t rx  = pHandle->Instance->DR ;
		uint8_t  dat = ( uint8_t )( rx ) ;

		ReceiveUartRx( dat , port ) ;
	}
}


void ReceiveUartRx( uint8_t const dat , uint8_t const port )
{
	/**/ if( 1 == port )
	{
		uart.Recv_A_CH( dat ) ;
	}
}
