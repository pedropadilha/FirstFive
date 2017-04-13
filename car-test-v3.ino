#define countof(X) (sizeof(X) / sizeof(X[0]))

int leftSensor = 0;
int middleSensor = 1;
int rightSensor = 2;

int QTD_LEITURAS = 10;
int WAIT_TIME = 5;

int DIREITA_FRENTE = 5;
int DIREITA_ATRAS = 6;

int ESQUERDA_FRENTE = 9;
int ESQUERDA_ATRAS = 10;

int _direction;

int DEBUG_MODE = 0;


void setup()
{
  Serial.begin(9600);
  
  pinMode(DIREITA_FRENTE, OUTPUT);
  pinMode(DIREITA_ATRAS, OUTPUT);

  pinMode(ESQUERDA_FRENTE, OUTPUT);
  pinMode(ESQUERDA_ATRAS, OUTPUT);

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
    case 1:
      turnLeft();
      break;
    case 2:
      turnRight();
      break;
  }

  Serial.print("*************");
  Serial.println(millis());

}

void updateSensors()
{
  int leftSensorReadings[QTD_LEITURAS];
  int middleSensorReadings[QTD_LEITURAS];
  int rightSensorReadings[QTD_LEITURAS];

  for(int x=0; x < QTD_LEITURAS; x++)
  {
    leftSensorReadings[x] = getLeftRead();
    middleSensorReadings[x] = getMiddleRead();
    rightSensorReadings[x] = getRightRead();
  }  
  
  leftSensor = calculateFinalReading(leftSensorReadings);
  middleSensor = calculateFinalReading(middleSensorReadings);
  rightSensor = calculateFinalReading(rightSensorReadings);
  
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

  if(DEBUG_MODE)
  {
    Serial.print(leftSensor);
    Serial.print("|");
    Serial.print(middleSensor);
    Serial.print("|");
    Serial.println(rightSensor);
  }
}

int getLeftRead() 
{
  int leitura = analogRead(A0);

  if(DEBUG_MODE)
  {
    Serial.print( "esquerda= " );
    Serial.println( leitura );
  }
  return leitura;
}

int getMiddleRead() 
{
  int leitura = analogRead(A1);

  if(DEBUG_MODE)
  {
    Serial.print( "meio= " );
    Serial.println( leitura );
  }
  return leitura;
}

int getRightRead() 
{
  int leitura = analogRead(A2);

  if(DEBUG_MODE)
  {
    Serial.print( "direita= " );
    Serial.println( leitura );
  }
  return leitura;
}

void moveForward()
{

  if(DEBUG_MODE)
  {
    Serial.println( "andando para frente" );
  }

  /*
  digitalWrite(DIREITA_FRENTE, HIGH);
  digitalWrite(ESQUERDA_FRENTE, HIGH);
  delay(WAIT_TIME);
  digitalWrite(DIREITA_FRENTE, LOW);
  digitalWrite(ESQUERDA_FRENTE, LOW);
  */

  analogWrite(DIREITA_FRENTE, 150);
  analogWrite(ESQUERDA_FRENTE, 150);
  delay(WAIT_TIME);
  analogWrite(DIREITA_FRENTE, LOW);
  analogWrite(ESQUERDA_FRENTE, LOW);

}

int determineNewDirection()
{
  int result = 0;
  
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

  if(DEBUG_MODE)
  {
    Serial.println( "vira para esquerda" );
  }

  // Gira para esquerda
  /*
  digitalWrite(DIREITA_FRENTE, HIGH);
  delay(WAIT_TIME);
  digitalWrite(DIREITA_FRENTE, LOW);
  */

  analogWrite(DIREITA_FRENTE, 150);
  analogWrite(ESQUERDA_ATRAS, 30);
  delay(WAIT_TIME);
  analogWrite(DIREITA_FRENTE, LOW);
  analogWrite(ESQUERDA_ATRAS, LOW);

}

void turnRight()
{

  if(DEBUG_MODE)
  {
    Serial.println( "vira para direita" );
  }

  // Gira para esquerda
  /*  
  digitalWrite(ESQUERDA_FRENTE, HIGH);
  delay(WAIT_TIME);
  digitalWrite(ESQUERDA_FRENTE, LOW);
  */

  analogWrite(ESQUERDA_FRENTE, 150);
  analogWrite(DIREITA_ATRAS, 30);
  delay(WAIT_TIME);
  analogWrite(ESQUERDA_FRENTE, LOW);
  analogWrite(DIREITA_ATRAS, LOW);

}

int calculateFinalReading(int paramArray[])
{
  int leituraFinal = 0;
  
  for(int x=0; x < QTD_LEITURAS; x++)
  {
    leituraFinal += paramArray[x];
  }
  leituraFinal /= QTD_LEITURAS;

  return leituraFinal;
}

