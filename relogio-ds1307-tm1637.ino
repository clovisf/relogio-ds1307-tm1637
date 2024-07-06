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


char* hour;
char* minute;
int hourint;
int minuteint;
int hourminute;

const uint8_t cletter[] = {
	SEG_A | SEG_D | SEG_E | SEG_F            //Letter 'C'
	};

TM1637Display display(CLK, DIO);

// Thermistor pin
const int pinThermistor = A0;
 
// thermistor parameters
const double beta = 3950.0;
const double r0 = 10000.0;
const double t0 = 273.0 + 25.0;
const double rx = r0 * exp(-beta/t0);
 
// circuit parameters
const double vcc = 4.92;
const double R = 9810.0;
 
// Number of samples
const int nsamples = 5;

int currenttime;
int oldtime;
int sweepcounter;

void setup() {
  // put your setup code here, to run once:
  rtc.halt(false);
  //Serial.begin(9600);
  display.clear();
}

void loop() {

hour = strtok(rtc.getTimeStr(), ":");
//Serial.print("hour= ");
//Serial.println(hour);
minute= strtok(NULL, ":");
//Serial.print("minute= ");
//Serial.println(minute);
hourint= atoi(hour)*100; //to integer conversion
minuteint= atoi(minute);
hourminute= hourint + minuteint;
display.setBrightness(0x0f);
if(sweepcounter == 1){
  display.clear();
}
display.showNumberDecEx(hourminute, 0x40, false);
// how to show the dots in the middle: https://forum.arduino.cc/t/how-to-show-the-two-dots-on-4-digit-7-segments-display/592130/2
delay(2000);
// Read the sensor a couple of times
int sum = 0;
for (int i = 0; i < nsamples; i++) {
  sum += analogRead(pinThermistor);
delay (5);
}

// Thermistor resistance
double v = (vcc*sum)/(nsamples*1024.0);
double rt = (vcc*R)/v - R;

// Temperature calculations (celsius)
double t = beta / log(rt/rx);
int tempcelsius= t-273.0;

display.showNumberDecEx(tempcelsius, false, 1, 3);
display.setSegments(cletter, 1, 3); //Letter 'C'
delay(2000);    

  
     
}
  

