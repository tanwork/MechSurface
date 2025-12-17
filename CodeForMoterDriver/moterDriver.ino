
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;  // 蓝牙串口对象

int EN_PIN= 16;
int DIR_PIN = 4;
int STEP_PIN =2; 

int state = 0;
int buffer[10];
int direction = 0;
int index2 =0;
long distance=0;
void moveDistance(int direction, int distance){
    digitalWrite(DIR_PIN,direction);
    Serial.println(distance);
    long puluse_number = 360/0.9;
    puluse_number =puluse_number*distance;
    Serial.println(puluse_number);
    for (long i =0;i<long(puluse_number);i++){
      digitalWrite(STEP_PIN,HIGH);
      delayMicroseconds(10);
      digitalWrite(STEP_PIN,LOW);
      delay(1);
    }
}

void stillMove(int direction){
    digitalWrite(DIR_PIN,direction);
    delay(1);

    digitalWrite(STEP_PIN,HIGH);
    delayMicroseconds(10);
    digitalWrite(STEP_PIN,LOW);
    delay(1);
}


void setup() {
  // put your setup code here, to run once:
  SerialBT.begin("ESP32-SPP-Serial"); 
  Serial.begin(9600);
  pinMode(EN_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  digitalWrite(EN_PIN,HIGH);
  digitalWrite(DIR_PIN,HIGH);
  digitalWrite(STEP_PIN,LOW);
  delay(1);
}

void loop() {
  if(SerialBT.available()>0){
    char a= SerialBT.read();
    buffer[index2]=a;
    index2 = index2+1; 
    while(a!=' '){
      if(SerialBT.available()>0){
        a=SerialBT.read();
        buffer[index2]=a;   
        index2 = index2+1; 
      }
    }
    if(buffer[0]=='1'){
      if(index2 == 3){
        if(buffer[1]=='0'){
          direction=1;
        }
        else{
          direction=0;
        }
        state = 1;
        Serial.println(state);
      }
      else{
        if(buffer[1]=='0'){
          direction=1;
        }
        else{
          direction=0;
        }
        distance = 0;
        for (int i =2;i<index2-1;i++){
          distance = distance*10+ buffer[i]-'0';
        }
        state = 2;
        Serial.println(state);
      }
    }
    else{
        state = 0;
        Serial.println(state);
    }
    for(int i =0;i<index2;i++){
      Serial.print(buffer[i]);
    }
    Serial.println();
    index2 = 0;
  }

  if (state ==0){

  }
  else if (state ==1){
    stillMove(direction);
  }
  else if (state ==2){  
    moveDistance(direction, distance);
    state =0;
    Serial.println(state);
  }
  else{

  }
}



