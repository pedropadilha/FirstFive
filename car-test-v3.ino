const byte btnInterrupt = 2;

const byte leitor1 = 7;
const byte leitor2 = 8;

const byte ledMode = 13;

boolean mode = false;

int leftSensor = 0;
int middleSensor = 1;
int rightSensor = 2;

int WAIT_TIME = 9;
int WAIT_TIME_CURVA = 3;

int DIREITA_FRENTE = 6;
int DIREITA_ATRAS = 5;

int ESQUERDA_FRENTE = 9;
int ESQUERDA_ATRAS = 10;

int _direction;

int anda = 140;
int andacurva = 40;
int andacurva2 = 20;

void setup() {
  Serial.begin(9600);

  pinMode(ledMode, OUTPUT);

  pinMode(leitor1, INPUT);
  pinMode(leitor2, INPUT);

  pinMode(btnInterrupt, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(btnInterrupt), changeMode, FALLING);
  
  pinMode(DIREITA_FRENTE, OUTPUT);
  pinMode(DIREITA_ATRAS, OUTPUT);

  pinMode(ESQUERDA_FRENTE, OUTPUT);
  pinMode(ESQUERDA_ATRAS, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

void loop() {

  while (mode) {
    digitalWrite(ledMode, HIGH);
    
    int leitura1 = digitalRead(leitor1);
    int leitura2 = digitalRead(leitor2);

    if (leitura1 == 0 && leitura2 == 0) {
      Serial.println("Parado");
      analogWrite(DIREITA_FRENTE, LOW);
      analogWrite(ESQUERDA_FRENTE, LOW);
    }
    
    else if (leitura1 == 0 && leitura2 == 1) {
      Serial.println("Esquerda");
      analogWrite(ESQUERDA_FRENTE, 100);
      analogWrite(DIREITA_FRENTE, 50);
      delay(WAIT_TIME_CURVA);
      analogWrite(ESQUERDA_FRENTE, LOW);
      analogWrite(DIREITA_FRENTE, LOW);
    }
    
    else if (leitura1 == 1 && leitura2 == 0) {
      Serial.println("Direita");
      analogWrite(DIREITA_FRENTE, 100);
      analogWrite(ESQUERDA_FRENTE, 50);
      delay(WAIT_TIME_CURVA);
      analogWrite(DIREITA_FRENTE, LOW);
      analogWrite(ESQUERDA_ATRAS, LOW);
    }
    
    else if (leitura1 == 1 && leitura2 == 1) {
      Serial.println("Frente");
      moveForward();
    }

  }

  digitalWrite(ledMode, LOW);

  // Leitura inicial dos sensores
  updateSensors();

  // Enquanto estiver 'reto'
  while(leftSensor==0 && middleSensor==1 && rightSensor==0) {
    // Anda para frente
    moveForward();

    // Lê novamente os sensores
    updateSensors();
  }

  // Determina a nova direção
  _direction = determineNewDirection();

  // Se move conforme a nova direção
  switch (_direction) {
    case 1:
      turnLeft();
      break;
    case 2:
      turnRight();
      break;
  }

}

void updateSensors() {
  leftSensor = getLeftRead();
  middleSensor = getMiddleRead();
  rightSensor = getRightRead();
  
  if(leftSensor > 500) {
    leftSensor = 1; 
  } else {
    leftSensor = 0;  
  }

  if(rightSensor > 500) {
    rightSensor = 1; 
  } else {
    rightSensor = 0;  
  }

  if(middleSensor > 500) {
    middleSensor = 1; 
  } else {
    middleSensor = 0;  
  }

}

int getLeftRead() {
  int leitura = analogRead(A0);
  return leitura;
}

int getMiddleRead() {
  int leitura = analogRead(A1);
  return leitura;
}

int getRightRead() {
  int leitura = analogRead(A2);
  return leitura;
}

void moveForward() {

  analogWrite(DIREITA_FRENTE, anda);
  analogWrite(ESQUERDA_FRENTE, anda);
  delay(WAIT_TIME);
  analogWrite(DIREITA_FRENTE, LOW);
  analogWrite(ESQUERDA_FRENTE, LOW);

}

int determineNewDirection() {
  int result = 0;
  
  updateSensors();

  if(leftSensor==1 && rightSensor==0) {
    result = 1;  
  } else if(rightSensor==1 && leftSensor==0) {
    result = 2;  
  }

  return result;
}

void turnLeft() {
  analogWrite(DIREITA_FRENTE, andacurva);
  analogWrite(ESQUERDA_ATRAS, andacurva2);
  delay(WAIT_TIME_CURVA);
  analogWrite(DIREITA_FRENTE, LOW);
  analogWrite(ESQUERDA_ATRAS, LOW);
}

void turnRight() {
  analogWrite(ESQUERDA_FRENTE, andacurva);
  analogWrite(DIREITA_ATRAS, andacurva2);
  delay(WAIT_TIME_CURVA);
  analogWrite(ESQUERDA_FRENTE, LOW);
  analogWrite(DIREITA_ATRAS, LOW);
}

void changeMode() {
  static unsigned long lastInterrupt = 0;
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterrupt > 200) {
    mode = !mode;
  }
  lastInterrupt = interruptTime;
}
