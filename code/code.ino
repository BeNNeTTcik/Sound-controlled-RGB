#define Rpin 11
#define Gpin 10
#define Bpin 9
#define czujnik_sygnal A0


float wartosc=0, sygnal_zprzedzialowany = 0, przedzial[] = {21, 26};
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
  
  Serial.println(sygnal_zprzedzialowany);
  
  if(sygnal_zprzedzialowany>przedzial[1]){
      digitalWrite(Rpin,HIGH);
      digitalWrite(Bpin,LOW);
      digitalWrite(Gpin,LOW);
      delay(1);
    } else if(sygnal_zprzedzialowany>przedzial[0] && sygnal_zprzedzialowany<przedzial[1]){
      digitalWrite(Gpin,HIGH);
      digitalWrite(Bpin,LOW);
      digitalWrite(Rpin,LOW);
      delay(1);
    } else if(sygnal_zprzedzialowany<przedzial[0]){
      digitalWrite(Bpin,HIGH);
      digitalWrite(Rpin,LOW);
      digitalWrite(Gpin,LOW);
      delay(1);
    }
}

void FiltrlLP(float sygnal) {
  sygnal_zprzedzialowany = (0.945*sygnal_zprzedzialowany) + (0.0549*sygnal);
}
