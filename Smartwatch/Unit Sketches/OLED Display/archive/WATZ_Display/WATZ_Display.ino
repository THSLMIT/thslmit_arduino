// Pin Definitions
int leftSelect = 22;
int rightSelect = 24;

// Button States
int leftState;
int rightState;

// Last Button States
int leftLState = LOW;
int rightLState = LOW;

// Debounce Times
int leftDTime = 0;
int rightDTime = 0;

int delayTime = 50;

// Button State Booleans
boolean L_SEL = false;

void setup() {
  Serial.begin(9600);
  
  // Button Pin Set
  pinMode(22, INPUT);
  pinMode(24, INPUT);
}

void loop() {
  checkButtonState();
}
