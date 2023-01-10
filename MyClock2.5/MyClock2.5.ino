#include <Wire.h>
#include <DS3231.h>
#include <SimpleDHT.h>

DS3231 clock;
RTCDateTime dt;
SimpleDHT11 dht11;

const int dataPin = 8;
const int latchPin = 9;
const int clockPin = 10;
const int sensePin=5;
int tempPin = 6;

const int del = 100;

const byte num[] = {
  B11111100,  //0
  B01100000,  //1
  B11011010,  //2
  B11110010,  //3
  B01100110,  //4
  B10110110,  //5
  B10111110,  //6
  B11100000,  //7
  B11111110,  //8
  B11110110,  //9
};

const byte digit[4] = {
  B11001111,
  B11010111,
  B11011011,
  B11011101
};

int ha=0;
int hb=0;
int ma=0;
int mb=0;
int sa=0;
int sb=0;

int ta=0;
int tb=0;
unsigned long lastTemp=0;

void setup() {
  Serial.begin(9600);

  Serial.println("Initialize DS3231");;
  clock.begin();
  Serial.println("Done!");
  clock.setDateTime(__DATE__, __TIME__);
   
  //Initialise Pins
  pinMode(sensePin, INPUT);
  
  //Initialise Serial Register Pins
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  //Reset Clock Display
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,MSBFIRST, 0);
  shiftOut(dataPin,clockPin,MSBFIRST, B11111111);
  digitalWrite(latchPin,HIGH);
    
}

void loop() {
  dt = clock.getDateTime();

  ha=dt.hour/10;
  hb=dt.hour%10;
  ma=dt.minute/10;
  mb=dt.minute%10;
  sb=dt.second;
if (digitalRead(sensePin)==LOW) {
  //SevSeg Section
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST, num[ha]);
  shiftOut(dataPin,clockPin,LSBFIRST, digit[0]);
  digitalWrite(latchPin,HIGH);
  delayMicroseconds(del);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST, num[hb]);
  shiftOut(dataPin,clockPin,LSBFIRST, digit[1]);
  digitalWrite(latchPin,HIGH);
  delayMicroseconds(del);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST, num[ma]);
  shiftOut(dataPin,clockPin,LSBFIRST, digit[2]);
  digitalWrite(latchPin,HIGH);
  delayMicroseconds(del);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST, num[mb]);
  shiftOut(dataPin,clockPin,LSBFIRST, digit[3]);
  digitalWrite(latchPin,HIGH);
  delayMicroseconds(del);
  if (sb % 2 == 0) {
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST, B00000001);
  shiftOut(dataPin,clockPin,LSBFIRST, B11011110);
  digitalWrite(latchPin,HIGH);
  delayMicroseconds(del);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST, B00000000);
  shiftOut(dataPin,clockPin,LSBFIRST, B11011111);
  digitalWrite(latchPin,HIGH);
  } else {
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST, B00000000);
    shiftOut(dataPin,clockPin,LSBFIRST, digit[3]);
    digitalWrite(latchPin,HIGH);
  }
} else {
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST, num[ta]);
  shiftOut(dataPin,clockPin,LSBFIRST, digit[0]);
  digitalWrite(latchPin,HIGH);
  delayMicroseconds(del);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST, num[tb]);
  shiftOut(dataPin,clockPin,LSBFIRST, digit[1]);
  digitalWrite(latchPin,HIGH);
  delayMicroseconds(del);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST, B11000110);
  shiftOut(dataPin,clockPin,LSBFIRST, digit[2]);
  digitalWrite(latchPin,HIGH);
  delayMicroseconds(del);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST, B10011100);
  shiftOut(dataPin,clockPin,LSBFIRST, digit[3]);
  digitalWrite(latchPin,HIGH);
  delayMicroseconds(del);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST, B00000000);
  shiftOut(dataPin,clockPin,LSBFIRST, digit[3]);
  digitalWrite(latchPin,HIGH);
}
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(tempPin, &temperature, &humidity, data)) {
    return;
  }
  if (temperature >0) {
  ta=(int)temperature/10;
  tb=(int)temperature%10;
  }
}
