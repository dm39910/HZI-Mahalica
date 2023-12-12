// Programski kod za Mahalicu


byte NumberBytesChar = 21;
#include "Mahalica_font.h"

// Definiranje upotrijebljenih Arduino pinova
const byte LEDpins[] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17}; 

// Broj korištenih LEDica
int LedCount() { return sizeof(LEDpins)/sizeof(*LEDpins); }


// Definicija grafika 64 (Sirina) X 16 (Visina)  *********************************************************************************************************************** 
byte graphic[2][128] = {
// Srca 64 X 16
{
0x00, 0x00, 0xf0, 0x00, 0xf8, 0x01, 0x0c, 0x03, 0x06, 0x06, 0x06, 0x0c, 0x06, 0x18, 0x0c, 0x30, 0x18, 0x60, 0x0c, 0x30, 0x06, 0x18, 0x06, 0x0c, 0x06, 0x06, 0x0c, 0x03, 0xf8, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x01, 0xe0, 0x03, 0xf0, 0x07, 0xf0, 0x0f, 0xe0, 0x1f, 0xc0, 0x3f, 0xe0, 0x1f, 0xf0, 0x0f, 0xf0, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x08, 0x01, 0x04, 0x02, 0x02, 0x04, 0x02, 0x08, 0x02, 0x10, 0x04, 0x20, 0x08, 0x40, 0x04, 0x20, 0x02, 0x10, 0x02, 0x08, 0x02, 0x04, 0xf4, 0x02, 0xf8, 0x01, 0xfc, 0x03, 0xfe, 0x07, 0xfe, 0x0f, 0xfe, 0x1f, 0xfc, 0x3f, 0xf8, 0x7f, 0xfc, 0x3f, 0xfe, 0x1f, 0xfe, 0x0f, 0xfe, 0x07, 0xfc, 0x03, 0xf8, 0x01, 0xf0, 0x00, 0x00, 0x00
},

// Strelice 64 x 16
{
0x00, 0x00, 0x00, 0x00, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xf8, 0x0f, 0xf0, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xfe, 0x3f, 0xfc, 0x1f, 0xf8, 0x0f, 0xf0, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xff, 0x7f, 0xfe, 0x3f, 0xfc, 0x1f, 0xf8, 0x0f, 0xf0, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x80, 0x00, 0x00, 0x00
}

};
  
  
const int NUMBER_OF_ELEMENTS = 4;

const char textString01 [] PROGMEM = "Volim";
const char textString02 [] PROGMEM = "Arduino";
const char textString03 [] PROGMEM = "Istra";
const char textString04 [] PROGMEM = "u";


const char * const messages[NUMBER_OF_ELEMENTS] PROGMEM = 
{ 
  textString01,
  textString02,
  textString03,
  textString04,
};


unsigned long startTime = millis();
unsigned long elapsedTime = 800;     // 0.8 sekundi prije ponovnog aktiviranja prikaza
 
unsigned long startTime2 = millis();
unsigned long elapsedTime2 = 3000;   // 3 sekunde za prikaz svake tekstualne poruke ili slike
 
const byte triggerPin = 7;            //pin A7 spojen na senzor nagiba
const int charDelay = 3000;          // Vremenski razmak u milisekundama između dva znaka
const int tColDelay = 900;           // Vremenski razmak u milisekundama između dva stupca za znakove
const int gColDelay = 800;           // Vremenski razmak u milisekundama između dva stupca za grafiku

byte textMsgSelection = 1;
byte graphicSelection = 1;
byte max_graphicCount = sizeof(graphic)/sizeof(graphic[0]);

boolean displayGraphics = false;
boolean firstByte = true;
  
  

void setup()
{
  for (int i = 0; i < LedCount(); i++)
    pinMode(LEDpins[i], OUTPUT);          
}
 
 

void loop()
{     
  if ((millis()-startTime) > elapsedTime)
  {
    if (analogRead(triggerPin) < 200)   // Okidač za početak ispisa
    {      
      if (displayGraphics==false)       // Ispiši tekstualne poruke
      {       
        char * ptr = (char *) pgm_read_word (&messages [textMsgSelection-1]);
        char buffer [80];
        strcpy_P (buffer, ptr);
 
        for (int k=0; k<strlen(buffer); k++)   
          printLetterLarge(buffer[k]);                              
               
        if ((millis()-startTime2) > elapsedTime2)
        {               
           textMsgSelection++;    
        
           if (textMsgSelection > NUMBER_OF_ELEMENTS)
           {
             textMsgSelection = 1;
             graphicSelection = 1; 
             displayGraphics = true;
           }
        
           startTime2 = millis();  
        }
      }  
      else // Prikaži grafiku
      {  
        firstByte = true; 
    
        for (int k=0; k<(sizeof(graphic)/max_graphicCount); k++)   
        {
          ApplyGraphic(k);
          delayMicroseconds(gColDelay);
        }
        
        if ((millis()-startTime2) > elapsedTime2)
        {               
           graphicSelection++;    
        
           if (graphicSelection > max_graphicCount)
           {
             textMsgSelection = 1; 
             displayGraphics = false;
           }
        
           startTime2 = millis();  
        }        
      }   

      startTime = millis();  
    }            
  } 
} 



void printLetterLarge(char ch)
{
  // Provjera je li znak sadržan u abecedi definiranoj u Mahalica_font.h datoteci
  // Ako nije, ispiši prazno mjesto (razmak)        
  if (ch < 32 || ch > 126)
    ch = 32;
   
  // Prodi kroz svaki bajt niza znakova  
  for(int i=0; i < pgm_read_byte(&(MyFont[((ch - 32) * NumberBytesChar)])); i++)
  {
    byte b = pgm_read_byte(&(MyFont[((ch - 32) * NumberBytesChar) + 1 + (i*2)]));
    byte b2 = pgm_read_byte(&(MyFont[((ch - 32) * NumberBytesChar) + 2 + (i*2)]));     
  
    // Pomak bita kroz bajt i izlaz na pin
    for (int j=0; j<8; j++) 
    {
      digitalWrite(LEDpins[j], !!(b & (1 << j)));
      digitalWrite(LEDpins[j+8], !!(b2 & (1 << j)));         
    }

    // Razmak između stupaca
    delayMicroseconds(tColDelay);
  }   
      
  // Obrisi/ugasi LEDice
  for (int i = 0; i<LedCount(); i++)
    digitalWrite(LEDpins[i], LOW);
  
  // Razmak između znakova
  delayMicroseconds(charDelay);
 }


int GraphicLength()
{  
  return (sizeof(graphic[0])/sizeof(*graphic[0]));
}



void ApplyGraphic(int position)
{    
  if (firstByte==true)
  {
    for(byte i=0,bit=1;i<8;++i,bit<<=1)
    {
      firstByte=false;
      digitalWrite( LEDpins[i], (graphic[graphicSelection-1][position]&bit)?HIGH:LOW);
    }
  }
  else
  {
    for(byte i=8,bit=1;i<16;++i,bit<<=1)
    {
      firstByte=true;
      digitalWrite( LEDpins[i], (graphic[graphicSelection-1][position]&bit)?HIGH:LOW);
    }
  }  
}

