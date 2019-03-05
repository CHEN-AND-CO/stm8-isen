#include "iostm8s105.h"

//parametres de la maison//vv 
#define coef_af 0.927007299  //  a fenetre fermée
#define coef_ao 0.795918367 // a fenetre ouverte
#define coef_bf 0.03649635 // b fenetre fermée
#define coef_bo 0.102040816  //b  fenetre ouverte
#define coef_df 25.196850 //d  fenetre fermée
#define coef_do 8.398950 // d fenetre ouverte

// adresse I2C adc AD7991
#define adresse_esclave 0x50   


// ecran principal, carte controle, carte simulateur

const uint8_t control[]="CONTROLE";
const uint8_t simu[]="SIMU";
const uint8_t text[]="Text:"; 
const uint8_t tint[]="Tint:"; 
const uint8_t puis[]="PUIS:"; 
const uint8_t fenetre[]="Fenetre:"; 

// ecran choix couleur, carte controle
const uint8_t texte[]="Texte:";
const uint8_t fond[]="Fond:";
const uint8_t valeurs[]="Valeurs:";