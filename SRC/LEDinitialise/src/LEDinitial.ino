#define SRCLK 5
#define RCLK 6
#define SER 8

void setup(){
    pinMode(SRCLK, OUTPUT);
    pinMode(RCLK, OUTPUT);
    pinMode(SER, OUTPUT);
    Serial.begin(9600);
}

void loop(){
    
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
        Serial.println(i);
        rollLED(led, ledmax);
/*        while(led < ledmax){ 
            led = led << 1;
            shiftOut(SER, SRCLK, LSBFIRST, led);
            digitalWrite(RCLK, LOW);
            digitalWrite(RCLK, HIGH);
            delay(100);
        }*/
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
