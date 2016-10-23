#include <ESP8266WebServer.h>
#include <EEPROM.h>
#define MEM_ALOC_SIZE 160 //Quantidade necessaria para salvar 5 variaveis para cada hora do dia
#define TIME_EXEC 2000 // execução normal de funcionamento do perceptron
#define TIME_DELAY 120000 //após interração pelo usuário o perceptron passar a ficar este tempo sem executar
float luminosidade = 0;
bool movimento = 0;
int hora=0;
bool alteracaoUsuario = false;
bool alteracaoMemoria = false;
//valores utilizados na memoria
uint8_t desejaLigar = 128;
float Wb = -0.2;
float Wm = 0.7;
float Wl = -0.4;
float valorLuzDesejada = 0.68;
uint8_t tempoDesliga = 60;//valor em que o contador tem que chegar para assim desligar a lampada, multiplicado pelo tempoPercetron ocorre o tempo que fica ligado
unsigned long tempoPerceptron = TIME_EXEC;//tempo em que é realizado o perceptron

void setup() {    
  beginLumiControl();
  initWifi();
  configuraSensores();
  luminosidade = getLuminosidade();
  movimento = getMovimento();
  hora = initTimeNTP();   
  EEPROM.begin(MEM_ALOC_SIZE);  
  LeituraInicial();
  alteraTabela();
}

void loop() {    
  int novaHora = newHourNTP();
  if(hora != novaHora){    
    if(!alteracaoMemoria){        
        ajusteHoraParada();
    }    
    GravaNovosValores();
    alteracaoMemoria = false;
    hora = novaHora;
    LeituraInicial(); 
  }
  chamaPerceptron();
}
