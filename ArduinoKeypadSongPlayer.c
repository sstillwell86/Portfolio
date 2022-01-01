#include <SoftwareSerial.h>  
#include <Keypad.h>
String song, playSong = "none";
bool asteriskPressed = false;
int ledFlash = 1;
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
#define NOTE_C4  262   //Defining note frequency
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988
int currentNote = 0;
long songspeed = 1.5;
int notes[] = {       //Note of the song, 0 is a rest/pulse
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
   NOTE_D5, NOTE_E5, NOTE_A4, 0,
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,

   NOTE_A4, NOTE_A4,
   //Repeat of first part
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,

   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
   NOTE_D5, NOTE_E5, NOTE_A4, 0,
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,
   //End of Repeat

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
};
//*****************************************
int toneDuration[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125,
 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125,
 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125,
  250, 125, 250, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 375,

  250, 125,
  //Rpeat of First Part
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125,
 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125,
 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125,
  250, 125, 250, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 375,
  //End of Repeat
 
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500,

  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500
};
byte rowPins[ROWS] = {A0, A1, A2, A5}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {A3, 4, 3}; //connect to the column pinouts of the kpd
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
String msg;
int bluetoothTx = 9;
int bluetoothRx = 8;
#define trigPin 6
#define echoPin 10
int maximumRange = 255;
int minimumRange = 0;
long duration, distance;
int freqOut = 0;
int freqIn = 0;
int dc;
int correctedFreq = 0;
int top;
int bottom;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
const int DATA_PIN = 13;
const int CLK_PIN = 12;
const int SS_PIN = 11;
void char2LCD(const byte);
void char2LCD(const int dataPin, const int clockPin,
              const int ssPin, const byte ch,
              const int byteOrder);
void str2LCD(unsigned char *str);
void turnBlinkingCursorOn();
void turnBlinkingCursorOff();
void setCursorPos(unsigned char pos);
void clearScreen();
void lcdSPISetup();
void char2LCD(const int dataPin, const int clockPin,
              const int ssPin, const byte ch,
              const int byteOrder = MSBFIRST)
{
  byte compareValue = 0x80;
  if(byteOrder == MSBFIRST)
  {
    compareValue = 0x80;
  } else
  {
    compareValue = 0x01;
  }
  digitalWrite(ssPin, LOW);
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(dataPin, (ch&compareValue)?HIGH:LOW);
    if(byteOrder == MSBFIRST)
    {
        compareValue = compareValue >> 1;
    } else
    {
        compareValue = compareValue << 1;
    }
    digitalWrite(clockPin, LOW);
    delayMicroseconds(4);
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(14);
  }
  digitalWrite(ssPin, HIGH);
}

void char2LCD(const byte ch)
{
  char2LCD(DATA_PIN, CLK_PIN, SS_PIN, ch);
}

void str2LCD(const char *str)
{
    int i = 0;
    while(str[i]) {
        char2LCD(str[i]);
        i++;
    }  
}

void turnBlinkingCursorOn()
{
    char2LCD(0xFE);
    char2LCD(0x4B);
    delayMicroseconds(101);      
}

void turnBlinkingCursorOff()
{
    char2LCD(0xFE);
    char2LCD(0x4C);
    delayMicroseconds(101);      
}

void setCursorPos(unsigned char pos)
{
    char2LCD(0xFE);
    char2LCD(0x45);
    char2LCD(pos);
    delayMicroseconds(110);  
}

void clearScreen()
{
    char2LCD(0xFE);
    char2LCD(0x51);
    delayMicroseconds(2000);
}

void lcdSPISetup()
{
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(SS_PIN, OUTPUT);
  turnBlinkingCursorOn();
}

void setup(){
  noInterrupts();  
  OCR1A=0;
  interrupts();
  Serial.begin(9600);
  delay(2000);
  pinMode(trigPin, OUTPUT);
  pinMode(2, INPUT);
  pinMode(5, OUTPUT);
  pinMode(echoPin, INPUT);
  lcdSPISetup();
  msg = "";
  bluetooth.begin(115200);
  delay(100);  
  UCSR0B &= ~ ( 1 << TXEN0);
  clearScreen();
}

void loop(){
  ledFlash = digitalRead(2);
  digitalWrite(5, ledFlash);
  if (playSong == "none" || playSong == "Pirates\n") {
      if (kpd.getKeys() || bluetooth.available()) {
        playSong = "";  
      }
      int wait = (toneDuration[currentNote] * songspeed);
      tone(A4,notes[currentNote],wait);          //tone(pin,frequency,duration)
      currentNote++;
      if (currentNote == 204) {
        currentNote = 0;
      }
      delay(wait);
    }
    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    asteriskPressed = false;
    if (playSong == "Test\n") {
      tone(A4, 523.2);
      delay(100);
      noTone(A4);
      tone(A4, 1000);
      delay(100);
      tone(A4, 523.2);
      delay(100);
      noTone(A4);
    }
    if (kpd.getKeys())
    {
        playSong = "";
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = kpd.key[i].kchar;
                    for (int i=0; i <LIST_MAX; i++) {
                     if (kpd.key[i].kchar == '*') {
                       asteriskPressed = true;
                      }
                    }
                    if (kpd.key[i].kchar == '1'){
                      if (asteriskPressed == true) {
                         tone(A4, 523.2);
                         asteriskPressed = false;
                      }
                      else {
                        tone(A4, 261.6);
                      }
                    }
                    if (kpd.key[i].kchar == '2'){
                       if (asteriskPressed == true) {
                         tone(A4, 587.2);
                         asteriskPressed = false;
                      }
                      else {
                        tone(A4, 293.6);
                      }
                    }
                    if (kpd.key[i].kchar == '3'){
                       if (asteriskPressed == true) {
                         tone(A4, 659.2);
                         asteriskPressed = false;
                      }
                      else {
                        tone(A4, 329.6);
                      }
                    }
                    if (kpd.key[i].kchar == '4'){
                       if (asteriskPressed == true) {
                         tone(A4, 698.4);
                         asteriskPressed = false;
                      }
                      else {
                        tone(A4, 349.2);
                      }
                    }
                    if (kpd.key[i].kchar == '5'){
                      if (asteriskPressed == true) {
                         tone(A4, 784.0);
                         asteriskPressed = false;
                      }
                      else {
                        tone(A4, 392.0);
                      }
                    }
                    if (kpd.key[i].kchar == '6'){
                       if (asteriskPressed == true) {
                         tone(A4, 880.0);
                         asteriskPressed = false;
                      }
                      else {
                        tone(A4, 440.0);
                      }
                    }
                    if (kpd.key[i].kchar == '7'){
                      if (asteriskPressed == true) {
                         tone(A4, 987.6);
                         asteriskPressed = false;
                      }
                      else {
                        tone(A4, 493.8);
                      }
                    }              
                    break;
                    case HOLD:
                    msg = "";
                break;
                    case RELEASED:
                    msg = "";
                    noTone(A4);
                break;
                    case IDLE:
                    msg = "";
                }
                Serial.print(msg);
          }
      }
  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/(29.1*2);
  if (duration == 0 && digitalRead(echoPin) == HIGH)  {
      pinMode(echoPin, OUTPUT);
      digitalWrite(echoPin, LOW);
      delay(10);
      pinMode(echoPin, INPUT);
  }
  else if (distance < maximumRange) {
      freqIn = 2000;
      freqOut = freqIn/2000;
      noInterrupts();
      if (OCR1A == 0) {
          TCCR1A = 0;
          TCCR1B = 0;
          TCNT1=0;
          TCCR1A=0b10100010;
          TCCR1B=0b10011101;
          ICR1 = 15625;
      }
      OCR1A=(15625/255)*distance;
      songspeed = (distance/3);
      interrupts();
  }
  delay(100);
  if(bluetooth.available())  {
    playSong = "";
    song += ((char)bluetooth.read());  
  }
  else {
    if (song != "") {
      playSong = song;
      song = "";
      playSong = "";
      song += ((char)bluetooth.read());  
    }
    else {
      if (song != "") {
        playSong = song;
        song = "";
      }
    }
  }
  if(Serial.available())  // If stuff was typed in the serial monitor
  {
    bluetooth.print((char)Serial.read());
  }
}