#include <DHT.h>
#include <DHT_U.h>
#include <printf.h>


#define LED_G 12
#define LED_R 11
#define PIN_DHT 5
#define SW_PIN 2
//#define X_PIN A0
//#define Y_PIN A1

DHT dht(PIN_DHT, DHT11);
const int X_PIN = 0;
const int Y_PIN = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_G, OUTPUT);
  //digitalWrite( LED_G, HIGH);
  pinMode(LED_R, OUTPUT);
  //digitalWrite( LED_R, HIGH);
  pinMode(SW_PIN, HIGH);
  digitalWrite(SW_PIN, HIGH);
 
  Serial.begin(9600);
  dht.begin();
}

void loop() {
 
    float temp, humid; 
    int Engine_shut_down;
    int Shut_Down_Count = 1;
    temp = dht.readHumidity();
    humid = dht.readTemperature();
    digitalWrite( LED_R, LOW);  
    digitalWrite( LED_G, HIGH);
    while(temp >= 0){ //check to make sure temperature is above zero degrees celsius 
      int potValue = analogRead(A2); //poteniometer Reading
      int angleValue = map(potValue,0,1023,0,180); //poteniometer Reading angle
      Serial.println(analogRead(X_PIN)); 
      Serial.println(analogRead(Y_PIN));
      Serial.println(angleValue);
      Serial.println(Engine_shut_down);
      Serial.println(Shut_Down_Count);
      Serial.println(temp);
      if(angleValue <= 60){//if the potenitometer is in a low range
           Engine_shut_down = 60;//set time to 10 minutes
         }
      if((120 <= angleValue)  && (angleValue <= 180)) {
          Engine_shut_down = 180;//set time to 20 minutes
          }
       if((60 <= angleValue) && (angleValue <= 120)){
          Engine_shut_down = 120;//set time to 30 minutes
          }
            
      if ((((((analogRead(X_PIN) >= 512) && (analogRead(X_PIN)) <= 522)) && ((analogRead(Y_PIN)) >= 532)) && ((analogRead(Y_PIN)) <= 540))){ //Test to see if throttle, high idle have been used
         delay(10000); //set delay 10 seconds
         Shut_Down_Count++; //if the conditions are met increment the timer
          if(Shut_Down_Count == Engine_shut_down){// check to see if count has reached point of inactivity
           digitalWrite( LED_R, HIGH);  //send engine kill signal
           digitalWrite( LED_G, LOW);
           delay(10000); // set kill status for ao seconds
           Shut_Down_Count = 0; // reset count
           digitalWrite( LED_R, LOW);  //reset engine kill status
           digitalWrite( LED_G, HIGH);
           }
         }else{ 
        Shut_Down_Count = 0;  //reset Counter if throttle is used
        delay(1000);
       } 
    }
}

    
