/*	BASIC INTERRUPT VECTOR TABLE FOR STM8 devices
 *	Copyright (c) 2007 STMicroelectronics
 */

#include "iostm8s105.h"

extern volatile unsigned char int_2s_ok;
extern volatile uint8_t PUIS;
extern volatile uint8_t menu_sel, sous_menu_sel;

typedef void @far (*interrupt_handler_t)(void);

struct interrupt_vector {
	unsigned char interrupt_instruction;
	interrupt_handler_t interrupt_handler;
};

@far @interrupt void NonHandledInterrupt (void)
{
	/* in order to detect unexpected events during development, 
	   it is recommended to set a breakpoint on the following instruction
	*/
	return;
}

@far @interrupt void int_timer1_2s(void){
	int_2s_ok = 1;
	
	TIM1_SR1 &= ~1;
}

@far @interrupt void pwm_update(void){
	if(PUIS!=127)PB_ODR &= ~1;

	TIM3_SR1 &= 0b11111101;
}

@far @interrupt void pwm_reset(void){
	PB_ODR |= 1;
	
	TIM3_SR1 &= ~1;
}

@far @interrupt void int_bouton_menu(void){
	menu_sel++;
	sous_menu_sel = 0;
	
	menu_sel%=4;
}

@far @interrupt void int_bouton_ok(void){	
	sous_menu_sel++;
	
	sous_menu_sel%=8;
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
	{0x82, int_bouton_ok}, /* irq6  */ //D
	{0x82, int_bouton_menu}, /* irq7  */ //E
	{0x82, NonHandledInterrupt}, /* irq8  */
	{0x82, NonHandledInterrupt}, /* irq9  */
	{0x82, NonHandledInterrupt}, /* irq10 */
	{0x82, int_timer1_2s}, /* irq11 */
	{0x82, NonHandledInterrupt}, /* irq12 */
	{0x82, NonHandledInterrupt}, /* irq13 */ //Update/overflow
	{0x82, NonHandledInterrupt}, /* irq14 */ //Capture/comp
	{0x82, pwm_reset}, /* irq15 */
	{0x82, pwm_update}, /* irq16 */
	{0x82, NonHandledInterrupt}, /* irq17 */
	{0x82, NonHandledInterrupt}, /* irq18 */
	{0x82, NonHandledInterrupt}, /* irq19 */
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
