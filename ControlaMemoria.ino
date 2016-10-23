
//eh armazenado valores de 0 a 255, mas o perceptron trabalha de -1 a 1 para isso os valores serão multiplicados por 100 e somados por mais cem. tendo assim valores de 0 a 200
uint8_t mWb ; // -0,26*100 + 100
uint8_t mWl ; // -0,47*100 + 100
uint8_t mWm ; // 0,61*100 + 100
uint8_t mLd ; // 0,68*100
uint8_t mTd ; // valor direto

void LeituraInicial(){
  mWb = EEPROM.read(0+hora);
  mWl = EEPROM.read(24+hora);
  mWm = EEPROM.read(48+hora);
  mLd = EEPROM.read(72+hora);
  mTd = EEPROM.read(96+hora);
  desejaLigar = EEPROM.read(120+hora);
  Wb = ajustaValorPerceptron(mWb);  
  Wl = ajustaValorPerceptron(mWl);
  Wm = ajustaValorPerceptron(mWm);
  valorLuzDesejada = ((float) mLd)/100;
  if(valorLuzDesejada > 0.9) valorLuzDesejada = 0.9;
  if(valorLuzDesejada < 0.05) valorLuzDesejada = 0.05;
  tempoDesliga = mTd;
  if(tempoDesliga > 100) tempoDesliga = 100;
  if(tempoDesliga < 5) tempoDesliga = 5;
}

void GravaNovosValores(){
  alteracaoMemoria = true;
  mWb = (uint8_t) ((Wb*100) + 100);
  mWl = (uint8_t) ((Wl*100) + 100);
  mWm = (uint8_t) ((Wm*100) + 100);
  mLd = (uint8_t) (valorLuzDesejada*100);
  mTd = tempoDesliga;
  EEPROM.write(0+hora,mWb);
  EEPROM.write(24+hora,mWl);
  EEPROM.write(48+hora,mWm);
  EEPROM.write(72+hora,mLd);
  EEPROM.write(96+hora,mTd);
  EEPROM.write(120+hora,desejaLigar);
  EEPROM.commit();
}

float ajustaValorPerceptron(uint8_t valor){
  float novoValor = (((float)valor)-100)/100;
  if(novoValor > 1) return 1;
  if(novoValor < -1) return -1;
  return novoValor;
}

