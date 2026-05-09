int pos=1;
int guardapos=0;
int SW=13;
int DT=9;
int CLK=8;
int ledRojo=11;
int ledAmarillo=12;
int ledAzul=10;
int estadoActual;
int estadoAntes;
bool cambiaPos=true;
unsigned long millisPrevios = 0;
const unsigned long intervalo = 1000;
const unsigned long miniIntervalo = 300;

int tiempoPomo=0;
int tiempoDesc=0;
int tiempoDescL=0;
int cantidadDePomo=1;
int modo=0;





void setup() {
  Serial.begin(9600);

  pinMode(ledRojo, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledAzul, OUTPUT);

  pinMode(SW, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(CLK, INPUT_PULLUP);


  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(A0, OUTPUT);

  pinMode(A1, OUTPUT);

  estadoAntes=digitalRead(CLK);

}

void beep(){
  digitalWrite(A1,HIGH);
  delay(50);
  digitalWrite(A1,LOW);
}




void displaySevenSeg(int pos){

digitalWrite(7, LOW);
digitalWrite(6, LOW);
digitalWrite(5, LOW);
digitalWrite(3, LOW);
digitalWrite(2, LOW);
digitalWrite(4, LOW);
digitalWrite(A0, LOW);

switch(pos){

case 0:
digitalWrite(6,HIGH);
digitalWrite(5,HIGH);
digitalWrite(4,HIGH);
digitalWrite(3,HIGH);
digitalWrite(2,HIGH);
digitalWrite(A0,HIGH);

break;

case 1:
digitalWrite(A0, HIGH);
digitalWrite(4, HIGH);
break;

case 2:
digitalWrite(4,HIGH);
digitalWrite(3,HIGH);
digitalWrite(7,HIGH);
digitalWrite(5,HIGH);
digitalWrite(2,HIGH);

break;

case 3:
digitalWrite(4,HIGH);
digitalWrite(5,HIGH);
digitalWrite(7,HIGH);
digitalWrite(A0,HIGH);
digitalWrite(2,HIGH);
break;

case 4:
digitalWrite(7, HIGH);
digitalWrite(4, HIGH);
digitalWrite(6, HIGH);
digitalWrite(A0,HIGH);
break;

case 5:
digitalWrite(6, HIGH);
digitalWrite(7, HIGH);
digitalWrite(5, HIGH);
digitalWrite(A0, HIGH);
digitalWrite(2, HIGH);
break;

case 6:
digitalWrite(7, HIGH);
digitalWrite(2, HIGH);
digitalWrite(A0,HIGH);
digitalWrite(6, HIGH);
digitalWrite(5, HIGH);
digitalWrite(3, HIGH);
break;

case 7:
digitalWrite(4,HIGH);
digitalWrite(5,HIGH);
digitalWrite(A0,HIGH);
break;

case 8:
digitalWrite(7, HIGH);
digitalWrite(2, HIGH);
digitalWrite(A0,HIGH);
digitalWrite(6, HIGH);
digitalWrite(5, HIGH);
digitalWrite(3, HIGH);
digitalWrite(4, HIGH);
break;

case 9:
digitalWrite(7, HIGH);
digitalWrite(2, HIGH);
digitalWrite(A0,HIGH);
digitalWrite(6, HIGH);
digitalWrite(5, HIGH);
digitalWrite(4, HIGH);
break;
}

cambiaPos=false;

}



void waitMode(){
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledAmarillo, LOW);
  bool start = false;
  bool nuevo=true;
  bool viejo=false;
  bool guardaviejo=false;
  switch(modo){
    case 0:
    loop();
    break;

    case 1:
    while(start==false){
      unsigned long currentMillis = millis();
      if (digitalRead(SW)== false and currentMillis - millisPrevios >= miniIntervalo){
        millisPrevios=currentMillis;
        start=true;
      }
      else{
        digitalWrite(11 ,nuevo);
        viejo=nuevo;
        nuevo=guardaviejo;
        guardaviejo=viejo;
      }
    }
    pomodoro();
    break;

    case 2:
    while (start==false){
      unsigned long currentMillis=millis();
      if (digitalRead(SW)==false and currentMillis-millisPrevios>=miniIntervalo){
        millisPrevios=currentMillis;
        start=true;
      }
      else{
        digitalWrite(ledAmarillo,nuevo);
        viejo=nuevo;
        nuevo=guardaviejo;
        guardaviejo=viejo;
      }
    }
    descCorto();
    break;

    case 3:
    while (start==false){
      unsigned long currentMillis=millis();
      if (digitalRead(SW)==false and currentMillis-millisPrevios>miniIntervalo){
        millisPrevios=currentMillis;
        start=true;
      }
      else{
        digitalWrite(ledAzul,nuevo);
        viejo=nuevo;
        nuevo=guardaviejo;
        guardaviejo=viejo;
      }
    }
    descLargo();
    break;




    
    }
  }


void descCorto(){
  bool nuevo=true;
  bool viejo=false;
  bool guardaviejo=false;

  while(tiempoDesc>0){
    unsigned long currentMillis = millis();

    if (currentMillis - millisPrevios >=intervalo){
      digitalWrite(ledAmarillo, nuevo);
      tiempoDesc--;
      millisPrevios=currentMillis;

      viejo=nuevo;
      nuevo=guardaviejo;
      guardaviejo=viejo;
    }
  }
  tiempoDesc=300*pos;
  modo=1;
  beep();
  waitMode(); 
}

void descLargo(){

    bool nuevo=true;
  bool viejo=false;
  bool guardaviejo=false;

  while(tiempoDescL>0){
    unsigned long currentMillis = millis();

    if (currentMillis - millisPrevios >=intervalo){
      digitalWrite(ledAzul, nuevo);
      tiempoDescL--;
      millisPrevios=currentMillis;

      viejo=nuevo;
      nuevo=guardaviejo;
      guardaviejo=viejo;
    }
  }
  modo=0;
  beep();
  beep();
  waitMode(); 

}

void pomodoro(){
  bool nuevo=true;
  bool viejo=false;
  bool guardaviejo=false;

  while(tiempoPomo>0){
    unsigned long currentMillis = millis();

    if (currentMillis - millisPrevios >=intervalo){
      digitalWrite(ledRojo, nuevo);
      tiempoPomo--;
      millisPrevios=currentMillis;

      viejo=nuevo;
      nuevo=guardaviejo;
      guardaviejo=viejo;
    }
  }
  tiempoPomo=1500*pos;
  cantidadDePomo++;
  modo=2;
  if(cantidadDePomo==4){
    modo=3;
  }
  beep();
  waitMode();  
}


void loop() {

unsigned long currentMillis = millis();

if (digitalRead(SW)== false and currentMillis - millisPrevios >= miniIntervalo){
  millisPrevios=currentMillis;
  tiempoPomo=1500*pos;
  tiempoDesc=300*pos;
  tiempoDescL=600*pos;
  beep();
  pomodoro();
}

if (digitalRead(CLK)== false and currentMillis - millisPrevios >= miniIntervalo){
  millisPrevios=currentMillis;
  pos++;
  cambiaPos=true;
}

if (digitalRead(DT)== false and currentMillis - millisPrevios >= miniIntervalo){
  millisPrevios=currentMillis;
  pos--;
  cambiaPos=true;
}

if (pos>9){
  pos = 1;
}
else{
  if (pos<1){
    pos = 9;
  }
}

if (cambiaPos==true){
  displaySevenSeg(pos);
}

}


/*
código para el codificador rotativo:

estadoActual = digitalRead(CLK);

 if (estadoActual != estadoAntes && estadoActual ==1){
  if(digitalRead(DT)!=estadoActual){
    pos++;
  }
  else{
    pos--;
  }
  cambiaPos=true;
 }
 estadoAntes = estadoActual;

if (pos>9){
  pos = 0;
}
else{
  if (pos<0){
    pos = 9;
  }
}

if (cambiaPos==true){
  displaySevenSeg(pos);
}


*/