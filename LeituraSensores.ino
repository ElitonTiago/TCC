float luzLampada = 0;
//Configuracao sensores
int pinoSensorMov = 4;
void configuraSensores(){
  pinMode(pinoSensorMov, INPUT);
}
float getLuminosidade(){  
  int j;  
  float valorLuminosidade = 0;
  for(j = 0; j < 10; j++){
    valorLuminosidade += analogRead(A0);
    yield();
  } 
  valorLuminosidade = (valorLuminosidade/10)/1024;
  return valorLuminosidade; //soma com a luminosidade criada pela lampada
}
bool getMovimento(){  
  bool valorSensorMov = 0;
  valorSensorMov = digitalRead(pinoSensorMov);
  return valorSensorMov;
}
void luzDaLampada(){
  luzLampada = (getLuminosidade() - luminosidade);
  if(luzLampada < 0 || !leLampada()){
    luzLampada = 0;
  }
}

float getLuzDaLampada(){
  return luzLampada;
}

