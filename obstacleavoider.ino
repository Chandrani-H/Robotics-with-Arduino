//The wheeled bot moves forward until it detects an obstacle and avoids it by moving left.

//These are the pins that I used to connect the motors connected wheels of the chassis to the arduino
//Motor Pins
int leftup = 8;
int rightup = 5;
int leftdown = 7;
int rightdown = 6;

#define FAST 190
#define SLOW 95
#define OFF 0

int sensor=13; //Pin used for sensor that detects the obstacle
int echo=0;
int inches=0;
//setup() function initializes and sets the initial values
void setup() {
  Serial.begin(9600);
  //The following pins are all used as OUTPUT PINS
  pinMode(sensor,OUTPUT);
  pinMode(leftup,OUTPUT);
  pinMode(rightup,OUTPUT);
  pinMode(leftdown,OUTPUT);
  pinMode(rightdown,OUTPUT);
 
}

//This function is called in a loop
void motion(int a) 
{
  switch(a)
  {
    case 0: //STOP
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
  pinMode(sensor,OUTPUT);		//sensor mode is OUTPUT
  digitalWrite(sensor,LOW);	//sensor outputs LOW
  delayMicroseconds(2);			//for 2 microseconds
  digitalWrite(sensor,HIGH);	//sensor outputs HIGH
  delayMicroseconds(5);			//for 5 microseconds
  digitalWrite(sensor,LOW);	//changing sensor output to LOW again
  pinMode(sensor,INPUT);  		//switching sensor MODE to INPUT
  digitalWrite(sensor,HIGH); 	//turn on pullup resistor
  echo=pulseIn(sensor,HIGH);  //listening for echo
  inches=(echo/58.138)*(.39); //converting distance into inches
  return inches;
}

//The loop() function does precisely what its name suggests, and loops consecutively, allowing your program to change and respond.
void loop()
{
int x=0;
x=ping();		
delay(250);    //delay 1/4 seconds
while (x<=10)  //If the distance between the bot and obstacle is <= 10 inches, it turns left
{
  x=ping();
  motion(4);   //turning left
  delay(50);	//Delay to allow the bot to turn
}
motion(1);		//If no obstacle, move forward

}





