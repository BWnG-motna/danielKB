/*
 * HID_InputReport_NKRO.cpp
 *
 *  Created on: Aug 4, 2026
 *      Author: Daniel Lee
 */


#include "HID_InputReport_NKRO.h"


daniel::HID_InputReport_NKRO::HID_InputReport_NKRO( uint8_t const & _reportId )
	: reportId( _reportId ) ,
	  rightGUI( 0x00 ) , rightALT( 0x00 ) , rightSHIFT( 0x00 ) , rightCTRL( 0x00 ) ,
	   leftGUI( 0x00 ) ,  leftALT( 0x00 ) ,  leftSHIFT( 0x00 ) ,  leftCTRL( 0x00 ) ,
	  reserved( 0x00 ) , consumerKey( 0x00 )
{
	for( uint8_t pos = 0 ; pos < 20 ; ++pos )
	{
		keyMap[ pos ] = 0 ;
	}
}


daniel::HID_InputReport_NKRO::HID_InputReport_NKRO( HID_InputReport_NKRO const & o )
	: reportId( o.reportId ) ,
	  rightGUI( o.rightGUI ) , rightALT( o.rightALT ) , rightSHIFT( o.rightSHIFT ) , rightCTRL( o.rightCTRL ) ,
	   leftGUI( o.leftGUI  ) ,  leftALT( o.leftALT  ) ,  leftSHIFT( o.leftSHIFT  ) ,  leftCTRL( o.leftCTRL  ) ,
	  reserved( o.reserved ) , consumerKey( o.consumerKey )
{
    for( uint8_t pos = 0 ; pos < 20 ; ++pos )
    {
        keyMap[ pos ] = o.keyMap[ pos ] ;
    }
}


daniel::HID_InputReport_NKRO & daniel::HID_InputReport_NKRO::operator=( HID_InputReport_NKRO const & o )
{
    if( this == & o )
    {
        return * this ;
    }

    reportId    = o.reportId ;
    rightGUI    = o.rightGUI ;
    rightALT    = o.rightALT ;
    rightSHIFT  = o.rightSHIFT ;
    rightCTRL   = o.rightCTRL ;
    leftGUI     = o.leftGUI ;
    leftALT     = o.leftALT ;
    leftSHIFT   = o.leftSHIFT ;
    leftCTRL    = o.leftCTRL ;
    reserved    = o.reserved ;
    consumerKey = o.consumerKey ;

    for( uint8_t pos = 0 ; pos < 20 ; ++pos )
    {
        keyMap[ pos ] = o.keyMap[ pos ] ;
    }

    return * this ;
}


bool daniel::HID_InputReport_NKRO::operator==( HID_InputReport_NKRO const & o ) const
{
    if( reportId != o.reportId )
    {
        return false ;
    }

    if(       rightGUI != o.rightGUI
    	||    rightALT != o.rightALT
		||  rightSHIFT != o.rightSHIFT
		||   rightCTRL != o.rightCTRL
		||     leftGUI != o.leftGUI
		||     leftALT != o.leftALT
		||   leftSHIFT != o.leftSHIFT
		||    leftCTRL != o.leftCTRL
		||    reserved != o.reserved
        || consumerKey != o.consumerKey )
    {
        return false ;
    }


    for( uint8_t pos = 0 ; pos < 20 ; ++pos )
    {
        if( keyMap[ pos ] != o.keyMap[ pos ] )
        {
            return false ;
        }
    }

    return true ;
}


bool daniel::HID_InputReport_NKRO::operator!=( HID_InputReport_NKRO const & o ) const
{
    return !( * this == o ) ;
}


void daniel::HID_InputReport_NKRO::Reset()
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

	consumerKey = 0x00 ;

	for( uint8_t pos = 0 ; pos < 20 ; ++pos )
	{
		keyMap[ pos ] = 0 ;
	}
}


void daniel::HID_InputReport_NKRO::SetRightGUI( bool const & isSet )
{
	rightGUI = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport_NKRO::SetRightALT( bool const & isSet )
{
	rightALT = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport_NKRO::SetRightSHIFT( bool const & isSet )
{
	rightSHIFT = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport_NKRO::SetRightCTRL( bool const & isSet )
{
	rightCTRL = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport_NKRO::SetLeftGUI( bool const & isSet )
{
	leftGUI = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport_NKRO::SetLeftALT( bool const & isSet )
{
	leftALT = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport_NKRO::SetLeftSHIFT( bool const & isSet )
{
	leftSHIFT = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport_NKRO::SetLeftCTRL( bool const & isSet )
{
	leftCTRL = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport_NKRO::SetReportID( uint8_t const & id )
{
	reportId = id ;
}


void daniel::HID_InputReport_NKRO::SetConsumerKey( uint16_t const & key )
{
	consumerKey = key ;
}


uint8_t * daniel::HID_InputReport_NKRO::GetSerialized() const
{
	static uint8_t keyCode[ 23 ] ;

	for( uint8_t pos = 0 ; pos < 23 ; ++pos )
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

		for( uint8_t pos = 0 ; pos < 20 ; ++pos )
		{
			keyCode[ 3 + pos ] = keyMap[ pos ] ;
		}
	}
	else if( 0x02 == reportId )
	{
		keyCode[ 0 ] = reportId ;
		keyCode[ 1 ] = ( consumerKey >> 0 ) & 0x00FF ;
		keyCode[ 2 ] = ( consumerKey >> 8 ) & 0x00FF ;
	}


	return keyCode ;
}


uint16_t daniel::HID_InputReport_NKRO::GetSerializedLength() const
{
	/**/ if( 1 == reportId )
	{
		return 23 ;
	}
	else if( 2 == reportId )
	{
		return 3 ;
	}

	return 0 ;
}


uint8_t daniel::HID_InputReport_NKRO::GetModKey() const
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


void daniel::HID_InputReport_NKRO::SetModKey( uint8_t const & modKey )
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


uint8_t daniel::HID_InputReport_NKRO::GetReportId() const
{
	return reportId ;
}


void daniel::HID_InputReport_NKRO::SetKeyCode( uint8_t const & keycode , bool const & isPress )
{
	if( 160 <= keycode )
	{
		return ;
	}

	if( true == isPress )
	{
		keyMap[ keycode / 8 ] |=   ( 1 << ( keycode % 8 ) ) ;
	}
	else
	{
		keyMap[ keycode / 8 ] &= ~ ( 1 << ( keycode % 8 ) ) ;
	}
}
