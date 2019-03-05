/************************************************************************
* TITLE: fonc_I2C.c              
* AUTHOR: A REBOUX               
* DESCRIPTION: fonctions I2C spécial TP 
* VERSION: adaptation carte STM8
************************************************************************/

/* INCLUDE *************************************************************/
#include <iostm8s105.h>
#include "fonc_delay.h"
	
/* DEFINE **************************************************************/



/*******************************************************************************
* Function Name  : init_I2C
* Description    : initialise I2C  
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Init_I2C_Master(void)
{
	// when configure Option Byte (bit AFR6) for alternate function 	
// you have I2C_SCL on PB4 and I2C_SDA on PB5

	// Port B Control Register 1	
	//	PB_CR1 =  PB_CR1 & 0b11001111; // sortie open drain PB4, PB5 (facultatif)
	
	// Port B Control Register 2
	//	PB_CR2 = PB_CR2 & 0b11001111; // sortie open drain standar PB4, PB5 (facultatif)


	// enable clock peripheral I2C
	// Peripheral Clock Gating Enable
	CLK_PCKENR1 |= 0b00000001;	//	CLK_PCKEN1 bit 0 = enable clock peripheral I2C
		
	// FREQuency Register 
	I2C_FREQR = (I2C_FREQR & 0b11000000)| 0b00000010; // FREQ= 000010 -> peripheral clock = 2MHz 
	
	// select clock I2C frequency 
	// CCR = (FMASTER x FI2C)/2
	// Clock Control Register Low
	I2C_CCRL = 0x0A;	// CCR = 10 -> FI2C = 100kHz avec FMASTER = 2MHz
	
	// Clock Control Register High
	I2C_CCRH = (I2C_CCRH & 0b00110000)| 0x00;	// standard mode 
								// CCR MSB = 0
	
	// Time RISE Register 
	// TRISE = (1e-6 x FMASTER )+1
	I2C_TRISER = (I2C_TRISER & 0b11000000)| 0b00000011;	// TRISE = 3 -> TRISE = 1us avec FMASTER = 2MHz 
	
	// enable I21C peripheral
	// I2C Control Register 1
 	I2C_CR1 = (I2C_CR1 & 0b00111110)| 0b00000001;	// clock stretching disable
									// general call disable
									// peripheral enable PE = 1
	I2C_CR2=0; //rajouté								
						
	
}
/*******************************************************************************
* Function Name  : Start_I2C
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Start_I2C(void)
{
	char dummy; 
		// I2C Control Register 2
	I2C_CR2 = (I2C_CR2 & 0b01110000);
	I2C_CR2|= 0b00000001;	// start

	// wait EV5 : Start Bit condition
	// test I2C Status Register 1
	//lecture SR1 pour   , après start 
	while ( ( I2C_SR1 & 0b00000001) == 0);  // wait for SB = Start Bit = 1 
	
}
/*******************************************************************************
* Function Name  : Stop_I2C
* Description    :   
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void Stop_I2C(void)
{
	char dummy;
	I2C_CR2 = (I2C_CR2 & 0b01110000) | 0b00000010;	// stop after receive NOACK
	
	// vvait EV7 : receive register not empty condition
	//test I2C Status Register 1
	//vvhile ( ( I2C_SR1 & 0b01000000) == 0); // wait for RXNE = 1 
	//lecture SR1 pour   , après stop
	dummy=I2C_SR1;
	
}
/*******************************************************************************
* Function Name  : Write_I2C
* Description    :  
* Input          : char data
* Output         : None
* Return         : None
*******************************************************************************/

void Write_I2C(char data)
{
	char dummy; 
I2C_DR = data;
	
	// wait EV8 : transmit register empty and acknowledge condition
	// test I2C Status Register 1
	//while ( ( I2C_SR1 & 0b10000000) == 0); // wait for TXE = 1 
	while ( (( I2C_SR1 & 0b00000010) == 0)&(( I2C_SR1 & 0b10000000) == 0)); // wait for ADDR =1,  Ack ou wait for TXE=1 ( paré à envoyer un autre byte)
	dummy=I2C_SR3;
}

/*******************************************************************************
* Function Name  : read_I2C
* Description    :   
* Input          : None
* Output         : char 
* Return         : None
*******************************************************************************/
char Read_I2C(void)
{ 
	while ( ( I2C_SR1 & 0b01000000) == 0); // wait for RXNE = 1 
	return I2C_DR;

	
}
/*******************************************************************************
* Function Name  : Ack_I2C
* Description    :  
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Ack_I2C(void)
{
	I2C_CR2 =(I2C_CR2 & 0b01110000)| 0b00000100;	//ACK
	
}

/*******************************************************************************
* Function Name  : NoAck_I2C
* Description    : initialise I2C  
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NoAck_I2C(void)
{
	I2C_CR2 =(I2C_CR2 & 0b01110000);// bit ACK laissé à 0, 
}
