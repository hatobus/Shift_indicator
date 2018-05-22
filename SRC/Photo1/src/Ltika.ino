#define N 5

void setup(){
    int LEDlist[N];
    for(int i=2; i <= N; i++) pinMode(i, OUTPUT);
    Serial.begin(9600);
}

void loop(){
    
    int i;

    Serial.println("L");
    
    for(i=2; i <= N; i++){
        digitalWrite(i, HIGH);
        delay(50);
    }

    delay(1000);

    for(int j=0; j < 20; j++){
        digitalWrite(N, LOW);
        delay(100);
        digitalWrite(N, HIGH);
        delay(100);
    }
    
    //delay(1000);
    Serial.println("tika");
    
    for(i=N; i >= 2; i--){
        digitalWrite(i, LOW);
        delay(50);
    }

    delay(100);

    }
