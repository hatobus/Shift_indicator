#define gear1 0 // pin18
#define gear2 1 // pin19
#define gear3 2 // pin20
#define gear4 3 // pin21
#define gear5 10 // pin10
#define gear6 6 // pin4

#define SRCLK 5
#define RCLK 6
#define SER 8

#define NUM_OF_GEAR 6

#define LEDPIN 4

const int geatList[] = {gear1, gear2, gear3, gear4, gear5};

const uint8_t SHIFT_PATTERNS[] = {
    0b11111100, // 0 -> N
    0b01100000, // 1
    0b11011010, // 2
    0b11110010, // 3
    0b01100110, // 4
    0b10110110, // 5
    0b11101110  // R
};

int val;
int isin;

void setup(){
    pinMode(LEDPIN, OUTPUT);
    Ltika();
    
    Serial.begin(9600);

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
    val = analogRead(gear1);
    Serial.println(val);

    isin = val >> 9;

    printStatus(SHIFT_PATTERNS[isin]);
    Serial.println(isin);
    delay(50);
}

void Ltika(){
    // 確認用コード
    for(int i = 0; i < 5; i++){
        digitalWrite(LEDPIN, HIGH);
        delay(500);
        digitalWrite(LEDPIN, LOW);
        delay(100);
    }
}

void onInitialise(){
    
    // シフトインジケータの初期化処理
    // 小数点の部分を二回点滅させて、バーを二回回す

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
    
    // 光のバーを回すところ
    // F -> E -> D -> C -> B -> A
    // の順で点灯させていくと光のバーが回転しているようになる。
    // いずれはもうちょっとかっこよくしたい

    while(led < ledmax){ 
        led = led << 1;
        shiftOut(SER, SRCLK, LSBFIRST, led);
        digitalWrite(RCLK, LOW);
        digitalWrite(RCLK, HIGH);
        delay(100);
    }
}

void printStatus(uint8_t now_gear){
    
    // 現在のギアの位置に合わせてセグメントLEDに表示する
    shiftOut(SER, SRCLK, LSBFIRST, now_gear);
    digitalWrite(RCLK, LOW);
    digitalWrite(RCLK, HIGH);
    delay(50);

}
