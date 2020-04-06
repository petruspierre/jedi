#include <Ultrasonic.h>
#include <SoftwareSerial.h>

/*IDEIAS

- Colocar pra ele dar ré na descida
- Verificar se os valores são muito absurdos quando ele vê beco na rampa
 
- Tem que colocar para ele parar quando ver o verde com preto na frente, pra ver se pode verificar o tudo preto de outra maneira quando for fazer a segunda verificação do verde pq talvez possa não verificar o 1 e 4 como preto
- Pq na segunda verificação do verde ele vai pra frente e não pra tras? Pq qualquer coisa da pra botar pra ir pra tras e se não for verde ele dá uma virada pra alinhar já que o problema é provavelmente pq ele ta chegando torto
*/

// Portas
#define s7 A13
#define s6 A9
#define s5 A12
#define s4 A14
#define s3 A15
#define s2 A10
#define s1 A11

#define ledPin A8

#define servoGarra1 12
#define servoGarra2 13
#define servoCacamba1 10
#define servoCacamba2 11

#define vel1 7
#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6
#define vel2 2

#define tiltSubida 14  // 0 ta subindo
#define tiltDescida 15 // 0 ta descendo (se colocar o sensor apontado pra tras)

SoftwareSerial Serial4(50, 51); // RX, TX

// Variaveis
int sensor1, sensor2, sensor3, sensor4, sensor5, sensor6, sensor7; // Valores dos sensores
int corte = 400;
int contagemDesafio = 0;
int corteSecundario = 250;
int corteSecundario7 = 140; // so ta usando no beco sem saída
int cortePretoMeio = 200;
int corteVerde = 300; // tava 250
int corteVerdeDireita = 300;

int delayVoltaProMeioDesvio = 300;
int delayOlhaProLadoDesvio = 50; // * 25
int tempoPrimeiroFrenteDesvio = 650;
int tempoSegundoFrenteDesvio = 1250;
int tempoPrimeiroFrenteDesvioRe = 350;
int tempoSegundoFrenteDesvioRe = 950;
int tempoEntreParedes = 5000;
int tempoEntreParedes120 = 7000;
int tempoFrenteVaiProMeio = 700;
int tempoBateNaParede = 2500;
int tempoSeAfastaVaiProMeio = 360;
int tempoAfastaBolinha = 1000;
int tempoPrimeiroNoventaResgate = 1050;
int tempoGarra = 1000;
int tempoNoventaGraus = 945;
int tempoNoventaGrausTerceira = 900;
int tempoNoventaGrausEsquerda = 900;
int tempoFrenteVerdeNoventa = 550;
int tempoFrenteNoventa = 200;

const int intervaloUS = 150; // Intervalo de leitura do Ultrassom
unsigned long int contUS=0, tempoIntervalo; // Contagem e tempo de intervalo da leitura do Ultrassom

int distanciaVerifUS = 15;

bool entrada = false;
bool subida = false;
bool descida = false;
bool cima = false;
bool lado = 0; // 0 pra direita e 1 pra esquerda
bool prioridade = 0; // 0 pra direita e 1 pra esquerda

int velE = 210; // tava 210
int velD = 210;
int velER = 180;
int velDR = 180;
int velER2 = 255;
int velDR2 = 255;

Ultrasonic usFrente(16,17);
Ultrasonic usLateralDireita(19,18);
Ultrasonic usLateralEsquerda(20,21);

void setup() {
  setPinModes();
  Serial.begin(9600);
  parar(0);
  pararGarra();
  pararCacamba();
  delay(1500);
}
 
void loop() { 
  
  
  lerSensores();
  //printarSensores();
  //printarUltrassom();
  //testarTilt();

  //resgate();

  verificarObstaculo();
  
  if(!entrada and !subida and !cima and !descida) seguirFaixa();
  else if(entrada) seguirFaixaEntradaResgate();
  else if(cima) seguirFaixaEmCima();
  else if(subida)seguirFaixaSubindo();
  else if(descida) seguirFaixaDescendo();
}

void seguirFaixa(){
  if(sensor2 < corteVerde && sensor6 >= cortePretoMeio && sensor3 < corteVerdeDireita){
    frente(velE, velD);
  }

  else if(sensor1 >= corte && sensor2 >= corteVerde && sensor3 >= corteVerdeDireita && sensor4 >= corte && sensor6 >= cortePretoMeio){ // aqui ainda pode colocar o sensor 5 e 7 como branco caso dê problema
    tudoPreto();
  }

  else if (sensor1 >= corte && sensor2 < corteVerde && sensor3 < corteVerdeDireita && sensor4 < corte && sensor5 < corte && sensor6 < cortePretoMeio && sensor7 < corte) {
    pontaEsquerda();
  }

  else if (sensor1 < corte && sensor2 < corteVerde && sensor3 < corteVerdeDireita && sensor4 >= corte && sensor5 < corte && sensor6 < cortePretoMeio && sensor7 < corte) {
    pontaDireita();
  }

  else if(sensor1 >= corte && sensor2 >= corteVerde && sensor6 < cortePretoMeio){ // dá pra colocar mais condições (sensor4) se tiver vendo 90 no verde, mas no geral ta ok
    noventaEsquerda();
  }

  else if(sensor1 < corte && sensor6 < cortePretoMeio && sensor3 >= corteVerdeDireita && sensor4 >= corte){ // verificar usando sem o sensor1
    noventaDireita();
  }

  else if(sensor6 >= cortePretoMeio && sensor1 >= corte && sensor2 >= corteVerde){ // TAVA USANDO CORTE NORMAL NO SENSOR2
    tEsquerda();
  }

  else if(sensor6 >= cortePretoMeio && sensor3 >= corteVerdeDireita && sensor4 >= corte){ // TAVA USANDO O SENSOR 1 EU TIREI
    tDireita();
  }

  else if(sensor2 >= corteVerde && sensor6 < cortePretoMeio && sensor3 < corteVerdeDireita){ // satisfatorio
    curvaAbertaEsquerda();
  }

  else if(sensor2 < corteVerde && sensor6 < cortePretoMeio && sensor3 >= corteVerdeDireita){ // satisfatorio
    curvaAbertaDireita();
  }

  else if(sensor1 < corte && sensor4 < corte && sensor2 >= corteVerde && sensor5 >= corteSecundario/* && sensor6 >= cortePretoMeio*/){
    verdeEsquerdaPreto();
  }

  else if(sensor1 < corte && sensor4 < corte && sensor3 >= corteVerdeDireita && sensor7 >= corteSecundario/* && sensor6 >= cortePretoMeio*/){
    verdeDireitaPreto();
  }

  else if(sensor3 >= corteVerdeDireita && sensor5 >= corte && sensor2 >= corteVerde && sensor7 > corte && sensor1 < corte && sensor4 < corte){ // antes todos os pretos estavam no cortePretoMeio, verificar se melhorou (mesma coisa para as verificações nos verdes dos lados)
    becoSemSaida();
  }

  else if (sensor1 < corte && sensor2 < corteVerde && sensor3 < corteVerdeDireita && sensor4 < corte && sensor5 < corte && sensor6 < cortePretoMeio && sensor7 < corte) {
    tudoBranco();
  }
}

void seguirFaixaEntradaResgate(){ // Antes de entrar na sala de resgate
  if(sensor2 < corteVerde && sensor6 >= cortePretoMeio && sensor3 < corteVerdeDireita){
    frente(velE, velD);
  }

  else if(sensor1 >= corte && sensor2 >= corteVerde && sensor3 >= corteVerdeDireita && sensor4 >= corte && sensor6 >= cortePretoMeio){ // aqui ainda pode colocar o sensor 5 e 7 como branco caso dê problema
    tudoPreto();
  }

  else if(sensor2 >= corteVerde && sensor6 < cortePretoMeio && sensor3 < corteVerdeDireita){ // satisfatorio
    //curvaAbertaEsquerda();
    frente(velER,velDR2);
    delay(50);
  }

  else if(sensor2 < corteVerde && sensor6 < cortePretoMeio && sensor3 >= corteVerdeDireita){ // satisfatorio
    //curvaAbertaDireita();
    frente(velER2,velDR);
    delay(50);
  }

  else if (sensor1 >= corte && sensor2 < corteVerde && sensor3 < corteVerdeDireita && sensor4 < corte && sensor5 < corte && sensor6 < cortePretoMeio && sensor7 < corte) {
    //pontaEsquerda();
    frente(0,255);
  }

  else if (sensor1 < corte && sensor2 < corteVerde && sensor3 < corteVerdeDireita && sensor4 >= corte && sensor5 < corte && sensor6 < cortePretoMeio && sensor7 < corte) {
    //pontaDireita();
    frente(255,0);
  }

  else if (sensor1 < corte && sensor2 < corteVerde && sensor3 < corteVerdeDireita && sensor4 < corte && sensor5 < corte && sensor6 < cortePretoMeio && sensor7 < corte) {
    tudoBranco();
  }
  
  if(usLateralEsquerda.read() > 20){
    if(usLateralEsquerda.read() > 20){
      lado = 0; // direita
      resgate();
    }
  } else {
    lado = 1; // esquerda
    resgate();
  }
}

void seguirFaixaSubindo(){ // Ta subindo na rampa
  if(sensor2 < corteVerde && sensor6 >= cortePretoMeio && sensor3 < corteVerdeDireita){
    frente(velE, velD);
  }

  else if(sensor1 >= corte && sensor2 >= corteVerde && sensor3 >= corteVerdeDireita && sensor4 >= corte && sensor6 >= cortePretoMeio){ // aqui ainda pode colocar o sensor 5 e 7 como branco caso dê problema
    tudoPreto();
  }

  else if(sensor2 >= corteVerde && sensor6 < cortePretoMeio && sensor3 < corteVerdeDireita){ // satisfatorio
    //curvaAbertaEsquerda();
    frente(velER,velDR2);
    delay(50);
  }

  else if(sensor2 < corteVerde && sensor6 < cortePretoMeio && sensor3 >= corteVerdeDireita){ // satisfatorio
    //curvaAbertaDireita();
    frente(velER2,velDR);
    delay(50);
  }

  else if (sensor1 >= corte && sensor2 < corteVerde && sensor3 < corteVerdeDireita && sensor4 < corte && sensor5 < corte && sensor6 < cortePretoMeio && sensor7 < corte) {
    //pontaEsquerda();
    frente(0,255);
  }

  else if (sensor1 < corte && sensor2 < corteVerde && sensor3 < corteVerdeDireita && sensor4 >= corte && sensor5 < corte && sensor6 < cortePretoMeio && sensor7 < corte) {
    //pontaDireita();
    frente(255,0);
  }

  else if (sensor1 < corte && sensor2 < corteVerde && sensor3 < corteVerdeDireita && sensor4 < corte && sensor5 < corte && sensor6 < cortePretoMeio && sensor7 < corte) {
    tudoBranco();
  }

  if(digitalRead(tiltSubida)){       // chegou no topo
    if(digitalRead(tiltSubida)){
      if(digitalRead(tiltSubida)){
        delay(50);

        if(digitalRead(tiltSubida)){
          Serial.println("chegou");
          velE = 210;
          velD = 210;
          cima = true;
          subida = false;
        }
      }
    }
  }
  
}

void seguirFaixaEmCima(){ // Subiu a rampa
  if(sensor2 < corteVerde && sensor6 >= cortePretoMeio && sensor3 < corteVerdeDireita){
    frente(velE, velD);
  }

  else if (sensor1 >= corte && sensor2 < corteVerde && sensor3 < corteVerdeDireita && sensor4 < corte && sensor5 < corte && sensor6 < cortePretoMeio && sensor7 < corte) {
    pontaEsquerda();
  }

  else if (sensor1 < corte && sensor2 < corteVerde && sensor3 < corteVerdeDireita && sensor4 >= corte && sensor5 < corte && sensor6 < cortePretoMeio && sensor7 < corte) {
    pontaDireita();
  }

  else if(sensor1 >= corte && sensor2 >= corteVerde && sensor6 < cortePretoMeio){ // dá pra colocar mais condições (sensor4) se tiver vendo 90 no verde, mas no geral ta ok
    noventaEsquerda();
  }

  else if(sensor1 < corte && sensor6 < cortePretoMeio && sensor3 >= corteVerdeDireita && sensor4 >= corte){ // verificar usando sem o sensor1
    noventaDireita();
  }

  else if(sensor2 >= corteVerde && sensor6 < cortePretoMeio && sensor3 < corteVerdeDireita){ // satisfatorio
    curvaAbertaEsquerda();
  }

  else if(sensor2 < corteVerde && sensor6 < cortePretoMeio && sensor3 >= corteVerdeDireita){ // satisfatorio
    curvaAbertaDireita();
  }

  else if (sensor1 < corte && sensor2 < corteVerde && sensor3 < corteVerdeDireita && sensor4 < corte && sensor5 < corte && sensor6 < cortePretoMeio && sensor7 < corte) {
    tudoBranco();
  }

  if(!digitalRead(tiltDescida)){      // se tiver descendo
    if(!digitalRead(tiltDescida)){
      if(!digitalRead(tiltDescida)){
        delay(50);
        if(!digitalRead(tiltDescida)){
          Serial.println("desceu");
          velE = 190;
          velD = 190;
          descida = true;
          subida = false;
          cima = false;
        }
      }
    }
  }
}

void seguirFaixaDescendo(){
  if(sensor2 < corteVerde && sensor6 >= cortePretoMeio && sensor3 < corteVerdeDireita){
    frente(velE, velD);
  }

  else if(sensor1 >= corte && sensor2 >= corteVerde && sensor3 >= corteVerdeDireita && sensor4 >= corte && sensor6 >= cortePretoMeio){ // aqui ainda pode colocar o sensor 5 e 7 como branco caso dê problema
    tudoPreto();
  }

  else if(sensor2 >= corteVerde && sensor6 < cortePretoMeio && sensor3 < corteVerdeDireita){ // satisfatorio
    //curvaAbertaEsquerda();
    frente(velER,velDR2);
    delay(50);
  }

  else if(sensor2 < corteVerde && sensor6 < cortePretoMeio && sensor3 >= corteVerdeDireita){ // satisfatorio
    //curvaAbertaDireita();
    frente(velER2,velDR);
    delay(50);
  }

  else if (sensor1 >= corte && sensor2 < corteVerde && sensor3 < corteVerdeDireita && sensor4 < corte && sensor5 < corte && sensor6 < cortePretoMeio && sensor7 < corte) {
    //pontaEsquerda();
    frente(0,255);
  }

  else if (sensor1 < corte && sensor2 < corteVerde && sensor3 < corteVerdeDireita && sensor4 >= corte && sensor5 < corte && sensor6 < cortePretoMeio && sensor7 < corte) {
    //pontaDireita();
    frente(255,0);
  }

  else if (sensor1 < corte && sensor2 < corteVerde && sensor3 < corteVerdeDireita && sensor4 < corte && sensor5 < corte && sensor6 < cortePretoMeio && sensor7 < corte) {
    tudoBranco();
  }

  if(digitalRead(tiltDescida)){
    if(digitalRead(tiltDescida)){
      if(digitalRead(tiltDescida)){
        delay(50);

        if(digitalRead(tiltDescida)){
          Serial.println("acabou");
          descida = false;
        }
      }
    }
  }
}

void tudoBranco() {
  frente(velE, velD);
}

void pontaEsquerda() {
  lerSensores();
  esquerda(velE, velD);
  while (sensor6 < cortePretoMeio) {
    sensor6 = analogRead(s6);
    delay(1);
  }
}

void pontaDireita() {
  lerSensores();
  direita(velE, velD);
  while (sensor6 < cortePretoMeio) {
    sensor6 = analogRead(s6);
    delay(1);
  }
}

void tudoPreto(){
  Serial.println("Tudo preto");
  frente(velE, velD);
  delay(300);
}

void verdeDireitaPreto(){
  Serial.println("verde direita com preto na frente 1 verif");
  parar(100);
  frente(velE,velD);
  delay(35); // aqui não existia esse delay
  parar(100);
  lerSensores();
  //pararEler();
  if(sensor1 >= corte && sensor2 >= corteVerde && sensor3 >= corteVerdeDireita && sensor4 >= corte && sensor6 >= cortePretoMeio){ // aqui ainda pode colocar o sensor 5 e 7 como branco caso dê problema
    tudoPreto();
  } else if(sensor1 < corte && sensor4 < corte && sensor3 >= corteVerdeDireita && sensor7 >= corteSecundario){
   if(sensor3 >= corteVerdeDireita && sensor5 >= corteSecundario && sensor2 >= corteVerde && sensor7 >= corteSecundario && sensor1 < corte && sensor4 < corte){
     becoSemSaida();
   } else {
    frente(velE,velD);
   Serial.println("verde direita com preto na frente 2 verif");
   delay(tempoFrenteVerdeNoventa);
   direita(230, 230);
   delay(400);
   lerSensores();
   while (sensor6 < cortePretoMeio) {
     sensor6 = analogRead(s6);
     delay(1);
   }
   delay(50);
   frente(velE, velD);
   delay(75);
   }
  } else {
    frente(velE,velD);
  }
}

void verdeEsquerdaPreto(){
  Serial.println("verde esquerda com preto na frente 1 verif");
  parar(100);
  printarSensores();
  frente(velE,velD);
  delay(35);
  parar(100);
  lerSensores();
  printarSensores(); 
  if(sensor1 >= corte && sensor2 >= corteVerde && sensor3 >= corteVerdeDireita && sensor4 >= corte && sensor6 >= cortePretoMeio){ // aqui ainda pode colocar o sensor 5 e 7 como branco caso dê problema
    tudoPreto();
  } else if(sensor1 < corte && sensor4 < corte && sensor2 >= corteVerde && sensor5 >= corteSecundario){
    if(sensor3 >= corteVerdeDireita && sensor5 >= corteSecundario && sensor2 >= corteVerde && sensor7 >= corteSecundario && sensor1 < corte && sensor4 < corte){
      becoSemSaida();
    } else {
    Serial.println("verde esquerda com preto na frente 2 verif");
    frente(velE, velD);
    delay(tempoFrenteVerdeNoventa);
    esquerda(230, 230);
    delay(400);
    lerSensores();
    while (sensor6 < cortePretoMeio) {
      sensor6 = analogRead(s6);
      delay(1);
    }
    delay(50);
    frente(velE, velD);
    delay(75);
    }
  } else {
    frente(velE, velD);
  }
}

void becoSemSaida(){
  tras(velE, velD);
  delay(50); // tava 120
  parar(100);
  lerSensores();
  //pararEler();
  Serial.println("Beco sem saída 1 verif");
  printarSensores();
  if(sensor3 >= corteVerdeDireita && sensor5 >= corteSecundario && sensor2 >= corteVerde && sensor7 >= corteSecundario7 && sensor1 < corte && sensor4 < corte){
    Serial.println("Beco sem saida 2 verif");
    //frente(230,230);
    //delay(200);
    direita(230, 230);
    delay(1500);
    lerSensores();
    while (sensor6 < cortePretoMeio) {
      sensor6 = analogRead(s6);
      delay(1);
    }
    delay(50);
    frente(velE, velD);
    delay(200);
  } else {
    frente(velE,velD);
  }
}

void curvaAbertaDireita(){
  delay(30);
  lerSensores();
  if (sensor2 < corteVerde && sensor6 < cortePretoMeio && sensor3 >= corteVerdeDireita) {
    direita(velE, velD);
  }
}

void curvaAbertaEsquerda(){
  delay(30);
  lerSensores();
  if (sensor2 >= corteVerde && sensor6 < cortePretoMeio && sensor3 < corteVerdeDireita) {
    esquerda(velE, velD);
  }
}

void tDireita(){
  frente(velE, velD);
  delay(50);
  lerSensores();
  //pararEler();
  if(sensor1 < corte && sensor6 >= cortePretoMeio && sensor3 >= corte && sensor4 >= corte){
    Serial.println("T direita");
    frente(velE, velD);
    delay(400);
  }
}

void tEsquerda(){
  Serial.println("T esquerda");
  frente(velE, velD);
  delay(20); // da pra aumentar esse delay
  lerSensores();
  if(sensor6 >= cortePretoMeio){
    frente(velE,velD);
    delay(400);
  }
}

void noventaEsquerda(){
  frente(velE, velD);
  delay(50); // bom definir um delay padrao (tava 25) acho que 50 ta bom
  lerSensores();
  if (sensor1 >= corte && sensor2 >= corteVerde && sensor6 < cortePretoMeio){ // alterar aqui tambem caso coloque os sensor4 ou colocar somente aqui
    Serial.println("90 esquerda");
    printarSensores();
    delay(tempoFrenteNoventa);
    direita(230, 230);
    delay(350);
    esquerda(230, 230);
    while (sensor6 < cortePretoMeio) {
      sensor6 = analogRead(s6);
      delay(1);
    }
    delay(75); // tava 50 aumentei pra 100
    frente(velE, velD);
    delay(300);
  }
}

void noventaDireita(){ // adicionei segunda verificação
  frente(velE, velD);
  delay(50);
  lerSensores();
  if(sensor1 < corte && sensor6 < cortePretoMeio && sensor3 >= corteVerdeDireita && sensor4 >= corte){
    Serial.println("90 direita");
    delay(tempoFrenteNoventa);
    esquerda(230, 230);
    delay(350);
    direita(230, 230);
    while (sensor6 < cortePretoMeio) {
      sensor6 = analogRead(s6);
      delay(1);
    }
    delay(75); // tava 50 aumentei pra 100
    frente(velE, velD);
    delay(300); //tava 450
  }
}

void verificarObstaculo(){ // acho que tá errado

  //tempoIntervalo = millis();
  if(millis()-contUS > intervaloUS){
    verificarResgate();
    verificarUltrassom();
    verificarRampa();
    contUS = millis();
  }
  
}

void verificarUltrassom(){
  if(usFrente.read() <= 7){
    if(usFrente.read() <= 7){
      int l = usFrente.read();
      if(l <= 7){
        // detectou obstaculo
        Serial.println("obstaculo");

        int contEsquerda = 999, contDireita = 999;

        esquerda(190,190);
        while(usFrente.read() <= l+3){  
          analogWrite(ledPin,1023);
          delay(1);
        }
        delay(400);
        analogWrite(ledPin,0);
        
        for(int i=0;i<delayOlhaProLadoDesvio;i++){
          parar(0);
          int l1 = usFrente.read();
          if(l1 < contEsquerda){
            contEsquerda = l1;
            piscarLed(100);
          }
          esquerda(190,190);
          delay(25);
        }

        direita(210,210);
        delay(delayVoltaProMeioDesvio);
        
        while(usFrente.read()>=l+4){
          delay(1);
        }
        delay(100);

        parar(100);
        
        direita(190,190);
        while(usFrente.read() <= l+3){  
          analogWrite(ledPin,1023);
          delay(1);
        }
        delay(400);
        analogWrite(ledPin,0);
        
        for(int i=0;i<delayOlhaProLadoDesvio;i++){
          parar(0);
          int l1 = usFrente.read();
          if(l1 < contDireita){
            contDireita = l1;
            piscarLed(100);
          }
          direita(190,190);
          delay(25);
        }

        parar(0);

        esquerda(210,210);
        delay(delayVoltaProMeioDesvio);

        while(usFrente.read()>=l+4){
          delay(1);
        }

        delay(100);
        
        parar(0);

        //int mEsquerda = contEsquerda/delayOlhaProLadoDesvio;
        //int mDireita = contDireita/delayOlhaProLadoDesvio; 

        //Serial.println(mEsquerda);
        //Serial.println(mDireita);

        parar(100);

        if(contEsquerda < contDireita){
          desviarRe();
        } else {
          desviar();
        }
        
      }
    }
  }
}

bool verificarErroMaiorUSDireita(int dist){
  int i,contErros=0;
  for (int i=0;i<10;i++){
    if(usLateralDireita.read()>dist) contErros++;
    delay(5);
  }
  if(contErros > 3) return false;
  else return true;
}

bool verificarErroMenorUSDireita(int dist){
  int i,contErros=0;
  for (int i=0;i<10;i++){
    if(usLateralDireita.read()<dist) contErros++;
    delay(5);
  }
  if(contErros > 3) return false;
  else return true;
}

void verificarResgate(){
  if(usLateralDireita.read() < 15 && usLateralEsquerda.read() < 15){
    frente(velE,velD);
    delay(800);
    if(usLateralDireita.read() < 15 && usLateralEsquerda.read() < 15){
      if(usLateralDireita.read() < 15 && usLateralEsquerda.read() < 15){
        entrada = true;
      }
    }
  }
}

void verificarRampa(){
  if(!digitalRead(tiltSubida)){
    if(!digitalRead(tiltSubida)){
      if(!digitalRead(tiltSubida)){

        delay(100);
        if(!digitalRead(tiltSubida)){
          Serial.println("subiu");
          subida = true;
          velE=255;
          velD=255;
        }
        
      }
    }
  }
}

void desviar() {
  frente(0, 0);
  delay(250);
  while (usLateralDireita.read() > 9) { // se der ruim usar a nova verificação
    esquerda(255, 255);
  }
  delay(210);
  frente(255,255);
  delay(100);
  while (verificarErroMaiorUSDireita(15)) { // quando for maior que 15 três vezes, retorna falso
    frente(255, 255);
  }
  delay(tempoPrimeiroFrenteDesvio);
  direita(0, 255);
  delay(750);
  direita(255, 0);
  delay(800);
  while (verificarErroMenorUSDireita(15)) { // quando for menor que 15 três vezes, retorna falso
    frente(255, 255);
  }
  delay(tempoSegundoFrenteDesvio);
  direita(0, 255);
  delay(800);
  direita(255, 0);
  delay(800);
  frente(velE, velD);
  delay(250);
  lerSensores();
  while (sensor6 < 500) {
    sensor6 = analogRead(s6);
    delay(1);
  }
  delay(500);
  
  esquerda(velE, velD);
  lerSensores();
  while(sensor6 < 500){
    sensor6 = analogRead(s6);
    delay(1);
  }
  delay(300);
  
}

void desviarRe() {
  frente(0, 0);
  delay(250);
  while (usLateralDireita.read() > 9) { // se der ruim usar a nova verificação
    esquerda(255, 255);
  }
  delay(210);
  tras(255,255);
  delay(100);
  while (verificarErroMaiorUSDireita(15)) { // quando for maior que 15 três vezes, retorna falso
    tras(255, 255);
  }
  delay(tempoPrimeiroFrenteDesvioRe);
  esquerda(255, 0);
  delay(800);
  esquerda(0, 255);
  delay(750);
  while (verificarErroMenorUSDireita(15)) { // quando for menor que 15 três vezes, retorna falso
    tras(255, 255);
  }
  delay(tempoSegundoFrenteDesvioRe);
  direita(0, 255);
  delay(800);
  direita(255, 0);
  delay(1100);
  frente(velE, velD);
  lerSensores();
  while (sensor6 < 500) {
    sensor6 = analogRead(s6);
    delay(1);
  }
  delay(500);
  
  direita(velE, velD);
  lerSensores();
  while(sensor6 < 500){
    sensor6 = analogRead(s6);
    delay(1);
  }
  delay(300);
  
}
