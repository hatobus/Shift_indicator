#define SRCLK (5)
#define RCLK (6)
#define SER (8)

int printnumber = 0;

volatile const int InterruptUp = 2;
volatile const int InterruptDown = 3;

volatile unsigned long time_prev = 0, time_now;
unsigned long time_chat = 20;
// 点灯パターン(1=点灯)

const uint8_t PATTERNS[] = {
  0b11111100, // 0
  0b01100000, // 1
  0b11011010, // 2
  0b11110010, // 3
  0b01100110, // 4
  0b10110110, // 5
  0b10111110, // 6
  0b11100100, // 7
  0b11111110, // 8
  0b11110110, // 9
};

void setup() {
  pinMode(SRCLK, OUTPUT);
  pinMode(RCLK,  OUTPUT);
  pinMode(SER,   OUTPUT);
  Serial.begin(9600);
  onInitialise();
}


void loop() {
  
//  int max_pattern = sizeof(PATTERNS)/sizeof(PATTERNS[0]);
  
  Serial.println(digitalRead(7));
  Serial.println(digitalRead(3));

  attachInterrupt(digitalPinToInterrupt(InterruptUp), countUp, LOW);
  attachInterrupt(digitalPinToInterrupt(InterruptDown), countDown, LOW); 
  
  //for (uint8_t i=0; i<max_pattern; i++) {
    // 8ビット分のデータをシフトレジスタへ送る
    Serial.println(printnumber);
    shiftOut(SER, SRCLK, LSBFIRST, PATTERNS[printnumber]); 

    // シフトレジスタの状態をストアレジスタへ反映させる
    digitalWrite(RCLK,  LOW);
    digitalWrite(RCLK,  HIGH);

    delay(100);
  //}
}

void countUp(void){
/*    time_now = mills();
    if(time_now - time_prev > time_chat){
        Serial.println("Up");*/
        printnumber += 1;
        if(printnumber > 9) printnumber = 0;
      //  time_prev  = time_now;
    //}

}

void countDown(void){
//    Serial.println("Down");
    printnumber -= 1;
    if(printnumber < 0) printnumber = 9;
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
