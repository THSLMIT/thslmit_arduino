/* Button States for WATZ Firmware */

/*
[Button Mapping Key]
22 - Left Select
24 - Right Select
*/

void checkButtonState() {
  leftSelectBS();
}

void leftSelectBS() {
  int state = digitalRead(leftSelect);
  if (state != leftLState) leftDTime = millis();
  
  if ((millis() - leftDTime) > delayTime) {
    if (state != leftState) {
      leftState = state;
      if (leftState = HIGH) Serial.println("Button Pressed!");
    }
  }
  
  leftLState = state;
}

void check() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) lastDebounceTime = millis(); 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) Serial.println("pushed!");
    }
  }
