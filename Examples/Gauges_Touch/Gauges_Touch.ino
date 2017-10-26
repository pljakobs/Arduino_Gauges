#include <Adafruit_ILI9341.h>
#include <Gauges.h>
#include <XPT2046_Touchscreen.h>

#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>

#define _sclk 13
#define _miso 12

#define _mosi 11
#define _cs   10
#define _dc   9
#define _rst  8
#define _led  6

#define _int_t 4
#define _cs_t  20



// Common 16-bit colors:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//XPT2046_Touchscreen ts(_cs_t);
XPT2046_Touchscreen ts(_cs_t,_int_t);
Adafruit_ILI9341 tft=Adafruit_ILI9341(_cs, _dc,_rst);

textGauge horizontal = textGauge(&tft,20,20,100,40);
textGauge vertical   = textGauge(&tft,20,80,100,40);
textGauge pressure   = textGauge(&tft,20,140,100,40);
tapeGauge t_horizontal = tapeGauge(&tft,0,220,300,20,TAPE_RIGHTLEFT);
tapeGauge t_vertical   = tapeGauge(&tft,300,0,20,220,TAPE_BOTTOMUP);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  
  pinMode(_led, OUTPUT);
  
  tft.begin();
  tft.setRotation(3);
  tft.clearDisplay();
  ts.begin();
  //analogWrite(_led,512);

  // configure Gauges - only on setup
  
  horizontal.setAutoRedraw(true);
  horizontal.setFGColor(WHITE);
  horizontal.setBGColor(BLACK);
  horizontal.setBorder(2);
  horizontal.setBorderColor(BLUE);
  horizontal.setGutter(2);
  horizontal.setHAlign(TEXT_RIGHT);
  horizontal.setVAlign(TEXT_CENTER);
  horizontal.setFont(&FreeMonoBold18pt7b);

  t_horizontal.setAutoRedraw(true);
  t_horizontal.setBorder(2);
  t_horizontal.setFGColor(RED);
  t_horizontal.setBGColor(BLACK);
  t_horizontal.setBorderColor(WHITE);
  t_horizontal.setGutter(1);
  t_horizontal.setMinMax(250,3800);
  t_horizontal.setValue(0);
  
  vertical.setAutoRedraw(true);
  vertical.setFGColor(WHITE);
  vertical.setBGColor(BLACK);
  vertical.setBorder(2);
  vertical.setBorderColor(BLUE);
  vertical.setGutter(2);
  vertical.setHAlign(TEXT_RIGHT);
  vertical.setVAlign(TEXT_CENTER);
  vertical.setFont(&FreeMonoBold18pt7b);

  t_vertical.setAutoRedraw(true);
  t_vertical.setBorder(2);
  t_vertical.setFGColor(RED);
  t_vertical.setBGColor(BLACK);
  t_vertical.setBorderColor(WHITE);
  t_vertical.setGutter(1);
  t_vertical.setMinMax(250,3800);
  t_vertical.setValue(0);  

  pressure.setAutoRedraw(true);
  pressure.setFGColor(WHITE);
  pressure.setBGColor(BLACK);
  pressure.setBorder(2);
  pressure.setBorderColor(BLUE);
  pressure.setGutter(2);
  pressure.setHAlign(TEXT_RIGHT);
  pressure.setVAlign(TEXT_CENTER);
  pressure.setFont(&FreeMonoBold18pt7b);

  horizontal.setValue(0);
  vertical.setValue(0);
  pressure.setValue(0);
  t_horizontal.setValue(250);
  t_vertical.setValue(250);

}

void loop() {
  // put your main code here, to run repeatedly:

  bool istouched=ts.touched();
  
  if(istouched){
    TS_Point p = ts.getPoint();
    Serial.printf("x: %i, y: %i, z: %i\n",p.x,p.y,p.z);
    horizontal.setValue(p.y);
    t_horizontal.setValue(p.y);
    vertical.setValue(p.x);
    t_vertical.setValue(p.x);
    pressure.setValue(p.z);
  }else{
    Serial.println("no touch");
  }
  delay(100);
}
