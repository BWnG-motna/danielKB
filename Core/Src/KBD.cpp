/*
 * KBD.cpp
 *
 *  Created on: Feb 24, 2025
 *      Author: Daniel Lee
 */



#include "KBD.h"
#include "usbd_hid.h"


uint8_t const daniel::KBD::modPos[ modKeyCnt ] = {
	    keySpPos ,     keyFnPos ,
	 keyLCtrlPos ,  keyRCtrlPos ,
	keyLShiftPos , keyRShiftPos ,
	  keyLAltPos ,   keyRAltPos ,
	  keyLGuiPos ,   keyRGuiPos
} ;


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
/* H */ key::CapsLock    , key::None       , key::None      , key::Space         , key::Space       , key::Space        , key::Space       , key::None      ,
/* I */ key::LeftCONTROL , key::None       , key::None      , key::None          , key::None        , key::None         , key::None        , key::None      ,
/* J */ key::LeftSHIFT   , key::RightSHIFT , key::None      , key::None          , key::None        , key::None         , key::None        , key::None      ,
/* K */ key::None        , key::None       , key::None      , key::None          , key::None        , key::None         , key::LeftALT     , key::RightALT  ,
/* L */ key::None        , key::None       , key::None      , key::None          , key::None        , key::None         , key::LeftGUI     , key::RightGUI  ,
} ;


daniel::KBD::KBD()
	: pAdcHandle( nullptr ) , pUsbHandle( nullptr ) , pGpio( nullptr ) , keyProfile( KeyProfile::Profile_NKRO ) , useIme( false )
{

}


daniel::KBD::KBD( ADC_HandleTypeDef * _pAdcHandle , USBD_HandleTypeDef * _pUsbHandle )
	: pAdcHandle( _pAdcHandle ) , pUsbHandle( _pUsbHandle ) , pGpio( nullptr ) , keyProfile( KeyProfile::Profile_NKRO ) , useIme( false )
{

}


daniel::KBD::KBD( ADC_HandleTypeDef * _pAdcHandle , USBD_HandleTypeDef * _pUsbHandle , GPIO * pGpioHandle )
	: pAdcHandle( _pAdcHandle ) , pUsbHandle( _pUsbHandle ) , pGpio( pGpioHandle ) , keyProfile( KeyProfile::Profile_NKRO ) , useIme( false )
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


void daniel::KBD::SetGpio( GPIO * pHandle )
{
	pGpio = pHandle ;
}


void daniel::KBD::SetProfile( KeyProfile const & profile )
{
	keyProfile = profile ;
}


void daniel::KBD::UseIme( bool const & is )
{
	useIme = is ;
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
#if 0
	for( uint8_t pos = 0 ; pos < inSignal ; ++pos )
	{
		inKey[ pos ] = false ;
	}
#endif

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

	/**/ if(  50 <= adc && 190 > adc )
	{
		inKey[ 0 ] = true  ;
		inKey[ 1 ] = false ;
	}
	else if( 190 <= adc && 450 > adc )
	{
		inKey[ 0 ] = false ;
		inKey[ 1 ] = true  ;
	}
	else if( 450 <= adc )
	{
		inKey[ 0 ] = true ;
		inKey[ 1 ] = true ;
	}
	else
	{
		inKey[ 0 ] = false ;
		inKey[ 1 ] = false ;
	}
}


void daniel::KBD::GetInB()
{
	uint32_t adc = GetAdcB() ;

	/**/ if(  50 <= adc && 190 > adc )
	{
		inKey[ 2 ] = true  ;
		inKey[ 3 ] = false ;
	}
	else if( 190 <= adc && 450 > adc )
	{
		inKey[ 2 ] = false ;
		inKey[ 3 ] = true  ;
	}
	else if( 450 <= adc )
	{
		inKey[ 2 ] = true ;
		inKey[ 3 ] = true ;
	}
	else
	{
		inKey[ 2 ] = false ;
		inKey[ 3 ] = false ;
	}
}


void daniel::KBD::GetInC()
{
	uint32_t adc = GetAdcC() ;

	/**/ if(  50 <= adc && 190 > adc )
	{
		inKey[ 4 ] = true  ;
		inKey[ 5 ] = false ;
	}
	else if( 190 <= adc && 450 > adc )
	{
		inKey[ 4 ] = false ;
		inKey[ 5 ] = true  ;
	}
	else if( 450 <= adc )
	{
		inKey[ 4 ] = true ;
		inKey[ 5 ] = true ;
	}
	else
	{
		inKey[ 4 ] = false ;
		inKey[ 5 ] = false ;
	}
}


void daniel::KBD::GetInD()
{
	uint32_t adc = GetAdcD() ;

	/**/ if(  50 <= adc && 190 > adc )
	{
		inKey[ 6 ] = true  ;
		inKey[ 7 ] = false ;
	}
	else if( 190 <= adc && 450 > adc )
	{
		inKey[ 6 ] = false ;
		inKey[ 7 ] = true  ;
	}
	else if( 450 <= adc )
	{
		inKey[ 6 ] = true ;
		inKey[ 7 ] = true ;
	}
	else
	{
		inKey[ 6 ] = false ;
		inKey[ 7 ] = false ;
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
		currK[ pos ] = false ;
		prevK[ pos ] = false ;
		prevT[ pos ] = false ;

		reptT[ pos ] = false ;
		reptC[ pos ] = false ;
	}
	if( nullptr != pGpio )
	{
		pGpio->SetDbgLed1( false ) ;
		pGpio->SetDbgLed2( false ) ;
		pGpio->SetDbgLed3( false ) ;
	}


	while( true )
	{
		/**/ if( KeyProfile::Profile_6KRO == keyProfile )
		{
			LoopFor6KRO() ;
		}
		else if( KeyProfile::Profile_NKRO == keyProfile )
		{
			LoopForNKRO() ;
		}
	}
}


void daniel::KBD::LoopFor6KRO()
{
	ReadKeyMatrix() ;
	SpKey() ;

	HID_InputReport_6KRO input = MakeHIDInputReport_6KRO() ;

	uint8_t keyCode[ 6 ] ;
	inputReport6KRO.GetKeyCode( keyCode ) ;

	input.SortKeyCode( keyCode ) ;

	WakeUp( input.AnyKeyPressed() ) ;
	if( inputReport6KRO != input )
	{
		KeyPress( input ) ;
		inputReport6KRO = input ;
	}
}


void daniel::KBD::LoopForNKRO()
{
	ReadKeyMatrix() ;
	SpKey() ;

	HID_InputReport_NKRO input = MakeHIDInputReport_NKRO() ;

	WakeUp( input.AnyKeyPressed() ) ;
	if( inputReportNKRO != input )
	{
		KeyPress( input ) ;
		inputReportNKRO = input ;
	}
}


void daniel::KBD::ReadKeyMatrix()
{
	for( uint8_t pos = 0 ; pos < modKeyCnt ; ++pos )
	{
		modKeySt[ pos ].keyPos    = modPos[ pos ] ;
		modKeySt[ pos ].isPressed = false ;
	}

	if( true == useIme )
	{
		modKeySt[ 7 ].keyPos = keyCnt ;
	}


	bool isRegKey = false ;
	bool isModKey = false ;

	for( uint8_t outPos = 0 , mPos = 0 ; outPos < outSignal ; ++outPos )
	{
		SetOut( outPos ) ;
		GetIn() ;

		for( uint8_t inPos = 0 ; inPos < inSignal ; ++inPos )
		{
			uint8_t idx = outPos * inSignal + inPos ;
			currK[ idx ] = inKey[ inPos ] ;

			if( keyCnt <= modKeySt[ mPos ].keyPos )
			{
				++mPos ;
			}

			if( modKeySt[ mPos ].keyPos != idx && true == inKey[ inPos ] )
			{
				isRegKey = true ;
			}

			if( modKeyCnt > mPos && modKeySt[ mPos ].keyPos == idx )
			{
				if( 1 < mPos && true == inKey[ inPos ] )
				{
					isModKey = true ;
				}

				modKeySt[ mPos++ ].isPressed = inKey[ inPos ] ;
			}
		}
	}

	if( nullptr != pGpio )
	{
		pGpio->SetDbgLed1( isRegKey ) ;
		pGpio->SetDbgLed2( isModKey ) ;
	}
}


daniel::HID_InputReport_6KRO daniel::KBD::MakeHIDInputReport_6KRO()
{
	HID_InputReport_6KRO input( 1 ) ;
	uint8_t keyCodeP[ 6 ] ;
	uint8_t keyCodePCnt = 0 ;

	uint8_t keyCodeR[ 6 ] ;
	uint8_t keyCodeRCnt = 0 ;

	for( uint8_t pos = 0 ; pos < 6 ; ++pos )
	{
		keyCodeP[ pos ] = 0 ;
		keyCodeR[ pos ] = 0 ;
	}

	for( uint8_t pos = 0 , mPos = 0 ; pos < keyCnt ; ++pos )
	{
		bool isModK = false ;

		uint32_t const currT = millis() ;
		uint32_t const diffT = currT - prevT[ pos ] ;

		if( modKeyCnt  > mPos && modKeySt[ mPos ].keyPos == pos )
		{
			isModK = true ;
			++mPos ;
		}

		if( modKeyCnt  > mPos && modKeySt[ mPos ].keyPos == keyCnt )
		{
			++mPos ;
		}

		/**/ if( false == currK[ pos ] && false == prevK[ pos ] )
		{
			reptT[ pos ] = 0 ;
			reptC[ pos ] = 0 ;
			continue ;
		}
		else if( false == currK[ pos ] &&  true == prevK[ pos ] )
		{
			reptT[ pos ] = 0 ;
			reptC[ pos ] = 0 ;
			prevK[ pos ] = currK[ pos ] ;
			continue ;
		}
		else if(  true == currK[ pos ] &&  true == prevK[ pos ] )
		{
			reptT[ pos ] = ( 3 <= reptT[ pos ] ) ? 3 : reptT[ pos ] + 1 ;
		}

		daniel::KeyPage k = ( true == modKeySt[ 1 ].isPressed ) ? keymap[ keyCnt + pos ] : keymap[ pos ] ; // with FN key
		bool isConsumer = IsConsumerProfile( k ) ;

		if( true == isConsumer && true == currK[ pos ] )
		{
			uint16_t const repeatDelay[ 4 ] = { 800 , 400 , 280 , 100 } ;
			if( 0 < reptT[ pos ] && diffT < repeatDelay[ reptC[ pos ] ] )
			{
				continue ;
			}

			ConsumerKey( k ) ;
			reptC[ pos ] += ( 3 <= reptC[ pos ] ) ? 0 : 1 ;
		}

		prevT[ pos ] = currT ;
		prevK[ pos ] = currK[ pos ] ;

		if( true == isConsumer || true == isModK || key::None == k )
		{
			continue ;
		}

		if( true == useIme && key::RightALT == k )
		{
			k = key::Lang1 ;
		}

		/**/ if( 0 <  reptT[ pos ] && 6 > keyCodePCnt )
		{
			keyCodeP[ keyCodePCnt++ ] = static_cast< uint8_t >( k ) ;
		}
		else if( 0 == reptT[ pos ] && 6 > keyCodeRCnt )
		{
			keyCodeR[ keyCodeRCnt++ ] = static_cast< uint8_t >( k ) ;
		}
	}

	for( uint8_t posP = keyCodePCnt , posR = 0 ; posP < 6 ; ++posP , ++posR )
	{
		keyCodeP[ posP ] = keyCodeR[ posR ] ;
	}

	input.SetLeftCTRL  ( true == modKeySt[ 2 ].isPressed ? true : false ) ;
	input.SetRightCTRL ( true == modKeySt[ 3 ].isPressed ? true : false ) ;
	input.SetLeftSHIFT ( true == modKeySt[ 4 ].isPressed ? true : false ) ;
	input.SetRightSHIFT( true == modKeySt[ 5 ].isPressed ? true : false ) ;
	input.SetLeftALT   ( true == modKeySt[ 6 ].isPressed ? true : false ) ;
	input.SetRightALT  ( true == modKeySt[ 7 ].isPressed ? true : false ) ;
	input.SetLeftGUI   ( true == modKeySt[ 8 ].isPressed ? true : false ) ;
	input.SetRightGUI  ( true == modKeySt[ 9 ].isPressed ? true : false ) ;

	input.SetKeyCode( keyCodeP ) ;

	return input ;
}


daniel::HID_InputReport_NKRO daniel::KBD::MakeHIDInputReport_NKRO()
{
	HID_InputReport_NKRO input( 1 ) ;

	for( uint8_t pos = 0 , mPos = 0 ; pos < keyCnt ; ++pos )
	{
		bool isModK = false ;

		uint32_t const currT = millis() ;
		uint32_t const diffT = currT - prevT[ pos ] ;

		if( modKeyCnt  > mPos && modKeySt[ mPos ].keyPos == pos )
		{
			isModK = true ;
			++mPos ;
		}

		if( modKeyCnt  > mPos && modKeySt[ mPos ].keyPos == keyCnt )
		{
			++mPos ;
		}

		/**/ if( false == currK[ pos ] && false == prevK[ pos ] )
		{
			reptT[ pos ] = 0 ;
			reptC[ pos ] = 0 ;
			continue ;
		}
		else if( false == currK[ pos ] &&  true == prevK[ pos ] )
		{
			reptT[ pos ] = 0 ;
			reptC[ pos ] = 0 ;
			prevK[ pos ] = currK[ pos ] ;
			continue ;
		}
		else if(  true == currK[ pos ] &&  true == prevK[ pos ] )
		{
			reptT[ pos ] = ( 3 <= reptT[ pos ] ) ? 3 : reptT[ pos ] + 1 ;
		}

		daniel::KeyPage k = ( true == modKeySt[ 1 ].isPressed ) ? keymap[ keyCnt + pos ] : keymap[ pos ] ; // with FN key
		bool isConsumer = IsConsumerProfile( k ) ;

		if( true == isConsumer && true == currK[ pos ] )
		{
			uint16_t const repeatDelay[ 4 ] = { 800 , 400 , 280 , 100 } ;
			if( 0 < reptT[ pos ] && diffT < repeatDelay[ reptC[ pos ] ] )
			{
				continue ;
			}

			ConsumerKey( k ) ;
			reptC[ pos ] += ( 3 <= reptC[ pos ] ) ? 0 : 1 ;
		}

		prevT[ pos ] = currT ;
		prevK[ pos ] = currK[ pos ] ;

		if( true == isConsumer || true == isModK || key::None == k )
		{
			continue ;
		}

		if( true == useIme && key::RightALT == k )
		{
			k = key::Lang1 ;
		}

		input.SetKeyCode( static_cast< uint8_t >( k ) , currK[ pos ] ) ;
	}

	input.SetLeftCTRL  ( true == modKeySt[ 2 ].isPressed ? true : false ) ;
	input.SetRightCTRL ( true == modKeySt[ 3 ].isPressed ? true : false ) ;
	input.SetLeftSHIFT ( true == modKeySt[ 4 ].isPressed ? true : false ) ;
	input.SetRightSHIFT( true == modKeySt[ 5 ].isPressed ? true : false ) ;
	input.SetLeftALT   ( true == modKeySt[ 6 ].isPressed ? true : false ) ;
	input.SetRightALT  ( true == modKeySt[ 7 ].isPressed ? true : false ) ;
	input.SetLeftGUI   ( true == modKeySt[ 8 ].isPressed ? true : false ) ;
	input.SetRightGUI  ( true == modKeySt[ 9 ].isPressed ? true : false ) ;

	return input ;
}


void daniel::KBD::ConsumerKey( KeyPage const & k )
{
	if( nullptr != pGpio )
	{
		pGpio->SetDbgLed3( true ) ;
	}

	using KP = daniel::KeyProfile ;

	/**/ if( KP::Profile_6KRO == keyProfile )
	{
		HID_InputReport_6KRO input( 2 ) ;
		uint16_t value = GetConsumerKeyValue( k ) ;

		input.SetConsumerKey( value ) ;
		KeyPress( input ) ;
		input.SetConsumerKey( 0 ) ;
		KeyPress( input ) ;
	}
	else if( KP::Profile_NKRO == keyProfile )
	{
		HID_InputReport_NKRO input( 2 ) ;
		uint16_t value = GetConsumerKeyValue( k ) ;

		input.SetConsumerKey( value ) ;
		KeyPress( input ) ;
		input.SetConsumerKey( 0 ) ;
		KeyPress( input ) ;
	}

	if( nullptr != pGpio )
	{
		pGpio->SetDbgLed3( false ) ;
	}
}


void daniel::KBD::SpKey()
{
	if( false == modKeySt[ 0 ].isPressed || false == modKeySt[ 1 ].isPressed )
	{
		return ;
	}

	volatile uint32_t const countAddr = 0x0803F000 ;
	volatile uint32_t const  passAddr = 0x0803F001 ;
	volatile uint8_t  const passCount = ( * ( __IO uint8_t * ) countAddr ) ;

	if( 0x00 == passCount || 0xFF == passCount )
	{
		return ;
	}

	using KP = daniel::KeyProfile ;

	/**/ if( KP::Profile_6KRO == keyProfile )
	{
		HID_InputReport_6KRO input( 1 ) ;

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

			input.SetKeyCode( static_cast< uint8_t const >( reqKey ) ) ;
			KeyPress( input ) ;

			DelayMs( ( HID_HS_BINTERVAL < HID_FS_BINTERVAL ) ?  HID_FS_BINTERVAL : HID_HS_BINTERVAL ) ; // consider polling interval
		}
	}
	else if( KP::Profile_NKRO == keyProfile )
	{
		HID_InputReport_NKRO input( 1 ) ;

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

			input.SetKeyCode( static_cast< uint8_t >( reqKey ) , true ) ;
			KeyPress( input ) ;

			DelayMs( ( HID_HS_BINTERVAL < HID_FS_BINTERVAL ) ?  HID_FS_BINTERVAL : HID_HS_BINTERVAL ) ; // consider polling interval

			input.SetKeyCode( static_cast< uint8_t >( reqKey ) , false ) ;
			KeyPress( input ) ;

			DelayMs( ( HID_HS_BINTERVAL < HID_FS_BINTERVAL ) ?  HID_FS_BINTERVAL : HID_HS_BINTERVAL ) ; // consider polling interval
		}
	}
}


bool daniel::KBD::WakeUp( bool const & isAnyKeyPressed ) const
{
	if( nullptr == pUsbHandle )
	{
		return false ;
	}

	if( USBD_STATE_SUSPENDED != pUsbHandle->dev_state )
	{
		return false ;
	}

	if( 1 != pUsbHandle->dev_remote_wakeup )
	{
		return false ;
	}

	if( false == isAnyKeyPressed )
	{
		return false ;
	}

	PCD_HandleTypeDef * pTypeDef = static_cast< PCD_HandleTypeDef * >( pUsbHandle->pData ) ;
	if( nullptr == pTypeDef )
	{
		return false ;
	}

	HAL_PCD_ActivateRemoteWakeup( pTypeDef ) ;
	HAL_Delay( 10 ) ;
	HAL_PCD_DeActivateRemoteWakeup( pTypeDef ) ;

	pUsbHandle->dev_state = USBD_STATE_CONFIGURED ;
	pUsbHandle->dev_remote_wakeup = 0U ;

	return true ;
}


bool daniel::KBD::SendReport( uint8_t * pDat , uint16_t const & len )
{
	if( nullptr == pUsbHandle )
	{
		return false ;
	}

	if( USBD_STATE_CONFIGURED != pUsbHandle->dev_state )
	{
		return false ;
	}

	USBD_HID_HandleTypeDef * phhid = ( USBD_HID_HandleTypeDef * ) pUsbHandle->pClassData ;

	if( nullptr == phhid )
	{
		return false ;
	}

	if( HID_IDLE != phhid->state )
	{
		return false ;
	}

	phhid->state = HID_BUSY ;
	USBD_StatusTypeDef typeDef = USBD_LL_Transmit( pUsbHandle , HID_EPIN_ADDR , pDat , len ) ;
	if( USBD_OK != typeDef )
	{
		return false ;
	}

	return true ;
}


void daniel::KBD::KeyPress( HID_InputReport_6KRO const & ir )
{
	while( false == SendReport( ir.GetSerialized() , ir.GetSerializedLength() ) )
	{
		;
	}
}


void daniel::KBD::KeyPress( HID_InputReport_NKRO const & ir )
{
	while( false == SendReport( ir.GetSerialized() , ir.GetSerializedLength() ) )
	{
		;
	}
}


bool daniel::KBD::IsConsumerProfile( KeyPage const & keyPage )
{
	using ckey = daniel::HID::ConsumerProfile::KeyPage ;

	uint16_t const none   = static_cast< uint16_t >( ckey::None ) ;
	uint16_t const keyVal = GetConsumerKeyValue( keyPage ) ;

	if( none == keyVal )
	{
		return false ;
	}

	return true ;
}


uint16_t daniel::KBD::GetConsumerKeyValue( KeyPage const & keyPage )
{
	using ckey = daniel::HID::ConsumerProfile::KeyPage ;

	ckey k = ckey::None ;

	switch( keyPage )
	{
		case key::VolumeUp :
			k = ckey::VolumeIncrement ;
			break ;

		case key::VolumeDown :
			k = ckey::VolumeDecrement ;
			break ;

		case key::Mute :
			k = ckey::Mute ;
			break ;

		default :
			k = ckey::None ;
			break ;
	}

	return static_cast< uint16_t >( k ) ;
}
