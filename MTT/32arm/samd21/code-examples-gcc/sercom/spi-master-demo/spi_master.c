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
 
 
 		//This is another way to configure the Pin Mux that might be easier for some to understand
		const PORT_WRCONFIG_Type wrconfig = {
		.bit.WRPINCFG = 1,
		.bit.WRPMUX = 1,
		.bit.PMUX = MUX_PB16C_SERCOM5_PAD0,
		.bit.PMUXEN = 1,
		.bit.HWSEL = 1,
		.bit.INEN = 1,
		.bit.PINMASK = (uint16_t)((PORT_PB16) >> 16)
	};
		PORT->Group[1].WRCONFIG.reg = wrconfig.reg;
	
 		//This is another way to configure the Pin Mux that might be easier for some to understand	
		const PORT_WRCONFIG_Ty
		pe wrconfig1 = {
		.bit.WRPINCFG = 1,
		.bit.WRPMUX = 1,
		.bit.PMUX = MUX_PB22D_SERCOM5_PAD2,
		.bit.PMUXEN = 1,
		.bit.HWSEL = 1,
		.bit.PINMASK = (uint16_t)((PORT_PB22 | PORT_PB23) >> 16)
		};
	
		PORT->Group[1].WRCONFIG.reg |= wrconfig1.reg;
	
 */

#include "sam.h"
#include "gpio.h"
#include "spi_master.h"


void SPI_init(void)
{
	/* Wait for synchronization */
	while(SERCOM5->SPI.SYNCBUSY.bit.ENABLE);

	/* Disable the SERCOM SPI module */
	SERCOM5->SPI.CTRLA.bit.ENABLE = 0;

	/* Wait for synchronization */
	while(SERCOM5->SPI.SYNCBUSY.bit.SWRST);

	/* Perform a software reset */
	SERCOM5->SPI.CTRLA.bit.SWRST = 1;

	/* Wait for synchronization */
	while(SERCOM5->SPI.CTRLA.bit.SWRST);

	/* Wait for synchronization */
	while(SERCOM5->SPI.SYNCBUSY.bit.SWRST || SERCOM5->SPI.SYNCBUSY.bit.ENABLE);
		
	//Using the WRCONFIG register to bulk configure PB16 for being configured the SERCOM5 SPI MASTER MISO
	PORT->Group[SPI_SERCOM_PINS_PORT_GROUP].WRCONFIG.reg = 
		PORT_WRCONFIG_WRPINCFG |											//Enables the configuration of PINCFG
		PORT_WRCONFIG_WRPMUX |												//Enables the configuration of the PMUX for the selected pins
		PORT_WRCONFIG_PMUXEN |												//Enables the PMUX for the pins
		PORT_WRCONFIG_PMUX(MUX_PB16C_SERCOM5_PAD0) |						//Bulk configuration for PMUX "C" for SERCOM5
		PORT_WRCONFIG_HWSEL |												//Select the correct pin configurations for 16-31
		PORT_WRCONFIG_INEN |												//Enable input on this pin MISO
		PORT_WRCONFIG_PINMASK((uint16_t)((PORT_PB16) >> 16));				//Selecting which pin is configured  PB16  This bit needs to shift to fit the 16 bit macro requirements
		
	//Using the WRCONFIG register to bulk configure both PB22 and PB23 for being configured the SERCOM5 SPI MASTER MOSI and SCK pins
	PORT->Group[SPI_SERCOM_PINS_PORT_GROUP].WRCONFIG.reg =
		PORT_WRCONFIG_WRPINCFG |											//Enables the configuration of PINCFG
		PORT_WRCONFIG_WRPMUX |												//Enables the configuration of the PMUX for the selected pins
		PORT_WRCONFIG_PMUX(MUX_PB22D_SERCOM5_PAD2) |						//Bulk configuration for PMUX
		PORT_WRCONFIG_PMUXEN |												//Enables the PMUX for the pins
		PORT_WRCONFIG_HWSEL |												//Select the correct pin configurations for 16-31
		PORT_WRCONFIG_PINMASK ((uint16_t)((SPI_SERCOM_MOSI_PIN | SPI_SERCOM_SCK_PIN) >> 16));	//Selecting which pin is configured
		
	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM5;								//Enable the SERCOM 5 under the PM
	
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(SERCOM5_GCLK_ID_CORE) |				//Provide necessary clocks to the peripheral
	GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN(SPI_SERCOM_CLK_GEN);
	
	while(GCLK->STATUS.bit.SYNCBUSY);										//Wait for clock sync
		
	SPI_SERCOM->SPI.CTRLA.reg = SERCOM_SPI_CTRLA_MODE_SPI_MASTER|			//Configure the Peripheral as SPI Master
	SERCOM_SPI_CTRLA_DOPO(1);												//DOPO is set to PAD[2,3]

	
	SPI_SERCOM->SPI.CTRLB.reg = SERCOM_SPI_CTRLB_RXEN;						//Enable receive on SPI
	
	uint16_t BAUD_REG = ((float)SPI_CLK_FREQ / (float)(2 * SPI_BAUD)) - 1;	//Calculate BAUD value
	SPI_SERCOM->SPI.BAUD.reg =	SERCOM_SPI_BAUD_BAUD(BAUD_REG);				//Set the SPI baud rate	
	SPI_SERCOM->SPI.CTRLA.reg |= SERCOM_SPI_CTRLA_ENABLE;					//Enable the Sercom SPI
	while(SPI_SERCOM->SPI.SYNCBUSY.bit.ENABLE);								//What for the enable to finish
	
}

uint8_t spiSend(uint8_t data)
{	
	while(SPI_SERCOM->SPI.INTFLAG.bit.DRE == 0);
	SPI_SERCOM->SPI.DATA.reg = data;
	while(SPI_SERCOM->SPI.INTFLAG.bit.RXC == 0);
	return (uint8_t)SPI_SERCOM->SPI.DATA.reg;	
}