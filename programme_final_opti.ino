#include <TinyGPS++.h>//include the library code
#include <SoftwareSerial.h>//include the library code
#include <Servo.h>
#define buzzer  10
#define echoPin 13
#define trigPin 12
#define echoPin2 17
#define trigPin2 16
#define echoPin1 3// Echo Pin
#define trigPin1 2 // Trigger Pin
// motor one
#define enA  11
#define in1  9
#define in2  8
// motor two
#define enB  5

#define in3  7
#define in4  6
//Speed of the Motors
#define ENASpeed 65
#define ENBSpeed 55
#define Led_R 14 
#define Led_V 15 

Servo myservo;  // create servo object to control a servo
float droite=0;
int const maximumRange=200;
int const minimumRange=0;
long duration, distance; 
long duration1, distance1;
long duration2, distance2;// Duration used to calculate distance
int const phi_init=105;
int const phi_gauche=165;
int const phi_droite=55;
int i=0;
//*************************************************************
TinyGPSPlus gps;// The TinyGPS++ object
boolean msg=0;
void setup()
{
   pinMode(trigPin, OUTPUT);
 pinMode(buzzer, OUTPUT);
 pinMode(echoPin, INPUT);
  // put your setup code here, to run once:
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(Led_R, OUTPUT);
  pinMode(Led_V, OUTPUT);
  myservo.attach(4);
  analogWrite(enA,ENASpeed);
  analogWrite(enB,ENBSpeed);
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);
 pinMode(buzzer, OUTPUT);
 
  pinMode(23,INPUT);
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();

  digitalWrite(Led_V,LOW);
  digitalWrite(Led_R,LOW);
  
}

float ultrason_avant()
{
   digitalWrite(trigPin1, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin1, LOW);
 duration1 = pulseIn(echoPin1, HIGH); 
 distance1 = duration1/58.2;

  if((distance1<=20)&&(distance1>0))
{
digitalWrite(buzzer,HIGH);

  }
 else 
 {
 digitalWrite(buzzer,LOW);
 }
 //Calculate the distance (in cm) based on the speed of sound.
 }

  

void go() {


  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  }
  
void back() {
  
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnleft() {

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  }
 
void turnright() {
 

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  }
void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  }
float  ultrason()
{
   digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH); 
 distance = duration/58.2;

 if (distance >= maximumRange || distance <= minimumRange){
  return -1; }
 else {
 return distance;
 //Calculate the distance (in cm) based on the speed of sound.
 }

  }
  float  ultrason2()
{
   digitalWrite(trigPin2, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin2, LOW);
 duration2 = pulseIn(echoPin2, HIGH); 
 distance2 = duration2/58.2;

 if (distance2 >= maximumRange || distance2 <= minimumRange){
  return -1; }
 else {
 return distance2;
 //Calculate the distance (in cm) based on the speed of sound.
 }

  }
float dis_droite() {
  myservo.write(phi_droite);
delay(500);
float dis_droite =  ultrason();
//Serial.print("droite = ");
//Serial.println(dis_droite);
return dis_droite;

  
}
float dis_gauche() {
  myservo.write(phi_gauche);
delay(500);
float dis_gauche =  ultrason();
//Serial.print("gauche = ");
//Serial.println(dis_gauche);
return dis_gauche;
  
  
}
float dis_centrale() {
  
myservo.write(phi_init);
delay(500);
float dis_central =  ultrason();
//Serial.print("initial = "); 
//Serial.println(dis_central); 
return dis_central;
  
}
void suiveur ()
{
   digitalWrite(Led_V,HIGH);

   float dis_turnright =  ultrason2();
  if (dis_turnright<20 && dis_turnright>0) {
    ultrason_avant();
    do{
      turnright();
    //Serial.print("turn right ");
    droite = dis_centrale();
    ultrason_avant();
    }while (droite > 20 );
  }
  
 float cd =  dis_centrale();
 ultrason_avant();
  while (cd < 20 && cd >0){
  Stop();
  //Serial.println("Stop");
   ultrason_avant();
  
  cd =  dis_centrale();

displayInfo();

  }
  
  float dd =  dis_droite();
ultrason_avant();
  if (dd < 20 && dd >0){
  ultrason_avant();
    myservo.write(phi_init);
    do { go();
      ultrason_avant();
     cd = dis_centrale();
   //  Serial.println("go");
    
  }
   while (cd>20 || cd==20);
  }
  
 
  float dg = dis_gauche();
   ultrason_avant();
   if (dg < 20 && dg >0){
    myservo.write(phi_init);
    do { back();
      ultrason_avant();
     cd = dis_centrale();
  //   Serial.println("back");

  }
   while (cd> 20|| cd== 20) ;
    ultrason_avant();
  
   }
  //dis_gauche();
  //dis_centrale();

  //dis_droite();
  


}


void loop()
{

    if(Serial1.available() > 0){
    while(Serial1.available() > 0){
      Serial.print((char)Serial1.read());
    }
  }

 if (i<10)
 {
  Serial1.println("AT");
  delay(1000);
  i++;
  }

   else 
   {     
       Serial1.println("at+gps=1");
        delay(2000);
         Serial1.println("at+gpsrd=1");
        delay(2000);
      Serial.println("###################################");
      
      while (1)
      {
 
  // This sketch displays information every time a new sentence is correctly encoded.
  while (Serial1.available() > 0)
    if (gps.encode(Serial1.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    
 
  digitalWrite(Led_R,HIGH);
  
    Serial.println(F("No GPS detected: check wiring."));
    while(1){suiveur();}
  }/////////////////

        } //   
       
    }
 
  
  }

void displayInfo()
{


        msg=digitalRead(23);

        if (msg==HIGH)
        {
          Stop();
        Serial1.println("at+cmgf=1");
        delay(2000);
        Serial1.println("at+cmgs=+21655920706");
        delay(2000);
        Serial1.print("guideMe : http://www.google.com/maps/place/" + String (gps.location.lat()) + "," + String (gps.location.lng()));//
        Serial1.print((char)26); 
        
        }
      
suiveur();


 /* 
  Serial.print(F("Location: ")); 
 if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
 {
   Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
  */
}
