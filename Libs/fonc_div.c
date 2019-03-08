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
	}while(nombre || i>2);
}

void affiche_etat_fen(unsigned char fermee){
	displayChar_TFT(DISPLAY_FEN_X+96, DISPLAY_FEN_Y, fermee, ST7735_YELLOW, ST7735_BLACK, 2);
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

void init_I2C_Slave(void) {
	//Enable I2C link
	CLK_PCKENR1 |= 0x01;

	//Slave address (emulating the AD7991)
	I2C_OARH = 0;
	I2C_OARL = 0b01010000;

	I2C_FREQR = (I2C_FREQR & 0xC0) | 0x02;		//1MHz: Standard mode
	// I2C_CCRL = 0x0A;	//I2C clock control (from fonc_I2C.c)
	// I2C_CCRH = 0x00; 	//			"			"
	// I2C_TRISER = (I2C_TRISER & 0b11000000) | 0b00000011; // TRISE = 3 -> TRISE = 1us avec FMASTER = 2MHz (from fonc_I2C.c)
	
	//Interrupt configuration
	I2C_ITR = (I2C_ITR & ~0x01) | 0x06;	//ITBUFEN enabled, ITEVTEN enabled, ITERTEN disabled
	
	//I2C configuration
	I2C_CR1 = (I2C_CR1 & 0b00111110) | 1; //I2C_CR1-PE: Enable I2C, enable clock stretching (slave), disable broadcast
	I2C_CR2 = (I2C_CR2 & 0b01110000) | 0x04; //Auto ACK
}

uint8_t read_I2C_Slave(void) {
	while ( !(I2C_SR1 & 0x02) );
	return I2C_DR;
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
}

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

unsigned int read_AD7991(uint8_t mot_conf){
	unsigned int result = 0;
	
	Start_I2C();
	
	Write_I2C(adresse_esclave);
	NoAck_I2C();
	
	Write_I2C(mot_conf);
	Stop_I2C();
	
	Start_I2C();
	
	Write_I2C(adresse_esclave|0x01);
	Ack_I2C();
	
	result = (Read_I2C()<<8);
	NoAck_I2C();
	
	result |= Read_I2C();
	Stop_I2C();
	
	return result;
}

uint8_t etat_fen(uint16_t temp_ext, uint16_t temp_int, uint8_t puissance){
	uint8_t d = 0;
	if(!puissance){
		d = temp_int-temp_ext;
	}else{
		d = (temp_int-temp_ext)/puissance;
	}
	
	if(d < coef_do+8){
		return 'O';
	}else if(d > coef_df-8 && d < coef_df+8){
		return 'F';
	}else{
		return '?';
	}
}

void init_LED_PWM(void){
	PB_DDR |= 1;
	PB_CR1 |= 1;
	PB_CR2 |= 1;
	
	//PB_ODR |= 1;
}

void init_timer3_pwm(void){
	CLK_PCKENR1 |= (1<<5);
	
	TIM3_PSCR = 25;
	TIM3_ARRH = 0;
	TIM3_ARRL = 100;
	
	TIM3_CCMR1 |= 0b01101000;
	TIM3_CCMR1 &= 0b11101100;
	TIM3_CCER1 |= 0b00000001;
	TIM3_CCER1 &= 0b11111101;
	TIM3_CR1 = 0x81;
	TIM3_IER |= 0x03;
}

void init_Bouton_Menu_Couleur(void){
		PE_DDR &= ~(1<<5);
		PE_CR1 &= ~(1<<5);
		PE_CR2 |= (1<<5);
}

void init_Bouton_Couleur_OK(void){
		PD_DDR &= ~(1<<3);
		PD_CR1 &= ~(1<<3);
		PD_CR2 |= (1<<3);
}