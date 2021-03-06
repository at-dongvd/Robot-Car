#include <Servo.h>
String data;

int enA = 5;
int in1 = 7;
int in2 = 4;
// motor two
int enB = 6;
int in3 = 3;
int in4 = 2;

// Pin Led
int Pin_Led = 10;

// Servo control hand shift Left or Right 
Servo servo1;

// Servo control hand shift Up or Down
Servo servo2;

// Servo control hand shift In or Out
Servo servo3;

// Servo control hand with hold or Throw
Servo servo4;

Servo servo;

// Set start degrees of servo 1
int i=90;

// Set start degrees of serrvo 2
int j=90;

// Set start degrees of servo 3
int k=90;

// Set start degrees of servo 4
int m=120;

int Degrees;

// Servo 1 Pin Init
int servo_Pin_1 = 9;

// Servo 2 Pin Init
int servo_Pin_2 = 11;

// Servo 3 Pin Init
int servo_Pin_3 = 12;

// Servo 4 Pin init
int servo_Pin_4 = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(Pin_Led, OUTPUT);

  servo1.attach(servo_Pin_1);

  servo2.attach(servo_Pin_2);

  servo3.attach(servo_Pin_3);

  servo4.attach(servo_Pin_4);
}

// Function stop car
void Stop(){
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        // set speed to 0 out of possible range 0~255
        analogWrite(enA, 0);
        // turn on motor B
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        // set speed to 0 out of possible range 0~255
        analogWrite(enB, 0);
  }

// Function Forward car
void Forward(){
       digitalWrite(in1, HIGH);
       digitalWrite(in2, LOW);
       // set speed to 170 out of possible range 0~255
       analogWrite(enA, 170);
      // turn on motor B
       digitalWrite(in3, HIGH);
       digitalWrite(in4, LOW);
      // set speed to 170 out of possible range 0~255
      analogWrite(enB, 170);
  }

// Function Reverse car
void Reverse(){
       digitalWrite(in1, LOW);
       digitalWrite(in2, HIGH);
       // set speed to 170 out of possible range 0~255
       analogWrite(enA, 170);
       // turn on motor B
       digitalWrite(in3, LOW);
       digitalWrite(in4, HIGH);
       // set speed to 170 out of possible range 0~255
       analogWrite(enB, 170);
  }
  
// Function turnleft car
void turnLeft(){
       digitalWrite(in1, HIGH);
       digitalWrite(in2, LOW);
       // set speed to 170 out of possible range 0~255
       analogWrite(enA, 170);
       // turn on motor B
       digitalWrite(in3, LOW);
       digitalWrite(in4, HIGH);
       // set speed to 170 out of possible range 0~255
       analogWrite(enB, 170);
  }

// Function turnright car 
void turnRight(){
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        // set speed to 170 out of possible range 0~255
        analogWrite(enA, 170);
        // turn on motor B
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        // set speed to 170 out of possible range 0~255
        analogWrite(enB, 170);
  }

// Function turn on light
void turnOn(){
  digitalWrite(Pin_Led, HIGH);
  }

// Function turn off light
void turnOff(){
  digitalWrite(Pin_Led, LOW);
  }

//count up from Degrees->max
void countUp(int max){
  while(Degrees<max){
  Degrees++;
  servo.write(Degrees);
  Serial.print(Degrees);
  delay(75);
  char c = Serial.read();
  if(c=='S') break;
  }
}

//count down from Degrees->min
void countDown(int min){
  while(Degrees>min){
  Degrees--;
  servo.write(Degrees);
  Serial.print(Degrees);
  delay(75);
  char c = Serial.read();
  if(c=='S') break;
  }
}

// Function Shift right the Hand
void Left(){
  Degrees=i;
  servo=servo1;
  countUp(180);
  i=Degrees;
}

// Function Shift left the Hand
void Right(){
  Degrees=i;
  servo=servo1;
  countDown(0);
  i=Degrees;
}

// Function Shift Up the hand
void Up(){
  Degrees=j;
  servo=servo2;
  countUp(100);
  j=Degrees;
}

// Function Shift Down the hand
void Down(){
  Degrees=j;
  servo=servo2;
  countDown(50);
  j=Degrees;
}

// Function Shift In the hand
void In(){
  Degrees=k;
  servo=servo3;
  countUp(180);
  k=Degrees;
}

// Function Shift Out the hand
void Out(){
  Degrees=k;
  servo=servo3;
  countDown(0);
  k=Degrees;
}

// Function Throw
void throwHand(){
  Degrees=m;
  servo=servo4;
  countUp(180);
  m=Degrees;
}

// Function Hold
void holdHand(){
  Degrees=m;
  servo=servo4;
  countDown(110);
  m=Degrees;
}

// Function handle command
void handleCommand(String command){
  // Control lights
  if(command=="On"){     
      turnOn();                                     // Turn on Lights
  }
  else if(command=="Off"){
      turnOff();                                    // Turn off Lights
  }
  
  // Drive Car
  if(command=="Forward"){
      Forward();                                    // go to Forward
  }
  else if(command=="Backward"){
      Reverse();                                    // go to Backward
  }
  else if(command=="TLeft"){
     turnLeft();                                    // go to Forward Left
  }
  else if(command=="TRight"){
     turnRight();                                   // go to Forward Left
  }
  // Control Hand
  else if(command=="Left"){                         // shift left
    Left();
    }
  else if(command=="Right"){                        // shift right
    Right();
    }
  else if(command=="Up"){                           // shift up
    Up();
    }
  else if(command=="Down"){                         // shift down
    Down();
    }
  else if(command=="Out"){                          // shift out
    Out();
    }
  else if(command=="In"){                           // shift in
    In();
    }
  else if(command=="Hold"){                         // Hold
    holdHand();
    }
  else if(command=="Throw"){                        // Throw
    throwHand();
    }
  else if(command=="Stop"){                         // Stop working
    Stop();                                    
    }
}  
  
void loop() {
    while(Serial.available())
    { 
      char c = Serial.read();                       // listeing data send to
      data+=c;                                      // add string
      delay(2);                                     // delay 2ms
    }
    if(data.length()>0){
      Serial.println(data);
      handleCommand(data);                          // run function handle command
      }
      data="";                                      // clear string
}
