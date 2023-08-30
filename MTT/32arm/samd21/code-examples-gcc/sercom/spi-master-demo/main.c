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


#include "sam.h"
#include "gpio.h"
#include "tmr.h"
#include "spi_master.h"

uint8_t EE_Write_data, EE_Read_data;

int main(void)
{
	/* Initialize the SAM system */
    SystemInit();
	GPIO_Init();
	TMR_Init();
	SPI_init();

    /* Replace with your application code */
	
	//Start unlocking the EEProm
	EE_Write_data = 0;
	EE_Read_data = 0;
	
	uint32_t blinkTimer = 0;	
    while (1) 
	{		
		if(GLOBAL_TMR_IS_EXPIRED(blinkTimer))
		{
 			//toggle LED on SPI communication entry
			 GPIO_LED_TGL();
			//Reset 1 second timer for next SPI communication 
			blinkTimer = GLOBAL_TMR_SET(GLOBAL_TMR_TO_1000MS);
			//Write Enable
			GPIO_SS_LOW();
			EE_Read_data = spiSend(0x06);
			GPIO_SS_HIGH();
			//Write Status Register Byte 1
			GPIO_SS_LOW();
			EE_Read_data = spiSend(0x01);
			EE_Read_data = spiSend(0x00);
			GPIO_SS_HIGH();
			//read Status register
			GPIO_SS_LOW();
			EE_Read_data = spiSend(0x05);
			EE_Read_data = spiSend(0xFF);
			GPIO_SS_HIGH();
			//Read Manufacturer ID
			GPIO_SS_LOW();
			EE_Read_data = spiSend(0x9F);
			EE_Read_data = spiSend(0xFF);
			EE_Read_data = spiSend(0xFF);
			EE_Read_data = spiSend(0xFF);
			GPIO_SS_HIGH();
		}
	}
}
