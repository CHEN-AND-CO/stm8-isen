/*******************************************************************************
* Noms binome  :                                                                                         
* Description    : fonctions diverses projet numérique année 3  
*******************************************************************************/

#include "fonc_div.h"

void init_port_SPI(void){
	CLK_PCKENR1 |= (1 << 1);
	
	SPI_CR1 |= 0x2F;
	SPI_CR2 |= 0x03;
	
	SPI_CR1 |= (1 << 6); // Activate SPI port
	
	PC_DDR |= 0x80;
	PC_CR1 |= 0x80;
	PC_CR2 &= 0x40;
	
	EXTI_CR1 &= 0xFE;
	EXTI_CR2 |= 0x02;
}

void affiche_mot(uint8_t *mot, uint8_t col, uint8_t ligne){
}

void affiche_temp(uint16_t nombre, uint8_t ligne, uint8_t col){
}

void affiche_puis(uint8_t nombre, uint8_t ligne, uint8_t col){
}

void affiche_etat_fen(unsigned char fermee){
}

void init_timer2_pwm(void){
}