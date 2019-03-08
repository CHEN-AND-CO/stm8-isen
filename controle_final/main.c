/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */

#include "fonc_div.h"

extern volatile uint16_t display_bg_color;
extern volatile uint16_t display_values_color;
extern volatile uint16_t display_text_color;

volatile uint8_t f_fermee;
volatile uint16_t Cent_Text;
volatile uint16_t Cent_Tint;
volatile uint8_t PUIS;
volatile unsigned char int_2s_ok;

main(){
	uint16_t tmp_sot = 0;
	
	display_bg_color = ST7735_BLACK;
	
	Cent_Text = 2045;
	Cent_Tint = 3278;
	f_fermee = 'O';
	PUIS = 40;
	int_2s_ok = 0;
	
	init_port_SPI();
	init_TFT();
	init_timer2_pwm();
	init_port_UART2(9600);
	init_timer1_2s();

	TIM2_CCR1L=PUIS*2;
	
	_asm("rim");

	affiche_mot(control, DISPLAY_TITLE_X, DISPLAY_TITLE_Y);
	affiche_mot(fenetre, DISPLAY_FEN_X, DISPLAY_FEN_Y);
	affiche_mot(text, DISPLAY_TEXT_X, DISPLAY_TEXT_Y);
	affiche_mot(tint, DISPLAY_TINT_X, DISPLAY_TINT_Y);
	affiche_mot(puis, DISPLAY_PUIS_X, DISPLAY_PUIS_Y);

	while (1){		
		if(int_2s_ok){
			affiche_temp(Cent_Text, DISPLAY_TEXT_Y, DISPLAY_TEXT_X+60);
			affiche_temp(Cent_Tint, DISPLAY_TINT_Y, DISPLAY_TINT_X+60);
			affiche_puis(PUIS, DISPLAY_PUIS_Y, DISPLAY_PUIS_X+60);
			affiche_etat_fen(f_fermee);
			
			tmp_sot = (Cent_Text>>2) + 991;
			write_UART2(((tmp_sot>>8)&0x0F)|0x00);
			write_UART2(((tmp_sot>>4)&0x0F)|0x10);
			write_UART2(((tmp_sot)&0x0F)|0x20);
		
			tmp_sot = (Cent_Tint>>2) + 991;
			write_UART2(((tmp_sot>>8)&0x0F)|0x80);
			write_UART2(((tmp_sot>>4)&0x0F)|0x90);
			write_UART2(((tmp_sot)&0x0F)|0xA0);
			
			int_2s_ok = 0;
		}
		
		if(UART2_SR&0x20){
			PUIS = UART2_DR;
			TIM2_CCR1L = 2*PUIS;
		}
	}
}