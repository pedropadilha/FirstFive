#define countof(X) (sizeof(X) / sizeof(X[0]))

int leftSensor = 0;
int middleSensor = 1;
int rightSensor = 2;

int DIREITA_FRENTE = 5;
int DIREITA_ATRAS = 6;

int ESQUERDA_FRENTE = 9;
int ESQUERDA_ATRAS = 10;

int _direction;

int tentativasBack = 0;


void setup()
{
  Serial.begin(9600);
  
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

void loop()
{

  // Leitura inicial dos sensores
  updateSensors();

  // Enquanto estiver 'reto'
  while(leftSensor==0 && middleSensor==1 && rightSensor==0)
  {
    // Anda para frente
    moveForward();

    // Lê novamente os sensores
    updateSensors();
  }

  // Determina a nova direção
  _direction = determineNewDirection();

  // Se move conforme a nova direção
  switch (_direction) {
    case 0:
      if(tentativasBack>4)
      {
        tentativasBack = 0;
        moveBack();
      } else {
        tentativasBack++;
      }
      break;
    case 1:
      turnLeft();
      break;
    case 2:
      turnRight();
      break;
  }

}

void updateSensors()
{
  leftSensor = getLeftRead();
  middleSensor = getMiddleRead();
  rightSensor = getRightRead();
  
  if(leftSensor > 500)
  {
    leftSensor = 1; 
  } else {
    leftSensor = 0;  
  }

  if(rightSensor > 500)
  {
    rightSensor = 1; 
  } else {
    rightSensor = 0;  
  }

  if(middleSensor > 500)
  {
    middleSensor = 1; 
  } else {
    middleSensor = 0;  
  }

  Serial.print(leftSensor);
  Serial.print("|");
  Serial.print(middleSensor);
  Serial.print("|");
  Serial.println(rightSensor);
}

int getLeftRead() 
{
  //TODO: trocar pela leitura do sensor da esquerda
  //return testTrack[_step][0];
  int leitura = analogRead(A0);
  Serial.print( "esquerda= " );
  Serial.println( leitura );
  return leitura;
}

int getMiddleRead() 
{
  //TODO: trocar pela leitura do sensor do meio
  //return testTrack[_step][1];
  int leitura = analogRead(A1);
  Serial.print( "meio= " );
  Serial.println( leitura );
  return leitura;
}

int getRightRead() 
{
  //TODO: trocar pela leitura do sensor da direita
  //return testTrack[_step][2];
  int leitura = analogRead(A2);
  Serial.print( "direita= " );
  Serial.println( leitura );
  return leitura;
}

void moveForward()
{
  //TODO: trocar pela gravação do byte na porta c, para ambos motores andarem ao mesmo tempo
  Serial.println( "andando para frente" );

  digitalWrite(DIREITA_FRENTE, HIGH);
  digitalWrite(ESQUERDA_FRENTE, HIGH);
  delay(20);
  digitalWrite(DIREITA_FRENTE, LOW);
  digitalWrite(ESQUERDA_FRENTE, LOW);

}

void moveBack()
{
  //TODO: trocar pela gravação do byte na porta c, para ambos motores andarem ao mesmo tempo
  Serial.println( "andando para trás" );

  digitalWrite(DIREITA_ATRAS, HIGH);
  digitalWrite(ESQUERDA_ATRAS, HIGH);
  delay(20);
  digitalWrite(DIREITA_ATRAS, LOW);
  digitalWrite(ESQUERDA_ATRAS, LOW);
  
}

int determineNewDirection()
{
  int result = 0;

  //TODO: colocar em um loop de forma a garantir a leitura correta
  
  updateSensors();

  if(leftSensor==1 && rightSensor==0)
  {
    result = 1;  
  } else if(rightSensor==1 && leftSensor==0)
  {
    result = 2;  
  }

  return result;
}

void turnLeft()
{
  //TODO: trocar pela gravação do byte na porta c, para acionar o motor da direita
  Serial.println( "vira para esquerda" );
  
  // Gira para esquerda
  digitalWrite(DIREITA_FRENTE, HIGH);
  delay(20);
  digitalWrite(DIREITA_FRENTE, LOW);

}

void turnRight()
{
  //TODO: trocar pela gravação do byte na porta c, para acionar o motor da esquerda
  Serial.println( "vira para direita" );

  // Gira para esquerda
  digitalWrite(ESQUERDA_FRENTE, HIGH);
  delay(20);
  digitalWrite(ESQUERDA_FRENTE, LOW);

}

