#define Rpin 11
#define Gpin 10
#define Bpin 9
#define czujnik_sygnal A0


float wartosc=0, sygnal_zfiltrowany = 0, filtr[] = {21, 26};
void setup () { 
  Serial.begin (9600);
  pinMode(czujnik_sygnal, INPUT);
  pinMode(Gpin, OUTPUT);
  pinMode(Rpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
}

void loop () {
  wartosc=analogRead(czujnik_sygnal)*(5.0/128.0);
  
  FiltrLP(wartosc);
  
  Serial.println(sygnal_zfiltrowany);
  
  if(sygnal_zfiltrowany>filtr[1]){
      digitalWrite(Rpin,HIGH);
      digitalWrite(Bpin,LOW);
      digitalWrite(Gpin,LOW);
      delay(1);
    } else if(sygnal_zfiltrowany>filtr[0] && sygnal_zfiltrowany<filtr[1]){
      digitalWrite(Gpin,HIGH);
      digitalWrite(Bpin,LOW);
      digitalWrite(Rpin,LOW);
      delay(1);
    } else if(sygnal_zfiltrowany<filtr[0]){
      digitalWrite(Bpin,HIGH);
      digitalWrite(Rpin,LOW);
      digitalWrite(Gpin,LOW);
      delay(1);
    }
}

void FiltrLP(float sygnal) {
  sygnal_zfiltrowany = (0.945*sygnal_zfiltrowany) + (0.0549*sygnal);
}
