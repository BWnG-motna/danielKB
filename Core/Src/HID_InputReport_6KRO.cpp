/*
 * HID_InputReport.cpp
 *
 *  Created on: Feb 24, 2025
 *      Author: Daniel Lee
 */


#include "HID_InputReport_6KRO.h"


daniel::HID_InputReport_6KRO::HID_InputReport_6KRO( uint8_t const & _reportId )
	: reportId( _reportId ) ,
	  rightGUI( 0x00 ) , rightALT( 0x00 ) , rightSHIFT( 0x00 ) , rightCTRL( 0x00 ) ,
	   leftGUI( 0x00 ) ,  leftALT( 0x00 ) ,  leftSHIFT( 0x00 ) ,  leftCTRL( 0x00 ) ,
	  reserved( 0x00 ) , consumerKey( 0x00 ) , keyPos( 0 )
{
	for( uint8_t pos = 0 ; pos < 6 ; ++pos )
	{
		keyMap[ pos ] = 0x00 ;
	}
}



daniel::HID_InputReport_6KRO::HID_InputReport_6KRO( HID_InputReport_6KRO const & o )
	: reportId( o.reportId ) ,
	  rightGUI( o.rightGUI ) , rightALT( o.rightALT ) , rightSHIFT( o.rightSHIFT ) , rightCTRL( o.rightCTRL ) ,
	   leftGUI( o.leftGUI  ) ,  leftALT( o.leftALT  ) ,  leftSHIFT( o.leftSHIFT  ) ,  leftCTRL( o.leftCTRL  ) ,
	  reserved( o.reserved ) , consumerKey( o.consumerKey ) , keyPos( o.keyPos )
{
    for( uint8_t pos = 0 ; pos < 6 ; ++pos )
    {
        keyMap[ pos ] = o.keyMap[ pos ] ;
    }
}


daniel::HID_InputReport_6KRO & daniel::HID_InputReport_6KRO::operator=( HID_InputReport_6KRO const & o )
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
    keyPos      = o.keyPos ;

    for( uint8_t pos = 0 ; pos < 6 ; ++pos )
    {
        keyMap[ pos ] = o.keyMap[ pos ] ;
    }

    return * this ;
}


bool daniel::HID_InputReport_6KRO::operator==( HID_InputReport_6KRO const & o ) const
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


    for( uint8_t pos = 0 ; pos < 6 ; ++pos )
    {
        if( keyMap[ pos ] != o.keyMap[ pos ] )
        {
            return false ;
        }
    }

    return true ;
}


bool daniel::HID_InputReport_6KRO::operator!=( HID_InputReport_6KRO const & o ) const
{
    return !( * this == o ) ;
}


void daniel::HID_InputReport_6KRO::Reset()
{
	reportId    = 0x00 ;
	rightGUI    = 0x00 ;
	rightALT    = 0x00 ;
	rightSHIFT  = 0x00 ;
	rightCTRL   = 0x00 ;

	leftGUI     = 0x00 ;
	leftALT     = 0x00 ;
	leftSHIFT   = 0x00 ;
	leftCTRL    = 0x00 ;

	reserved    = 0x00 ;

	for( uint8_t pos = 0 ; pos < 6 ; ++pos )
	{
		keyMap[ pos ] = 0x00 ;
	}

	consumerKey = 0x00 ;
	keyPos = 0 ;
}


void daniel::HID_InputReport_6KRO::SetRightGUI( bool const & isSet )
{
	rightGUI = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport_6KRO::SetRightALT( bool const & isSet )
{
	rightALT = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport_6KRO::SetRightSHIFT( bool const & isSet )
{
	rightSHIFT = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport_6KRO::SetRightCTRL( bool const & isSet )
{
	rightCTRL = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport_6KRO::SetLeftGUI( bool const & isSet )
{
	leftGUI = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport_6KRO::SetLeftALT( bool const & isSet )
{
	leftALT = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport_6KRO::SetLeftSHIFT( bool const & isSet )
{
	leftSHIFT = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport_6KRO::SetLeftCTRL( bool const & isSet )
{
	leftCTRL = ( true == isSet ) ? 0x01 : 0x00 ;
}


void daniel::HID_InputReport_6KRO::SetKeyCode1( uint8_t const & keyCode )
{
	keyMap[ 0 ] = keyCode ;
}


void daniel::HID_InputReport_6KRO::SetKeyCode2( uint8_t const & keyCode )
{
	keyMap[ 1 ] = keyCode ;
}


void daniel::HID_InputReport_6KRO::SetKeyCode3( uint8_t const & keyCode )
{
	keyMap[ 2 ] = keyCode ;
}


void daniel::HID_InputReport_6KRO::SetKeyCode4( uint8_t const & keyCode )
{
	keyMap[ 3 ] = keyCode ;
}


void daniel::HID_InputReport_6KRO::SetKeyCode5( uint8_t const & keyCode )
{
	keyMap[ 4 ] = keyCode ;
}


void daniel::HID_InputReport_6KRO::SetKeyCode6( uint8_t const & keyCode )
{
	keyMap[ 5 ] = keyCode ;
}


void daniel::HID_InputReport_6KRO::SetKeyCode( uint8_t const & keyCode )
{
	for( uint8_t pos = 0 ; pos < 6 ; ++pos )
	{
		if( keyPos == pos )
		{
			keyMap[ pos ] = keyCode ;
		}
		else
		{
			keyMap[ pos ] = 0x00 ;
		}
	}

	++keyPos ;
	if( 6 <= keyPos )
	{
		keyPos = 0 ;
	}
}


void daniel::HID_InputReport_6KRO::SetKeyCode( uint8_t const ( & keyCode )[ 6 ] )
{
	keyPos = 0 ;

	for( uint8_t pos = 0 ; pos < 6 ; ++pos )
	{
		keyMap[ pos ] = keyCode[ pos ] ;
	}
}


void daniel::HID_InputReport_6KRO::SetReportID( uint8_t const & id )
{
	reportId = id ;
}


void daniel::HID_InputReport_6KRO::GetKeyCode( uint8_t ( & keyCode )[ 6 ] )
{
	for( uint8_t pos = 0 ; pos < 6 ; ++pos )
	{
		keyCode[ pos ] = keyMap[ pos ] ;
	}
}


void daniel::HID_InputReport_6KRO::SortKeyCode( uint8_t const ( & prev )[ 6 ] )
{
	uint8_t curr[ 6 ] ;
	for( uint8_t pos = 0 ; pos < 6 ; ++pos )
	{
		curr[ pos ] = keyMap[ pos ] ;
		keyMap[ pos ] = 0 ;
	}

	bool used[ 6 ] = { false , false , false , false , false , false } ;

	for( uint8_t kpos = 0 ; kpos < 6 ; ++kpos )
	{
		if( 0 == prev[ kpos ] )
		{
			continue ;
		}

		for( uint8_t cpos = 0 ; cpos < 6 ; ++cpos )
		{
			if( false == used[ cpos ] && curr[ cpos ] == prev[ kpos ] )
			{
				keyMap[ kpos ] = curr[ cpos ] ;
				used[ cpos ] = true ;
				break ;
			}
		}
	}

	for( uint8_t cpos = 0 ; cpos < 6 ; ++cpos )
	{
		if( true == used[ cpos ] || 0 == curr[ cpos ] )
		{
			continue ;
		}

		for( uint8_t kpos = 0 ; kpos < 6 ; ++kpos )
		{
			if( 0 == keyMap[ kpos ] )
			{
				keyMap[ kpos ] = curr[ cpos ] ;
				used[ cpos ] = true ;
				break ;
			}
		}
	}
}


uint8_t * daniel::HID_InputReport_6KRO::GetSerialized() const
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
		keyCode[ 3 ] = keyMap[ 0 ] ;
		keyCode[ 4 ] = keyMap[ 1 ] ;
		keyCode[ 5 ] = keyMap[ 2 ] ;
		keyCode[ 6 ] = keyMap[ 3 ] ;
		keyCode[ 7 ] = keyMap[ 4 ] ;
		keyCode[ 8 ] = keyMap[ 5 ] ;
	}
	else if( 0x02 == reportId )
	{
		keyCode[ 0 ] = reportId ;
		keyCode[ 1 ] = ( consumerKey >> 0 ) & 0x00FF ;
		keyCode[ 2 ] = ( consumerKey >> 8 ) & 0x00FF ;
	}


	return keyCode ;
}


uint16_t daniel::HID_InputReport_6KRO::GetSerializedLength() const
{
	/**/ if( 1 == reportId )
	{
		return 9 ;
	}
	else if( 2 == reportId )
	{
		return 3 ;
	}

	return 0 ;
}


uint8_t daniel::HID_InputReport_6KRO::GetModKey() const
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


void daniel::HID_InputReport_6KRO::SetModKey( uint8_t const & modKey )
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


uint8_t daniel::HID_InputReport_6KRO::GetReportId() const
{
	return reportId ;
}


void daniel::HID_InputReport_6KRO::SetConsumerKey( uint16_t const & key )
{
	consumerKey = key ;
}
