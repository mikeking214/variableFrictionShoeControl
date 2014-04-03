int dirpin = 2;
int steppin = 3;
int currentPos = 0;
int maxSteps = 2000;
int error = 0;
int potVal = 0;
int reqPos = 0;

void moveStepper(int steps)
{
  if(steps < 0){
    digitalWrite(dirpin, LOW);     // Set the direction. 
    steps = -steps;
  }else{
    digitalWrite(dirpin, HIGH);     // Set the direction.
  }
  int i = 0;
  for(i = 0; i < steps*1000; i++){
    digitalWrite(steppin, LOW);  // This LOW to HIGH change is what creates the
    digitalWrite(steppin, HIGH); // "Rising Edge" so the easydriver knows to when to step.
    delayMicroseconds(500);      // This delay time is close to top speed for this
  }
}

void setup() 
{
  pinMode(dirpin, OUTPUT);
  pinMode(steppin, OUTPUT);
}
void loop()
{
  potVal = analogRead(A0);
  
  reqPos = map(potVal, 0, 1023, 0, 9);
  error = reqPos - currentPos;
  currentPos += error;
  moveStepper(error);
  Serial.println(currentPos);
  delay(1000);
}


