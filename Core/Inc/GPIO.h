#pragma once

#include "common.h"

namespace daniel
{

class GPIO
{

public :
	void SetDbgLed1( bool const & isOn ) ;
	void SetDbgLed2( bool const & isOn ) ;
	void SetDbgLed3( bool const & isOn ) ;

	void ToggleDbgLed1() ;
	void ToggleDbgLed2() ;
	void ToggleDbgLed3() ;

public :
	GPIO() ;

} ; // class GPIO

} // namespace daniel
