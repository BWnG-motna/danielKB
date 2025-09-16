#include "HID_InputReport.h"


uint8_t daniel::HID_InputReport::keyPos = 1 ;


daniel::HID_InputReport::HID_InputReport()
	: rightGUI( 0x00 ) , rightALT( 0x00 ) , rightSHIFT( 0x00 ) , rightCTRL( 0x00 ) ,  leftGUI( 0x00 ) ,  leftALT( 0x00 ) , leftSHIFT( 0x00 ) , leftCTRL( 0x00 ) ,
	  reserved( 0x00 ) , keyCode1( 0x00 ) ,   keyCode2( 0x00 ) ,  keyCode3( 0x00 ) , keyCode4( 0x00 ) , keyCode5( 0x00 ) ,  keyCode6( 0x00 )
{

}


void daniel::HID_InputReport::Reset()
{
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


void daniel::HID_InputReport::SetKeyCode( uint8_t const & keyCode )
{
	switch( keyPos )
	{
		case 1 :
			SetKeyCode1( keyCode ) ;
			SetKeyCode2( 0 ) ;
			SetKeyCode3( 0 ) ;
			SetKeyCode4( 0 ) ;
			SetKeyCode5( 0 ) ;
			SetKeyCode6( 0 ) ;
			break ;

		case 2 :
			SetKeyCode1( 0 ) ;
			SetKeyCode2( keyCode ) ;
			SetKeyCode3( 0 ) ;
			SetKeyCode4( 0 ) ;
			SetKeyCode5( 0 ) ;
			SetKeyCode6( 0 ) ;
			break ;

		case 3 :
			SetKeyCode1( 0 ) ;
			SetKeyCode2( 0 ) ;
			SetKeyCode3( keyCode ) ;
			SetKeyCode4( 0 ) ;
			SetKeyCode5( 0 ) ;
			SetKeyCode6( 0 ) ;
			break ;

		case 4 :
			SetKeyCode1( 0 ) ;
			SetKeyCode2( 0 ) ;
			SetKeyCode3( 0 ) ;
			SetKeyCode4( keyCode ) ;
			SetKeyCode5( 0 ) ;
			SetKeyCode6( 0 ) ;
			break ;

		case 5 :
			SetKeyCode1( 0 ) ;
			SetKeyCode2( 0 ) ;
			SetKeyCode3( 0 ) ;
			SetKeyCode4( 0 ) ;
			SetKeyCode5( keyCode ) ;
			SetKeyCode6( 0 ) ;
			break ;

		case 6 :
			SetKeyCode1( 0 ) ;
			SetKeyCode2( 0 ) ;
			SetKeyCode3( 0 ) ;
			SetKeyCode4( 0 ) ;
			SetKeyCode5( 0 ) ;
			SetKeyCode6( keyCode ) ;
			break ;
	}

	++keyPos ;

	if( 6 < keyPos )
	{
		keyPos = 1 ;
	}
}


uint8_t * daniel::HID_InputReport::GetSerialized() const
{
	static uint8_t keyCode[ 8 ] = { 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 } ;

	for( uint8_t pos = 0 ; pos < 8 ; ++pos )
	{
		keyCode[ pos ] = 0x00 ;
	}

	keyCode[ 0 ] = keyCode[ 0 ] | ( 0 < rightGUI   ? 0x80 : 0x00 ) ;
	keyCode[ 0 ] = keyCode[ 0 ] | ( 0 < rightALT   ? 0x40 : 0x00 ) ;
	keyCode[ 0 ] = keyCode[ 0 ] | ( 0 < rightSHIFT ? 0x20 : 0x00 ) ;
	keyCode[ 0 ] = keyCode[ 0 ] | ( 0 < rightCTRL  ? 0x10 : 0x00 ) ;
	keyCode[ 0 ] = keyCode[ 0 ] | ( 0 < leftGUI    ? 0x08 : 0x00 ) ;
	keyCode[ 0 ] = keyCode[ 0 ] | ( 0 < leftALT    ? 0x04 : 0x00 ) ;
	keyCode[ 0 ] = keyCode[ 0 ] | ( 0 < leftSHIFT  ? 0x02 : 0x00 ) ;
	keyCode[ 0 ] = keyCode[ 0 ] | ( 0 < leftCTRL   ? 0x01 : 0x00 ) ;

	keyCode[ 1 ] = reserved ;
	keyCode[ 2 ] = keyCode1 ;
	keyCode[ 3 ] = keyCode2 ;
	keyCode[ 4 ] = keyCode3 ;
	keyCode[ 5 ] = keyCode4 ;
	keyCode[ 6 ] = keyCode5 ;
	keyCode[ 7 ] = keyCode6 ;

	return keyCode ;
}


uint16_t daniel::HID_InputReport::GetSerializedLength() const
{
	return 8 ;
}


bool daniel::HID_InputReport::operator==( HID_InputReport const & ir )
{
	uint8_t * pSelf  =    GetSerialized() ;
	uint8_t * pOther = ir.GetSerialized() ;

	for( uint8_t pos = 0 ; pos < 8 ; ++pos )
	{
		if( pSelf[ pos ] != pOther[ pos ] )
		{
			return false ;
		}
	}

	return true ;
}


bool daniel::HID_InputReport::operator!=( HID_InputReport const & ir )
{
	uint8_t * pSelf  =    GetSerialized() ;
	uint8_t * pOther = ir.GetSerialized() ;

	for( uint8_t pos = 0 ; pos < 8 ; ++pos )
	{
		if( pSelf[ pos ] != pOther[ pos ] )
		{
			return true ;
		}
	}

	return false ;
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
