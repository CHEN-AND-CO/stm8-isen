#ifndef FONC_DIV_H
#define FONC_DIV_H

#include "iostm8s105.h"
#include "fonc_tft.h"
#include "fonc_i2c.h"
#include "defs.h"

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

//control_3

unsigned int read_AD7991(uint8_t mot_conf);

uint8_t etat_fen(uint16_t temp_ext, uint16_t temp_int, uint8_t puissance);

//control_f
extern volatile uint16_t display_bg_color;
extern volatile uint16_t display_values_color;
extern volatile uint16_t display_text_color;

void init_LED_PWM(void);

void init_timer3_pwm(void);

void init_Bouton_Menu_Couleur(void);

void init_Bouton_Couleur_OK(void);

//simu
void init_PE5(void);
void init_PD4(void);

void init_ADC(void);
uint16_t read_ADC(void);

void init_timer1_500ms(void);
void init_timer3(void);

#endif /* FONC_DIV_H */