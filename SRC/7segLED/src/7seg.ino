#define SRCLK (5)
#define RCLK (6)
#define SER (8)

int printnumber = 0;

volatile const int InterruptUp = 4;
volatile const int InterruptDown = 0;

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
}


void loop() {
  Serial.println("Start");  
//  int max_pattern = sizeof(PATTERNS)/sizeof(PATTERNS[0]);
  
  Serial.println(digitalRead(7));
  Serial.println(digitalRead(3));

  attachInterrupt(digitalPinToInterrupt(InterruptUp), countUp(), HIGH);
  attachInterrupt(digitalPinToInterrupt(InterruptDown), countDown(), HIGH); 
  
  //for (uint8_t i=0; i<max_pattern; i++) {
    // 8ビット分のデータをシフトレジスタへ送る
    shiftOut(SER, SRCLK, LSBFIRST, PATTERNS[printnumber]); 

    // シフトレジスタの状態をストアレジスタへ反映させる
    digitalWrite(RCLK,  LOW);
    digitalWrite(RCLK,  HIGH);

    delay(100);
  //}
}

void countUp(){
    Serial.print("Up");
    printnumber += 1;
    if(printnumber > 9) printnumber = 0;
}

void countDown(){
    printnumber -= 1;
    if(printnumber < 0) printnumber = 9;
}
