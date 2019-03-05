/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */

#include "fonc_div.h"
#include "defs.h"

volatile uint8_t f_fermee, PUIS;
volatile uint8_t int_500ms_ok;
uint16_t Cent_Text, Cent_Tint;
// uint16_t old_Text, old_Tint;

main()
{
	f_fermee = 0;
	PUIS = 40;
	
	init_port_SPI();
	init_TFT();
	init_PE5();
	init_ADC();
	init_timer1_500ms();

	affiche_mot(simu, 36, DISPLAY_TITLE_Y);
	affiche_mot(fenetre, DISPLAY_FEN_X, DISPLAY_FEN_Y);
	affiche_mot(text, DISPLAY_TEXT_X, DISPLAY_TEXT_Y);
	affiche_mot(tint, DISPLAY_TINT_X, DISPLAY_TINT_Y);
	affiche_mot(puis, DISPLAY_PUIS_X, DISPLAY_PUIS_Y);

	affiche_temp(Cent_Text, DISPLAY_TEXT_Y, DISPLAY_TEXT_X + 60);
	affiche_temp(Cent_Tint, DISPLAY_TINT_Y, DISPLAY_TINT_X + 60);
	affiche_puis(PUIS, DISPLAY_PUIS_Y, DISPLAY_PUIS_X + 60);
	affiche_etat_fen(f_fermee);

	while (1) {
		if (int_500ms_ok) {
			Cent_Text = read_ADC() * 4;
			//calcul tint
		}
	}
}