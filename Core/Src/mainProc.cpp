/*
 * mainProc.cpp
 *
 *  Created on: Feb 24, 2025
 *      Author: Daniel Lee
 */


#include "mainProc.h"
#include "KBD.h"

#if ( USB_ENABLED )
#include "usb_device.h"
#include "usbd_hid.h"
#endif

extern ADC_HandleTypeDef hadc1 ;
extern TIM_HandleTypeDef htim7 ;

#if ( USB_ENABLED )
extern USBD_HandleTypeDef hUsbDeviceFS ;
#endif


daniel::KBD kbd ;



void MainProc()
{
	HAL_TIM_Base_Start_IT( & htim7 ) ;

	kbd.SetAdcHandle( & hadc1 ) ;

#if ( USB_ENABLED )
	//MX_USB_DEVICE_Init() ;
	kbd.SetUSBHandle( & hUsbDeviceFS ) ;
#endif

	kbd.Run() ;

	while( true ) ;
}
