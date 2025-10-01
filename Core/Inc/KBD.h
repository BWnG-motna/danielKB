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
#include "usb_device.h"
#include "HID_InputReport.h"


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
	static constexpr uint8_t const keyLShiftPos = 72 ;
	static constexpr uint8_t const keyRShiftPos = 73 ;
	static constexpr uint8_t const keyLAltPos   = 86 ;
	static constexpr uint8_t const keyRAltPos   = 87 ;
	static constexpr uint8_t const keyLGuiPos   = 94 ;
	static constexpr uint8_t const keyRGuiPos   = 95 ;

private :
	static KeyPage const keymap[ keyCnt * 2 ] ;

private :
	bool inKey[ 8 ] ;
	bool currKeyPressed[ keyCnt ] ;
	bool prevKeyPressed[ keyCnt ] ;


private :
	uint32_t prevTime[ keyCnt ] ;
	uint8_t  repeat  [ keyCnt ] ;

private :
	GPIO gpio ;


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
	void Loop() ;

private :
	void KeyPress( HID_InputReport const & ir ) ;
	void KeyRelease( HID_InputReport const & ir ) ;

private :
	bool     IsConsumerProfile( KeyPage const & keyPage ) ;
	uint16_t GetConsumerKeyValue( KeyPage const & keyPage ) ;

public :
	void Run() ;
	void SetAdcHandle( ADC_HandleTypeDef  * pHandle ) ;
	void SetUSBHandle( USBD_HandleTypeDef * pHandle ) ;

public :
	KBD() ;
	KBD( ADC_HandleTypeDef * pAdcHandle , USBD_HandleTypeDef * pUsbHandle ) ;


} ; // class KBD


} // namespace daniel
