int a=0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);         // initializing Serial monitor
pinMode(4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
a=millis()/1000;
if (millis()/1000 % 2) {
  digitalWrite(4,HIGH);
}
else {
  digitalWrite(4,LOW);
}
Serial.println(a);   // writing the read value on Serial monitor

}
