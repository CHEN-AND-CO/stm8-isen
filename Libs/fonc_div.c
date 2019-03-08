/*******************************************************************************
* Noms binome  :   Kevin Le Torc'h Gwenolé Leroy Ferrec                
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
		displayChar_TFT(col+DISPLAY_CHAR_SIZE*i, ligne, mot[i], ST7735_RED, ST7735_BLACK, 2);
	}
}

void affiche_temp(uint16_t nombre, uint8_t ligne, uint8_t col){
	uint8_t i=5;
	
	do{
		displayChar_TFT(col+DISPLAY_CHAR_SIZE*--i, ligne,'0'+(nombre%10), ST7735_YELLOW, ST7735_BLACK, 2);
		nombre /= 10;
		
		if(i==3) displayChar_TFT(col+DISPLAY_CHAR_SIZE*--i, ligne,'.', ST7735_YELLOW, ST7735_BLACK, 2);
	}while(nombre || i>0);
}

void affiche_puis(uint8_t nombre, uint8_t ligne, uint8_t col){
	uint8_t i=5;
	
	do{
		displayChar_TFT(col+DISPLAY_CHAR_SIZE*--i, ligne,'0'+(nombre%10), ST7735_YELLOW, ST7735_BLACK, 2);
		nombre /= 10;
	}while(nombre || i>0);
}

void affiche_etat_fen(unsigned char fermee){
	displayChar_TFT(DISPLAY_FEN_X+96, DISPLAY_FEN_Y, (fermee)? 'F' : 'O', ST7735_YELLOW, ST7735_BLACK, 2);
}

void init_timer1_500ms(void) {
	CLK_PCKENR1 |= (1<<7);
	
	TIM1_PSCRH = 0;
	TIM1_PSCRL = 15;

	TIM1_ARRH = 0;
	TIM1_ARRL = 249;

	TIM1_CR1 = 0;
	TIM1_IER |= (1<<0);
	TIM1_SR1 = 0;
	TIM1_CR1 |= (1<<0);
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

void init_ADC(void) {
	CLK_PCKENR2 |= (1<<3);

	PF_DDR &= ~(1<<4);
	PF_CR1 &= ~(1<<4);
	PF_CR2 &= ~(1<<4);

	ADC_CSR = 0x0C;
	ADC_CR1 = 0x01;
}

uint16_t read_ADC(void) {
	uint16_t ctemp;
	
	ADC_CR1 |= 0x01;

	while ( !(ADC_CSR & 0x80) );

	ctemp = (ADC_DRH << 2) | (ADC_DRL & 0x03);
	ADC_CSR &= ~0x80;

	return ctemp;
}

void init_I2C(void) {
	I2C_FREQR = 1; //1MHz: Standard mode

	I2C_OARH = 0;
	// I2C_OARL = 
	
}

void init_PE5(void) {
	PE_DDR &= ~(1<<5);
	PE_CR1 &= ~(1<<5);
	PE_CR2 |= (1<<5);

	EXTI_CR1 |= (1<<7);
	EXTI_CR1 &= ~(1<<6);
}

void init_PD4(void) {
	PD_DDR &= ~(1<<4);
	PD_CR1 |= (1<<4);
	PD_CR2 |= (1<<4);

	EXTI_CR1 |= 0xC0;
}

void init_timer3(void) {
	CLK_PCKENR1 |= (1 << 6);

	TIM3_PSCR = 0;
	
	TIM3_ARRH = 0xFF;
	TIM3_ARRL = 0xFF;

	TIM3_CR1 = 0;
	// TIM3_IER &= ~(1 << 0);
	// TIM3_SR1 = 0;
	// TIM3_CR1 |= (1 << 0);
}
// void init_port_UART(void) {
// 	uint16_t uartdiv;

// 	CLK_PCKENR1 |= (1<<3);
void init_timer1_2s(void){
	CLK_PCKENR1 |= (1<<7);
	
	TIM1_PSCRH = 0x07;
	TIM1_PSCRL = 0xCF;

	TIM1_ARRH = 0x07;
	TIM1_ARRL = 0xCF;

	TIM1_CR1 = 0x00;
	TIM1_IER |= 1;
	TIM1_SR1 = 0;
	TIM1_CR1 |= 1;
}

void init_port_UART2(uint16_t UART_BAUDRATE){
	uint16_t uartdiv = 2000000/UART_BAUDRATE;
	
	CLK_PCKENR1 |= (1<<3);
	
	UART2_BRR1 = (uartdiv>>4);
	UART2_BRR2 = ((uartdiv>>8)&0xF0)|(uartdiv&0x0F);
	
	UART2_CR1 = 0b00000000;
	UART2_CR2 |= (0b00001100);
	
	UART2_CR3 &= (0b10000000);
}

void write_UART2(uint8_t data){
	UART2_DR = data;
	while(!(UART2_SR>>7));
}	

uint8_t read_UART2(void){
	while(UART2_SR>>7);
	return UART2_DR;
}