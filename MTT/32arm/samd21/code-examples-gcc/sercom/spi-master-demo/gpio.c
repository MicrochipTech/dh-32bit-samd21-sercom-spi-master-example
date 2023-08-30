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

#include "gpio.h"

void GPIO_Init(void)
{
	//Pre setting LED to clear
	GPIO_LED_CLR();
	//Pre setting Slave Select (SS) manually controlled high
	GPIO_SS_HIGH();
	//Setting LED as an output
	PORT->Group[GPIO_GROUP_LED].DIRSET.reg = GPIO_MAP_LED;

//SPI
	//Setting SPI Slave Select as an output 
	PORT->Group[GPIO_GROUP_SS].DIRSET.reg = GPIO_MAP_SS;
	//Other SPI pins are configured with the PMUX settings and controller via the SERCOM			

	
}