int dirPin = 2; // pin that controls direction
int stepPin = 3; //pin that controls stepping

int setPoint; // desired position
int currentHeight = 0; // estimated current height (last setPoint)
int error = 0; // initialize error
const int INTERVALS = 50; // number of intervals to split up full height into
int sensorVal = 0; 

const int NUMBERSAMPLES = 3;
int samples[NUMBERSAMPLES] = {0};
int pointerInSamples = 0;

const int STEPS = 10000; // total number of microsteps from all the way down to all the way up - CALIBRATE

void setup() { //declare Outputs
pinMode(dirPin, OUTPUT); //direction
pinMode(stepPin, OUTPUT); 
}

// Moving average filter
void addSample(int newSample){

  samples[pointerInSamples] = newSample;
  if(pointerInSamples == (NUMBERSAMPLES - 1)){
  pointerInSamples = 0;
  }
   else pointerInSamples++;
} 

// average values
int getAverage() {
 int sum = 0;
  for (int i =0 ; i<NUMBERSAMPLES; i++){
 sum = samples[i] + sum;
 }
 int avg = sum/NUMBERSAMPLES;
  Serial.print("  sum = ");      
  Serial.println(sum); 
 return avg;
}

void changeHeight(){
  if (error > 0){
     digitalWrite(dirPin, HIGH);     // Set the direction
  }
  else {
    digitalWrite(dirPin, LOW);     // Set the opposite direction
  }
  for (int i = 0; i < abs(STEPS*error)/INTERVALS; i++)
  {      
    digitalWrite(stepPin, LOW);  // This LOW to HIGH change is what creates the
    digitalWrite(stepPin, HIGH); // "Rising Edge" so the easydriver knows to when to step.
    delayMicroseconds(470);      // Delay time - ~270 is fastest before stalling (short=fast)
  } 
}


//main loop
void loop() {
  
  sensorVal = analogRead(A0);    // read the value from the sensor:
  
  addSample(sensorVal);
  //getAverage();
  setPoint = map(getAverage(), 0, 1023, 0, INTERVALS); //map value from potentiometer to 
  error = setPoint - currentHeight;    //calculate error
  changeHeight();         // change the height based on the total number of steps and the number of intervals
  
  // print the results to the serial monitor:     
 Serial.println(setPoint);  
  
  currentHeight += error; //set current height to setpoint, which assumes you reached the setpoint via the open loop control
  delay(100); //milliseconds


             
}
