.#include <SPI.h>
#include <SD.h>
#include <FTOLED.h>
#include <fonts/Droid_Sans_36.h>
#include <fonts/Droid_Sans_16.h>
#include <fonts/Arial_Black_16.h>
#include <fonts/SystemFont5x7.h>

const byte oled_cs = 7;
const byte oled_dc = 2;
const byte oled_reset = 3;

OLED oled(oled_cs, oled_dc, oled_reset);

String day[] = {"Sudnday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

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
  
  oled.begin();
}

int scrnMode = 0;
int scrnPage = 0;

void loop() {
  // Button State Check Code
  resetBtnState();
  for (int i = 0; i < 4; i++) buttonCheck(i);
  
  if (btnPressed[2]) {
    if (scrnMode == 0) scrnMode = 1;
    else scrnMode = 0;
    
    scrnPage = 0;
  } else {
    if (scrnMode == 0) {
      if (btnPressed[0] && scrnPage > 0) scrnPage--;
      if (btnPressed[1] && scrnPage < 1) scrnPage++;
    } else if (scrnMode == 1) {
      if (btnPressed[0] && scrnPage > 0) scrnPage--;
      if (btnPressed[1] && scrnPage < 2) scrnPage++;
    }
  }
  
  if (btnPressed[0] || btnPressed[1] || btnPressed[2] || btnPressed[3]) {
    oled.clearScreen();
    
    Serial.print("Screen Level: ");
    Serial.println(scrnMode);
    
    Serial.print("Screen Page: ");
    Serial.println(scrnPage);
  }
  
  if (scrnMode == 0) {
    if (scrnPage == 0) time(8,25);
    else if (scrnPage == 1) date(6,3,5,2014);
  } else if (scrnMode == 1) {
    if (scrnPage == 0) patientInfo_name("Yuya", "Ong");
    else if (scrnPage == 1) patientInfo_addr("123 Sesame Street", "Tenafly, NJ 07670");
    else if (scrnPage == 2) patientInfo_contact("Jeremy Ong", "Brother", "555-555-5555");
  }
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

void time(int h, int m) {
  dispPersonIcon();
  dispCalIcon();
  
  String time = "";
  
  if (h < 10) {
    time += "0";
    time += h;
  } else time += h;
  time += ":";
  if (m < 10) {
    time += "0";
    time += m;
  } else time += m;
  
  oled.selectFont(Droid_Sans_36);
  int x = oled.stringWidth(time);
  oled.drawString(((128-x)/2),(128/3),time,GREEN,BLACK);
}

void date(int dat, int m, int dt, int y) {
  dispPersonIcon();
  
  dayText(dat);
  row2(m, dt);
}

void dayText(int d) {
  oled.selectFont(Droid_Sans_16);
  int x = oled.stringWidth(day[d]);
  oled.drawString(((128-x)/2),(128/2),day[d],GREEN,BLACK);  
}

void row2(int m, int d) {
  String month[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
  String dy = "";
  
  if (d < 10) dy += "0"; 
  dy += d;
  dy += ",";
  
  int x = oled.stringWidth(dy);
  
  oled.selectFont(Droid_Sans_16);
  oled.drawString((128/5.6),(128/3),month[m],GREEN,BLACK);
  oled.drawString(((128-x)/2),(128/3),dy,GREEN,BLACK);
  oled.drawString((128/1.65),(128/3),"2014",GREEN,BLACK);
}

// Patient Information Screens
void patientInfo_name(String first, String last) {
  oled.selectFont(Droid_Sans_16);
  oled.drawString((128/4.5),90,"[About-Me]",GREEN, BLACK);  
  
  oled.selectFont(SystemFont5x7);
  oled.drawString(0,(128/1.8),"First Name: ",GREEN,BLACK);  
  
  oled.selectFont(Arial_Black_16);
  oled.drawString(0,(120/2.4),first,GREEN,BLACK);
  
  oled.selectFont(SystemFont5x7);
  oled.drawString(0,(128/3.9),"Last Name: ",GREEN,BLACK);  
  
  oled.selectFont(Arial_Black_16);
  oled.drawString(0,(120/10.5),last,GREEN,BLACK);
}

void patientInfo_addr(String addr1, String addr2) {
  oled.selectFont(Droid_Sans_16);
  oled.drawString((128/4.5),90,"[About-Me]",GREEN,BLACK);  
  
  oled.selectFont(SystemFont5x7);
  oled.drawString(0,(128/1.8),"<Home Address>",GREEN,BLACK);  
  
  oled.drawString(0,(120/2.4),addr1,GREEN,BLACK);
  oled.drawString(0,(128/3.5),addr2,GREEN,BLACK);  
}

void patientInfo_contact(String name, String role, String num) {
  oled.selectFont(Droid_Sans_16);
  oled.drawString((128/4.5),90,"[About-Me]",GREEN,BLACK);  
  
  oled.selectFont(SystemFont5x7);
  oled.drawString(0,(128/1.8),"<Emergency Contact>",GREEN, BLACK);  
  
  oled.drawString(0,(120/2.4),"Name: " + name,GREEN,BLACK);
  oled.drawString(0,(128/4.0),"Role: " + role,GREEN,BLACK);  
  oled.drawString(0,(128/7.7),"Phone: " + num,GREEN,BLACK);
}

void dispPersonIcon() {
  oled.drawFilledCircle(111, 124, 3, WHITE);
  oled.drawFilledBox(106,115,116,120,WHITE);
  
  oled.drawLine(122, 117, 122, 125, WHITE);
  oled.drawLine(122, 117, 127, 121, WHITE);
  oled.drawLine(122, 125, 127, 121, WHITE);
}

void dispCalIcon() {
  oled.drawBox(106,0,116,8,1,WHITE);
  
  oled.drawLine(107, 9, 107, 10, WHITE);
  oled.drawLine(115, 9, 115, 10, WHITE);
  
  oled.drawLine(108, 3, 109, 3, WHITE);
  oled.drawLine(111, 3, 112, 3, WHITE);
  oled.drawLine(114, 3, 114, 3, WHITE);
  
  oled.drawLine(108, 5, 108, 5, WHITE);
  oled.drawLine(110, 5, 111, 5, WHITE);
  oled.drawLine(113, 5, 114, 5, WHITE);
    
  oled.drawLine(122, 0, 122, 8, WHITE);
  oled.drawLine(122, 0, 127, 4, WHITE);
  oled.drawLine(122, 8, 127, 4, WHITE);
}
