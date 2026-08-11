/*
 * KBD.h
 *
 *  Created on: Feb 24, 2025
 *      Author: Daniel Lee
 */

#pragma once


#include "common.h"
#include "GPIO.h"

#include "KeyPage.h"
#include "KeyStatus.h"
#include "KeyProfile.h"
#include "usb_device.h"

#include "HID_InputReport_6KRO.h"
#include "HID_InputReport_NKRO.h"


namespace daniel
{

using KeyPage = daniel::HID::DesktopProfile::KeyPage ;


class KBD
{

private :
	ADC_HandleTypeDef  * pAdcHandle ;
	USBD_HandleTypeDef * pUsbHandle ;

private :
	uint32_t adcValues[ 4 ] ;

private :
	static constexpr uint8_t const outSignal = 12 ;
	static constexpr uint8_t const  inSignal =  8 ;
	static constexpr uint8_t const keyCnt    = outSignal * inSignal ;

	static constexpr uint8_t const keySpPos     = 47 ;
	static constexpr uint8_t const keyFnPos     = 55 ;
	static constexpr uint8_t const keyLCtrlPos  = 64 ;
	static constexpr uint8_t const keyRCtrlPos  = keyCnt ;
	static constexpr uint8_t const keyLShiftPos = 72 ;
	static constexpr uint8_t const keyRShiftPos = 73 ;
	static constexpr uint8_t const keyLAltPos   = 86 ;
	static constexpr uint8_t const keyRAltPos   = 87 ;
	static constexpr uint8_t const keyLGuiPos   = 94 ;
	static constexpr uint8_t const keyRGuiPos   = 95 ;

private :
	static KeyPage const keymap[ keyCnt * 2 ] ;

private :
	bool inKey[ inSignal ] ;
	bool currK[ keyCnt ] ;
	bool prevK[ keyCnt ] ;

private :
	uint8_t  reptC[ keyCnt ] ;
	uint8_t  reptT[ keyCnt ] ;
	uint32_t prevT[ keyCnt ] ;

private :
	static constexpr uint8_t const modKeyCnt = 10 ;
	static uint8_t const modPos[ modKeyCnt ] ;
	KeyStatus modKeySt[ modKeyCnt ] ;

private :
	GPIO * pGpio ;

private :
	KeyProfile keyProfile ;

private :
	HID_InputReport_NKRO inputReportNKRO ;
	HID_InputReport_6KRO inputReport6KRO ;

private :
	bool useIme ;

private :
	void SetSigA( bool const & isSet ) ;
	void SetSigB( bool const & isSet ) ;
	void SetSigC( bool const & isSet ) ;
	void SetSigD( bool const & isSet ) ;
	void SetSigE( bool const & isSet ) ;
	void SetSigF( bool const & isSet ) ;
	void SetSigG( bool const & isSet ) ;
	void SetSigH( bool const & isSet ) ;
	void SetSigI( bool const & isSet ) ;
	void SetSigJ( bool const & isSet ) ;
	void SetSigK( bool const & isSet ) ;
	void SetSigL( bool const & isSet ) ;

private :
	void DefaultOutPut() ;
	void SetOut( uint8_t const & outNo ) ;

private :
	void GetIn() ;
	void GetInA() ;
	void GetInB() ;
	void GetInC() ;
	void GetInD() ;

private :
	uint32_t GetAdc( uint8_t const ch ) const ;
	uint32_t GetAdcA() const ;
	uint32_t GetAdcB() const ;
	uint32_t GetAdcC() const ;
	uint32_t GetAdcD() const ;

private :
	void LoopFor6KRO() ;
	void LoopForNKRO() ;

private :
	bool SendReport( uint8_t * pDat , uint16_t const & len ) ;

private :
	void KeyPress( HID_InputReport_6KRO const & ir ) ;
	void KeyPress( HID_InputReport_NKRO const & ir ) ;

private :
	void ReadKeyMatrix() ;
	void ConsumerKey( KeyPage const & k ) ;
	void SpKey() ;

private :
	HID_InputReport_NKRO MakeHIDInputReport_NKRO() ;
	HID_InputReport_6KRO MakeHIDInputReport_6KRO() ;

private :
	bool     IsConsumerProfile( KeyPage const & keyPage ) ;
	uint16_t GetConsumerKeyValue( KeyPage const & keyPage ) ;

public :
	void Run() ;
	void SetAdcHandle( ADC_HandleTypeDef  * pHandle ) ;
	void SetUSBHandle( USBD_HandleTypeDef * pHandle ) ;
	void SetGpio( GPIO * pHandle ) ;
	void SetProfile( KeyProfile const & profile ) ;
	void UseIme( bool const & is ) ;

public :
	KBD( ADC_HandleTypeDef * pAdcHandle , USBD_HandleTypeDef * pUsbHandle , GPIO * pGpioHandle ) ;
	KBD( ADC_HandleTypeDef * pAdcHandle , USBD_HandleTypeDef * pUsbHandle ) ;
	KBD() ;


} ; // class KBD


} // namespace daniel
