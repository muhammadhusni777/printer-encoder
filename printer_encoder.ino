//////////////////////////////////////////////////////////////
////Implementing differential math using printer encoder/////
////written by : Muhammad Husni                       //////
///////////////////////////////////////////////////////////



#define encoder0PinA 2
#define encoder0PinB 3
#define encoder0Btn 4
int encoder0Pos = 0;

float Time;
float elapsedTime;
float timePrev;

void setup() {
  Serial.begin(115200);
  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);
  attachInterrupt(0, doEncoder, CHANGE);
}
int x,last_x;
int x_dot, last_x_dot;
int x_dot_dot;
void loop() {

  //direction   
  if(x>last_x)
  {
  Serial.print("  CW");
  }
  
  if(x<last_x)  {
  Serial.print("  CCW");
  }
  
  //got position value from interrupt
  //pulse
  Serial.print(" position : ");
  Serial.print(x);

  //got velocity/speed value from position using numerical derivation
  //pulse per second
  x_dot = (x-last_x)/elapsedTime;
  Serial.print(" speed : ");
  Serial.print(x_dot);
  last_x = x;
  
  //got acceleration value from velocity using numerical derivation
  //pulse per second square
  x_dot_dot = (x_dot-last_x_dot)/elapsedTime;
  Serial.print(" acceleration : ");
  Serial.print(x_dot_dot);
  last_x_dot = x_dot;
  Serial.println(" ");
  delay(250);

  //TIMER
  timePrev = Time;                            // the previous time is stored before the actual time read
  Time = millis();                            // actual time read
  elapsedTime = (Time - timePrev) / 1000;
}


//position value interrupt
void doEncoder()
{
  if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB))
  {
  encoder0Pos++;
  }
  else
  {
  encoder0Pos--;
  }
  x = encoder0Pos/2.5;
}
