/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */

#include "fonc_div.h"
#include "defs.h"

volatile uint8_t f_fermee, PUIS;
volatile uint8_t int_500ms_ok;
uint16_t Cent_Text, Cent_Tint;
uint16_t old_Text, old_Tint;

main()
{
	//Initialisation
	f_fermee = 0;
	PUIS = 42;

	//Fréquence fCPU à 16MHz
	CLK_CKDIVR = 1;
	
	init_port_SPI();
	init_TFT();
	init_PE5();
	init_ADC();
	init_timer1_500ms();
	
	_asm("rim");

	//Affichage titres
	affiche_mot(simu, 36, DISPLAY_TITLE_Y);
	affiche_mot(fenetre, DISPLAY_FEN_X, DISPLAY_FEN_Y);
	affiche_mot(text, DISPLAY_TEXT_X, DISPLAY_TEXT_Y);
	affiche_mot(tint, DISPLAY_TINT_X, DISPLAY_TINT_Y);
	affiche_mot(puis, DISPLAY_PUIS_X, DISPLAY_PUIS_Y);

	//FÖREVËR THE LÖÖP
	while (1) {
		while ( int_500ms_ok == 0 );

		Cent_Text = read_ADC() * 4;
		
		//calcul tint probablement faussé facteur 100
		if ( f_fermee ) {
			Cent_Tint = old_Tint * coef_af + ((old_Text + coef_df * PUIS) + (Cent_Text + coef_df * PUIS )) * coef_bf;
		} else {
			Cent_Tint = old_Tint * coef_ao + ((old_Text + coef_do * PUIS) + (Cent_Text + coef_do * PUIS)) * coef_bo;
		}

		old_Text = Cent_Text;
		old_Tint = Cent_Tint;

		//Affichage valeurs
		affiche_temp(Cent_Text, DISPLAY_TEXT_Y, DISPLAY_TEXT_X + 60);
		affiche_temp(Cent_Tint, DISPLAY_TINT_Y, DISPLAY_TINT_X + 60);
		affiche_puis(PUIS, DISPLAY_PUIS_Y, DISPLAY_PUIS_X + 60);
		affiche_etat_fen(f_fermee);

		//Reset du timer
		int_500ms_ok = 0;
	}
}