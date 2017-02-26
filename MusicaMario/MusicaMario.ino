
/*
 * Desenvolvido por Guilherme de Cleva Farto (guilherme.farto@gmail.com)
 * Projeto educacional para placa "Solda é facil" (design e conceito original por Maurício "MauMaker" Jabur e PandoraLab)
 * 
 * Pressione o botão S2 (do LED verde) para iniciar a música-tema do Super Mario World
 * Pressione o botão S1 (do LED vermelho) para cancelar/encerrar a música-tema do Super Mario World
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

// #####

int portSpeak(BZ);

int melodia[] = {660, 660, 660, 510, 660, 770, 380, 510, 380, 320, 440, 480, 450, 430, 380, 660, 760, 860, 700, 760, 660, 520, 580, 480, 510, 380, 320, 440, 480, 450, 430, 380, 660, 760, 860, 700, 760, 660, 520, 580, 480, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 500, 760, 720, 680, 620, 650, 1020, 1020, 1020, 380, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 585, 550, 500, 380, 500, 500, 500, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 500, 760, 720, 680, 620, 650, 1020, 1020, 1020, 380, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 585, 550, 500, 380, 500, 500, 500, 500, 500, 500, 500, 580, 660, 500, 430, 380, 500, 500, 500, 500, 580, 660, 870, 760, 500, 500, 500, 500, 580, 660, 500, 430, 380, 660, 660, 660, 510, 660, 770, 380};

int duracao[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 80, 100, 100, 100, 80, 50, 100, 80, 50, 80, 80, 80, 80, 100, 100, 100, 100, 80, 100, 100, 100, 80, 50, 100, 80, 50, 80, 80, 80, 80, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 150, 200, 80, 80, 80, 100, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 150, 200, 80, 80, 80, 100, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 60, 80, 60, 80, 80, 80, 80, 80, 80, 60, 80, 60, 80, 80, 80, 80, 80, 60, 80, 60, 80, 80, 80, 80, 80, 80, 100, 100, 100, 100, 100, 100, 100};

int pausa[] = {150, 300, 300, 100, 300, 550, 575, 450, 400, 500, 300, 330, 150, 300, 200, 200, 150, 300, 150, 350, 300, 150, 150, 500, 450, 400, 500, 300, 330, 150, 300, 200, 200, 150, 300, 150, 350, 300, 150, 150, 500, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 220, 300, 100, 150, 150, 300, 300, 300, 150, 300, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 420, 450, 420, 360, 300, 300, 150, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 220, 300, 100, 150, 150, 300, 300, 300, 150, 300, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 420, 450, 420, 360, 300, 300, 150, 300, 150, 300, 350, 150, 350, 150, 300, 150, 600, 150, 300, 350, 150, 150, 550, 325, 600, 150, 300, 350, 150, 350, 150, 300, 150, 600, 150, 300, 300, 100, 300, 550, 575};

byte ledAnterior = -1;

boolean iniciarMusica = false;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < sizeof(BOTAO); i++) {
    Serial.println(i);
    pinMode(BOTAO[i], INPUT_PULLUP);
  }
}

void loop() {
  lerBotao();

  if (iniciarMusica) {
    executarMusicaMario();
  }
}

void lerBotao() {
  if (digitalRead(S2) == PRESS) {
    iniciarMusica = true;
  } else if (digitalRead(S1) == PRESS) {
    iniciarMusica = false;
  }
}

void executarMusicaMario() {
  for (int nota = 0; nota < sizeof(melodia) && iniciarMusica; nota++) {
    lerBotao();

    tone(portSpeak, melodia[nota], duracao[nota]);

    delay(pausa[nota]);

    if (ledAnterior != -1) {
      apagar(ledAnterior);

      ledAnterior = map(melodia[nota], 320, 1020, 0, 3);

      acender(ledAnterior);
    }
  }

  noTone(portSpeak);

  apagar(ledAnterior);
}

void acender(byte led) {
  analogWrite(LED[led], BRILHO[led]);
}

void apagar(byte led) {
  analogWrite(LED[led], 0);
}
