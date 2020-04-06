void piscarLed(int oi){
  analogWrite(ledPin,1023);
  delay(oi);
  analogWrite(ledPin,0);
  delay(oi);
}

void setPinModes(){
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  pinMode(s6, INPUT);
  pinMode(s7, INPUT);

  pinMode(tiltSubida, INPUT_PULLUP);
  pinMode(tiltDescida, INPUT_PULLUP);

  pinMode(servoGarra1, OUTPUT);
  pinMode(servoGarra2, OUTPUT);
  pinMode(servoCacamba1, OUTPUT);
  pinMode(servoCacamba2, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(vel1, OUTPUT);
  pinMode(vel2, OUTPUT);
}

void pararGarra(){
  digitalWrite(servoGarra1, LOW);
  digitalWrite(servoGarra2, LOW);
}

void subirGarra(int d){
  digitalWrite(servoGarra1, HIGH);
  digitalWrite(servoGarra2, LOW);
  delay(d);
}

void subirCacamba(int d){
  digitalWrite(servoCacamba1, HIGH);
  digitalWrite(servoCacamba2, LOW);
  delay(d);
}

void descerCacamba(int d){
  digitalWrite(servoCacamba1, LOW);
  digitalWrite(servoCacamba2, HIGH);
  delay(d);
}

void pararCacamba(){
  digitalWrite(servoCacamba1, LOW);
  digitalWrite(servoCacamba2, LOW);
}

void descerGarra(int d){
  digitalWrite(servoGarra1, LOW);
  digitalWrite(servoGarra2, HIGH);
  delay(d);
}

void parar( long long d ) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  delay(d);
}

void frente( int velocidade1, int velocidade2 ) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(vel1, velocidade2);
  analogWrite(vel2, velocidade1);
}

void tras( int velocidade1, int velocidade2 ) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(vel1, velocidade2);
  analogWrite(vel2, velocidade1);
}

void esquerda( int velocidade1, int velocidade2 ) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(vel1, velocidade2);
  analogWrite(vel2, velocidade1);
}

void direita( int velocidade1, int velocidade2 ) {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(vel1, velocidade2);
  analogWrite(vel2, velocidade1);
}

void printarSensores() {
  Serial.print("S1: ");
  Serial.print(analogRead(s1));
  Serial.print(" ");

  Serial.print("S2: ");
  Serial.print(analogRead(s2));
  Serial.print(" ");

  Serial.print("S3: ");
  Serial.print(analogRead(s3));
  Serial.print(" ");

  Serial.print("S4: ");
  Serial.print(analogRead(s4));
  Serial.print(" ");

  Serial.print("S5: ");
  Serial.print(analogRead(s5));
  Serial.print(" ");

  Serial.print("S6: ");
  Serial.print(analogRead(s6));
  Serial.print(" ");

  Serial.print("S7: ");
  Serial.print(analogRead(s7));
  Serial.println(" ");

  delay(1);
}

void printarUltrassom(){
  Serial.print("US FRENTE: ");
  Serial.print(usFrente.read());
  delay(100);
  Serial.print(" US DIREITA: ");
  Serial.print(usLateralDireita.read());
  delay(100);
  Serial.print(" US ESQUERDA: ");
  Serial.println(usLateralEsquerda.read());
  delay(300);
}

void testarTilt(){
  Serial.print(digitalRead(tiltDescida));
  Serial.print(" ");
  Serial.println(digitalRead(tiltSubida));
}

void lerSensores() {
  sensor1 = analogRead(s1);
  sensor2 = analogRead(s2);
  sensor3 = analogRead(s3);
  sensor4 = analogRead(s4);
  sensor5 = analogRead(s5);
  sensor6 = analogRead(s6);
  sensor7 = analogRead(s7);
}

void pararEler() {
  while (true) {
    frente(0, 0);
    lerSensores();
    printarSensores();
    delay(500);
  }
}

void sambar(){
  while(true){
    esquerda(255,255);
    delay(800);
    direita(255,255);
    delay(800);
  }
}
