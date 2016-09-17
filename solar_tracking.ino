#include <Servo.h>
Servo verticalServo;
Servo horizontalServo;
class Motor{
  int vertical;
  int horizontal;
  int initializeVerticalDegree = 10;
  int initializeHorizontalDegree = 10;
  int stepMovement = 5;
  int protectionDelayMinSec = 50;
  public:
    void attachVertical(int digitalPin){
        delay(protectionDelayMinSec);
        verticalServo.attach(digitalPin);
        verticalServo.write(10);
      }
    void attachHorizontal(int digitalPin){
        delay(protectionDelayMinSec);
        horizontalServo.attach(digitalPin);
        horizontalServo.write(10);
      }
    void moving(int TR , int DR , int TL, int DL){
        vertical = (TR +  TL) - (DR + DL);
        horizontal = (TL + DL) - (TR + DR);
        Serial.print("vertical:");
        Serial.println(vertical);
        Serial.print("horizontal:");
        Serial.println(horizontal);
        Serial.print("initializeVerticalDegree:");
        Serial.println(initializeVerticalDegree);
        Serial.print("initializeHorizontalDegree:");
        Serial.println(initializeHorizontalDegree);
        if (vertical <= 0){
            up();
          }
        else{
           down();
          }

        if (horizontal <= 0){
           right();
          }
        else{
           left();
          }
      }
  private:
    void right(){
//        Serial.println("go Right");
        if (initializeHorizontalDegree >= 175) return;
        initializeHorizontalDegree += stepMovement;
        horizontalServo.write(initializeHorizontalDegree);
        delay(protectionDelayMinSec);
      }
    void left(){
//        Serial.println("go Left");
        if (initializeHorizontalDegree <= 5) return;
        initializeHorizontalDegree -= stepMovement;
        horizontalServo.write(initializeHorizontalDegree);
        delay(protectionDelayMinSec);
      }
    void up(){
//        Serial.println("go Up");
        if (initializeVerticalDegree >= 175) return;
        initializeVerticalDegree += stepMovement;
        verticalServo.write(initializeVerticalDegree);
        delay(protectionDelayMinSec);
      }
    void down(){
//        Serial.println("go Down");
        if (initializeVerticalDegree <= 5) return;
        initializeVerticalDegree -= stepMovement;
        verticalServo.write(initializeVerticalDegree);
        delay(protectionDelayMinSec);
      }
};

int topRightResistor;
int downRightResistor;
int topLeftResistor;
int downLeftResistor;

Motor motor;

//lightSensor max value 1023 in 5V when Lightness is heigh it's become smaller minimum is 0
void setup() {
  motor.attachVertical(11);
  motor.attachHorizontal(10);
  Serial.begin(9600);
}

void loop() {
  Serial.print("This is the A0 TR Rresistor reslut:");
  topRightResistor = analogRead(A0);
  Serial.println(topRightResistor);
  Serial.print("This is the A1 DR Rresistor reslut:");
  downRightResistor = analogRead(A1);
  Serial.println(downRightResistor);
  Serial.print("This is the A2 TL Rresistor reslut:");
  topLeftResistor = analogRead(A2);
  Serial.println(topLeftResistor);
  Serial.print("This is the A3 DL Rresistor reslut:");
  downLeftResistor = analogRead(A3);
  Serial.println(downLeftResistor); 
  motor.moving(topRightResistor, downRightResistor, topLeftResistor, downLeftResistor);
  Serial.println("=============================================");
}
