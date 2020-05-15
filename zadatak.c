#include <LiquidCrystal.h>
#include <util/delay.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

byte srce[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

byte tref[] = {
  B00000,
  B00100,
  B01110,
  B10101,
  B11111,
  B10101,
  B00100,
  B00000
};

byte pik[] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B00100,
  B00000,
  B00000
};

byte karo[] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

byte randomNiz[4] = {};
byte pozicija = 0;
byte znak = 0;
byte resenje[4] = {};

char ocitaj_taster()
{
  char taster = 0;
  unsigned char row;
  
  MCUCR &= ~0x10;
  PORTD = 0x0f; 
  
  for(row = 0x80; row != 0x08; row >>= 1)
  {
    DDRD = row;
	_delay_ms(2);
    
    switch(row | ((~PIND) & 0x0f))
    {
      case 0x88:
      	taster = '1'; break;
      case 0x84:
      	taster = '2'; break;
      case 0x82:
      	taster = '3'; break;
      case 0x81:
      	taster = 'A'; break;
		
	  case 0x48:
      	taster = '4'; break;
      case 0x44:
      	taster = '5'; break;
      case 0x42:
      	taster = '6'; break;
      case 0x41:
      	taster = 'B'; break;
		
	  case 0x28:
      	taster = '7'; break;
      case 0x24:
      	taster = '8'; break;
      case 0x22:
      	taster = '9'; break;
      case 0x21:
      	taster = 'C'; break;
		
	  case 0x18:
      	taster = '*'; break;
      case 0x14:
      	taster = '0'; break;
      case 0x12:
      	taster = '#'; break;
      case 0x11:
      	taster = 'D'; break;
    }
  }
  
  return taster;
}

int main()
{
  	lcd.begin(16, 2);
	lcd.print("Pritisni * ");
    int i;
  
 	
  	
  	lcd.createChar(0, srce);
  	lcd.createChar(1, karo);
    lcd.createChar(2, tref);
    lcd.createChar(3, pik);

  //	randomSeed(analogRead(A2));
    
	while(1)
    { 
	  char taster = ocitaj_taster();
      if (taster != 0 && taster == '*')
      {
        lcd.clear();
        for (i = 0; i <=3; i++) {
         // randomSeed(analogRead(A0));
          byte randomBroj = rand() % 4;
          Serial.println(randomBroj);
          lcd.write(randomBroj);
          randomNiz[i] = randomBroj;
        }
        _delay_ms(2000);
        lcd.clear();
        lcd.print("----");
        
        lcd.setCursor(pozicija,0);
        lcd.cursor();
	
      }
      if (taster!=0 && taster == '4') {
      
        if(pozicija >= 0 ) {
        	pozicija--;
          lcd.setCursor(pozicija, 0);
          lcd.cursor();
          
      	_delay_ms(500);
        }
      }
      
      if(taster!=0 && taster == '6') {
        if(pozicija < 4 ) {
        	pozicija++;
          	lcd.setCursor(pozicija, 0);
          lcd.cursor();
          
      	_delay_ms(500);
        
        }
      }
      if(taster!=0 && taster == '2') {
      	lcd.write(znak);
        lcd.setCursor(pozicija, 0);
        
        resenje[pozicija] = znak;
        if(znak == 3) {
         znak = 0;
        } 
        
        znak++;
      	_delay_ms(500);
      }
      
      if(taster!=0 && taster == '8') {
      	lcd.write(znak);
        lcd.setCursor(pozicija, 0);
        
        resenje[pozicija] = znak;
        if(znak == 0) {
         znak = 4;
        } 
        
        znak--;
      	_delay_ms(500);
      
      }
      
      
      
      if(taster!=0 && taster == '5') {
        int tacno = 0;
        for (int i = 0; i < 4; i++) {
          if(resenje[i] == randomNiz[i]) {
          	tacno++;
          }
        }
        
        for (int i = 0; i < 4; i++) {
        	lcd.setCursor(i,1);
          	lcd.write(randomNiz[i]);
        }
        if(tacno == 4) {
            lcd.setCursor(6, 1);
        	lcd.print("tacno");
        } else {
            lcd.setCursor(6, 1);
            lcd.print("netacno");
        }
        _delay_ms(1000);
        
        
        _delay_ms(1000);
        lcd.clear();
        
        lcd.print("Ponovo *");
      }
      
      
      
    }
  
  	return 0;
} 