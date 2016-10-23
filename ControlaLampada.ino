bool statusRele = false;
uint8_t tabelaLampERele = 0;
int lampada = 13; //pino que fica conectado o rele que aciona a lampada

void beginLumiControl(){
  pinMode(12,INPUT);
  pinMode(lampada, OUTPUT);
  digitalWrite(lampada, 0); 
  alteraTabela();
}

bool leLampada(){
  return digitalRead(12);
}

bool ligaLampada(){
  bool ligou = false;
  if(!leLampada()){
    statusRele = !statusRele;
    digitalWrite(lampada, statusRele);
    int timeout = 5 * 10; // 5 seconds
    while(!leLampada() && (timeout-- > 0)){
      delay(100);//tempo para bater o rele e carregar o capacitor para dar retorno na entrada.
    }
    luzDaLampada();
    alteraTabela();
    ligou = true;
  }
  return ligou;
}

bool desligaLampada(){
  bool desligou = false;
  if(leLampada()){
    statusRele = !statusRele;
    digitalWrite(lampada,statusRele);
    int timeout = 5 * 10; // 5 seconds
    while(leLampada() && (timeout-- > 0)){
      delay(100);//tempo para bater o rele e descarregar o capacitor para dar retorno na entrada.
    }    
    luzDaLampada();
    alteraTabela();
    desligou = true;
  }
  return desligou;
}

bool verificaLampada(){// verifica toda tabela verdade
  if(!statusRele && !leLampada()){// quando os dois em zero
    if(tabelaLampERele != 0){//se não fechar corretamente eh realizado o perceptron de alteracao de usuario
      alteracaoUsuario = true;
      alteraTabela();
    }
  }else if(statusRele && !leLampada()){//quando a lampada desligada e rele ligado
    if(tabelaLampERele != 1){
      alteracaoUsuario = true;
      alteraTabela();
    }
  }else if(!statusRele && leLampada()){//quando a lampada ligada e rele desligado
    if(tabelaLampERele != 2){
      alteracaoUsuario = true;
      alteraTabela();
    }
  }else if(statusRele && leLampada()){//quando os dois ligados
    if(tabelaLampERele != 3){
      alteracaoUsuario = true;
      alteraTabela();
    }
  }
  return alteracaoUsuario;
}

void alteraTabela(){// tabela verdade da relação entre o rele e o status da lampada
  if(!statusRele && !leLampada()){// quando os dois em zero
    tabelaLampERele = 0;
  }else if(statusRele && !leLampada()){//quando a lampada desligada e rele ligado
    tabelaLampERele = 1;
  }else if(!statusRele && leLampada()){//quando a lampada ligada e rele desligado
    tabelaLampERele = 2;
  }else if(statusRele && leLampada()){//quando os dois ligados
    tabelaLampERele = 3;
  }
}

