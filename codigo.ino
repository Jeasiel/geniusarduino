#include <stdlib.h>

const int botVerde = 10;
const int botAm = 11;
const int botVerm = 12;

const int ledVerde = 5;
const int ledAm = 6;
const int ledVerm = 7;

const int sz = 50;
int sequencia[sz];

int ind = 0;

void setup() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAm, OUTPUT);
  pinMode(ledVerm, OUTPUT);
  pinMode(botVerde, INPUT_PULLUP);
  pinMode(botAm, INPUT_PULLUP);
  pinMode(botVerm, INPUT_PULLUP);

  srand(analogRead(A0)); //rand() % (2 + 1) para 0 - 2
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  gerarNumero();
  mostrarSequencia();
  compararSequencia();
}

void gerarNumero(){
  sequencia[ind] = (rand() % (2 + 1)) + 1;
  ind++;
}

void mostrarSequencia(){
  for(int i = 0; i < ind; i++){
    switch(sequencia[i]){
      case 1:
        piscarLed(ledVerde, 1000);
      break;
      case 2:
        piscarLed(ledAm, 1000);
      break;
      case 3:
        piscarLed(ledVerm, 1000);
      break;
    }
  }
}

void compararSequencia(){
  for(int i = 0; i < ind; i++){
    if(lerBotao(sequencia[i]) == 0){
      //acertou
    } else {
      //errou - reseta
      ind = 0;
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledAm, HIGH);
      digitalWrite(ledVerm, HIGH);
      delay(2000);
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAm, LOW);
      digitalWrite(ledVerm, LOW);
    }
  }
  delay(1000);
}

int lerBotao(int comparador){
  int press = 0;
  while(press == 0){
    if(digitalRead(botVerde) == LOW){
      press = 1;
    } else if(digitalRead(botAm) == LOW) {
      press = 2;
    } else if(digitalRead(botVerm) == LOW) {
      press = 3;
    }
  }
  if(press == comparador){
    switch(press){
      case 1:
        piscarLed(ledVerde, 1000);
      break;
      case 2:
        piscarLed(ledAm, 1000);
      break;
      case 3:
        piscarLed(ledVerm, 1000);
      break;
    }
    return 0;
  } else {
    return 1;
  }
}

void piscarLed(byte led, int tempo){
  digitalWrite(led, HIGH);
  delay(tempo);
  digitalWrite(led, LOW);
  delay(100);
}
