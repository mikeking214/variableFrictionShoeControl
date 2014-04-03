int dirPin = 2; // pin that controls direction
int stepPin = 3; //pin that controls stepping

int setPoint; // desired position
int currentHeight = 0; // estimated current height (last setPoint)
int error = 0; // initialize error
const int INTERVALS = 20; // number of intervals to split up full height into
int sensorVal = 0; 

// MOVING AVERAGE VARIABLES
const int NUMBERSAMPLES = 3;
int samples[NUMBERSAMPLES] = {0};
int pointerInSamples = 0;

const int STEPS = 3000; // total number of microsteps from all the way down to all the way up - CALIBRATE - 8666 is max steps

void setup() { //declare Outputs
pinMode(dirPin, OUTPUT); //direction
pinMode(stepPin, OUTPUT); 
}

// MOVING SAMPLE
void addSample(int newSample){
  samples[pointerInSamples] = newSample;
  if(pointerInSamples == (NUMBERSAMPLES - 1)){
  pointerInSamples = 0;
  }
   else pointerInSamples++;
} 

// AVERAGE VALUES
int getAverage() {
 int sum = 0;
  for (int i =0 ; i<NUMBERSAMPLES; i++){
 sum = samples[i] + sum;
 }
 int avg = sum/NUMBERSAMPLES;
 return avg;
}

// CHANGE THE HEIGHT WITH OPEN LOOP CONTROL
void changeHeight(){
  if (error > 0){
     digitalWrite(dirPin, LOW);     // Set the direction
  }
  else {
    digitalWrite(dirPin, HIGH);     // Set the opposite direction
  }
  for (int i = 0; i < abs(STEPS*error)/INTERVALS; i++)
  {      
    digitalWrite(stepPin, LOW);  // This LOW to HIGH change is what creates the
    digitalWrite(stepPin, HIGH); // "Rising Edge" so the easydriver knows to when to step.
    delayMicroseconds(470);      // Delay time. ~270 is fastest before stalling with 12V (short=fast)
  } 
}


// MAIN LOOP
void loop() {
  
  addSample(analogRead(A0));          // read the value from the sensor and add it to the moving sample
  setPoint = map(getAverage(), 0, 1023, 0, INTERVALS); // map the average value from the potentiometer to the desired # of intervals
  error = setPoint - currentHeight;    // calculate the proportional error
  changeHeight();         // change the height based on the total number of steps and the number of intervals
  
  // print the results to the serial monitor:     
 Serial.println(setPoint);   // prints the desired interval
  
  currentHeight += error; //add the error to the current height, which assumes you reached the setpoint via the open loop control
  delay(100); // in milliseconds
             
}
