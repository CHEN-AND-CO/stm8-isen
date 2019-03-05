/************************************************************************
* TITLE: fonc_delay.c               
* AUTHOR:               
* DESCRIPTION: fonction de temporisation         
* VERSION : 1.1
*           2.0 adapatation carte STM8
************************************************************************/

/* INCLUDE *************************************************************/
#include <iostm8s105.h>

	
/* DEFINE **************************************************************/


/* FUNCTION ************************************************************/

/*******************************************************************************
* Function Name  : attend_1ms
* Description    : temporisation de 1ms
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*; 1 cycle = 1/ Fcpu avec FoscRC HSI interne = 16 MHz et Fcpu = FoscRC HSI / 8 par defaut 
; 2000 cycles avec le CALL si Fcpu = 2 MHz
; Nboucle_1ms	EQU	397		; (400 - 3 pour compensations 16 cycles appel et retour)
*/
void attend_1ms( void)
{
#asm

	PUSHW	X			; 1 cycles

	LDW		X,#397      ; 2 cycles 
	
tempo5cyc:
; boucle 5 cycles
	NOP					; 1 cycle
	NOP					; 1 cycle
	
	DECW 	X			; 1 cycles X = X-1
	JRNE	tempo5cyc	 ; 2 cycles si X <> 0 alors continue tempo (1 cycle si X=0)
	
	POPW		X			; 2 cycles
#endasm						
}	// RET = 4 cycles


/*******************************************************************************
* Function Name  : attend_500ms
* Description    : temporisation de 500ms
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void attend_500ms( void)
{
	unsigned int n;


	for ( n = 0; n < 500; n++)
		attend_1ms(); // duree  cycles par boucle 
}

/*******************************************************************************
* Function Name  : attend_ms
* Description    : temporisation reglable de 0 a 255ms
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void attend_ms( unsigned char nb_ms)
{
	unsigned char n;


	for ( n = 0; n < nb_ms; n++)
		attend_1ms();  
}

