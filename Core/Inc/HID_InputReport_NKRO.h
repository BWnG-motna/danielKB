/*
 * HID_InputReport_NKRO.h
 *
 *  Created on: Aug 4, 2026
 *      Author: Daniel Lee
 */

#pragma once

#include "common.h"


namespace daniel
{

class HID_InputReport_NKRO
{

private :
	uint8_t reportId ;
	uint8_t rightGUI   : 1 ;
	uint8_t rightALT   : 1 ;
	uint8_t rightSHIFT : 1 ;
	uint8_t rightCTRL  : 1 ;
	uint8_t leftGUI    : 1 ;
	uint8_t leftALT    : 1 ;
	uint8_t leftSHIFT  : 1 ;
	uint8_t leftCTRL   : 1 ;
	uint8_t reserved ;
	uint8_t keyMap[ 20 ] ;

	uint16_t consumerKey ;

public :
	void SetReportID  ( uint8_t const & reportId ) ;
	void SetRightGUI  ( bool const & isSet ) ;
	void SetRightALT  ( bool const & isSet ) ;
	void SetRightSHIFT( bool const & isSet ) ;
	void SetRightCTRL ( bool const & isSet ) ;
	void SetLeftGUI   ( bool const & isSet ) ;
	void SetLeftALT   ( bool const & isSet ) ;
	void SetLeftSHIFT ( bool const & isSet ) ;
	void SetLeftCTRL  ( bool const & isSet ) ;

public :
	uint8_t GetModKey()   const ;
	uint8_t GetReportId() const ;
	void    SetModKey( uint8_t const & modKey ) ;

	void SetConsumerKey( uint16_t const & key ) ;
	void SetKeyCode( uint8_t const & keycode , bool const & isPress ) ;

public :
	void Reset() ;

public :
	uint8_t * GetSerialized() const ;
	uint16_t  GetSerializedLength() const ;

public :
	HID_InputReport_NKRO & operator=( HID_InputReport_NKRO const & o ) ;
	bool operator==( HID_InputReport_NKRO const & o ) const ;
	bool operator!=( HID_InputReport_NKRO const & o ) const ;

public :
	HID_InputReport_NKRO( HID_InputReport_NKRO const & o ) ;
	HID_InputReport_NKRO( uint8_t const & reportId = 1 ) ;

} ; // class HID_InputReport

}   // namespace daniel
