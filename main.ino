//https://www.instructables.com/id/Using-an-I2C-LCD-on-Attiny85/

 /*
  * Connect pull up resistor 4.7K for SDA and SCL to +5V
  * Connect I2C_LCD as following
  * VCC >>> 5V
  * SDA >>> A0
  * SCL >>> A2
  * Gnd >>> Gnd
  * 
  * Connect BH1750 as following :
  * VCC >>> 3.3V
  * SDA >>> A0 
  * SCL >>> A2
  * Gnd >>>Gnd
  */

#include <TinyWireM.h>              //I2C lib
#include <LiquidCrystal_I2C.h>      //LCD lib

#define LCD_I2C_ADD 0x3F
#define BH1750_ADD 0x23

LiquidCrystal_I2C lcd(LCD_I2C_ADD,16,2);  // set address & 16 chars / 2 lines

byte buff[2];
void setup()
{
  TinyWireM.begin();                    // initialize I2C lib

  lcd.init();                           // initialize the lcd 
  lcd.backlight(); 
  lcd.clear();  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("BH1750 sensor");
  lcd.setCursor(0, 1);
  lcd.print("Please Wait....");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Intensity: ");
}

void loop()
{
   BH1750_Init(BH1750_ADD);
   delay(200);
   if(2==BH1750_Read(BH1750_ADD))
   {
     uint16_t val=((buff[0]<<8)|buff[1])/1.2;
     lcd.setCursor(0, 1);
     lcd.print(val, DEC);
   }
   delay(1000);
}
int BH1750_Read(int address) //
{
  int i=0;
  TinyWireM.beginTransmission(address);
  TinyWireM.requestFrom(address, 2);
  while(TinyWireM.available()) //
  {
    buff[i] = TinyWireM.receive();  // receive one byte
    i++;
  }
  TinyWireM.endTransmission();  
  return i;
}

void BH1750_Init(int address) 
{
  TinyWireM.beginTransmission(address);
  TinyWireM.send(0x11);//1lx reolution 120ms
  TinyWireM.endTransmission();
}

