#include<QTRSensors.h>

#define right 10
#define left 16
#define emitter 14

QTRSensorsRC qtrrc((unsigned char[]) {right, left}, 2, 2000, emitter);
unsigned int sensorVal[2];

void setup(){
    Serial.println(9600);
    for(int i = 0; i<400; i++){
        qtrrc.calibrate();
    }

    Serial.println("Start");

    for (int i = 0; i < 2; i++){
        Serial.print(qtrrc.calibratedMinimumOn[i]);
        Serial.print(' ');
    }

  Serial.println();
  
  for (int i = 0; i < 2; i++){
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }

  Serial.println();
  Serial.println();
  delay(1000);

}

void loop(){
    Serial.println("OK");
    unsigned int position = qtrrc.readLine(sensorVal);

    for(unsigned char i = 0; i < 2; i++){
        Serial.println(sensorVal[i]);
    }

    Serial.println(position);

    delay(200);
    
}
