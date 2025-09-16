#pragma once


#include "common.h"
#include "GPIO.h"

#include "KeyPage.h"
#include "HID_InputReport.h"
#include "RingBuffer.h"

#if ( USB_ENABLED )
#include "usb_device.h"
#endif

namespace daniel
{

class KBD
{

private :
	ADC_HandleTypeDef  * pAdcHandle ;

#if ( USB_ENABLED )
	USBD_HandleTypeDef * pUsbHandle ;
#endif

private :
	uint32_t adcValues[ 4 ] ;

private :
	static constexpr uint8_t const outSignal = 12 ;
	static constexpr uint8_t const  inSignal =  8 ;
	static constexpr uint8_t const keyCnt    = outSignal * inSignal ;

private :
	static KeyPage const keymap[ keyCnt * 2 ] ;

private :
	bool inKey[ 8 ] ;

	bool repeat[ keyCnt ] ;
	bool currKeyPressed[ keyCnt ] ;
	bool prevKeyPressed[ keyCnt ] ;

	bool anyKeyPressed ;
	bool isBlink ;
	bool isBufAble ;

private :
	uint32_t prevTime [ keyCnt ] ;

private :
	GPIO gpio ;

private :
	RingBuffer< HID_InputReport > rBuf ;

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

public :
	void Run() ;
	void SetAdcHandle( ADC_HandleTypeDef  * pHandle ) ;

#if ( USB_ENABLED )
	void SetUSBHandle( USBD_HandleTypeDef * pHandle ) ;
#endif

public :
	KBD() ;
	KBD( ADC_HandleTypeDef * pAdcHandle
#if ( USB_ENABLED )
    , USBD_HandleTypeDef * pUsbHandle
#endif
	) ;

} ;


} // namespace daniel
