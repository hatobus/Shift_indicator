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

QTRSensorsRC qtrrc((unsigned char[]){9, 10, 18, 19, 20, 21}, NUM_SENSORS, TIMEOUT, EMITTER); 
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

    onInitialise();

    shiftOut(SER, SRCLK, LSBFIRST, 0b00000000);
    digitalWrite(RCLK, LOW);
    digitalWrite(RCLK, HIGH);
    delay(200);
}

void loop(){
}

void Ltika(){
    for(int i = 0; i < 5; i++){
        digitalWrite(LEDPIN, HIGH);
        delay(500);
        digitalWrite(LEDPIN, LOW);
        delay(100);}
    }
}

void onInitialise(){
    
    uint8_t led = 0b00000010;
    uint8_t ledmax = 0b10000000;
    int i = 0;

    for(int i = 0; i < 2; i++){
        shiftOut(SER, SRCLK, LSBFIRST, 0b00000001);
        digitalWrite(RCLK, LOW);
        digitalWrite(RCLK, HIGH);
        delay(250);
        shiftOut(SER, SRCLK, LSBFIRST, 0b00000000);
        digitalWrite(RCLK, LOW);
        digitalWrite(RCLK, HIGH);
        delay(250);
    }

    while(i < 2){
        rollLED(led, ledmax);
        i++;
    }

}

void rollLED(uint8_t led, uint8_t ledmax){
    while(led < ledmax){ 
        led = led << 1;
        shiftOut(SER, SRCLK, LSBFIRST, led);
        digitalWrite(RCLK, LOW);
        digitalWrite(RCLK, HIGH);
        delay(100);
    }
}
