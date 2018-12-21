#include <string.h>

#define analogPin 3
#define CONTROLADOR 2
#define LED 3
#define TAM 21
#define PONTO 200
#define TENSAOMINIMA 200
#define PAUSALETRA 150
#define PAUSAPALAVRA 700
#define PAUSAMAXIMA 1000

int tensao, pausa = 0, toque = 0;
char buffer[TAM];

char *tradutor(char buf[]) {
  if(!strcmp(buf, ".-"))
    return "a";
  else if(!strcmp(buf, "-..."))
    return "b";
  else if(!strcmp(buf, "-.-."))
    return "c";
  else if(!strcmp(buf, "-.."))
    return "d";    
  else if(!strcmp(buf, "."))
    return "e";
  else if(!strcmp(buf, "..-."))
    return "f";
  else if(!strcmp(buf, "--."))
    return "g";
  else if(!strcmp(buf, "...."))
    return "h";
  else if(!strcmp(buf, ".."))
    return "i";
  else if(!strcmp(buf, ".---"))
    return "j";
  else if(!strcmp(buf, "-.-"))
    return "k";
  else if(!strcmp(buf, ".-.."))
    return "l";
  else if(!strcmp(buf, "--"))
    return "m";
  else if(!strcmp(buf, "-."))
    return "n";
  else if(!strcmp(buf, "---"))
    return "o";
  else if(!strcmp(buf, ".--."))
    return "p";            
  else if(!strcmp(buf, "--.-"))
    return "q";
  else if(!strcmp(buf, ".-."))
    return "r";
  else if(!strcmp(buf, "..."))
    return "s";
  else if(!strcmp(buf, "-"))
    return "t";
  else if(!strcmp(buf, "..-"))
    return "u";
  else if(!strcmp(buf, "...-"))
    return "v";
  else if(!strcmp(buf, ".--"))
    return "w";
  else if(!strcmp(buf, "-..-"))
    return "x";
  else if(!strcmp(buf, "-.--"))
    return "y";
  else if(!strcmp(buf, "--.."))
    return "z";                                        

  return "";
}

void append(char buf[], int tempo) {
  int tam = strlen(buf);
  
  if(tam < TAM - 1) {
    if(tempo < PONTO)
      strcat(buf, ".");
    else
      strcat(buf, "-");
  }
}

void imprime(char buf[]) {
  char letra[100];
  int tam = strlen(letra);
  strcpy(letra, tradutor(buf));

  for(int i = 0; i < tam; i++)
    Serial.print(letra);
}

void esvazia(char buf[]) {
  buf[0] = 0;
}

void setup() {
  Serial.begin(9600);
  pinMode(CONTROLADOR, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(CONTROLADOR, HIGH);
}

void loop() {
  tensao = analogRead(analogPin);
  digitalWrite(LED, LOW);

  //Enquanto estiver em um toque
  while (tensao >= TENSAOMINIMA) {
    //Deixa o led acesso e conta o tempo do toque
    digitalWrite(LED, HIGH);
    
    delay(1);
    tensao = analogRead(analogPin);
    
    toque ++;
  }

  //Quando terminar um toque
  if(toque > 0)  {
    //verifica se é começo de nova palavra ou nova letra
    if(pausa >= PAUSALETRA) { //se for uma nova letra
      if(pausa >= PAUSAPALAVRA) //se for nova palavra
        Serial.print(" ");
      imprime(buffer);
      esvazia(buffer);
    } 

    append(buffer, toque);
    
    pausa = 0;
    toque = 0;
  }

  //se acabou de digitar
  if (pausa > PAUSAPALAVRA) {
    imprime(buffer);
    Serial.print(" ");
    esvazia(buffer);
    pausa = -1; //a próxima entrada será o começo de uma frase
  }
  else if(pausa != -1) //se não for o começo de uma frase
    pausa ++;
    
  delay(1);
}
