//Motor Pins
int leftup = 8;
int rightup = 5;
int leftdown = 7;
int rightdown = 6;

#define FAST 190
#define SLOW 95
#define OFF 0

int sensor=13;
int echo=0;
int inches=0;

void setup() {
  Serial.begin(9600);
  pinMode(sensor,OUTPUT);
  
  pinMode(leftup,OUTPUT);
  pinMode(rightup,OUTPUT);
  pinMode(leftdown,OUTPUT);
  pinMode(rightdown,OUTPUT);
 
}

void motion(int a)
{
  switch(a)
  {
    case 0: //STOP
    //  Serial.println("HI!");
      analogWrite(leftup,FAST);
      analogWrite(rightup,FAST);
      analogWrite(leftdown,FAST);
      analogWrite(rightdown,FAST);
      //Serial.println("HI2!");
      break;
    
    case 1: //FORWARD
      analogWrite(leftup,FAST);
      analogWrite(rightup,FAST);
      analogWrite(leftdown,OFF);
      analogWrite(rightdown,OFF);
      break;
      
    case 2: //BACKWARD
      analogWrite(leftup,OFF);
      analogWrite(rightup,OFF);
      analogWrite(leftdown,SLOW);
      analogWrite(rightdown,SLOW);
      break;
    
    case 3: // POWER RIGHT
      analogWrite(leftup,FAST);
      analogWrite(rightup,OFF);
      analogWrite(leftdown,OFF);
      analogWrite(rightdown,FAST);
      break;
          
    case 4: // POWER LEFT
      analogWrite(leftup,OFF);
      analogWrite(rightup,FAST);
      analogWrite(leftdown,FAST);
      analogWrite(rightdown,OFF);
      break;
          
  }//Switch case end bracket
  
}

unsigned long ping()
{
  pinMode(sensor,OUTPUT);
  digitalWrite(sensor,LOW);
  delayMicroseconds(2);
  digitalWrite(sensor,HIGH);
  delayMicroseconds(5);
  digitalWrite(sensor,LOW);
  pinMode(sensor,INPUT);  //switch to input
  digitalWrite(sensor,HIGH); //turn on pullup resistor
  echo=pulseIn(sensor,HIGH);  //listen for echo
  inches=(echo/58.138)*(.39); //convert to inches
  return inches;
}

void loop()
{
int x=0;
x=ping();
delay(250);//delay 1/4 seconds
while (x<=10)
{
  x=ping();
  motion(4);
  delay(50);
}
motion(1);

}




