#pragma once

#include "common.h"


namespace daniel
{

class HID_InputReport
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
	uint8_t keyCode1 ;
	uint8_t keyCode2 ;
	uint8_t keyCode3 ;
	uint8_t keyCode4 ;
	uint8_t keyCode5 ;
	uint8_t keyCode6 ;

private :
	static uint8_t keyPos ;

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

public :
	bool operator==( HID_InputReport const & ir ) ;
	bool operator!=( HID_InputReport const & ir ) ;

public :
	uint8_t GetModKey()   const ;
	uint8_t GetReportId() const ;
	void    SetModKey( uint8_t const & modKey ) ;

public :
	void Reset() ;

public :
	uint8_t * GetSerialized() const ;

public :
	uint16_t GetSerializedLength() const ;

public :
	HID_InputReport( uint8_t const & reportId = 1 ) ;
} ;

} // namespace daniel
