#define countof(X) (sizeof(X) / sizeof(X[0]))

// variáveis que representam as leituras dos sensores
int leftSensor = 0;
int rightSensor = 0;
int middleSensor = 0;

// Proxima direção a virar
int _direction;

// Usado apenas para test com pista 'virtual'
int _step = 0;

// int testTrack[][3] = { {0,1,0} , {0,1,0}, {0,1,0}, {0,1,1}, {0,1,1}, {0,1,0}, {0,1,0}, {1,1,0}, {1,1,0}, {0,1,0}, {0,1,0}, {0,1,0} };
int testTrack[][3] = { {0,1,0} , {0,1,0}, {1,1,0}, {0,1,1}, {0,1,1}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {1,1,0}, {1,1,0}, {0,1,0} };

void setup()
{
  Serial.begin(9600);
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

    // Pega a próxima 'instrução'
    _step++;

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

  _step++;

  // Se acabou a pista
  if(_step > countof(testTrack))
  {
    halt();
  }

}

void halt()
{  
  while(true) {};
}

void updateSensors()
{
  leftSensor = getLeftRead();
  rightSensor = getRightRead();
  middleSensor = getMiddleRead();
}

int getLeftRead() 
{
  //TODO: trocar pela leitura do sensor da esquerda
  return testTrack[_step][0];
}

int getMiddleRead() 
{
  //TODO: trocar pela leitura do sensor do meio
  return testTrack[_step][1];
}

int getRightRead() 
{
  //TODO: trocar pela leitura do sensor da direita
  return testTrack[_step][2];
}

void moveForward()
{
  //TODO: trocar pela gravação do byte na porta c, para ambos motores andarem ao mesmo tempo
  Serial.println( "andando para frente" );
}

int determineNewDirection()
{
  int result = 0;

  //TODO: colocar em um loop de forma a garantir a leitura correta
  
  if(testTrack[_step][0] == 1)
  {
    // Esquerda
    result = 1;
  } else if(testTrack[_step][2] == 1)
  {
    // Direita
    result = 2;
  }

  return result;
}

void turnLeft()
{
  //TODO: trocar pela gravação do byte na porta c, para acionar o motor da direita
  Serial.println( "vira para esquerda" );
}

void turnRight()
{
  //TODO: trocar pela gravação do byte na porta c, para acionar o motor da esquerda
  Serial.println( "vira para direita" );
}
