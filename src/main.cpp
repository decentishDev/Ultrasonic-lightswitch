#include <Arduino.h>
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;

float currentR = 255;
float currentG = 0;
float currentB = 0;
String currentGoal = "G";

bool isLightOn = false;
bool isHandInFront = false;

int timeLeft = 0;

float modifier = 0;
float modifierDirection = 0;

void setup(){
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");

  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}

void RGB_color(float red_light_value, float green_light_value, float blue_light_value){
  int actualR = round(red_light_value);
  int actualG = round(green_light_value);
  int actualB = round(blue_light_value);
  analogWrite(red_light_pin, actualR);
  analogWrite(green_light_pin, actualG);
  analogWrite(blue_light_pin, actualB);
  Serial.print(actualR);
  Serial.print(" ");
  Serial.print(actualG);
  Serial.print(" ");
  Serial.println(actualB);
}

void loop(){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  // Serial.print("Distance: ");
  // Serial.print(distance);
  // Serial.println(" cm");

  if(currentGoal == "R"){
    if(currentR == 255){
      currentGoal = "G";
      currentR -= 1;
      currentG += 1;
    }else{
      currentR += 1;
      currentB -= 1;
    }
  }else{
    if(currentGoal == "G"){
      if(currentG == 255){
        currentGoal = "B";
        currentG -= 1;
        currentB += 1;
      }else{
        currentG += 1;
        currentR -= 1;
      }
    }else{
      if(currentB == 255){
        currentGoal = "R";
        currentB -= 1;
        currentR += 1;
      }else{
        currentB += 1;
        currentG -= 1;
      }
    }
  }
  if(distance < 100){
    if(distance < 30){
      isHandInFront = true;
    }else{
      isHandInFront = false;
    }
  }

  if(timeLeft > 0){
    timeLeft -= 1;
  }

  if(isHandInFront && timeLeft==0){
    isLightOn = !isLightOn;
    timeLeft = 100;
    
    if(isLightOn == true){
      modifierDirection = 1;
    }else{
      modifierDirection = -1;
    }
  }

  if(modifier == 0 && modifierDirection == -1){
    modifierDirection = 0;
  }
  if(modifier == 20 && modifierDirection == 1){
    modifierDirection = 0;
  }

  modifier = modifier + modifierDirection;

  // Serial.print(isLightOn);
  // Serial.print(modifierDirection);
  // Serial.println(modifier);
  RGB_color(currentR * (modifier/20), currentG * (modifier/20), currentB * (modifier/20));
  // if(isLightOn){
  //   RGB_color(0, 150, 150);
  // }else{
  //   RGB_color(0, 0, 0);
  // }
  delay(10);
}


