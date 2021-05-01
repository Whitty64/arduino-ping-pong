
//TODO
//- Start game using secret knock.
//- Start new round using secret knock. Maybe dribble, then wait 3 seconds and clear?
//- Or just make two buttons under the table


#include <KnockDetector.h>

//const int buttonPin = A8;     // the number of the pushbutton pin
//int buttonState = 0;         // variable for reading the pushbutton status


const int piezoInputPin = A0;
int piezoInputSignal = 0;

//Need to play a round and gather data to see what the threshold should actually be.
//const int pulseLength = 12345;
const int intensityThreshold = 2;


const int timeThreshold = 5000; // maximum amount of time allowed between knocks
int previousRunTime = 0;  // tracks time between knocks


int rallyPoints = 0 * 2;
int p1 = 0;
int p2 = 0;


//Last known postion 0->p1 1->p2
int lkp = 0;

//void onKnockReceived(float knockIntensity, long pulseLength) {
//  runTime = millis();
//  Serial.print("Timer Started ");
//  Serial.println(runTime);
//}

void callback(float knockIntensity, long pulseLength) {

  if (knockIntensity >= intensityThreshold) {
    rallyPoints = rallyPoints + 1;
    
    int currentRunTime = millis();
    Serial.print("Timer Started ");
    Serial.println(runTime);
  }

  //  Serial.println("Knock detected!");
  //  Serial.print("Intensity: ");
  //  Serial.println(knockIntensity);
  //  Serial.print("Pulse length: ");
  //  Serial.println(pulseLength);
  Serial.print("Rally Points: ");
  Serial.println(rallyPoints);

  if (runTime > timeThreshold ) {
    Serial.println("Exceeded Threshold");
    runTime = 0;
    if (lkp == 0) {
      p1 = p1 + rallyPoints;
      Serial.print("Player 1: ");
      Serial.println(p1);
    } else if (lkp == 1) {
      p2 = p2 + rallyPoints;
      Serial.print("Player 2: ");
      Serial.println(p2);
    }
    //    rallyPoints = 0;

  }
}

KnockDetector knockDetector(20, 5, callback);

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
}

void loop() {
  knockDetector.loop(analogRead(piezoInputPin));

  //  Start a timer once a ralley has started.
  //  if (rallyPoints > 0) {
  //    runTime = millis();

  //  If the time between two seperate knocks is greater than 5 seconds, then add the points to the correct players total.
  //    if((runTime > timeThreshold) && (lkp == 0) ) {
  //      p1 = p1 + rallyPoints;
  //      Serial.print("Player 1: ");
  //      Serial.println(p1);
  //    }
  //    else if((runTime > timeThreshold) && (lkp == 1) ) {
  //      p2 = p2 + rallyPoints;
  //      Serial.print("Player 2: ");
  //      Serial.println(p2);
  //    }
  //  }

  //  buttonState = digitalRead(buttonPin);
  //  if (buttonState == HIGH) {
  //    p1 = p1 + rallyPoints;
  //    Serial.print("Button Pressed P1: ");
  //    Serial.println(p1);
  //  }
  //  else {
  //
  //  }

}
