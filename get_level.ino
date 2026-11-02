#include <stdlib.h>

double empty_dis=12.88;
double full_dis=2.00;
double diff=empty_dis-full_dis;
int trigpin=7;
int echopin=8;
int gled=4;
int rled=5;
double distance;
double duration;
double percent_filled;

void getDistance(){
digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  duration=pulseIn(echopin,HIGH);
  distance=(duration*(0.0343))/2;

}
void getPercent(){
  percent_filled=(distance/diff)*100;
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


}

void loop() {
  // put your main code here, to run repeatedly:
  getDistance();
  getPercent();
  Serial.print("Distance = ");
  Serial.println(distance);
  delay(100);
  


}
