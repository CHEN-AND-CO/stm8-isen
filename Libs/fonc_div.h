#include "fonc_tft.h"
#include "iostm8s105.h"

#define DISPLAY_CHAR_SIZE 12

#define DISPLAY_TITLE_X 12	
#define DISPLAY_TITLE_Y 5
#define DISPLAY_FEN_X 1
#define DISPLAY_FEN_Y 40
#define DISPLAY_TEXT_X 1
#define DISPLAY_TEXT_Y 70
#define DISPLAY_TINT_X 1
#define DISPLAY_TINT_Y 100
#define DISPLAY_PUIS_X 1
#define DISPLAY_PUIS_Y 130

//prototype fonctions 
//control_1

void init_port_SPI(void);

void affiche_mot(uint8_t *mot, uint8_t col, uint8_t ligne);

void affiche_temp(uint16_t nombre, uint8_t ligne, uint8_t col);

void affiche_puis(uint8_t nombre, uint8_t ligne, uint8_t col);

void affiche_etat_fen(unsigned char fermee);

void init_timer2_pwm(void);


//control_2

void init_timer1_2s(void);

void init_port_UART2(uint16_t UART_BAUDRATE);

void write_UART2(uint8_t data);

uint8_t read_UART2(void);

//control_f


void init_PE5(void);
void init_PD4(void);

void init_ADC(void);
uint16_t read_ADC(void);

void init_I2C_Slave(void);
uint8_t read_I2C_Slave(void);

void init_timer1_500ms(void);
void init_timer3(void);
