/*
 * mainProc.cpp
 *
 *  Created on: Feb 24, 2025
 *      Author: Daniel Lee
 */


#include "mainProc.h"
#include "KBD.h"

#include "usb_device.h"
#include "usbd_hid.h"


extern ADC_HandleTypeDef  hadc1 ;
extern TIM_HandleTypeDef  htim7 ;
extern USBD_HandleTypeDef hUsbDeviceFS ;


void MainProc()
{
	HAL_TIM_Base_Start_IT( & htim7 ) ;

	daniel::KBD kbd( & hadc1 , & hUsbDeviceFS ) ;

	kbd.Run() ;

	while( true ) ;
}
