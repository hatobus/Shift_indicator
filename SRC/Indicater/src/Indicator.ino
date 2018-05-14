#define gear1 9
#define gear2 10
#define gear3 18
#define gear4 19
#define gear5 20
#define gear6 21 // R

#define SRCLK 6
#define RCLK 7
#define SER 8

#define NUM_SENSORS 6
#define TIMEOUT 100
#define EMITTER 5

#define LEDPIN 4

QTRSensorsRC qtrrc((unsigned char[]) {3, 4, 5, 6, 7, 8, 9, 10},  NUM_SENSORS, TIMEOUT, EMITTER); 
unsigned int sensorValues[NUM_SENSORS];

const uint8_t SHIFT_PATTERNS[] = {
    0b11111100, // 0 -> N
    0b01100000, // 1
    0b11011010, // 2
    0b11110010, // 3
    0b01100110, // 4
    0b10110110, // 5
    0b11101110  // R
}

void setup(){
    delay(100);
    
    pinMode(LEDPIN, OUTPUT);
    Ltika();
    
    Serial.begin(9600);

    for(int i = 0; i < 400; i++) 
        qtrrc.callibrate();


    pinMode(SRCLK, OUTPUT);
    pinMode(RCLK, OUTPUT);
    pinMode(SER, OUTPUT);
}

void loop(){
}

void Ltika(){
    for(int i = 0; i < 5; i++){
        digitalWrite(LEDPIN, HIGH);
        delay(1000);
        digitalWrite(LEDPIN, LOW);
        delay(100);}
    }
}
