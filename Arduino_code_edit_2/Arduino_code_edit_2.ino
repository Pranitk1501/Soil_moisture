#include <dht11.h>
#define datapin 8
//#define pumppin 5
dht11 DHT;
#define sensorpin A0
#define sensorPower 10 


void setup() {

  pinMode(sensorPower,OUTPUT);
  pinMode(sensorpin,INPUT);
  digitalWrite(sensorPower,LOW);  //keeping the sensor off at beginning 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

 String final_display= (get_dht_temp()+','+ get_mositure_data());
 delay(1000);
 Serial.flush();
 delay(1000);
 Serial.println(final_display);
 delay(2000);

}

String get_dht_temp()
{
  
int readData= DHT.read(datapin);
float t=DHT.temperature;
String st= String(t);
float h=DHT.humidity;
String sh= String(h);
return (st+','+sh);
//Serial.println("temp func called");
}
//String get_dht_humid()
//{
//  
//int readData= DHT.read(datapin);
//float h=DHT.humidity;
//String sh= String(h);
//return sh;
//}
String get_mositure_data()
{
  int val_data=readSensor();
  String sval_data=String(val_data);
  return sval_data;
  
  
//  Serial.println("Moist called");
}

int readSensor()
{
  digitalWrite(sensorPower,HIGH);
  delay(20);
  int valu = digitalRead(sensorpin);
  digitalWrite(sensorPower,LOW);
  return valu;
}
