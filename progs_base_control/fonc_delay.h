/************************************************************************
* TITLE: fonc_delay.h              
* AUTHOR:               
* DESCRIPTION:  
* VERSION : 1.1
*           2.0 suppression attend_2ms
************************************************************************/


/*******************************************************************************
* Function Name  : attend_1ms
* Description    : temporisation de 1ms
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void attend_1ms( void);

/*******************************************************************************
* Function Name  : attend_500ms
* Description    : temporisation de 500ms
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void attend_500ms( void);

/*******************************************************************************
* Function Name  : attend_ms
* Description    : temporisation reglable de 0 a 255ms
* Input          : Nombre de millisecondes de 0 a 255
* Output         : None
* Return         : None
*******************************************************************************/
void attend_ms( unsigned char nb_ms);
