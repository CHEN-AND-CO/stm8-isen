/*******************************************************************************
* Noms binome  :   Kevin Le Torc'h Gwenole Leroy Ferrec                
* Description    : fonctions diverses projet numérique année 3  
*******************************************************************************/

#include "fonc_div.h"

void init_port_SPI(void){
	CLK_PCKENR1 |= (1 << 1);
	
	SPI_CR1 |= 0x14;
	SPI_CR2 |= 0x03;
	
	SPI_CR1 |= (1 << 6); // Activate SPI port
	
	PC_DDR |= 0x80;
	PC_CR1 |= 0x80;
	PC_CR2 &= 0x7F;
	PC_ODR |= 0x80;
	
	PD_DDR |= 0x81;
	PD_CR1 |= 0x81;
	PD_CR2 &= ~0x81;
	PD_ODR &= ~0x81;
	
	EXTI_CR1 &= 0xFE;
	EXTI_CR2 |= 0x02;
}

void affiche_mot(uint8_t *mot, uint8_t col, uint8_t ligne){
	uint8_t i;
	for(i=0; mot[i]; i++){
		displayChar_TFT(col+DISPLAY_CHAR_SIZE*i, ligne, mot[i], ST7735_WHITE, ST7735_BLACK, 2);
	}
}

void affiche_temp(uint16_t nombre, uint8_t ligne, uint8_t col){
	uint8_t i=5;
	
	do{
		displayChar_TFT(col+DISPLAY_CHAR_SIZE*--i, ligne,'0'+(nombre%10), ST7735_WHITE, ST7735_BLACK, 2);
		nombre /= 10;
		
		if(i==3) displayChar_TFT(col+DISPLAY_CHAR_SIZE*--i, ligne,'.', ST7735_WHITE, ST7735_BLACK, 2);
	}while(nombre && i>=0);
}

void affiche_puis(uint8_t nombre, uint8_t ligne, uint8_t col){
	displayChar_TFT(col, ligne,'0'+(nombre/1000), ST7735_WHITE, ST7735_BLACK, 2);
	displayChar_TFT(col+12, ligne,'0'+(nombre/100), ST7735_WHITE, ST7735_BLACK, 2);
	displayChar_TFT(col+24, ligne,'0'+(nombre/10), ST7735_WHITE, ST7735_BLACK, 2);
	displayChar_TFT(col+36, ligne,'0'+(nombre%10), ST7735_WHITE, ST7735_BLACK, 2);
}

void affiche_etat_fen(unsigned char fermee){
	displayChar_TFT(DISPLAY_FEN_X+96, DISPLAY_FEN_Y, (fermee == 'F' || fermee == 'O')?fermee:'?', ST7735_WHITE, ST7735_BLACK, 2);
}

void init_timer2_pwm(void){
	CLK_PCKENR1 |= (1<<5);
	
	TIM2_PSCR = 0;
	TIM2_ARRH = 0;
	TIM2_ARRL = 253;
	
	TIM2_CCMR1 |= 0b01101000;
	TIM2_CCMR1 &= 0b11101100;
	TIM2_CCER1 |= 0b00000001;
	TIM2_CCER1 &= 0b11111101;
	TIM2_CR1 = 0x81;
}