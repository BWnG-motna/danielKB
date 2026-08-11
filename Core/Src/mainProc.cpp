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
#include "GPIO.h"

extern ADC_HandleTypeDef  hadc1  ;
extern TIM_HandleTypeDef  htim7  ;
extern TIM_HandleTypeDef  htim8  ;
extern I2C_HandleTypeDef  hi2c1  ;
extern UART_HandleTypeDef huart1 ;
extern USBD_HandleTypeDef hUsbDeviceFS ;

extern uint32_t millisec ;

daniel::USART uart ;

uint8_t keyDescProfileMode = 1 ; // 1 == NKRO , 2 == 6KRO
uint8_t HIDSerialNo[ 12 ] ;
uint8_t HIDSerialNoLen ;


void SetKeyDescProfileMode( daniel::GPIO & gpio , daniel::KeyProfile & kp ) ;
bool ReadImeMode( daniel::GPIO & gpio ) ;


void MainProc()
{
	HAL_TIM_Base_Start_IT( & htim7 ) ;
	HAL_TIM_Base_Start   ( & htim8 ) ;

	RegisterDelayTimer( & htim8 ) ;
	RegisterMillisCounter( & millisec ) ;

	uart.SetHandle( & huart1 ) ;
	uart.Begin() ;

	daniel::GPIO gpio( & hi2c1 ) ;
	daniel::KeyProfile kp ;

	SetKeyDescProfileMode( gpio , kp ) ;
	SetHIDSerialNo() ;

	MX_USB_DEVICE_Init() ;

	daniel::KBD kbd  ;
	kbd.SetAdcHandle( & hadc1 ) ;
	kbd.SetUSBHandle( & hUsbDeviceFS ) ;
	kbd.SetGpio( & gpio ) ;
	kbd.SetProfile( kp ) ;
	kbd.UseIme( ReadImeMode( gpio ) ) ;
	kbd.Run() ;

	while( true ) ;
}


void SetKeyDescProfileMode( daniel::GPIO & gpio , daniel::KeyProfile & kp )
{
	bool sw = false ;
	uint8_t const pos = 1 ;


	// Pre-processing was performed so that the keyboard operates normally,
	// even if the MCP23008T used as the GPIO expander does not operate properly.

	using KP = daniel::KeyProfile ;
	kp = ( 1 == keyDescProfileMode ) ? KP::Profile_NKRO : KP::Profile_6KRO ;

	if( false == gpio.GetSwStatus( sw , pos ) )
	{
		return ;
	}

	kp = ( true == sw ) ? KP::Profile_6KRO : KP::Profile_NKRO ;
	keyDescProfileMode = ( true == sw ) ? 2 : 1 ;
}


bool ReadImeMode( daniel::GPIO & gpio )
{
	bool sw = false ;
	uint8_t const pos = 2 ;

	if( false == gpio.GetSwStatus( sw , pos ) )
	{
		return false ;
	}

	return ( true == sw ) ? true : false ;
}


void SetHIDSerialNo()
{
	volatile uint32_t const countAddr = 0x08020000 ;
	volatile uint32_t const  dataAddr = 0x08020001 ;
	volatile uint8_t  const dataCount = ( * ( __IO uint8_t * ) countAddr ) ;

	HIDSerialNo[  0 ] = 'd' ;
	HIDSerialNo[  1 ] = 'a' ;
	HIDSerialNo[  2 ] = 'n' ;
	HIDSerialNo[  3 ] = 'i' ;
	HIDSerialNo[  4 ] = 'e' ;
	HIDSerialNo[  5 ] = 'l' ;
	HIDSerialNo[  6 ] = 'K' ;
	HIDSerialNo[  7 ] = 'B' ;
	HIDSerialNo[  8 ] = '_' ;
	HIDSerialNo[  9 ] = '0' ;
	HIDSerialNo[ 10 ] = '0' ;
	HIDSerialNo[ 11 ] = '0' ;

	HIDSerialNoLen = 12 ;

	if( 3 != dataCount )
	{
		return ;
	}

	for( uint8_t pos = 0 ; pos < dataCount ; ++pos )
	{
		volatile uint8_t const val = ( * ( __IO uint8_t * ) ( dataAddr + pos ) ) ;

		uint8_t no = val ;
		if( 9 < no )
		{
			no = 0 ;
		}

		HIDSerialNo[ 9 + pos ] = no + '0' ;
	}
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
