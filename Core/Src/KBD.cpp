/*
 * KBD.cpp
 *
 *  Created on: Feb 24, 2025
 *      Author: Daniel Lee
 */


#include "KBD.h"
#include "usbd_hid.h"
#include "HID_InputReport.h"


using key = daniel::HID::DesktopProfile::KeyPage ;


daniel::KeyPage const daniel::KBD::keymap[ daniel::KBD::keyCnt * 2 ] = {

/* A */ key::N1          , key::N2         , key::Q         , key::W             , key::A           , key::S            , key::Z           , key::X         ,
/* B */ key::N3          , key::N4         , key::E         , key::R             , key::D           , key::F            , key::C           , key::V         ,
/* C */ key::N5          , key::N6         , key::T         , key::Y             , key::G           , key::H            , key::B           , key::N         ,
/* D */ key::N7          , key::N8         , key::U         , key::I             , key::J           , key::K            , key::M           , key::Comma     ,
/* E */ key::N9          , key::N0         , key::O         , key::P             , key::L           , key::SemiColon    , key::Point       , key::Slash     ,
/* F */ key::Minus       , key::Equal      , key::BackSlash , key::GraveAccent   , key::LeftBracket , key::RightBracket , key::Quote       , key::None      ,
/* G */ key::Escape      , key::None       , key::None      , key::None          , key::None        , key::None         , key::None        , key::None      ,
/* H */ key::Tab         , key::BackSpace  , key::Enter     , key::Space         , key::Space       , key::Space        , key::Space       , key::None      ,
/* I */ key::LeftCONTROL , key::None       , key::None      , key::None          , key::None        , key::None         , key::None        , key::None      ,
/* J */ key::LeftSHIFT   , key::RightSHIFT , key::None      , key::None          , key::None        , key::None         , key::None        , key::None      ,
/* K */ key::None        , key::None       , key::None      , key::None          , key::None        , key::None         , key::LeftALT     , key::RightALT  ,
/* L */ key::None        , key::None       , key::None      , key::None          , key::None        , key::None         , key::LeftGUI     , key::RightGUI  ,

/* A */ key::F1          , key::F2         , key::None      , key::None          , key::None        , key::None         , key::VolumeDown  , key::VolumeUp  ,
/* B */ key::F3          , key::F4         , key::None      , key::None          , key::None        , key::None         , key::None        , key::None      ,
/* C */ key::F5          , key::F6         , key::None      , key::None          , key::None        , key::None         , key::None        , key::None      ,
/* D */ key::F7          , key::F8         , key::None      , key::Insert        , key::None        , key::None         , key::Mute        , key::None      ,
/* E */ key::F9          , key::F10        , key::None      , key::PrintScreen   , key::None        , key::LeftArrow    , key::None        , key::DownArrow ,
/* F */ key::F11         , key::F12        , key::None      , key::DeleteForward , key::UpArrow     , key::None         , key::RightArrow  , key::None      ,
/* G */ key::None        , key::None       , key::None      , key::None          , key::None        , key::None         , key::None        , key::None      ,
/* H */ key::None        , key::None       , key::None      , key::Space         , key::Space       , key::Space        , key::Space       , key::None      ,
/* I */ key::CapsLock    , key::None       , key::None      , key::None          , key::None        , key::None         , key::None        , key::None      ,
/* J */ key::None        , key::None       , key::None      , key::None          , key::None        , key::None         , key::None        , key::None      ,
/* K */ key::None        , key::None       , key::None      , key::None          , key::None        , key::None         , key::None        , key::None      ,
/* L */ key::None        , key::None       , key::None      , key::None          , key::None        , key::None         , key::None        , key::None      ,
} ;


daniel::KBD::KBD()
	: pAdcHandle( nullptr ) , pUsbHandle( nullptr )
{

}


daniel::KBD::KBD( ADC_HandleTypeDef * _pAdcHandle , USBD_HandleTypeDef * _pUsbHandle )
	: pAdcHandle( _pAdcHandle ) , pUsbHandle( _pUsbHandle )
{

}


void daniel::KBD::SetAdcHandle( ADC_HandleTypeDef * pHandle )
{
	pAdcHandle = pHandle ;
}


void daniel::KBD::SetUSBHandle( USBD_HandleTypeDef * pHandle )
{
	pUsbHandle = pHandle ;
}


void daniel::KBD::SetSigA( bool const & isSet )
{
	HAL_GPIO_WritePin( GPIOA , GPIO_PIN_5 , ( true == isSet ) ? GPIO_PIN_SET : GPIO_PIN_RESET ) ;
}


void daniel::KBD::SetSigB( bool const & isSet )
{
	HAL_GPIO_WritePin( GPIOA , GPIO_PIN_6 , ( true == isSet ) ? GPIO_PIN_SET : GPIO_PIN_RESET ) ;
}


void daniel::KBD::SetSigC( bool const & isSet )
{
	HAL_GPIO_WritePin( GPIOA , GPIO_PIN_7 , ( true == isSet ) ? GPIO_PIN_SET : GPIO_PIN_RESET ) ;
}


void daniel::KBD::SetSigD( bool const & isSet )
{
	HAL_GPIO_WritePin( GPIOC , GPIO_PIN_4 , ( true == isSet ) ? GPIO_PIN_SET : GPIO_PIN_RESET ) ;
}


void daniel::KBD::SetSigE( bool const & isSet )
{
	HAL_GPIO_WritePin( GPIOC , GPIO_PIN_5 , ( true == isSet ) ? GPIO_PIN_SET : GPIO_PIN_RESET ) ;
}


void daniel::KBD::SetSigF( bool const & isSet )
{
	HAL_GPIO_WritePin( GPIOB , GPIO_PIN_0 , ( true == isSet ) ? GPIO_PIN_SET : GPIO_PIN_RESET ) ;
}


void daniel::KBD::SetSigG( bool const & isSet )
{
	HAL_GPIO_WritePin( GPIOB , GPIO_PIN_1 , ( true == isSet ) ? GPIO_PIN_SET : GPIO_PIN_RESET ) ;
}


void daniel::KBD::SetSigH( bool const & isSet )
{
	HAL_GPIO_WritePin( GPIOB , GPIO_PIN_2 , ( true == isSet ) ? GPIO_PIN_SET : GPIO_PIN_RESET ) ;
}


void daniel::KBD::SetSigI( bool const & isSet )
{
	HAL_GPIO_WritePin( GPIOB , GPIO_PIN_10 , ( true == isSet ) ? GPIO_PIN_SET : GPIO_PIN_RESET ) ;
}


void daniel::KBD::SetSigJ( bool const & isSet )
{
	HAL_GPIO_WritePin( GPIOB , GPIO_PIN_11 , ( true == isSet ) ? GPIO_PIN_SET : GPIO_PIN_RESET ) ;
}


void daniel::KBD::SetSigK( bool const & isSet )
{
	HAL_GPIO_WritePin( GPIOB , GPIO_PIN_12 , ( true == isSet ) ? GPIO_PIN_SET : GPIO_PIN_RESET ) ;
}


void daniel::KBD::SetSigL( bool const & isSet )
{
	HAL_GPIO_WritePin( GPIOB , GPIO_PIN_13 , ( true == isSet ) ? GPIO_PIN_SET : GPIO_PIN_RESET ) ;
}


void daniel::KBD::DefaultOutPut()
{
	void ( daniel::KBD:: * fpArr[ outSignal ] )( bool const & isSet )
		= { & daniel::KBD::SetSigA , & daniel::KBD::SetSigB , & daniel::KBD::SetSigC ,
			& daniel::KBD::SetSigD , & daniel::KBD::SetSigE , & daniel::KBD::SetSigF ,
			& daniel::KBD::SetSigG , & daniel::KBD::SetSigH , & daniel::KBD::SetSigI ,
			& daniel::KBD::SetSigJ , & daniel::KBD::SetSigK , & daniel::KBD::SetSigL } ;

	for( uint8_t pos = 0 ; pos < outSignal ; ++pos )
	{
		void ( daniel::KBD:: * fp )( bool const & isSet ) = fpArr[ pos ] ;
		( this->*( fp ) )( false ) ;
	}
}


void daniel::KBD::SetOut( uint8_t const & outNo )
{
	void ( daniel::KBD:: * fpArr[ outSignal ] )( bool const & isSet )
	    = { & daniel::KBD::SetSigA , & daniel::KBD::SetSigB , & daniel::KBD::SetSigC ,
			& daniel::KBD::SetSigD , & daniel::KBD::SetSigE , & daniel::KBD::SetSigF ,
			& daniel::KBD::SetSigG , & daniel::KBD::SetSigH , & daniel::KBD::SetSigI ,
			& daniel::KBD::SetSigJ , & daniel::KBD::SetSigK , & daniel::KBD::SetSigL } ;

	if( outSignal <= outNo )
	{
		return ;
	}

	for( uint8_t pos = 0 ; pos < outSignal ; ++pos )
	{
		void ( daniel::KBD:: * fp )( bool const & isSet ) = fpArr[ pos ] ;
		if( pos == outNo )
		{
			( this->*( fp ) )( true ) ;
		}
		else
		{
			( this->*( fp ) )( false ) ;
		}
	}
}


void daniel::KBD::GetIn()
{
	for( uint8_t pos = 0 ; pos < inSignal ; ++pos )
	{
		inKey[ pos ] = false ;
	}

	void ( daniel::KBD:: * fpArr[ 4 ] )()
		= { & daniel::KBD::GetInA , & daniel::KBD::GetInB ,
			& daniel::KBD::GetInC , & daniel::KBD::GetInD } ;

	for( uint8_t pos = 0 ; pos < 4 ; ++pos )
	{
		void ( daniel::KBD:: * fp )() = fpArr[ pos ] ;
		( this->*( fp ) )() ;
	}
}


void daniel::KBD::GetInA()
{
	uint32_t adc = GetAdcA() ;

	/**/ if( 100 <= adc && 200 > adc )
	{
		inKey[ 0 ] = true  ;
		inKey[ 1 ] = false ;
	}
	else if( 200 <= adc && 450 > adc )
	{
		inKey[ 0 ] = false ;
		inKey[ 1 ] = true  ;
	}
	else if( 450 <= adc )
	{
		inKey[ 0 ] = true ;
		inKey[ 1 ] = true ;
	}
}


void daniel::KBD::GetInB()
{
	uint32_t adc = GetAdcB() ;

	/**/ if( 100 <= adc && 200 > adc )
	{
		inKey[ 2 ] = true  ;
		inKey[ 3 ] = false ;
	}
	else if( 200 <= adc && 450 > adc )
	{
		inKey[ 2 ] = false ;
		inKey[ 3 ] = true  ;
	}
	else if( 450 <= adc )
	{
		inKey[ 2 ] = true ;
		inKey[ 3 ] = true ;
	}
}


void daniel::KBD::GetInC()
{
	uint32_t adc = GetAdcC() ;

	/**/ if( 100 <= adc && 200 > adc )
	{
		inKey[ 4 ] = true  ;
		inKey[ 5 ] = false ;
	}
	else if( 200 <= adc && 450 > adc )
	{
		inKey[ 4 ] = false ;
		inKey[ 5 ] = true  ;
	}
	else if( 500 <= adc )
	{
		inKey[ 4 ] = true ;
		inKey[ 5 ] = true ;
	}
}


void daniel::KBD::GetInD()
{
	uint32_t adc = GetAdcD() ;

	/**/ if( 100 <= adc && 200 > adc )
	{
		inKey[ 6 ] = true  ;
		inKey[ 7 ] = false ;
	}
	else if( 200 <= adc && 450 > adc )
	{
		inKey[ 6 ] = false ;
		inKey[ 7 ] = true  ;
	}
	else if( 450 <= adc )
	{
		inKey[ 6 ] = true ;
		inKey[ 7 ] = true ;
	}
}


uint32_t daniel::KBD::GetAdcA() const
{
	return adcValues[ 0 ] ;
}


uint32_t daniel::KBD::GetAdcB() const
{
	return adcValues[ 1 ] ;
}


uint32_t daniel::KBD::GetAdcC() const
{
	return adcValues[ 2 ] ;
}


uint32_t daniel::KBD::GetAdcD() const
{
	return adcValues[ 3 ] ;
}


void daniel::KBD::Run()
{
	if( nullptr == pAdcHandle )
	{
		return ;
	}


	if( nullptr == pUsbHandle )
	{
		return ;
	}


	HAL_ADC_Start_DMA( pAdcHandle , ( uint32_t * ) adcValues , 4 ) ;
	DefaultOutPut() ;

	for( uint8_t pos = 0 ; pos < keyCnt ; ++pos )
	{
		currKeyPressed[ pos ] = false ;
		prevKeyPressed[ pos ] = false ;

		repeat  [ pos ] = false ;
		prevTime[ pos ] = 0 ;
	}

	gpio.SetDbgLed1( false ) ;
	gpio.SetDbgLed2( false ) ;
	gpio.SetDbgLed3( false ) ;

	while( true )
	{
		Loop() ;
	}
}


void daniel::KBD::Loop()
{
	typedef struct
	{
		uint8_t keyPos ;
		bool isPressed ;

	} KeyStatus ;

	KeyStatus modKeySt[ 9 ] = {
		{     keySpPos , false } , {     keyFnPos , false } ,
		{  keyLCtrlPos , false } ,
		{ keyLShiftPos , false } , { keyRShiftPos , false } ,
		{   keyLAltPos , false } , {   keyRAltPos , false } ,
		{   keyLGuiPos , false } , {   keyRGuiPos , false }
	} ;

	bool isRegKeyPressed = false ;
	bool isModKeyPressed = false ;

	for( uint8_t outPos = 0 , pivotPos  = 0 ; outPos < outSignal ; ++outPos )
	{
		SetOut( outPos ) ;
		GetIn() ;

		for( uint8_t inPos = 0 ; inPos < inSignal ; ++inPos )
		{
			uint8_t idx = outPos * inSignal + inPos ;
			currKeyPressed[ idx ] = inKey[ inPos ] ;

			if( modKeySt[ pivotPos ].keyPos != idx && true == inKey[ inPos ] )
			{
				isRegKeyPressed= true ;
			}

			if( 9 > pivotPos && modKeySt[ pivotPos ].keyPos == idx )
			{
				if( 1 < pivotPos && true == inKey[ inPos ] )
				{
					isModKeyPressed = true ;
				}

				modKeySt[ pivotPos++ ].isPressed = inKey[ inPos ] ;
			}
		}
	}


	gpio.SetDbgLed1( isRegKeyPressed ) ;
	gpio.SetDbgLed2( isModKeyPressed ) ;


	for( uint8_t pos = 0 , pivotPos = 0 ; pos < keyCnt ; ++pos )
	{
		uint32_t currTime = millis() ;
		uint32_t diffTime = currTime - prevTime[ pos ] ;

		bool isModKey = false ;
		if( 9 > pivotPos && modKeySt[ pivotPos ].keyPos == pos )
		{
			isModKey = true ;
			++pivotPos ;
		}

		/**/ if( false == currKeyPressed[ pos ] && false == prevKeyPressed[ pos ] )
		{
			repeat[ pos ] = 0 ;
			continue ;
		}
		else if( false == currKeyPressed[ pos ] &&  true == prevKeyPressed[ pos ] )
		{
			repeat[ pos ] = 0 ;
		}

		/**/ if(  true == currKeyPressed[ pos ] &&  true == prevKeyPressed[ pos ] )
		{
			uint16_t repeatDelay[ 4 ] = { 400 , 200 , 140 , 50 } ;
			if( repeatDelay[ repeat[ pos ] ] > diffTime )
			{
				continue ;
			}
			else
			{
				repeat[ pos ] += ( 3 <= repeat[ pos ] ) ? 0 : 1 ;
			}
		}

		prevTime[ pos ] = currTime ;
		prevKeyPressed[ pos ] = currKeyPressed[ pos ] ;

		daniel::KeyPage k = ( true == modKeySt[ 1 ].isPressed ) ? keymap[ keyCnt + pos ] : keymap[ pos ] ; // with FN key
		bool isConsumer = IsConsumerProfile( k ) ;

	    if( key::None != k && false == isConsumer )
		{
			if( KeyPage::CapsLock == k ) // exception handling - it recognize pressing FN + Left CTRL
			{
				isModKey = false ;
				modKeySt[ 1 ].isPressed = 0 ;
			}

			HID_InputReport input( 1 ) ;

			if( key::Tab == k )
			{
				input.SetKeyCode6( static_cast< uint8_t >( ( true == currKeyPressed[ pos ] ) ? key::Tab : key::None ) ) ;
			}
			else if( key::Tab != k && true == currKeyPressed[ pos ] )
			{
				input.SetKeyCode1( static_cast< uint8_t >( true  == isModKey ? key::None : k ) ) ;
			}

			input.SetLeftCTRL  ( true == modKeySt[ 2 ].isPressed ? true : false ) ;
			input.SetLeftSHIFT ( true == modKeySt[ 3 ].isPressed ? true : false ) ;
			input.SetRightSHIFT( true == modKeySt[ 4 ].isPressed ? true : false ) ;
			input.SetLeftALT   ( true == modKeySt[ 5 ].isPressed ? true : false ) ;
			input.SetRightALT  ( true == modKeySt[ 6 ].isPressed ? true : false ) ;
			input.SetLeftGUI   ( true == modKeySt[ 7 ].isPressed ? true : false ) ;
			input.SetRightGUI  ( true == modKeySt[ 8 ].isPressed ? true : false ) ;

			KeyPress( input ) ;

			if( false == isModKey && key::Tab != k )
			{
				KeyRelease( input ) ;
			}
		}
	    else if( key::None != k &&  true == isConsumer )
		{
			uint16_t value = GetConsumerKeyValue( k ) ;
			uint8_t msb = static_cast< uint8_t >( ( value >> 8 ) & 0x00FF ) ;
			uint8_t lsb = static_cast< uint8_t >( ( value >> 0 ) & 0x00FF ) ;

			HID_InputReport input( 2 ) ;

			if( true == currKeyPressed[ pos ] )
			{
				gpio.SetDbgLed3( true ) ;

				input.SetKeyCode1( lsb ) ;
				input.SetKeyCode2( msb ) ;

				KeyPress( input ) ;
				KeyRelease( input ) ;

				gpio.SetDbgLed3( false ) ;
			}
		}
	    else if( keySpPos == pos )
	    {
	    	if( false == modKeySt[ 0 ].isPressed || false == modKeySt[ 1 ].isPressed )
	    	{
	    		continue ;
	    	}

	    	volatile uint32_t const countAddr = 0x08010000 ;
	    	volatile uint32_t const  passAddr = 0x08010001 ;
	    	volatile uint8_t  const passCount = ( * ( __IO uint8_t * ) countAddr ) ;

	    	if( 0x00 == passCount || 0xFF == passCount )
	    	{
	    		continue ;
	    	}

	    	HID_InputReport input( 1 ) ;

	    	for( uint8_t passPos = 0 ; passPos < passCount ; ++passPos )
	    	{
	    		volatile uint8_t const modKey = ( * ( __IO uint8_t * ) ( passAddr + ( passPos * 2 ) + 0 ) ) ;
	    		volatile uint8_t const reqKey = ( * ( __IO uint8_t * ) ( passAddr + ( passPos * 2 ) + 1 ) ) ;

	    		input.SetLeftCTRL  ( ( 0 < ( modKey & 0x40 ) ) ? true : false ) ;
				input.SetLeftSHIFT ( ( 0 < ( modKey & 0x20 ) ) ? true : false ) ;
				input.SetRightSHIFT( ( 0 < ( modKey & 0x10 ) ) ? true : false ) ;
				input.SetLeftALT   ( ( 0 < ( modKey & 0x08 ) ) ? true : false ) ;
				input.SetRightALT  ( ( 0 < ( modKey & 0x04 ) ) ? true : false ) ;
				input.SetLeftGUI   ( ( 0 < ( modKey & 0x02 ) ) ? true : false ) ;
				input.SetRightGUI  ( ( 0 < ( modKey & 0x01 ) ) ? true : false ) ;

				input.SetKeyCode( reinterpret_cast< uint8_t const >( reqKey ) ) ;

				KeyPress( input ) ;
				HAL_Delay( ( HID_HS_BINTERVAL < HID_FS_BINTERVAL ) ?  HID_FS_BINTERVAL : HID_HS_BINTERVAL ) ; // consider polling interval
	    	}
	    }
	}
}


void daniel::KBD::KeyPress( HID_InputReport const & ir )
{
	USBD_StatusTypeDef typeDef ;

	do
	{
		typeDef = USBD_HID_SendReport( pUsbHandle , ir.GetSerialized() , ir.GetSerializedLength() ) ;

	} while( USBD_OK != typeDef ) ;

}


void daniel::KBD::KeyRelease( HID_InputReport const & ir )
{
	USBD_StatusTypeDef typeDef ;

	do
	{
		HID_InputReport resetIR( ir.GetReportId() ) ;
		typeDef = USBD_HID_SendReport( pUsbHandle , resetIR.GetSerialized() , resetIR.GetSerializedLength() ) ;

	} while( USBD_OK != typeDef ) ;
}


bool daniel::KBD::IsConsumerProfile( KeyPage const & keyPage )
{
	if( key::VolumeUp == keyPage || key::VolumeDown == keyPage || key::Mute == keyPage )
	{
		return true ;
	}

	return false ;
}


uint16_t daniel::KBD::GetConsumerKeyValue( KeyPage const & keyPage )
{
	using ckey = daniel::HID::ConsumerProfile::KeyPage ;

	ckey k = ckey::None ;

	if( key::VolumeUp == keyPage )
	{
		k = ckey::VolumeIncrement ;
	}
	else if( key::VolumeDown == keyPage )
	{
		k = ckey::VolumeDecrement ;
	}
	else if( key::Mute == keyPage )
	{
		k = ckey::Mute ;
	}
	else
	{
		k = ckey::None ;
	}

	return static_cast< uint16_t >( k ) ;
}
