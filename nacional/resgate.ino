
void resgate(){

  if(!lado){
    frente(233,255);
    delay(1300);
  
    parar(0); // para os motores
    descerGarra(tempoGarra); // chegou e desce a garra
    pararGarra();
    
    frente(255,255); // vai pra frente até bater na parede ou na área de resgate
    delay(tempoEntreParedes-300);
    frente(255,0);
    delay(4000);
    tras(255,255); // volta um pouco para afastar caso tenha batido na parede
    delay(200);
    parar(100); // para por 100 milissegundos
  
    reconhecerArea();
  } else {
    frente(255,233);
    delay(1300);

    parar(0);
    descerGarra(tempoGarra);
    pararGarra();

    frente(255,255);
    delay(tempoEntreParedes-300);
    frente(255,0);
    delay(4000);
    tras(255,255);
    delay(200);
    parar(100);

    reconhecerArea();
  }
  
}

void reconhecerArea(){
  if(!lado){ // entrou pela direita
    if(usFrente.read() > 11){ // verifica se a distancia é maior que sete, se for, então a área de resgate é a primeira
      Serial.println("Primeira posicao");
      Serial.println(usFrente.read());
      primeiraPosicaoEntrandoDireita();
    } else {
      tras(255,255);
      delay(300);
      parar(0); // para os motores
      subirGarra(tempoGarra); // chegou e desce a garra
      pararGarra();
      esquerda(255,255);
      delay(tempoNoventaGraus+100);
      tras(230,230);
      delay(950);
      frente(255,255);
      delay(1500);
      parar(0);
      descerGarra(tempoGarra);
      pararGarra();
      frente(255,255);
      delay(tempoEntreParedes120-1700);
      frente(255,0);
      delay(4000);
      tras(255,255);
      delay(270);
      parar(100);
      Serial.println(usFrente.read());
      if(usFrente.read() >11){ // verifica se a distancia é maior que sete, se for, então a área de resgate é a segunda
        if(usFrente.read() > 11){
          Serial.println("segunda posicao");
          Serial.println(usFrente.read());
          segundaPosicaoEntrandoDireita();
        } else {
          Serial.println("terceira posicao");
          terceiraPosicaoEntrandoDireita();
        }
      } else {
        Serial.println("terceira posicao");
        terceiraPosicaoEntrandoDireita();
      }
    }
  } else { // entrou pela direita
    if(usFrente.read() > 11){
      Serial.println("Primeira posicao");
      Serial.println(usFrente.read());
      primeiraPosicaoEntrandoEsquerda();
    } else{

      tras(255,255);
      delay(300);
      parar(0); // para os motores
      subirGarra(tempoGarra); // chegou e desce a garra
      pararGarra();
      direita(255,255);
      delay(tempoNoventaGraus+100);
      tras(230,230);
      delay(950);
      frente(255,255);
      delay(1500);
      parar(0);
      descerGarra(tempoGarra);
      pararGarra();
      frente(255,255);
      delay(tempoEntreParedes120-1700);
      frente(255,0);
      delay(4000);
      tras(255,255);
      delay(270);
      parar(100);
      Serial.println(usFrente.read());

      if(usFrente.read() >11){ // verifica se a distancia é maior que sete, se for, então a área de resgate é a segunda
        if(usFrente.read() > 11){
          Serial.println("segunda posicao");
          Serial.println(usFrente.read());
          segundaPosicaoEntrandoEsquerda();
        } else {
          Serial.println("terceira posicao");
          terceiraPosicaoEntrandoEsquerda();
        }
      } else {
        Serial.println("terceira posicao");
        terceiraPosicaoEntrandoEsquerda();
      }
      
    }
  }
}

void primeiraPosicaoEntrandoDireita(){

  direita(255,255);
  delay(tempoPrimeiroNoventaResgate);
  tras(255,255); // vai dando ré escorando na parede
  delay(tempoEntreParedes120);
  parar(100);


  // 1º parede
  vaiPraFrenteEnquantoSobeGarra();
  pegouBolaVaiPraEsquerda();
  tras(255,255);
  delay(tempoEntreParedes);

  // 2º parede
  vaiPraFrenteEnquantoSobeGarra();
  pegouBolaVaiPraEsquerdaEspecial();
  tras(255,250);
  delay(tempoEntreParedes120);

  // 3º parede
  vaiPraFrenteEnquantoSobeGarra();
  vaiProMeioDireita();
  tras(253,255);
  delay(tempoEntreParedes120);

  // 4º parede
  vaiPraFrenteEnquantoSobeGarra();
  vaiProMeioEsquerda();
  tras(253,255);
  delay(tempoEntreParedes120);


  // DEPOSITO
  depositoPrimeiraEntrandoDireita();
  
}

void depositoPrimeiraEntrandoDireita(){
  vaiPraFrenteEnquantoSobeGarra();

  tras(255,255);
  delay(1000);
  
  direita(255,255);
  delay(tempoNoventaGraus+100);
  frente(255,255);
  delay(2000);
  frente(255,0);
  delay(4000);
  tras(255,255);
  delay(200);

  direita(255,255);
  delay(tempoNoventaGraus);

  frente(255,255);
  delay(250);


  frente(255,255);
  delay(200);
  parar(0);
  
  parar(0);
  descerGarra(tempoGarra);
  pararGarra();
  subirCacamba(tempoGarra);
  pararCacamba();
  
  descerCacamba(tempoGarra);
  pararCacamba();

  subirGarra(tempoGarra);
  pararGarra();

  frente(0,250);
  delay(800);

  tras(255,255);
  delay(1200);
  frente(255,255);
  delay(1200);

  parar(0);
  descerGarra(tempoGarra);
  pararGarra();

  tras(255,255);
  delay(tempoEntreParedes120-1000);

  vaiPraFrenteEnquantoSobeGarra();

  frente(255,255);
  delay(tempoEntreParedes120-1000);

  direita(255,255);
  delay(700);
  tras(255,255);
  delay(400);

  parar(0);
  descerGarra(tempoGarra);
  pararGarra();

  subirCacamba(tempoGarra);
  pararCacamba();
  parar(0);
  parar(1000000);
}

void segundaPosicaoEntrandoDireita(){
  direita(255,255);
  delay(tempoPrimeiroNoventaResgate); // ajustar esse delay
  tras(255,255);
  delay(6000);

  // 1º parede
  vaiPraFrenteEnquantoSobeGarra();
  pegouBolaVaiPraEsquerdaEspecial();
  tras(255,252);
  delay(tempoEntreParedes);

  // 2º parede
  vaiPraFrenteEnquantoSobeGarra();
  vaiProMeioDireita();
  tras(255,255);
  delay(tempoEntreParedes120);

  // 3º parede
  vaiPraFrenteEnquantoSobeGarra();
  vaiProMeioEsquerda();
  tras(255,255);
  delay(tempoEntreParedes120);

  // 4º parede
  vaiPraFrenteEnquantoSobeGarra();
  vaiProMeioDireitaEspecial();
  
  depositoSegundaEntrandoDireita();
}

void depositoSegundaEntrandoDireita(){
  descerGarra(tempoGarra);
  pararGarra();
  tras(255,255);
  delay(tempoEntreParedes120/3);
  parar(0);
  subirGarra(tempoGarra);
  pararGarra();
  tras(190,190);
  delay(tempoEntreParedes/2);
  frente(255,255);
  delay(150);

  direita(255,255);
  delay(tempoNoventaGraus/2);
  tras(200,200);
  delay(1800);
  frente(255,255);
  delay(125);
  esquerda(255,255);
  delay(tempoNoventaGraus+200);
  parar(0);
  descerGarra(tempoGarra);
  pararGarra();
  subirCacamba(tempoGarra);

  pararCacamba();
  descerCacamba(tempoGarra);
  pararCacamba();
  
  subirGarra(tempoGarra);
  pararGarra();

  //SEGUNDA TENTATIVA

  esquerda(255,255);
  delay(tempoNoventaGraus);
  parar(0);

  frente(255,255);
  delay(1500);

  tras(255,255);
  delay(1200);

  frente(255,255);
  delay(1200);
  
  descerGarra(tempoGarra);
  pararGarra();
  
  esquerda(255,255);
  delay(600);
  parar(0);

  tras(255,255);
  delay(tempoEntreParedes);

  vaiPraFrenteEnquantoSobeGarra();

  frente(255,255);
  delay(tempoEntreParedes);

  frente(255,0);
  delay(3500);

  tras(255,255);
  delay(200);
  
  direita(255,255);
  delay(tempoNoventaGraus);
  
  tras(255,255);
  delay(300);
  parar(0);
  descerGarra(tempoGarra);
  pararGarra();
  subirCacamba(tempoGarra);
  pararCacamba();

  descerCacamba(tempoGarra);
  pararCacamba();

  subirGarra(tempoGarra);
  pararGarra();

  esquerda(255,255);
  delay(tempoNoventaGraus);

  tras(255,255);
  delay(1500);

  sambar();
  parar(1000000);
}

void terceiraPosicaoEntrandoDireita(){

  parar(0);
  tras(255,255);
  delay(200);
  esquerda(255,255);
  delay(350);
  parar(0);
  
  tras(255,255);
  delay(tempoEntreParedes);

  // 1 parede
  vaiPraFrenteEnquantoSobeGarraEspecial();
  vaiProMeioDireitaDescendoEspecial();
  tras(255,255);
  delay(tempoEntreParedes);

  // 2 parede
  vaiPraFrenteEnquantoSobeGarra();
  vaiProMeioEsquerdaDescendo();

      // DEPOSITA ANTES
  tras(255,255);
  delay(tempoEntreParedes);

  // 3 parede
  vaiPraFrenteEnquantoSobeGarra();
  vaiProMeioDireitaDescendoExtraEspecial();

  depositoTerceiraEntrandoDireita();
  
}

void depositoTerceiraEntrandoDireita(){

  tras(255,255);
  delay(tempoEntreParedes/3);
  parar(0);
  subirGarra(tempoGarra);
  pararGarra();
  tras(190,190);
  delay(tempoEntreParedes/2 + 1000);

  frente(255,255);
  delay(200);

  esquerda(255,255);
  delay((tempoNoventaGraus-100)/2);

  tras(200,200);
  delay(250);

  frente(255,255);
  delay(90);

  esquerda(255,255);
  delay(tempoNoventaGraus+200);
  
  frente(200,200);
  delay(300); 
  parar(0);
  descerGarra(tempoGarra);
  pararGarra();
  subirCacamba(tempoGarra);
  pararCacamba();

  //a 

  pararCacamba();
  descerCacamba(tempoGarra);
  pararCacamba();
  
  subirGarra(tempoGarra);
  pararGarra();

  esquerda(255,255);
  delay(tempoNoventaGraus);
  parar(0);

  frente(255,255);
  delay(1500);

  tras(255,255);
  delay(1200);

  frente(255,255);
  delay(1200);
  
  descerGarra(tempoGarra);
  pararGarra();
  
  esquerda(255,255);
  delay(600);
  parar(0);

  tras(255,255);
  delay(tempoEntreParedes);

  vaiPraFrenteEnquantoSobeGarra();

  frente(255,255);
  delay(tempoEntreParedes);

  frente(255,0);
  delay(3500);

  tras(255,255);
  delay(200);
  
  direita(255,255);
  delay(tempoNoventaGraus);
  
  tras(255,255);
  delay(300);
  parar(0);
  descerGarra(tempoGarra);
  pararGarra();
  subirCacamba(tempoGarra);
  pararCacamba();

  descerCacamba(tempoGarra);
  pararCacamba();

  subirGarra(tempoGarra);
  pararGarra();

  // 5 parede
  esquerda(255,255);
  delay(75);
  frente(255,255);
  delay(300);
  parar(0);
  descerGarra(tempoGarra);
  pararGarra();
  tras(255,255);
  delay(tempoEntreParedes/4);
  tras(190,0);
  delay(800);
  tras(0,190);
  delay(700);
  tras(255,255);
  delay(tempoEntreParedes/2);

  // 6 parede
  vaiPraFrenteEnquantoSobeGarra();
  frente(255,255);
  delay(tempoEntreParedes);
  
  direita(255,255);
  delay(tempoNoventaGraus);
  parar(0);
  descerGarra(tempoGarra);
  pararGarra();
  subirCacamba(tempoGarra);
  pararCacamba();
  
  parar(1000000);
}

void primeiraPosicaoEntrandoEsquerda(){
  
}

void segundaPosicaoEntrandoEsquerda(){
  
}

void terceiraPosicaoEntrandoEsquerda(){
  
}
