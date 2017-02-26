
/*
 * Desenvolvido por Guilherme de Cleva Farto (guilherme.farto@gmail.com)
 * Projeto educacional para placa "Solda é facil" (design e conceito original por Maurício "MauMaker" Jabur e PandoraLab)
 * 
 * Pressione os botões de S1 a S4 para ativar/desabilitar a seleção da senha
 * A senha correta é definida pela variável SENHA_CORRETA[] (por exemplo, 'true, false, true, true')
 * Quando a senha correta for selecionada, a função 'animar' será executada
 * - Você pode modificar/configurar a senha padrão alterando os valores de true e false da variável SENHA_CORRETA[]
 * - Você pode acrescentar mais funções para serem executadas assim que a senha correta for selecionada (invocar funções após 'animar' dentro da função 'iniciarPrograma')
 */

void functionS1();
void functionS2();
void functionS3();
void functionS4();

typedef void (* Caller)();

Caller functions[] = {&functionS1, &functionS2, &functionS3, &functionS4};

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

boolean SENHA_CORRETA[] = {true, false, true, true};
boolean SENHA_SELECIONADA[] = {false, false, false, false};

const byte BOTAO[] = {S1, S2, S3, S4};
const int PRESS = LOW;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < sizeof(BOTAO); i++) {
    pinMode(BOTAO[i], INPUT_PULLUP);
  }

  iniciarPrograma();
}

void loop() {
}

void iniciarPrograma() {
  while (!validarSenha()) {
    int botaoPressionado = lerBotao();

    if (botaoPressionado != -1) {
      functions[botaoPressionado]();
    }
  }

  Serial.println("A senha selecionada está correta...");

  animar();
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

void controlarLed(int led) {
  SENHA_SELECIONADA[led] = !SENHA_SELECIONADA[led];

  analogWrite(LED[led], SENHA_SELECIONADA[led] ? BRILHO[led] : 0);
}

boolean validarSenha() {
  for (int i = 0; i < sizeof(SENHA_CORRETA); i++) {
    if (SENHA_CORRETA[i] != SENHA_SELECIONADA[i]) {
      return false;
    }
  }

  return true;
}

void animar() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < sizeof(LED); j++) {
      analogWrite(LED[j], BRILHO[j]);
      delay(50);
    }

    for (int j = 0; j < sizeof(LED); j++) {
      analogWrite(LED[j], 0);
      delay(50);
    }
  }
}

void functionS1() {
  controlarLed(0);
}

void functionS2() {
  controlarLed(1);
}

void functionS3() {
  controlarLed(2);
}

void functionS4() {
  controlarLed(3);
}

