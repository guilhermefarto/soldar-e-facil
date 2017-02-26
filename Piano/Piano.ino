
/*
 * Desenvolvido por Guilherme de Cleva Farto (guilherme.farto@gmail.com)
 * Projeto educacional para placa "Solda é facil" (design e conceito original por Maurício "MauMaker" Jabur e PandoraLab)
 * 
 * Pressione os botões de S1 a S4 para executar simular um piano
 * - As notas executadas podem ser modificadas/configuradas na variável 'notas[]'
 * - A duração de execução da(s) nota(s) pressionada pode ser modificada/configurada na variável 'duracao[]'
 */

const byte BZ   = 2;

const byte S1   = 8;
const byte LED1 = 10;

const byte S2   = 7;
const byte LED2 = 9;

const byte S3   = 4;
const byte LED3 = 6;

const byte S4   = 3;
const byte LED4 = 5;

const byte LED[]    = {LED1, LED2, LED3, LED4};
const byte BRILHO[] = {32, 128, 64, 128};

const byte BOTAO[] = {S1, S2, S3, S4};
const int PRESS = LOW;

int portSpeak(BZ);

int notas[] = {1915, 1700, 1519, 1432};

int duracao[] = {100, 100, 100, 100};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < sizeof(BOTAO); i++) {
    pinMode(BOTAO[i], INPUT_PULLUP);
  }
}

void loop() {
  int botaoPressionado = lerBotao();

  if (botaoPressionado != -1) {
    controlarLed(botaoPressionado, true);
    
    tone(portSpeak, notas[botaoPressionado], duracao[botaoPressionado]);
  } else {
    noTone(portSpeak);

    controlarLed(-1, false);
  }
}

int lerBotao() {
  delay(200);

  for (int i = 0; i < sizeof(BOTAO); i++) {
    if (digitalRead(BOTAO[i]) == PRESS) {
      return i;
    }
  }

  return -1;
}

void controlarLed(int led, boolean acender) {
  if (led != -1) {
    analogWrite(LED[led], acender ? BRILHO[led] : 0);
  } else {
    for (int i = 0; i < sizeof(LED); i++) {
      analogWrite(LED[i], 0);
    }
  }
}
