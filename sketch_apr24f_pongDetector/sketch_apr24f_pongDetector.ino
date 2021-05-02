#include <KnockDetector.h>


//TODO
//- Start game using secret knock.
//- Start new round using secret knock. Maybe dribble, then wait 3 seconds and clear?
//- Or just make two buttons under the table


const int piezoInputPinOne = A0;
const int piezoInputPinTwo = A7;
//const int piezoInputPins[2] = {A0, A7}; //using a constant would keep you from making your error

//TIMING
int timeThreshold = 5000; // maximum amount of time allowed between knocks
unsigned long firstEventAt;
unsigned long secondEventAt;
unsigned long timeBetweenEvents;
bool weAreTiming;


//Need to play a round and gather data to see what the threshold should actually be.
//const int pulseLength = 12345;
const int intensityThreshold = 2;

int rallyPoints = 0;
int p1 = 0;
int p2 = 0;

//Last known postion 0->p1 1->p2
int lkp = 10;


void callback(float knockIntensity, long pulseLength) {

  if (knockIntensity >= intensityThreshold) {
    rallyPoints = rallyPoints + 1;
    //  Serial.println("Knock detected!");
    //  Serial.print("Pulse length: ");
    //  Serial.println(pulseLength);
    Serial.print("Intensity: ");
    Serial.println(knockIntensity);
    (lkp == 0) ? Serial.print("Left ") : Serial.print("Right ");
    Serial.println(lkp);

    if (!weAreTiming) {
      weAreTiming = true;
      firstEventAt = millis();
//      Serial.print(" start ");
//      Serial.println(firstEventAt);
    }
    else {
      secondEventAt = millis();
      // Serial.println(secondEventAt);
      timeBetweenEvents = secondEventAt - firstEventAt;
      Serial.print("  Time between events ");
      Serial.println(timeBetweenEvents);

      if (weAreTiming && (timeBetweenEvents >= timeThreshold)) {
        if (lkp == 0) {
          p1 = p1 + rallyPoints;
          Serial.print("**RALLY OVER** Added Points: ");
          Serial.println(rallyPoints);
          Serial.print("**RALLY OVER** (Left)Player 1 Total Points: ");
          Serial.println(p1);
          Serial.print("**RALLY OVER** (Right)Player 2 Total Points: ");
          Serial.println(p2);
        } else if (lkp == 1) {
          p2 = p2 + rallyPoints;
          Serial.print("**RALLY OVER** (Right)Player 2 Total Points: ");
          Serial.println(p2);
        }
        Serial.print("Current Rally Points: ");
        Serial.println(rallyPoints);
        rallyPoints = 0;

        Serial.println();
      }

      weAreTiming = false;
    }


  }
}
//These numbers are -> (int lowThreshold, int noiseThreshold, int pin, CALLBACK)
KnockDetector knockDetector(20, 5, callback);


void setup() {
  Serial.begin(115200);
  //  pinMode(buttonPin, INPUT);
}

void loop() {
  if (analogRead(piezoInputPinOne) > 1) {
    lkp = 0;
    knockDetector.loop(analogRead(piezoInputPinOne));
  }
  else if (analogRead(piezoInputPinTwo) > 1 ) {
    lkp = 1;
    knockDetector.loop(analogRead(piezoInputPinTwo));
  }


  //  for (byte y = 0; y < 2; y++) {
  //    knockDetector.loop(analogRead(piezoInputPins[y]));
  //
  //  }


  //  if (knockDetector.available()) {
  //  for (byte y = 0; y < 2; y++)
  //    {
  //      result[y] =
  //      Serial.print("\t test ");
  //      Serial.print(result[y]);
  //
  //    }
  //  }

}
