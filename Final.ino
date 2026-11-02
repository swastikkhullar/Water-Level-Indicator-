#include <stdlib.h>
#include <LiquidCrystal.h>

int rs=2;
int e=3;
int d4=12,d5=11,d6=10,d7=9;
int gled=4;
int rled=5;
int trigpin=7;
int echopin=8;
double distance;
double duration;
double empty_dis=12.88;
double full_dis=2.00;
double percent_filled;
double diff=empty_dis-full_dis;
LiquidCrystal lcd(rs,e,d4,d5,d6,d7);

void GetDistance(){
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  duration=pulseIn(echopin,HIGH);
  distance=(duration*(0.0343))/2;
  distance=fabs(distance-empty_dis);
  delay(500);
  }

void GetPercent(){
percent_filled=(distance/diff)*100;
}

void PrintPercent(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WaterLevel:");
  lcd.setCursor(0,1);
  lcd.print(percent_filled);
  lcd.print(" %");
  }



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(rled,OUTPUT);
  pinMode(gled,OUTPUT);
  digitalWrite(gled,LOW);
  digitalWrite(rled,LOW); 
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  }

void loop() {
  // put your main code here, to run repeatedly:
  
  GetDistance();
  GetPercent();
  PrintPercent();
  delay(50);

 if((percent_filled)<25){
    digitalWrite(rled,LOW);
    delay(50);
    digitalWrite(gled,HIGH);
    delay(50);
      while(1){
      GetDistance();
      GetPercent();
      PrintPercent();   
      delay(50);           
        if((percent_filled)>90){
          digitalWrite(gled,LOW);
          delay(50);
          digitalWrite(rled,HIGH);
          delay(50);                         
          break;
        }
      }
  }else if(percent_filled>25){
    digitalWrite(rled,HIGH);
    delay(50);
 }
  delay(50);
}
