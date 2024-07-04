#include <Arduino.h>
#include <TM1637Display.h>
//Load RTC DS1307's library
#include <DS1307.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

//Random comment
 
//i2c ports in Arduino UNO 
DS1307 rtc(A4, A5);

char horariocru;
char* hora;
char* minuto;
int horaint;
int minutoint;
int horaminuto;

TM1637Display display(CLK, DIO);

void setup() {
  // put your setup code here, to run once:
  rtc.halt(false);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //horariocru= ;
  hora = strtok(rtc.getTimeStr(), ":");
  Serial.print("hora= ");
  Serial.println(hora);
  minuto= strtok(NULL, ":");
  Serial.print("minuto= ");
  Serial.println(minuto);
  horaint= atoi(hora)*100;
  minutoint= atoi(minuto);
  horaminuto= horaint + minutoint;
  display.setBrightness(0x0f);
  display.clear();
  display.showNumberDec(horaminuto, false);
  
  delay(1000);
}
