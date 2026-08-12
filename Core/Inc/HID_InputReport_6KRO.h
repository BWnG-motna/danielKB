/*
 * HID_InputReport_6KRO.h
 *
 *  Created on: Feb 24, 2025
 *      Author: Daniel Lee
 */

#pragma once

#include "common.h"


namespace daniel
{

class HID_InputReport_6KRO
{

private :
	static constexpr uint8_t keyMapCnt = 6 ;

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
	uint8_t keyMap[ keyMapCnt ] ;

	uint16_t consumerKey ;

private :
	uint8_t keyPos ;

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
	void SetKeyCode1  ( uint8_t const & keyCode ) ;
	void SetKeyCode2  ( uint8_t const & keyCode ) ;
	void SetKeyCode3  ( uint8_t const & keyCode ) ;
	void SetKeyCode4  ( uint8_t const & keyCode ) ;
	void SetKeyCode5  ( uint8_t const & keyCode ) ;
	void SetKeyCode6  ( uint8_t const & keyCode ) ;
	void SetKeyCode   ( uint8_t const & keyCode ) ;
	void SetKeyCode   ( uint8_t const ( & keyCode )[ 6 ] ) ;

public :
	uint8_t GetModKey()   const ;
	uint8_t GetReportId() const ;
	void    SetModKey( uint8_t const & modKey ) ;
	void    SetConsumerKey( uint16_t const & key ) ;

public :
	void SortKeyCode( uint8_t const ( & keyCode )[ 6 ] ) ;
	void GetKeyCode( uint8_t ( & keyCode )[ 6 ] ) ;
	bool AnyKeyPressed() const ;

public :
	void Reset() ;

public :
	uint8_t * GetSerialized() const ;
	uint16_t  GetSerializedLength() const ;

public :
	HID_InputReport_6KRO & operator=( HID_InputReport_6KRO const & o ) ;
	bool operator==( HID_InputReport_6KRO const & o ) const ;
	bool operator!=( HID_InputReport_6KRO const & o ) const ;

public :
	HID_InputReport_6KRO( HID_InputReport_6KRO const & o ) ;
	HID_InputReport_6KRO( uint8_t const & reportId = 1 ) ;

} ; // class HID_InputReport

}   // namespace daniel
