//#include <IRremoteInt.h>
//#include <IRremoteTools.h>
//#include <IRremote.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

byte button_total = 7;
int button_id[] = {2,3,4,5,6,7,8};                  // toggle buttons
int point_id[] = {0,1,3,4,5,7,8};                   // points connected to Adafruit 16-channel PWM servo driver
int p_direction[] = {150,150,150,150,150,150,150};  // actual position
int p_straight[] = {150,150,150,150,150,150,150};   // value to move the point in straight position
int p_diverging[] = {270,270,270,270,270,270,270};  // value to move the point in diverging position
int l_straight[] = {7,8,9,10,11,12,13};             // leds, straight position
int l_diverging[] = {14,15,16,17,18,19,20};         // leds, diverging postition

int reading;            // current reading from the input pin
int previous = HIGH;    // previous reading from the input pin

//long time = 0;
byte debounce = 200;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup()
{
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  for(byte i = 0; i < button_total; i++)
  {
    pinMode(l_straight[i], OUTPUT);
    pinMode(button_id[i], INPUT);
    digitalWrite(button_id[i],HIGH);
    pwm.setPWM(point_id[i], 0, p_straight[i]);
    delay(300);
  }
}

void loop()
{
   for(byte index = 0; index < button_total; index++)
  {
    reading = digitalRead(button_id[index]);  // legge il valore di input
    if (reading == LOW && previous == HIGH) //  && millis() - time > debounce)      // check if a button was pressed
    {
          toggle_point(index);
    }
    previous = reading;
  }

}
void toggle_point(byte which)
{
    if (p_direction[which] == p_straight[which])
      {
      p_direction[which] = p_diverging[which];
      for (uint16_t pulselen = p_straight[which]; pulselen < p_diverging[which]; pulselen++) {
        pwm.setPWM(point_id[which], 0, pulselen);
        delay(5);
                  Serial.print("pulselen: ");
                  Serial.println(pulselen);
                  if (pulselen > (p_diverging[which]-(p_diverging[which]*.2)))
                  {
                    digitalWrite(13, HIGH);
                    }    
                  if (pulselen > (p_straight[which]+(p_straight[which]*.2)))
                  {
                    digitalWrite(12, LOW);
                  }
      }
      pwm.setPWM(point_id[which], 0, 0);              // turn off servo
      }
    else
      {
      p_direction[which] = p_straight[which];
      for (uint16_t pulselen = p_diverging[which]; pulselen > p_straight[which]; pulselen--) {
        pwm.setPWM(point_id[which], 0, pulselen);
        delay(5);
                  if (pulselen < (p_diverging[which]-(p_diverging[which]*.2)))
                  {
                    digitalWrite(13, LOW);
                  }
                  if (pulselen < (p_straight[which]+(p_straight[which]*.2)))
                  {
                    digitalWrite(12, HIGH);
                  }    
                  Serial.print("pulselen: ");
                  Serial.println(pulselen);
      }
      pwm.setPWM(point_id[which], 0, 0);              // turn off servo
      }
}

