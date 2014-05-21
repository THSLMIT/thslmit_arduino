// Pin Setup for Buttons
const int leftBtn = 30;
const int rightBtn = 32;
const int selectBtn = 34;
const int sosBtn = 36;

// Button States
int LBtnState;
int RBtnState;
int SelBtnState;
int SosBtnState;

// Last Button States
int LastLBtnState = LOW;
int LastRBtnState = LOW;
int LastSelBtnState = LOW;
int LastSosBtnState = LOW;

// Last Button Debounce Times
int LastLBtnDT = 0;
int LastRBtnDT = 0;
int LastSelBtnDT = 0;
int LastSosBtnDT = 0;

int delayTime = 100;

void setup() {
  Serial.begin(9600);
  
  // Pin Input Setup for Button
  pinMode(leftBtn, INPUT);
  pinMode(rightBtn, INPUT);
}

void loop() {
  checkLeftBtnState();
  checkRightBtnState();
  checkSelectBtnState();
  checkSosBtnState();
}

void checkLeftBtnState() {
  int state = digitalRead(leftBtn);
  if (state != LastLBtnState) LastLBtnState = millis();
  if ((millis() - LastLBtnDT) > delayTime) {
    if (state != LBtnState) {
      LBtnState = state;
      if (LBtnState == HIGH) Serial.println("[LEFT] Pressed!");
    }
  }
  
  LastLBtnState = state;
}

void checkRightBtnState() {
  int state = digitalRead(rightBtn);
  if (state != LastRBtnState) LastRBtnState = millis();
  if ((millis() - LastRBtnDT) > delayTime) {
    if (state != RBtnState) {
      RBtnState = state;
      if (RBtnState == HIGH) Serial.println("[RIGHT] Pressed!");
    }
  }
  
  LastRBtnState = state;
}

void checkSelectBtnState() {
  int state = digitalRead(selectBtn);
  if (state != LastSelBtnState) LastSelBtnState = millis();
  if ((millis() - LastSelBtnDT) > delayTime) {
    if (state != SelBtnState) {
      SelBtnState = state;
      if (SelBtnState == HIGH) Serial.println("[SELECT] Pressed!");
    }
  }
  
  LastSelBtnState = state;
}

void checkSosBtnState() {
  int state = digitalRead(sosBtn);
  if (state != LastSosBtnState) LastSosBtnState = millis();
  if ((millis() - LastSosBtnDT) > delayTime) {
    if (state != SosBtnState) {
      SosBtnState = state;
      if (SosBtnState == HIGH) Serial.println("[SOS EMERGENCY] Pressed!");
    }
  }
  
  LastSelBtnState = state;
}
