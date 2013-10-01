/*
Dieses Programm ist der einfachste Weg den Roboter zum Leben zu erwecken und nebenbei zu erklaeren, wie das Ganze funktioniert.
Falls du eine professionelle Version des Codes haben moechtest, benutze die "ProfiVersionVonFlo". 
Die Version von Flo ist auch die Version mit der der Roboter im Video lief.


*/

//Sobald man irgendwas mit Servo machen möchte, sollte man diese Servo-Bibliothek laden
#include <Servo.h> 
 
Servo servo;    //Hier wird dem Servo eine Bezeichnung gegeben

 
int servopos = 0;     //Hinter dem Wert servopos versteckt sich die Position des Servos

//in distanz wird der gemessene Wert gespeichert, den der Shapr Sensor misst.
//Hier muss man etwas umdenken, da je niedriger die Distanz, desto hoeher wird der Wert
int distanz = 0;      

const int sharp = A2;                  //Der Shapr Sensor wird an Analog-Pin 2 angeschlossen

//Mit Pin 12 & 13 laesst man den rechten und linken Motor vorwaerts (HIGH) oder rueckwaerts (LOW) laufen
const int motorlinks = 13;             
const int motorrechts = 12;            

//An Pin 11 & 3 kann man die Geschwindigkeit der Motoren einstellen
const int geschwindigkeitlinks = 11;   
const int geschwindigkeitrechts = 3;

//Mit Pin 8 & 9 kann man die Motoren anhalten.
const int bremselinks = 8;
const int bremserechts = 9;


//Damit man nicht jedes mal Haufen Pins ansteuern muss, packen wir das Ganze in Sub-Routinen. 
//So muss man spaeter im Programm nur Sub-Routinen aufrufen und nicht jeden einzelnen Pin nochmal ansteuern.


//Die namen der Sub-Routinen sprechen fuer sich ;-)
void vorwaerts()
{  
    analogWrite(geschwindigkeitlinks, 120);    //Geschwindigkeit fuer linken Motor (max. 255)
    analogWrite(geschwindigkeitrechts, 120);   //Geschwindigkeit fuer rechten Motor (max. 255) 
    digitalWrite(motorlinks, HIGH);            //Linker Motor HIGH = Rad dreht vorwaerts (LOW fuer rueckwaerts)
    digitalWrite(motorrechts, HIGH);           //Rechter Motor HIGH = Rad dreht vorwaerts (LOW fuer rueckwaerts)
    
    //Bremse fuer die beiden Motor loesen. (Mit HIGH statt LOW wird gebremst)
    digitalWrite(bremselinks, LOW);
    digitalWrite(bremserechts, LOW);
}

void drehenlinks()
{
    analogWrite(geschwindigkeitlinks, 120);    //Geschwindigkeit fuer linken Motor (max. 255)
    analogWrite(geschwindigkeitrechts, 120);   //Geschwindigkeit fuer rechten Motor (max. 255)
    digitalWrite(motorlinks, LOW);             //Linker Motor LOW = Rad dreht rueckwaerts (HIGH fuer vorwaerts)
    digitalWrite(motorrechts, HIGH);           //Rechter Motor HIGH = Rad dreht vorwaerts (LOW fuer rueckwaerts)
    
    //Bremse fuer die beiden Motor loesen.
    digitalWrite(bremselinks, LOW);
    digitalWrite(bremserechts, LOW);
}
 
void drehenrechts()
{
    analogWrite(geschwindigkeitlinks, 120);  //Geschwindigkeit fuer linken Motor (max. 255)
    analogWrite(geschwindigkeitrechts, 120); //Geschwindigkeit fuer rechten Motor (max. 255)
    digitalWrite(motorlinks, HIGH);            //Linker Motor LOW = Rad dreht rueckwaerts (HIGH fuer vorwaerts)
    digitalWrite(motorrechts, LOW);            //Rechter Motor HIGH = Rad dreht vorwaerts (LOW fuer rueckwaerts)
    
    //Bremse fuer die beiden Motor loesen.    
    digitalWrite(bremselinks, LOW);
    digitalWrite(bremserechts, LOW);
} 
 
//Zwischendurch muss der Roboter auch mal bremsen. Deswegen wird in oberen Sub-Routinen immer die Bremse geloest.
void bremse()
{
 digitalWrite(bremselinks, HIGH);
 digitalWrite(bremserechts, HIGH);
 delay(10);
  
}


//In void setup werden die Pins definiert was sie sind - Eingaenge oder Ausgaenge
void setup() 
{ 
  servo.attach(5);    //Hier wird dem Arduino mitgeteilt, an welchem Pin der Servo angeschlossen ist. Hier Pin 5        

//Die Pins fuer die Motoransteuerung sind alle als Ausgaenge (OUTPUT) zu konfigurieren.
  pinMode(motorlinks, OUTPUT);
  pinMode(motorrechts, OUTPUT);
  pinMode(geschwindigkeitlinks, OUTPUT);
  pinMode(geschwindigkeitrechts, OUTPUT);
  pinMode(bremselinks, OUTPUT);
  pinMode(bremserechts, OUTPUT);

  servo.write(90);    //Servo wird in 90Grad Stellung gebracht, der Sensor guckt nach vorne.
  
  
  delay(5000); //Niemand will dass der Roboter direkt in den Haenden losfaehrt :-) 5 Sekunden Pause
} 
 

// Hier - in void loop - beginnt das eigentliche Programm, das sich immer wieder wiederholt. 
void loop() 
{ 


//Die for-Schleife ist dafür da, damit der Servo hin und her dreht. Der Sharp Sensor dreht sich zwischen 50 und 130 Grad hin und her.
//Der Servo faengt bei 50 Grad an und dreht sich so lange in eine Richtung, bis der Winkel 130 Grad erreicht hat.
//Der Wert wird in der Variablen servopos abgelegt.

//for-Schleife 1 - Servo dreht nach links
for(servopos = 50; servopos < 130; servopos += 1)

{
  
  servo.write(servopos);    //Servo wird in die Position gebracht, die gerade in servopos steht
  
  distanz = analogRead(sharp);  //Der Sharp Sensor wird ausgelesen und der Wert wird in der Variablen distanz abgespeichert

//Wenn ein Hindernis auftaucht und der Servo guckt gerade mehr nach rechts, dreht der Roboter nach links.
      if (distanz >= 400 && servopos < 90)
     {
       bremse();
       drehenlinks();
       delay(100);    //Zeit, wie lange sich der Roboter drehen soll
     }

   
//Wenn ein Hindernis auftaucht und der Servo guckt gerade mehr nach links, dreht der Roboter nach rechts.     
     else if (distanz >= 400 && servopos > 90)
     {
       bremse();
       drehenrechts();
       delay(100);    //Zeit, wie lange sich der Roboter drehen soll
     }     

//Wenn kein Hindernis in Sichtweite ist, dann freie Fahrt :)     
     else
     {
       vorwaerts();
     }

}    
    delay(300);
    

//Hier wiederholt sich das Ganze nochmal, nur der Servo dreht jetzt in andere Richtung.    
//for-Schleife 2 - Servo dreht nach rechts    
  for(servopos = 130; servopos>=51; servopos-=1)
 {
   servo.write(servopos);
    distanz = analogRead(sharp);
    
      if (distanz >= 400 && servopos < 90)
     {
       bremse();
       drehenlinks();
       delay(100);    //Zeit, wie lange sich der Roboter drehen soll
     }


     
      else if (distanz >= 400 && servopos > 90)
     {
       bremse();
       drehenrechts();
       delay(100);    //Zeit, wie lange sich der Roboter drehen soll
     }     
     
     else
     {
     
       vorwaerts();
       
     }
        
 }  
    
  delay(300);
} 
