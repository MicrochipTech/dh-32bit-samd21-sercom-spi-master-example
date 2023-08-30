/* (C) 2018 Microchip Technology Inc. and its subsidiaries.
 * Subject to your compliance with these terms, you may use Microchip software
 *  and any derivatives exclusively with Microchip products. It is your 
 * responsibility to comply with third party license terms applicable to your
 *  use of third party software (including open source software) that may 
 * accompany Microchip software.
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE.
 * 
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, 
 * IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 */


#ifndef GPIO_H_
#define GPIO_H_

#include "sam.h"

#define GPIO_MAP_SS						PORT_PA13
#define GPIO_MAP_LED					PORT_PB30
#define GPIO_MAP_MISO					PORT_PB16
#define GPIO_MAP_MOSI					PORT_PB22
#define GPIO_MAP_SCK					PORT_PB23

#define GPIO_GROUP_SS					0
#define GPIO_GROUP_LED					1			
#define GPIO_GROUP_SPI					1

#define GPIO_PIN_NUM_MISO				PIN_PA16

#define GPIO_LED_CLR()					PORT->Group[GPIO_GROUP_LED].OUTSET.reg = GPIO_MAP_LED;
#define GPIO_LED_SET()					PORT->Group[GPIO_GROUP_LED].OUTCLR.reg = GPIO_MAP_LED;
#define GPIO_LED_TGL()					PORT->Group[GPIO_GROUP_LED].OUTTGL.reg = GPIO_MAP_LED;

#define GPIO_SS_LOW()					PORT->Group[GPIO_GROUP_SS].OUTCLR.reg = GPIO_MAP_SS;
#define GPIO_SS_HIGH()					PORT->Group[GPIO_GROUP_SS].OUTSET.reg = GPIO_MAP_SS;

void GPIO_Init(void);

#endif /* GPIO_H_ */