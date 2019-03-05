/************************************************************************
* TITLE: fonc_tft.h               
* AUTHOR:               
* DESCRIPTION: include pour afficheur graphique TFT          
************************************************************************/


	
/* DEFINE **************************************************************/
#define uint8_t	unsigned char
#define uint16_t	unsigned int

// Color definitions
#define 	ST7735_BLACK   0x0000
#define 	ST7735_BLUE    0x001F
#define	ST7735_RED     0xF800
#define	ST7735_GREEN   0x07E0
#define 	ST7735_CYAN    0x07FF
#define 	ST7735_MAGENTA 0xF81F
#define 	ST7735_YELLOW  0xFFE0  
#define 	ST7735_WHITE   0xFFFF

/* PROTOTYPE *************************************************************/
// init screen
void init_TFT( void);

// draw pixel
void drawPixel_TFT(uint16_t x, uint16_t y, uint16_t color);

// fill a rectangle
void fillRect_TFT(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

// fill screen
void fillScreen_TFT(uint16_t color);

// Draw a character
void displayChar_TFT(uint16_t x, uint16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);

void drawVLine_TFT(uint16_t x, uint16_t y, uint16_t h, uint16_t color);

void writedata(unsigned char dataout);