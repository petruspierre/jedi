void vaiProMeioEsquerdaDescendo(){
  tras(255,255); // bate na parede
  delay(tempoBateNaParede-1200);
  frente(255,255); // se afasta um pouco
  delay(tempoSeAfastaVaiProMeio);
  esquerda(255,255); // da um noventa graus
  delay(tempoNoventaGraus);
  tras(255,255); // um pouco pra tras
  delay(tempoFrenteVaiProMeio);
  esquerda(255,255); // noventa 
  delay(tempoNoventaGraus);
  frente(255,255); // bate na parede
  delay(1500);
  tras(255,255); // para afastar as bolinhas caso tenham algumas atrapalhando
  delay(tempoAfastaBolinha);
  frente(255,255); // bate na parede dnv
  delay(tempoBateNaParede);
  descerGarra(tempoGarra);
  pararGarra();
}

void vaiProMeioDireitaDescendo(){
  tras(255,255); // bate na parede
  delay(tempoBateNaParede-1200);
  frente(255,255); // se afasta um pouco
  delay(tempoSeAfastaVaiProMeio);
  direita(255,255); // da um noventa graus
  delay(tempoNoventaGraus);
  tras(255,255); // um pouco pra tras
  delay(tempoFrenteVaiProMeio);
  direita(255,255); // noventa 
  delay(tempoNoventaGraus);
  frente(255,255); // bate na parede
  delay(1500);
  tras(255,255); // para afastar as bolinhas caso tenham algumas atrapalhando
  delay(tempoAfastaBolinha);
  frente(255,255); // bate na parede dnv
  delay(tempoBateNaParede);
  descerGarra(tempoGarra);
  pararGarra();
}

void vaiProMeioDireitaDescendoExtraEspecial(){
  tras(255,255); // bate na parede
  delay(tempoBateNaParede-1200);
  frente(255,255); // se afasta um pouco
  delay(tempoSeAfastaVaiProMeio);
  direita(255,255); // da um noventa graus
  delay(tempoNoventaGraus);
  tras(255,255); // um pouco pra tras
  delay(tempoFrenteVaiProMeio+200);
  direita(255,255); // noventa 
  delay(tempoNoventaGraus);
  frente(255,255); // bate na parede
  delay(1500);
  tras(255,255); // para afastar as bolinhas caso tenham algumas atrapalhando
  delay(tempoAfastaBolinha);
  frente(255,255); // bate na parede dnv
  delay(tempoBateNaParede);
  descerGarra(tempoGarra);
  pararGarra();
}

void vaiProMeioDireitaDescendoEspecial(){

  tras(255,0);
  delay(1300);
  frente(160,255);
  delay(1100);
  tras(255,0);
  delay(1300);
  esquerda(255,255);
  delay(500);
  tras(255,255);
  delay(500);
  
  frente(255,255);
  delay(tempoFrenteVaiProMeio+300);

  esquerda(255,255);
  delay(tempoNoventaGraus);
  
  frente(255,255);
  delay(1700);

  tras(255,255);
  delay(tempoAfastaBolinha);

  frente(255,255);
  delay(tempoFrenteVaiProMeio);

  descerGarra(tempoGarra);
  pararGarra();
}

void vaiProMeioDireita(){
  tras(255,255); // bate na parede
  delay(tempoBateNaParede-1200);
  frente(255,255); // se afasta um pouco
  delay(tempoSeAfastaVaiProMeio);
  direita(255,255); // da um noventa graus
  delay(tempoNoventaGraus);
  frente(255,255); // um pouco pra tras
  delay(tempoFrenteVaiProMeio);
  direita(255,255); // noventa 
  delay(tempoNoventaGraus);
  frente(255,255); // bate na parede
  delay(tempoBateNaParede);
  tras(255,255); // para afastar as bolinhas caso tenham algumas atrapalhando
  delay(tempoAfastaBolinha);
  frente(255,255); // bate na parede dnv
  delay(tempoBateNaParede);
  descerGarra(tempoGarra);
  pararGarra();
}

void vaiProMeioDireitaEspecial(){
  tras(255,255); // bate na parede
  delay(tempoBateNaParede-1200);
  frente(255,255); // se afasta um pouco
  delay(tempoSeAfastaVaiProMeio);
  direita(255,255); // da um noventa graus
  delay(tempoNoventaGrausTerceira);
  frente(255,255); // um pouco pra tras
  delay(1150);
  direita(255,255); // noventa 
  delay(tempoNoventaGrausTerceira);
  frente(255,255); // bate na parede
  delay(tempoBateNaParede);
  tras(255,255); // para afastar as bolinhas caso tenham algumas atrapalhando
  delay(tempoAfastaBolinha);
  frente(255,255); // bate na parede dnv
  delay(tempoBateNaParede);
  descerGarra(tempoGarra);
  pararGarra();
}

void vaiProMeioEsquerda(){
  tras(255,255); // bate na parede
  delay(tempoBateNaParede-1200);
  frente(255,255); // se afasta um pouco
  delay(tempoSeAfastaVaiProMeio);
  esquerda(255,255); // da um noventa graus
  delay(tempoNoventaGraus);
  frente(255,255); // um pouco pra tras
  delay(tempoFrenteVaiProMeio);
  esquerda(255,255); // noventa 
  delay(tempoNoventaGraus);
  frente(255,255); // bate na parede
  delay(tempoBateNaParede);
  tras(255,255); // para afastar as bolinhas caso tenham algumas atrapalhando
  delay(tempoAfastaBolinha);
  frente(255,255); // bate na parede dnv
  delay(tempoBateNaParede);
  descerGarra(tempoGarra);
  pararGarra();
}

void pegouBolaVaiPraEsquerda(){

  tras(255,255);
  delay(150);
  
  tras(255,0);
  delay(1700);
  frente(0,255);
  delay(800);
  frente(255,255);
  delay(1500);
  
  direita(255,255);
  delay(100);
  tras(255,255);
  delay(1200);
  frente(255,255);
  delay(2000);
  tras(255,255);
  delay(100);
  
  parar(0);
  descerGarra(tempoGarra);
  pararGarra();
  
  direita(255,255);
  delay(100);
  parar(100);
}

void pegouBolaVaiPraEsquerdaEspecial(){
  
  tras(255,255);
  delay(150);
  
  tras(255,0);
  delay(1700);
  frente(0,255);
  delay(700);
  frente(255,255);
  delay(1800);
  
  direita(255,255);
  delay(100);
  tras(255,255);
  delay(1200);
  frente(255,255);
  delay(2000);
  tras(255,255);
  delay(100);
  
  parar(0);
  descerGarra(tempoGarra);
  pararGarra();
  parar(100);

  descerGarra(tempoGarra);
  pararGarra();
}

void vaiPraFrenteEnquantoSobeGarra(){
  frente(170,170);
  delay(250);
  subirGarra(1000);
  parar(0);
  subirGarra(800);
  pararGarra();
}

void vaiPraFrenteEnquantoSobeGarraEspecial(){
  frente(150,210);
  delay(250);
  subirGarra(1000);
  parar(0);
  subirGarra(800);
  pararGarra();
}
