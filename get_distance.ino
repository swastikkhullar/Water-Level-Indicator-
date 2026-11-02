
int trigpin=7;
int echopin=8;
double distance;
double duration;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(trigpin,OUTPUT);
pinMode(echopin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trigpin,LOW);
delayMicroseconds(2);
digitalWrite(trigpin,HIGH);
delayMicroseconds(10);
digitalWrite(trigpin,LOW);
duration=pulseIn(echopin,HIGH);
distance=(duration*0.0343)/2;
Serial.print("Distance = ");
Serial.println(distance);
delay(100);

}
