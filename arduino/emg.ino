#include <Servo.h> //Open servo library

Servo thumb, index, middle, wrist; //Create servo objects

//Store pin numbers for light system
int greenLED = 6;
int redLED = 7;

void setup() {
  // put your setup code here, to run once:
  //Attach servos to each object
  thumb.attach(9);
  middle.attach(10);
  index.attach(11);
  wrist.attach(12);

  //Control the output of the LEDs
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  //Helps communicate with python, USB, and arduino
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Communicates with python
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n'); //Python sends the degrees of the hand/finger
    
    //Checks predicted gesture vs actual gesture and returns LED
    if (data == "CORRECT") {
      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, LOW);
      return;
    }
    
    if (data == "INCORRECT") {
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);
      return;
    }

    // Identify commas of each python signal
    int c1 = data.indexOf(',');
    int c2 = data.indexOf(',', c1 + 1);
    int c3 = data.indexOf(',', c2 + 1);
    
    //Extract numbers from each 
    int a1 = data.substring(0, c1).toInt();
    int a2 = data.substring(c1 + 1, c2).toInt();
    int a3 = data.substring(c2 + 1, c3).toInt();
    int a4 = data.substring(c3 + 1).toInt();
    
    //Moves servos according to the python data (now simplified/separated)
    thumb.write(a1);
    middle.write(a2);
    index.write(a3);
    wrist.write(a4);
    
    //If it is a valid gesture...
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    
    //Send OK to python
    Serial.println("OK");
  }
}

