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




extern uint8_t g_USB_HID_keyDescProfileMode ; // 1 == NKRO , 2 == 6KRO


void SetKeyDescProfileMode( daniel::GPIO & gpio , daniel::KeyProfile & kp )
{
	bool sw = false ;
	uint8_t const pos = 1 ;


	// Pre-processing was performed so that the keyboard operates normally,
	// even if the MCP23008T used as the GPIO expander does not operate properly.

	using KP = daniel::KeyProfile ;
	kp = ( 1 == g_USB_HID_keyDescProfileMode ) ? KP::Profile_NKRO : KP::Profile_6KRO ;

	if( false == gpio.GetSwStatus( sw , pos ) )
	{
		return ;
	}

	kp = ( true == sw ) ? KP::Profile_6KRO : KP::Profile_NKRO ;
	g_USB_HID_keyDescProfileMode = ( true == sw ) ? 2 : 1 ;
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




extern uint8_t       g_USB_HID_SerialNo[ 126 ] ;
extern uint8_t       g_USB_HID_SerialNoLen ;
extern uint8_t const g_USB_HID_SerialNoMaxLen ;


void SetHIDSerialNo()
{
	volatile uint32_t const serialCntAddr = 0x08020000 ;
	volatile uint32_t const serialDatAddr = 0x08020001 ;
	volatile uint8_t  const serialCount   = ( * ( __IO uint8_t * ) serialCntAddr ) ;


	char const * pDefaultSerialNo = "danielKB_no.000" ;

	g_USB_HID_SerialNoLen = 15 ;
	for( uint8_t pos = 0 ; pos < 15 ; ++pos )
	{
		g_USB_HID_SerialNo[ pos ] = static_cast< uint8_t >( pDefaultSerialNo[ pos ] ) ;
	}

	if( 3 != serialCount )
	{
		return ;
	}


	for( uint8_t pos = 0 ; pos < serialCount ; ++pos )
	{
		volatile uint8_t const val = ( * ( __IO uint8_t * ) ( serialDatAddr + pos ) ) ;

		uint8_t no = val ;

		if( '0' <= no && '9' >= no )
		{
			no = no - '0' ;
		}
		if( 9 < no )
		{
			no = 0 ;
		}

		g_USB_HID_SerialNo[ 12 + pos ] = no + '0' ;
	}


	volatile uint32_t const descCntAddr = 0x08020010 ;
	volatile uint32_t const descDatAddr = 0x08020011 ;
	volatile uint8_t  const descCount   = ( * ( __IO uint8_t * ) descCntAddr ) ;

	if( 0 == descCount || ( g_USB_HID_SerialNoMaxLen - 17 ) < descCount )
	{
		return ;
	}

	g_USB_HID_SerialNo[ 15 ] = ' ' ;
	g_USB_HID_SerialNo[ 16 ] = ' ' ;
	g_USB_HID_SerialNoLen += 2 ;

	for( uint8_t pos = 0 ; pos < descCount ; ++pos )
	{
		volatile uint8_t const val = ( * ( __IO uint8_t * ) ( descDatAddr + pos ) ) ;

		uint8_t no = val ;
		if( 0x20 > no || 0x7e < no )
		{
			no = ' ' ;
		}

		g_USB_HID_SerialNo[ 17 + pos ] = no ;
		g_USB_HID_SerialNoLen++ ;
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
