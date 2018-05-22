#define refrecter 0

int val = 0;
int onebit;

void setup(){
    Serial.begin(9600);
    Serial.println("Hello!");
}

void loop(){
    val = analogRead(refrecter);
    Serial.println(val);
    onebit = val >> 8;
    Serial.print("1bit value :");
    Serial.println(onebit);
    delay(100);
}
