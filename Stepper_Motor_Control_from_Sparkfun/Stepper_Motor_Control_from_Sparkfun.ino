//This code controls a stepper motor with the 
//EasyDriver board. It spins forwards and backwards
//***************************/
int dirpin = 2;
int steppin = 3;

void setup() 
{
pinMode(dirpin, OUTPUT);
pinMode(steppin, OUTPUT);
}
void loop()
{

  int i;

  digitalWrite(dirpin, LOW);     // Set the direction.
  delay(100);


  for (i = 0; i<4000; i++)       // Iterate for 4000 microsteps.
  {
    digitalWrite(steppin, LOW);  // This LOW to HIGH change is what creates the
    digitalWrite(steppin, HIGH); // "Rising Edge" so the easydriver knows to when to step.
    delayMicroseconds(470);      // Delay time - ~270 is fastest before stalling (short=fast)
  }                            

  digitalWrite(dirpin, HIGH);    // Change direction.
  delay(100);


  for (i = 0; i<4000; i++)       // Iterate for 4000 microsteps
  {
    digitalWrite(steppin, LOW);  // This LOW to HIGH change is what creates the
    digitalWrite(steppin, HIGH); // "Rising Edge" so the easydriver knows to when to step.
    delayMicroseconds(470);      // Delay time - ~270 is fastest before stalling (short=fast)
  }                              

}
