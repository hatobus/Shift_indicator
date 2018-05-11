#define N 5

void setup(){
    int LEDlist[N];
    for(int i=2; i <= N; i++) pinMode(i, OUTPUT);
    Serial.begin(9600);
}

void loop(){
    
    Serial.println("L");
    
    for(int i=2; i <= N; i++){
        digitalWrite(i, HIGH);
        delay(100);
    }
    
    delay(1000);
    Serial.println("tika");
    
    for(int i=N; i >= 2; i--){
        digitalWrite(i, LOW);
        delay(100);
    }

    delay(1000);
}
