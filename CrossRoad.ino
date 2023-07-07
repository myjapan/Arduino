/*
   Simula il lampeggio di un passaggio a livello incustodito
   CrossRoad V 1.0 del 24/05/2014 
   (c)2014 Paolo Luongo http://aspettandoilbus.blogspot.it
*/

const int Uscita1=10; //Uscita analogica n.ro 1
const int Uscita2=11; //Uscita analogica n.ro 2
const int Ritardo=3; //Aumenta per variazione più lenta 

void setup(){
  pinMode(13,OUTPUT);         //faccio lampeggiare anche led 13
  pinMode(Uscita1,OUTPUT);
  pinMode(Uscita2,OUTPUT);
}

void Comanda( byte Vx){
     analogWrite(Uscita1,Vx);         
     analogWrite(Uscita2,255-Vx); 
     delay(Ritardo);
}

void loop(){
byte i=0;   //solo valori da 0 a 255

   digitalWrite(13,LOW);             //spegni led 13
   for ( i=0; i<255; i++) Comanda(i);
   digitalWrite(13,HIGH);            //accendi led 13
   for ( i=255; i>1; i--) Comanda(i);
}
