const int btn[] = {30, 32, 34, 36};
int btnState[4];
int lastBtnState[] = {LOW, LOW, LOW, LOW};
int lastBtnDT[] = {0, 0, 0, 0};
int delayTime = 500;

boolean btnPressed[] = {false, false, false, false};

void setup() {
  Serial.begin(9600);
  
  // Define Pin Input for Buttons
  for (int i = 0 ; i < 4; i++)
    pinMode(btn[i], INPUT);
}

void loop() {
  // Button State Check Code
  resetBtnState();
  for (int i = 0; i < 4; i++) buttonCheck(i);
  
}

void buttonCheck(int i) {
  int state = digitalRead(btn[i]);
  if (state != lastBtnState[i]) lastBtnState[i] = millis();
  if ((millis() - lastBtnState[i]) > delayTime) {
    if (state != btnState[i]) {
      btnState[i] = state;
      if (btnState[i] == HIGH) btnPressed[i] = true;
      else btnPressed[i] = false;
    }
  }
  lastBtnState[i] = state;
}

void resetBtnState() {
  for (int i = 0; i < 4; i++)
    btnPressed[i] = false;
}
