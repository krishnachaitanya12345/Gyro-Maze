#include <ESP8266WiFi.h>
#include <Servo.h>
#include <ESP8266HTTPClient.h>
String  i, x, y;
Servo myservo;
Servo myservo1;
WiFiServer server(80);
int k,a,b;
  int pos;
  int pos1;
void setup()
{
  myservo.attach(D2);
  myservo1.attach(D4);
  i = "";
  Serial.begin(9600);
  WiFi.disconnect();
  delay(2000);
  Serial.println("Connecting to WIFI");
  WiFi.begin("ECE01", "ecevasavi");
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(500);
    Serial.print("..");

  } Serial.println("I am Connected");
  Serial.println("My Local IP is : ");
  Serial.print((WiFi.localIP()));
  server.begin();
}
void turnacw(int pos)
{
  myservo.write(0);
  delay(7*pos);
  myservo.write(95);
  delay(100);
  myservo.write(180);
  delay(7*pos);
  myservo.write(95);
  
  return;
}
void turnaaw(int pos)
{
  myservo.write(170);
  delay(5*pos);
  myservo.write(95);
  delay(100);
  myservo.write(0);
  delay(5*pos);
  myservo.write(95);
  
  return;
  
}
void turnbcw(int pos1)
{
  myservo1.write(0);
  delay(6.5*pos1);
  myservo1.write(95);
  delay(100);
  myservo1.write(180);
  delay(6.9*pos1);
  myservo1.write(95);
  return;
}
void turnbaw(int pos1)
{
  myservo1.write(180);
  delay(4.5*pos1);
  myservo1.write(95);
  delay(100);
  myservo1.write(0);
  delay(4.3*pos1);
  myservo1.write(95);
  return;
}
void loop()
{

  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  i = (client.readStringUntil('\r'));
  Serial.println(i);
  i.remove(0, 5);
  i.remove(i.length() - 9, 9);
  k = i.indexOf('/');
  x = i.substring(0, k);
  y=i.substring(k+1,i.length());
  Serial.println(i);
  Serial.println(x);
  Serial.println(y);
  a= x.toInt();
  b= y.toInt();
  if(a>-95 && a<-45)
  {
    pos=map(a,-95,-45,0,40);
    turnacw(pos);
    Serial.println(pos);
  }
  if(a>45 && a<95)
  {
    pos=map(a,45,95,0,40);
    turnaaw(pos);
  }
  
  if(b>-95 && b<-45)
  {
    pos1=map(b,-95,-45,0,60);
    turnbcw(pos1);
  }
  
  if(b>45 && b<95)
  {
    pos1=map(b,45,95,0,60);
    turnbaw(pos1);
  }
}
