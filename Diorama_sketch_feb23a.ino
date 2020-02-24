/**********************************************
 *  Diorama Sketch 14Feb2020-d                *
 *  ESP32                                     *
 *  David Sparks                              *
 *  Demonstration: toggle LED on/off          *
 *  when corresponding pin is touched.        *
 **********************************************/

// array of GPIOs used for LEDs
char led[] = {16, 17, 5, 18, 19, 21, 22, 23};
// array of GPIO touch pin numers
char touch[] = {4, 15, 13, 12, 14, 27, 32, 33};
// array of time-out records for LED auto-off 
unsigned long ledTimer[8];
// variables used by touch pin interrupt handlers
bool touch0detected = false;
bool touch1detected = false;
bool touch2detected = false;
bool touch3detected = false;
bool touch4detected = false;
bool touch5detected = false;
bool touch6detected = false;
bool touch7detected = false;
// prototype function to manage LEDs
void toggleLED(int index, unsigned long lastTouch);
// prototype function to determine touch sense threshhold
int touchThreshold(int touchIndex);
// 
void setup() {
  // local variables
  int counter;
  // init the LED I/O pins and the pin time-out array
  for (counter = 0; counter < 8; counter++) {
    pinMode(led[counter], OUTPUT);
    digitalWrite(led[counter], LOW);
    ledTimer[counter] = 0;
  }
  // establish the length of a touch measurement
  touchSetCycles(5000,5000);
  // for each of the touch pins,
  // establish a touch threshhold based on its untouched level
  // then register its touch interrupt handler
  touchAttachInterrupt(touch[0], onTouch_0, touchThreshhold(0));
  touchAttachInterrupt(touch[1], onTouch_1, touchThreshhold(1));
  touchAttachInterrupt(touch[2], onTouch_2, touchThreshhold(2));
  touchAttachInterrupt(touch[3], onTouch_3, touchThreshhold(3));
  touchAttachInterrupt(touch[4], onTouch_4, touchThreshhold(4));
  touchAttachInterrupt(touch[5], onTouch_5, touchThreshhold(5));
  touchAttachInterrupt(touch[6], onTouch_6, touchThreshhold(6));
  touchAttachInterrupt(touch[7], onTouch_7, touchThreshhold(7));
  // cycle the LEDs to indicate setup completion
  // turn them on
  for (counter = 0; counter < 8; counter++) {
    digitalWrite(led[counter], HIGH);
    delay(100);
  }
  delay(1000);
  // turn them off
  for (counter = 0; counter < 8; counter++) {
    digitalWrite(led[counter], LOW);
    delay(100);
  }
}

void loop() {
  // local variables
  int counter;
  int timeOutInterval = 10000;  // 10 seconds
  unsigned long now;
  now = millis();
  //
  // test the interrupts
  if (touch0detected) {
    toggleLED(0, now);
    touch0detected = false;
  }
  //
  if (touch1detected) {
    toggleLED(1, now);
    touch1detected = false;
  }
  //
  if (touch2detected) {
    toggleLED(2, now);
    touch2detected = false;
  }
  //
  if (touch3detected) {
    toggleLED(3, now);
    touch3detected = false;
  }
  //
  if (touch4detected) {
    toggleLED(4, now);
    touch4detected = false;
  }
  //
  if (touch5detected) {
    toggleLED(5, now);
    touch5detected = false;
  }
  //
  if (touch6detected) {
    toggleLED(6, now);
    touch6detected = false;
  }
  //
  if (touch7detected) {
    toggleLED(7, now);
    touch7detected = false;
  }
  // survey the timers to
  // impose a rule that LEDs go dark
  // ten seconds after lighting up
  for (counter = 0; counter < 8; counter++) {
    // Two-part test:
    // 1. are we timing the LED?
    // AND
    // 2. has it timed out?
    if ((ledTimer[counter] != 0) &&
        (now - ledTimer[counter] > timeOutInterval) )
    {
      // both tests return TRUE
      // turn off the LED due to time-out
      digitalWrite(led[counter], LOW);
      // and zero the timer
      ledTimer[counter] = 0;
    }
  }
}

// "unbounce" the touch pin:
// turn a LED on or off only if 1/2 second has elapsed
// since the last time the corresponding touch pin was touched
// note: keeping the pin touched will blink the LED at 1/2-second intervals
void toggleLED(int index, unsigned long touchTime) {
  static unsigned long lastTouch[8];
  // print a notice of pin touched
  Serial.print("\nPin "); Serial.print(index);
  Serial.println(" touched.");
  // process pin only if 500 millis since previous touch
  if (touchTime - lastTouch[index] > 500) {
    // test returns TRUE; we shall process the pin.
    Serial.println("Toggling the LED.");
    // first update the lastTouch value
    lastTouch[index] = touchTime;
    // is the LED turned on?
    if (digitalRead(led[index]) == HIGH) {
      // turn it off
      digitalWrite(led[index], LOW);
      // and reset the timer
      ledTimer[index] = 0;
    } else {
      // turn the LED on
      digitalWrite(led[index], HIGH);
      // and start the timer
      ledTimer[index] = millis();
    }
  }
}

// return a touch sense threshhold value 
// below a pin's untouched value
// right now just return a constant 25
// I don't know why that value works for me?
// plan further work to calibrate this value
int touchThreshhold(int touchIndex) {
  return 25;
}

// Here are the touch event interrupt handlers

void onTouch_0() {
  touch0detected = true;
}

void onTouch_1() {
  touch1detected = true;
}

void onTouch_2() {
  touch2detected = true;
}

void onTouch_3() {
  touch3detected = true;
}

void onTouch_4() {
  touch4detected = true;
}

void onTouch_5() {
  touch5detected = true;
}

void onTouch_6() {
  touch6detected = true;
}

void onTouch_7() {
  touch7detected = true;
}
