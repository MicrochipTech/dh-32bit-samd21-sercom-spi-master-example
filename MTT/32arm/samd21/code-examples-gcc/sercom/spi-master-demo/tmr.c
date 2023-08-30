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
#include "tmr.h"
#include "gpio.h"

uint32_t	GlobalTick = 0;

void TC3_Handler(void)
{
	TC3->COUNT16.INTFLAG.reg = TC_INTFLAG_OVF;
	GlobalTick++;
	
}

void TMR_Init(void)
{
	PM->APBCMASK.reg |= PM_APBCMASK_TC3;								//Provide power to TC3
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(TC3_GCLK_ID) |
	GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN(0);							//Provide Clock to TC3, from generator 0

	TC3->COUNT16.CTRLA.reg =	TC_CTRLA_MODE_COUNT16 |					// Configuring TC3 to 16-bit operation
	TC_CTRLA_WAVEGEN_MFRQ |												// Match frequency wit CC0
	TC_CTRLA_PRESCALER_DIV4 |											// Prescaler to 4
	TC_CTRLA_PRESCSYNC_RESYNC;											// Reload or reset the counter on next generic clock. Reset the prescaler counter

	TC3->COUNT16.CC[0].reg = TC3_PER_10MS;								// Set overflow value
	TC3->COUNT16.COUNT.reg = 0;											// Clear Counter

	TC3->COUNT16.INTFLAG.reg = TC_INTFLAG_OVF;  						// Clear interrupt flag of timer overflow
	TC3->COUNT16.INTENSET.reg = TC_INTENSET_OVF;						// Enable interrupt on overflow
	NVIC_EnableIRQ(TC3_IRQn);											// Enable Global Interrupt for the Peripheral
	TC3->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;							// Start Timer*/

}