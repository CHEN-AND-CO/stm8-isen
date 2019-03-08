/*	BASIC INTERRUPT VECTOR TABLE FOR STM8 devices
 *	Copyright (c) 2007 STMicroelectronics
 */

#include "fonc_div.h"
#include "fonc_I2C.h"


typedef void @far (*interrupt_handler_t)(void);

extern volatile uint8_t f_fermee;
extern volatile uint8_t int_500ms_ok;
extern volatile uint16_t pwm_sampler_freq;

	struct interrupt_vector
{
	unsigned char interrupt_instruction;
	interrupt_handler_t interrupt_handler;
};

@far @interrupt void int_PE5(void)
{
	f_fermee = !f_fermee;
}

@far @interrupt void int_PD4(void) {

	if (PD_IDR & 0x10)	//Niveau haut --> front montant
	{
		// _asm("NOP");
		TIM3_CNTRH = 0;
		TIM3_CNTRL = 0;
		
		TIM3_CR1 |= (1 << 0);

	} else {			//Niveau bas --> front descendant
	
		TIM3_CR1 &= ~(1<<0);

		pwm_sampler_freq = ((TIM3_CNTRH << 8) | TIM3_CNTRL) / 16 +1;
		
		TIM3_CNTRH = 0;
		TIM3_CNTRL = 0;
	}
}

@far @interrupt void int_timer1_500ms(void) {
	int_500ms_ok = 1;
	TIM1_SR1 &= ~(1<<0);
}

@far @interrupt void int_timer3(void) {
	if (PD_IDR & 0x10) 	//Niveau haut --> ~127
	{
		pwm_sampler_freq = 128;
	} else {			//Niveau bas --> ~0
		pwm_sampler_freq = 255;
	}
}

@far @interrupt void int_I2C_Slave(void) {
	uint8_t rdata;
	
	rdata = read_I2C_Slave();

	//return if ();
}

@far @interrupt void NonHandledInterrupt (void)
{
	/* in order to detect unexpected events during development, 
	   it is recommended to set a breakpoint on the following instruction
	*/
	return;
}

extern void _stext();     /* startup routine */

struct interrupt_vector const _vectab[] = {
	{0x82, (interrupt_handler_t)_stext}, /* reset */
	{0x82, NonHandledInterrupt}, /* trap  */
	{0x82, NonHandledInterrupt}, /* irq0  */
	{0x82, NonHandledInterrupt}, /* irq1  */
	{0x82, NonHandledInterrupt}, /* irq2  */
	{0x82, NonHandledInterrupt}, /* irq3  */
	{0x82, NonHandledInterrupt}, /* irq4  */
	{0x82, NonHandledInterrupt}, /* irq5  */
	{0x82, int_PD4}, /* irq6  */
	{0x82, int_PE5}, /* irq7  */
	{0x82, NonHandledInterrupt}, /* irq8  */
	{0x82, NonHandledInterrupt}, /* irq9  */
	{0x82, NonHandledInterrupt}, /* irq10 */
	{0x82, int_timer1_500ms}, /* irq11 */
	{0x82, NonHandledInterrupt}, /* irq12 */
	{0x82, NonHandledInterrupt}, /* irq13 */ // 2s
	{0x82, NonHandledInterrupt}, /* irq14 */
	{0x82, NonHandledInterrupt}, /* irq15 */
	{0x82, NonHandledInterrupt}, /* irq16 */
	{0x82, NonHandledInterrupt}, /* irq17 */
	{0x82, NonHandledInterrupt}, /* irq18 */
	{0x82, int_I2C_Slave}, /* irq19 */
	{0x82, NonHandledInterrupt}, /* irq20 */
	{0x82, NonHandledInterrupt}, /* irq21 */
	{0x82, NonHandledInterrupt}, /* irq22 */
	{0x82, NonHandledInterrupt}, /* irq23 */
	{0x82, NonHandledInterrupt}, /* irq24 */
	{0x82, NonHandledInterrupt}, /* irq25 */
	{0x82, NonHandledInterrupt}, /* irq26 */
	{0x82, NonHandledInterrupt}, /* irq27 */
	{0x82, NonHandledInterrupt}, /* irq28 */
	{0x82, NonHandledInterrupt}, /* irq29 */
};
