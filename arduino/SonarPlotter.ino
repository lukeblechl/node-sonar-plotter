// Trig calculation help can be found @ 
// http://www.mathsisfun.com/sine-cosine-tangent.html

#include <Servo.h> 
 
Servo myservo;

const int trigPin = 2;
const int echoPin = 4;

int pos = 0;
int sweepTicks = 0;

// Min and max values not set to 0 and 180 b/c servo tends to 
// quickly twitch when going all the way to the end of the sweep
int minSweep = 6; 

// Cheap hobby motor has internal sensor issue that makes it keep 
// floating right slightly.
int maxSweep = 166; 

void setup() 
{ 

  int currSweepDeg = 0;

  myservo.attach(9);
  Serial.begin(9600);

  // Reset servo to 0 position
  Serial.println();
  myservo.write(0);
  delay(1000);

} 

void loop() 
{

  bool incPos = false;
  
  float cosLength,
        cosPercent, 
        currSweepDeg,
        currSweepRad,
        degPerSweepTick,
        duration,
        newDuration, 
        newPingInches, 
        pingInches,
        sinLength,
        sinPercent;
        
  int delayTime,
      verifyXTimes;
     
  delayTime = 20;
  degPerSweepTick = (float)180 / (float)(maxSweep - minSweep);
  pos = minSweep;
  verifyXTimes = 20;

  while(true) {

    myservo.write(pos); 

    // Initial values
    delay(delayTime);   
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
    duration = (float)pulseIn(echoPin, HIGH);
    pingInches = microsecondsToInches(duration);

    for(int x = 0; x < verifyXTimes; x++){
      delay(delayTime);   
      pinMode(trigPin, OUTPUT);
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      pinMode(echoPin, INPUT);
      newDuration = (float)pulseIn(echoPin, HIGH);
      newPingInches = microsecondsToInches(duration);
      duration = (newDuration + duration) / 2;
      pingInches = (newPingInches + pingInches) / 2;
    }

    delay(delayTime);
    
    currSweepDeg = (pos - minSweep) * degPerSweepTick;
    currSweepRad = currSweepDeg * 1000 / 57296;
    sinPercent = sin(currSweepRad);
    cosPercent = cos(currSweepRad);
    sinLength = sinPercent * pingInches;
    cosLength = cosPercent * pingInches;

    Serial.print("[");
    Serial.print(sinLength);
    Serial.print(", ");
    Serial.print(cosLength);
    Serial.print("],");
    Serial.println();

    incPos = ( (pos == minSweep) || (pos == maxSweep) ) ? !incPos : incPos; 
    pos = (incPos) ? ++pos : --pos;
  }
}

float microsecondsToInches(float microseconds) 
{
  return microseconds / 74.000 / 2.000;
}
