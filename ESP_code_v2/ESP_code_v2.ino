#include<ESP8266WiFi.h>
#include<FirebaseArduino.h>

#define FIREBASE_AUTH "Xoo68HdUHTZ3boPDzY312QsL7V7IXX3vWTL3krfN" 
#define FIREBASE_HOST "test-part2-ed291-default-rtdb.firebaseio.com"
#define WIFI_SSID "Pranit CE"
#define WIFI_PASSWORD "1234567890"
#define ledpin 0 
String final_display,sensor_data;
String humid_values,temp_values,moisture_values;  


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
   
  delay(1000);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
//    Serial.println("Connected");
    delay(500);
    
  }
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
  {
//    Serial.println("Connected to Firebase");
  }
}

void loop() {

bool sr=false;


  while(Serial.available())
  {
    sensor_data= Serial.readString();
    digitalWrite(ledpin,HIGH);
//    Serial.println("Took values from arduino");
    sr=true;
  }

  delay(1000);

  if(sr==true);
  
  {
   final_display=sensor_data;
    
  int fristCommaIndex = final_display.indexOf(',');
  int secondCommaIndex = final_display.indexOf(',', fristCommaIndex+1);
  int thirdCommaIndex = final_display.indexOf(',', secondCommaIndex+1);
  String temp_values = final_display.substring(0, fristCommaIndex);
  String humid_values = final_display.substring(fristCommaIndex+1, secondCommaIndex);
  String moisture_values = final_display.substring(secondCommaIndex+1,thirdCommaIndex-1);
 
  Firebase.setString("Temperature",temp_values);
  delay(10);
  Firebase.setString("Humidity",humid_values);
  delay(10);
  Firebase.setString("moisture",moisture_values);
  delay(10);

  delay(1000);
//  i++;
//  j++;
//  k++;

  Firebase.pushString("Past Temperature values",temp_values);
  delay(100);
// 
  Firebase.pushString("Past Moisture values",moisture_values);
  delay(100);
//
//  Firebase.pushInt("Past Humidity values",k++);
//  delay(100);
  Firebase.pushString("Past humidity values",humid_values);
  delay(100);
digitalWrite(ledpin,LOW);
//  delay(1000);
if(Firebase.failed())
{
//  Serial.print("failed");
  return;
  
}
  }
  
}
