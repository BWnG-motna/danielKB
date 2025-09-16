#include "KBD.h"
#include "HID_InputReport.h"

#if ( USB_ENABLED )
#include "usbd_hid.h"
#endif

using key = daniel::KeyPage ;

daniel::KeyPage const daniel::KBD::keymap[ daniel::KBD::keyCnt * 2 ] = {

/* A */ key::N1          , key::N2         , key::Q         , key::W             , key::A           , key::S            , key::Z          , key::X         ,
/* B */ key::N3          , key::N4         , key::E         , key::R             , key::D           , key::F            , key::C          , key::V         ,
/* C */ key::N5          , key::N6         , key::T         , key::Y             , key::G           , key::H            , key::B          , key::N         ,
/* D */ key::N7          , key::N8         , key::U         , key::I             , key::J           , key::K            , key::M          , key::Comma     ,
/* E */ key::N9          , key::N0         , key::O         , key::P             , key::L           , key::SemiColon    , key::Point      , key::Slash     ,
/* F */ key::Minus       , key::Equal      , key::BackSlash , key::GraveAccent   , key::LeftBracket , key::RightBracket , key::Quote      , key::None      ,
/* G */ key::Escape      , key::None       , key::None      , key::None          , key::None        , key::None         , key::None       , key::None      ,
/* H */ key::Tab         , key::BackSpace  , key::Enter     , key::Space         , key::Space       , key::Space        , key::Space      , key::None      ,
/* I */ key::LeftCONTROL , key::None       , key::None      , key::None          , key::None        , key::None         , key::None       , key::None      ,
/* J */ key::LeftSHIFT   , key::RightSHIFT , key::None      , key::None          , key::None        , key::None         , key::None       , key::None      ,
/* K */ key::None        , key::None       , key::None      , key::None          , key::None        , key::None         , key::LeftALT    , key::RightALT  ,
/* L */ key::None        , key::None       , key::None      , key::None          , key::None        , key::None         , key::LeftGUI    , key::RightGUI   ,

/* A */ key::F1          , key::F2         , key::None      , key::None          , key::None        , key::None         , key::VolumDown  , key::VolumUp   ,
/* B */ key::F3          , key::F4         , key::None      , key::None          , key::None        , key::None         , key::None       , key::None      ,
/* C */ key::F5          , key::F6         , key::None      , key::None          , key::None        , key::None         , key::None       , key::None      ,
/* D */ key::F7          , key::F8         , key::None      , key::Insert        , key::None        , key::None         , key::Mute       , key::None      ,
/* E */ key::F9          , key::F10        , key::None      , key::PrintScreen   , key::None        , key::LeftArrow    , key::None       , key::DownArrow ,
/* F */ key::F11         , key::F12        , key::None      , key::DeleteForward , key::UpArrow     , key::None         , key::RightArrow , key::None      ,
/* G */ key::None        , key::None       , key::None      , key::None          , key::None        , key::None         , key::None       , key::None      ,
/* H */ key::None        , key::None       , key::None      , key::None          , key::None        , key::None         , key::None       , key::None      ,
/* I */ key::CapsLock    , key::None       , key::None      , key::None          , key::None        , key::None         , key::None       , key::None      ,
/* J */ key::None        , key::None       , key::None      , key::None          , key::None        , key::None         , key::None       , key::None      ,
/* K */ key::None        , key::None       , key::None      , key::None          , key::None        , key::None         , key::None       , key::None      ,
/* L */ key::None        , key::None       , key::None      , key::None          , key::None        , key::None         , key::None       , key::None      ,
} ;


daniel::KBD::KBD()
	: pAdcHandle( nullptr ) ,
#if ( USB_ENABLED )
	  pUsbHandle( nullptr ) ,
#endif
	  anyKeyPressed( false ) , isBlink( false )
{

}


daniel::KBD::KBD(
	ADC_HandleTypeDef * _pAdcHandle
#if ( USB_ENABLED )
	, USBD_HandleTypeDef * _pUsbHandle
#endif
)
	: pAdcHandle( _pAdcHandle ) ,
#if ( USB_ENABLED )
	  pUsbHandle( _pUsbHandle ) ,
#endif
	  anyKeyPressed( false ) , isBlink( false )
{

}


void daniel::KBD::SetAdcHandle( ADC_HandleTypeDef * pHandle )
{
	pAdcHandle = pHandle ;
}


#if ( USB_ENABLED )
void daniel::KBD::SetUSBHandle( USBD_HandleTypeDef * pHandle )
{
	pUsbHandle = pHandle ;
}
#endif


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
	void ( daniel::KBD:: * fpArr[ 12 ] )( bool const & isSet )
		= { & daniel::KBD::SetSigA , & daniel::KBD::SetSigB , & daniel::KBD::SetSigC ,
			& daniel::KBD::SetSigD , & daniel::KBD::SetSigE , & daniel::KBD::SetSigF ,
			& daniel::KBD::SetSigG , & daniel::KBD::SetSigH , & daniel::KBD::SetSigI ,
			& daniel::KBD::SetSigJ , & daniel::KBD::SetSigK , & daniel::KBD::SetSigL } ;

	for( uint8_t pos = 0 ; pos < 12 ; ++pos )
	{
		void ( daniel::KBD:: * fp )( bool const & isSet ) = fpArr[ pos ] ;
		( this->*( fp ) )( false ) ;
	}
}


void daniel::KBD::SetOut( uint8_t const & outNo )
{
	void ( daniel::KBD:: * fpArr[ 12 ] )( bool const & isSet )
	    = { & daniel::KBD::SetSigA , & daniel::KBD::SetSigB , & daniel::KBD::SetSigC ,
			& daniel::KBD::SetSigD , & daniel::KBD::SetSigE , & daniel::KBD::SetSigF ,
			& daniel::KBD::SetSigG , & daniel::KBD::SetSigH , & daniel::KBD::SetSigI ,
			& daniel::KBD::SetSigJ , & daniel::KBD::SetSigK , & daniel::KBD::SetSigL } ;

	if( 12 <= outNo )
	{
		return ;
	}

	for( uint8_t pos = 0 ; pos < 12 ; ++pos )
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
	for( uint8_t pos = 0 ; pos < 8 ; ++pos )
	{
		inKey[ pos ] = false ;
	}

	GetInA() ;
	GetInB() ;
	GetInC() ;
	GetInD() ;

	anyKeyPressed = false ;
	for( uint8_t pos = 0 ; pos < 8 ; ++pos )
	{
		if( true == inKey[ pos ] )
		{
			anyKeyPressed = true ;
			break ;
		}
	}
}


void daniel::KBD::GetInA()
{
	uint32_t adc = GetAdcA() ;

	if( 150 <= adc && 250 > adc )
	{
		inKey[ 0 ] = true  ;
		inKey[ 1 ] = false ;
	}
	else if( 250 <= adc && 450 > adc )
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

	if( 150 <= adc && 250 > adc )
	{
		inKey[ 2 ] = true  ;
		inKey[ 3 ] = false ;
	}
	else if( 250 <= adc && 450 > adc )
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

	if( 150 <= adc && 250 > adc )
	{
		inKey[ 4 ] = true  ;
		inKey[ 5 ] = false ;
	}
	else if( 250 <= adc && 450 > adc )
	{
		inKey[ 4 ] = false ;
		inKey[ 5 ] = true  ;
	}
	else if( 450 <= adc )
	{
		inKey[ 4 ] = true ;
		inKey[ 5 ] = true ;
	}
}


void daniel::KBD::GetInD()
{
	uint32_t adc = GetAdcD() ;

	if( 150 <= adc && 250 > adc )
	{
		inKey[ 6 ] = true  ;
		inKey[ 7 ] = false ;
	}
	else if( 250 <= adc && 450 > adc )
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

#if ( USB_ENABLED )
	if( nullptr == pUsbHandle )
	{
		return ;
	}
#endif


	HAL_ADC_Start_DMA( pAdcHandle , ( uint32_t * ) adcValues , 4 ) ;
	DefaultOutPut() ;

	for( uint8_t pos = 0 ; pos < keyCnt ; ++pos )
	{
		currKeyPressed[ pos ] = false ;
		prevKeyPressed[ pos ] = false ;

		repeat  [ pos ] = false ;
		prevTime[ pos ] = 0 ;
	}

	gpio.SetDbgLed1( true  ) ;
	gpio.SetDbgLed2( false ) ;
	gpio.SetDbgLed3( false ) ;

	while( true )
	{
		Loop() ;
	}
}


void daniel::KBD::Loop()
{
	uint8_t const     fnPos = 55 ;
	uint8_t const  LCtrlPos = 64 ;
	uint8_t const LShiftPos = 72 ;
	uint8_t const RShiftPos = 73 ;
	uint8_t const   LAltPos = 86 ;
	uint8_t const   RAltPos = 87 ;
	uint8_t const   LGuiPos = 94 ;
	uint8_t const   RGuiPos = 95 ;

	uint8_t modKeyCnt[ 8 ][ 2 ] = {
		{     fnPos , 0 } , {  LCtrlPos , 0 } ,
		{ LShiftPos , 0 } , { RShiftPos , 0 } ,
		{   LAltPos , 0 } , {   RAltPos , 0 } ,
		{   LGuiPos , 0 } , {   RGuiPos , 0 }
	} ;

	for( uint8_t outPos = 0 , pivotPos  = 0 ; outPos < outSignal ; ++outPos )
	{
		SetOut( outPos ) ;
		GetIn() ;

		for( uint8_t inPos = 0 ; inPos < inSignal ; ++inPos )
		{
			uint8_t idx = outPos * 8 + inPos ;
			currKeyPressed[ idx ] = inKey[ inPos ] ;

			if( 7 >= pivotPos && modKeyCnt[ pivotPos ][ 0 ] == idx )
			{
				modKeyCnt[ pivotPos++ ][ 1 ] += ( true == inKey[ inPos ] ? 1 : 0 ) ;
			}
		}
	}


	for( uint8_t pos = 0 , pivotPos = 0 ; pos < keyCnt ; ++pos )
	{
		uint32_t currTime = millis() ;
		uint32_t diffTime = currTime - prevTime[ pos ] ;

		bool isModKey = false ;
		if( 7 >= pivotPos && modKeyCnt[ pivotPos ][ 0 ] == pos )
		{
			isModKey = true ;
			++pivotPos ;
		}

		/**/ if( false == currKeyPressed[ pos ] && false == prevKeyPressed[ pos ] )
		{
			repeat[ pos ] = false ;
			continue ;
		}
		else if( false == currKeyPressed[ pos ] &&  true == prevKeyPressed[ pos ] )
		{
			repeat[ pos ] = false ;
		}

		/**/ if(  true == currKeyPressed[ pos ] &&  true == prevKeyPressed[ pos ] )
		{
			if( false == repeat[ pos ] && ( 200 > diffTime ) )
			{
				repeat[ pos ] = true ;
				continue ;
			}

			if(  true == repeat[ pos ] && ( 140 > diffTime ) )
			{
				continue ;
			}
		}

		prevTime[ pos ] = currTime ;
		prevKeyPressed[ pos ] = currKeyPressed[ pos ] ;


	    if( key::None != keymap[ pos ] )
		{
			daniel::KeyPage k = ( 0 < modKeyCnt[ 0 ][ 1 ] ) ? keymap[ keyCnt + pos ] : keymap[ pos ] ; // with FN key

			HID_InputReport input ;

			if( KeyPage::CapsLock == k ) // exception handling - it recognize pressing FN + Left CTRL
			{
				isModKey = false ;
				modKeyCnt[ 1 ][ 1 ] = 0 ;
			}

			/**/ if( true  == isModKey && true == currKeyPressed[ pos ] )
			{
				input.SetKeyCode1( static_cast< uint8_t >( key::None ) ) ;

			}
			else if( false == isModKey && true == currKeyPressed[ pos ] )
			{
				input.SetKeyCode1( static_cast< uint8_t >( k ) ) ;
			}

			input.SetLeftCTRL  ( 0 < modKeyCnt[ 1 ][ 1 ] ? 0x01 : 0x00 ) ;
			input.SetLeftSHIFT ( 0 < modKeyCnt[ 2 ][ 1 ] ? 0x01 : 0x00 ) ;
			input.SetRightSHIFT( 0 < modKeyCnt[ 3 ][ 1 ] ? 0x01 : 0x00 ) ;
			input.SetLeftALT   ( 0 < modKeyCnt[ 4 ][ 1 ] ? 0x01 : 0x00 ) ;
			input.SetRightALT  ( 0 < modKeyCnt[ 5 ][ 1 ] ? 0x01 : 0x00 ) ;
			input.SetLeftGUI   ( 0 < modKeyCnt[ 6 ][ 1 ] ? 0x01 : 0x00 ) ;
			input.SetRightGUI  ( 0 < modKeyCnt[ 7 ][ 1 ] ? 0x01 : 0x00 ) ;

			KeyPress  ( input ) ;

			if( false == isModKey )
			{
				KeyRelease( input ) ;
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
		HID_InputReport resetIR ;
		typeDef = USBD_HID_SendReport( pUsbHandle , resetIR.GetSerialized() , resetIR.GetSerializedLength() ) ;

	} while( USBD_OK != typeDef ) ;
}


extern uint32_t millisec ;


uint32_t millis()
{
	return millisec ;
}

