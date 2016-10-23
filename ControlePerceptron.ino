//variaveis perceptron
bool bias = 1;
float aprendizagem = 0.01;
bool p1 = false; //valor do perceptron para ligar a lampada
int contDesliga = 0; 
unsigned long millisPerceptron = 0;


void chamaPerceptron(){  
  unsigned long millisAtual = (millis()) - millisPerceptron;
  if(millisAtual < 0) millisPerceptron = 0;
  if(millisAtual >= tempoPerceptron && !alteracaoUsuario){
    if(!verificaLampada()){
      millisPerceptron = millis();
      tempoPerceptron = TIME_EXEC;//sempre que executado o perceptron volta a executar no tempo normal
      luminosidade = getLuminosidade();
      movimento = getMovimento();
      p1 = perceptron(luminosidade, movimento);
      int saida = verificaErro(p1, luminosidade, movimento);
      if(saida != -1){
        if(saida == 1 && desejaLigar >= 125){
          contDesliga = 0; //Sempre que a saida for ligar zera o contador
          ligaLampada()
        }else{
          if(contDesliga <= (4*(tempoDesliga+1))){
            contDesliga++;// somente quando contador chegar ao valor do tempo eh que a saida ira desligar
          }
          if(contDesliga >= tempoDesliga){          
            if(desligaLampada()){
              tempoPerceptron = 5*TIME_EXEC;//se desligou aguarda cinco vezes o tempo normal para voltar a executar e religar a lampada
            }
          }
        }
      } 
    }
  }
  if(alteracaoUsuario){//caso o usuario altere antes do perceptron eh realizado verificacao e correcao dos valores
    alteracaoUsuario = false;
    millisPerceptron = millis();
    if(leLampada()){//Apos executar esta funcao o tempo para perceptron aumenta de forma igual para ligar ou desligar a lampada
      if(TIME_EXEC*tempoDesliga < TIME_DELAY)
        tempoPerceptron = TIME_DELAY - (TIME_EXEC*tempoDesliga);
      else
        tempoPerceptron = 0;
    }else{
      tempoPerceptron = TIME_DELAY;
    }
    luminosidade = getLuminosidade();
    movimento = getMovimento();
    p1 = perceptron(luminosidade, leLampada());
    //verifica se a lampada possui o mesmo status do perceptron se nao deve ser corrigido o erro
    if(p1 != leLampada()){
      int erroLuz = ((int) leLampada()) - ((int) p1);
      perceptronLuzDesejada(luminosidade,erroLuz);
      GravaNovosValores();      
    }
    if(!leLampada()){//se o usuario desligou a lampada
      perceptronDesejaLigar(-1);
      if(contDesliga < tempoDesliga && tempoDesliga > 5 && contDesliga > 0){//considera que deveria ter desligado e diminui o tempoDesliga
        int corTempo = tempoDesliga - contDesliga;//quanto mais rapido o usuario desligar mais vai influenciar no novo numero
        tempoDesliga = tempoDesliga + (-1*(aprendizagem*100)*corTempo)/100;
        GravaNovosValores();
      }else if(tempoDesliga < 5){
        tempoDesliga = 5;
      }
    }else{// se o usuario ligou a lampada
      perceptronDesejaLigar(1);
      if(contDesliga > tempoDesliga && contDesliga < (4*(tempoDesliga+1)) && tempoDesliga < 100){//considera que desligou rapido demais e aumenta o tempoDesliga
        int corTempo = contDesliga - tempoDesliga;//quanto mais rapido o usuario religar mais vai influenciar no novo numero
        tempoDesliga = tempoDesliga + (1*(aprendizagem*100)*corTempo)/100;//usuado a mesma conta de ajuste de valor do perceptron (erro*aprendizagem*valorlido)
        GravaNovosValores();
      }else if(tempoDesliga >= 100){
        tempoDesliga = 100;
      }
    }
    contDesliga = 0;
  }
}

bool perceptron(float mediaLuminosidade, bool valorSensorMov){
  float somatoria = (bias * Wb) + (mediaLuminosidade * Wl) + (valorSensorMov * Wm);
  if(somatoria > 0){
    return 1;
  }else{
    return 0;
  }
}

void ajusteHoraParada(){
  //ajuste para mais proximo da que foi lida na ultima hora
  if(valorLuzDesejada > luminosidade && valorLuzDesejada < 0.9){
    perceptronLuzDesejada(valorLuzDesejada-luminosidade, -1);
  }else if(valorLuzDesejada < luminosidade && valorLuzDesejada > 0.05){
    perceptronLuzDesejada(luminosidade-valorLuzDesejada, 1);
  }
  //ajuste de reducao do tempo ligado, pois nao foi ligado nesta hora
  if(tempoDesliga > 20){
    tempoDesliga = tempoDesliga + (-1*(aprendizagem*100)*tempoDesliga)/100;
  }
  perceptronDesejaLigar(-1);
}

bool perceptronLuzDesejada(float mediaLuminosidade, int erroLuz){
  valorLuzDesejada = valorLuzDesejada + (erroLuz * (aprendizagem*100) * mediaLuminosidade)/100;//utilizado a mesma regra de aprendizagem 
}

bool perceptronDesejaLigar(int erroLiga){
  if(desejaLigar > 5 && desejaLigar < 250){
    desejaLigar = desejaLigar + (erroLiga * (aprendizagem*100));//utilizado a mesma regra de aprendizagem 
  }else if(desejaLigar >= 250){ 
    desejaLigar = 249;
  }else if(desejaLigar <= 5){
    desejaLigar = 6;
  }
}

void correcaoErro(int erro, float mediaLuminosidade, bool valorSensorMov){
  Wb = Wb + (erro * aprendizagem * bias);
  Wl = Wl + (erro * aprendizagem * mediaLuminosidade);
  Wm = Wm + (erro * aprendizagem * valorSensorMov);
  GravaNovosValores();
}

int verificaErro(bool saida, float mediaLuminosidade, bool valorSensorMov){
  if(mediaLuminosidade < (valorLuzDesejada + getLuzDaLampada()) && valorSensorMov == 1){
    //Aqui eu espero que tenha 1 se não tiver, então 1 - 0 = 1
    if(!saida){
      correcaoErro(1, mediaLuminosidade, valorSensorMov);
      return -1;
    }else{
      return 1;
    }
  }else{
    //Aqui eu espero que tenha 0 se não tiver, então 0 - 1 = -1
    if(saida){
      correcaoErro(-1, mediaLuminosidade, valorSensorMov);
      return -1;
    }else{
      return 0;
    }
  }
}
