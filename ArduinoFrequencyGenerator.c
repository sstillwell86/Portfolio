//Lab 2 Part 3
String frequency;
long int freq = 0;
bool gotFreq = false;
int mode = 0;
bool setRegs = false;
bool gotInts = false;
int correctedFreq = 0;
int top;

 
void setup() {  
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    Serial.begin(9600);
    delay(2000);
    Serial.println("Enter a frequency for the wave: ");
}

void loop() {
    if(Serial.available() && !gotFreq){
      frequency = Serial.readStringUntil('\n');
      Serial.println("Frequency = " + frequency);
      gotFreq = true;
    }
    if (gotFreq && !gotInts){
      freq = frequency.toInt();
      int top = 16000000/(freq*2);
      gotInts = true;
    }  
    if (!setRegs && freq != 0){
      Serial.println("Producing frequency...");
      noInterrupts();
      TCCR0A = 0;
      TCCR0B = 0;
      TCNT0=0;
      TCCR0A=0b00100001;
      if (freq > 31372 && freq < 8000000) {
        TCCR0B=0b00001001;
        OCR0A = 16000000/(2*freq);
        OCR0B = OCR0A/2;
        interrupts();
        Serial.println("Prescalar 1");
      }
      else if (freq > 3920) {
        TCCR0B=0b00001010;
        OCR0A = 16000000/(freq*2*8);
        OCR0B = OCR0A/2;
        interrupts();
        Serial.println("Prescalar 8");
      }
      else if (freq > 490) {
        TCCR0B=0b00001011;
        OCR0A = 16000000/(2*freq*64);
        OCR0B = OCR0A/2;
        interrupts();
        Serial.println("Prescalar 64");
      }
      else if (freq > 122) {
        TCCR0B=0b00001100;
        OCR0A = 16000000/(2*freq*256);
        OCR0B = OCR0A/2;
        interrupts();
        Serial.println("Prescalar 256");
      }
      else if (freq > 30) {
        TCCR0B=0b00001101;
        OCR0A = 16000000/(2*freq*1024);
        OCR0B = OCR0A/2;
        interrupts();
        Serial.println("Prescalar 1024");
      }
      else {
        Serial.println("Frequency not recognized");
      }
      setRegs = true;
      Serial.println("Done");
    }
}