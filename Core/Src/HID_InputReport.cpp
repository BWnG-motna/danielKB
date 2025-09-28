#include "HID_InputReport.h"


daniel::HID_InputReport::HID_InputReport( uint8_t const & _reportId )
	: reportId( _reportId ) ,
	  rightGUI( 0x00 ) , rightALT( 0x00 ) , rightSHIFT( 0x00 ) , rightCTRL( 0x00 ) ,  leftGUI( 0x00 ) ,  leftALT( 0x00 ) , leftSHIFT( 0x00 ) , leftCTRL( 0x00 ) ,
	  reserved( 0x00 ) , keyCode1( 0x00 ) ,   keyCode2( 0x00 ) ,  keyCode3( 0x00 ) , keyCode4( 0x00 ) , keyCode5( 0x00 ) ,  keyCode6( 0x00 )
{

}


void daniel::HID_InputReport::Reset()
{
	reportId   = 0x00 ;
	rightGUI   = 0x00 ;
	rightALT   = 0x00 ;
	rightSHIFT = 0x00 ;
	rightCTRL  = 0x00 ;

	leftGUI    = 0x00 ;
	leftALT    = 0x00 ;
	leftSHIFT  = 0x00 ;
	leftCTRL   = 0x00 ;

	reserved   = 0x00 ;
	keyCode1   = 0x00 ;
	keyCode2   = 0x00 ;
	keyCode3   = 0x00 ;
	keyCode4   = 0x00 ;
	keyCode5   = 0x00 ;
	keyCode6   = 0x00 ;
}


void daniel::HID_InputReport::SetRightGUI( bool const & isSet )
{
	rightGUI = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport::SetRightALT( bool const & isSet )
{
	rightALT = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport::SetRightSHIFT( bool const & isSet )
{
	rightSHIFT = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport::SetRightCTRL( bool const & isSet )
{
	rightCTRL = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport::SetLeftGUI( bool const & isSet )
{
	leftGUI = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport::SetLeftALT( bool const & isSet )
{
	leftALT = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport::SetLeftSHIFT( bool const & isSet )
{
	leftSHIFT = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport::SetLeftCTRL( bool const & isSet )
{
	leftCTRL = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport::SetKeyCode1( uint8_t const & keyCode )
{
	keyCode1 = keyCode ;
}


void daniel::HID_InputReport::SetKeyCode2( uint8_t const & keyCode )
{
	keyCode2 = keyCode ;
}


void daniel::HID_InputReport::SetKeyCode3( uint8_t const & keyCode )
{
	keyCode3 = keyCode ;
}


void daniel::HID_InputReport::SetKeyCode4( uint8_t const & keyCode )
{
	keyCode4 = keyCode ;
}


void daniel::HID_InputReport::SetKeyCode5( uint8_t const & keyCode )
{
	keyCode5 = keyCode ;
}


void daniel::HID_InputReport::SetKeyCode6( uint8_t const & keyCode )
{
	keyCode6 = keyCode ;
}


void daniel::HID_InputReport::SetReportID( uint8_t const & id )
{
	reportId = id ;
}


uint8_t * daniel::HID_InputReport::GetSerialized() const
{
	static uint8_t keyCode[ 9 ] = { 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 } ;

	for( uint8_t pos = 0 ; pos < 9 ; ++pos )
	{
		keyCode[ pos ] = 0x00 ;
	}

	if( 0x01 == reportId )
	{
		keyCode[ 0 ] = reportId ;

		keyCode[ 1 ] = keyCode[ 1 ] | ( 0 < rightGUI   ? 0x80 : 0x00 ) ;
		keyCode[ 1 ] = keyCode[ 1 ] | ( 0 < rightALT   ? 0x40 : 0x00 ) ;
		keyCode[ 1 ] = keyCode[ 1 ] | ( 0 < rightSHIFT ? 0x20 : 0x00 ) ;
		keyCode[ 1 ] = keyCode[ 1 ] | ( 0 < rightCTRL  ? 0x10 : 0x00 ) ;
		keyCode[ 1 ] = keyCode[ 1 ] | ( 0 < leftGUI    ? 0x08 : 0x00 ) ;
		keyCode[ 1 ] = keyCode[ 1 ] | ( 0 < leftALT    ? 0x04 : 0x00 ) ;
		keyCode[ 1 ] = keyCode[ 1 ] | ( 0 < leftSHIFT  ? 0x02 : 0x00 ) ;
		keyCode[ 1 ] = keyCode[ 1 ] | ( 0 < leftCTRL   ? 0x01 : 0x00 ) ;

		keyCode[ 2 ] = reserved ;
		keyCode[ 3 ] = keyCode1 ;
		keyCode[ 4 ] = keyCode2 ;
		keyCode[ 5 ] = keyCode3 ;
		keyCode[ 6 ] = keyCode4 ;
		keyCode[ 7 ] = keyCode5 ;
		keyCode[ 8 ] = keyCode6 ;
	}
	else if( 0x02 == reportId )
	{
		keyCode[ 0 ] = reportId ;
		keyCode[ 1 ] = keyCode1 ;
		keyCode[ 2 ] = keyCode2 ;
	}


	return keyCode ;
}


uint16_t daniel::HID_InputReport::GetSerializedLength() const
{
	if( 1 == reportId )
	{
		return 9 ;
	}
	else if( 2 == reportId )
	{
		return 3 ;
	}

	return 0 ;
}


uint8_t daniel::HID_InputReport::GetModKey() const
{
	uint8_t keyCode = 0x00 ;

	keyCode = keyCode | ( 0 < rightGUI   ? 0x80 : 0x00 ) ;
	keyCode = keyCode | ( 0 < rightALT   ? 0x40 : 0x00 ) ;
	keyCode = keyCode | ( 0 < rightSHIFT ? 0x20 : 0x00 ) ;
	keyCode = keyCode | ( 0 < rightCTRL  ? 0x10 : 0x00 ) ;
	keyCode = keyCode | ( 0 < leftGUI    ? 0x08 : 0x00 ) ;
	keyCode = keyCode | ( 0 < leftALT    ? 0x04 : 0x00 ) ;
	keyCode = keyCode | ( 0 < leftSHIFT  ? 0x02 : 0x00 ) ;
	keyCode = keyCode | ( 0 < leftCTRL   ? 0x01 : 0x00 ) ;

	return keyCode ;
}


void daniel::HID_InputReport::SetModKey( uint8_t const & modKey )
{
	rightGUI   = ( 0 < ( modKey & 0x80 ) ) ? 0x01 : 0x00 ;
	rightALT   = ( 0 < ( modKey & 0x40 ) ) ? 0x01 : 0x00 ;
	rightSHIFT = ( 0 < ( modKey & 0x20 ) ) ? 0x01 : 0x00 ;
	rightCTRL  = ( 0 < ( modKey & 0x10 ) ) ? 0x01 : 0x00 ;
	leftGUI    = ( 0 < ( modKey & 0x08 ) ) ? 0x01 : 0x00 ;
	leftALT    = ( 0 < ( modKey & 0x04 ) ) ? 0x01 : 0x00 ;
	leftSHIFT  = ( 0 < ( modKey & 0x02 ) ) ? 0x01 : 0x00 ;
	leftCTRL   = ( 0 < ( modKey & 0x01 ) ) ? 0x01 : 0x00 ;
}


uint8_t daniel::HID_InputReport::GetReportId() const
{
	return reportId ;
}
