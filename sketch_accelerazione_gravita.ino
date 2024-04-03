#define pinAttuatore 2

// nero
#define pinLaser1 12
#define pinRicevitore1 3

// viola 
#define pinLaser2 4
#define pinRicevitore2 10

// arancione
#define pinLaser3 8
#define pinRicevitore3 5

// giallo
#define pinLaser4 13
#define pinRicevitore4 6

#define num_laser 4
int pinLaser [num_laser] = {pinLaser1, pinLaser2, pinLaser3, pinLaser4} ;
int pinRicevitore [num_laser] = {pinRicevitore1, pinRicevitore2, pinRicevitore3, pinRicevitore4};

void setup() {
  Serial.begin (9600) ;

  pinMode (pinAttuatore, OUTPUT) ;

  for (int i = 0 ; i < num_laser ; i++) {
    pinMode (pinLaser[i], OUTPUT) ;
    pinMode (pinRicevitore[i], INPUT) ;
    digitalWrite (pinLaser[i], HIGH) ; // accende il laser
  }

  Serial.println ("t1\t t2\t t3\t t4 ") ;
}

void loop() {

  digitalWrite (pinAttuatore, HIGH) ; // accende l'attuatore
  
  Serial.flush();
  Serial.read();
  Serial.read();

  while (Serial.available() == 0) 
    Serial.read () ;

  digitalWrite (pinAttuatore, LOW);  
  //Serial.println("===>>>");

  long int t_A = micros () ; // t_avvio
  
  for (int i = 0 ; i < num_laser ; i++) {
    while (true) {
      if (digitalRead (pinRicevitore[i]) == 1) {
        Serial.print (micros () - t_A) ; // tempo
        Serial.print ("\t") ;
        break;
      }
    }
  }
  
  Serial.println (" ") ;
  delay(1500);
}
