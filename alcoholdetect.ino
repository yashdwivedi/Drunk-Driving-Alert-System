#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_MOSI  20
#define OLED_CLK   21
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
#define SSD1306_LCDHEIGHT 64
const int AOUT = 0;
const int DOUT = 2;
int limit;
int value;
int flag = 0;
int count = 0;
SoftwareSerial mySerial(9, 10);

void setup()
{
  mySerial.begin(9600);  
  Serial.begin(9600);
  delay(100);
  pinMode(DOUT,INPUT);
  pinMode(4,OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC);
  delay(2000);
  display.clearDisplay();
}

void loop() {
  if (flag==0)
  {
    display.clearDisplay();
    count = 0;
  }
  value = analogRead(AOUT);
  limit = 120;
  if (flag==0)
  {
  Serial.print("Alcohol Value: ");
  value = value*0.21;
  Serial.println(value);
  Serial.print("Limit: ");
  Serial.println(limit);
  delay(300);} 
  if((value>=120 && flag==0)|| (value>=120 && flag==1 && count>0)){
    flag = 1;
    count = count+1;
    if (count==3)
    {
     Serial.println("alcohol detected");
     mySerial.println("AT+CMGF=1");
     delay(1000);
     mySerial.println("AT+CMGS=\"+919412319800\"\r"); 
     delay(1000);
     mySerial.println("Alert!!! Alcohol detected\nDriver Name : Pranshur Goel\nCar No.:UP23DAXXXX\n");
     delay(100);
     mySerial.println((char)26);
     delay(300);
     display.clearDisplay();
     detectedAlcohol();
     delay(2000);
     display.clearDisplay();
    }
   else
   {
    delay(1000);
   }
}
  else
  {  
     flag = 0;
     display.clearDisplay();
     noAlcohol();
     delay(3000);
     display.clearDisplay(); 
  }
}
 void noAlcohol() 
 {
  if (flag==0)
  {
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.clearDisplay();
    display.println("Alcohol amount in");
    display.print  ("range");
    display.display();
  }
}
 void detectedAlcohol() 
 {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.clearDisplay();
  display.println("Alert Sent!!");
  display.display();
  delay(10000);
}
