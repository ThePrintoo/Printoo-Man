/**********************************************************************
* © 2014 YD Ynvisible, S.A.
*
* FileName:        Printoo_Man.ino
* Dependencies:    -
* Processor:       ATmega328
* IDE:             Arduino 1.0.5
*
* Description:
* Animated 8x8 led matrix forming a face
* 
**********************************************************************/

//MATRIX PINS
//Pin connected to ST_CP of 74LV595
int latchPin = 9;
//Pin connected to SH_CP of 74LV595
int clockPin = 11;
//Pin connected to DS of 74LV595
int dataPin = 8;
//Pin connected to EN of 74LV595
int enPin = 13;
//Pin connected to the Regulator enable
int enRegPin = 12;

void configure_timers(void);               //using timers!
// **** DISPLAYS ***** 

int counter = 1;
boolean toggle1 = 0;

int LEDs_off[8][8] = {   
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}      
};

int face_1[8][8] = {        
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}      
};

int face_2[8][8] = {         
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}      
};

int face_3[8][8] = {      
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}      
};

int face_4[8][8] = {        
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}      
};

int face_5[8][8] = {     
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}      
};

int face_6[8][8] = {   
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}      
};


ISR(TIMER1_COMPA_vect){
 //generates pulse wave of frequency = X Hz 
  counter++;
}

void setup() {
  //set pins to output because they are addressed in the main loop
  configure_timers();
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(enRegPin, OUTPUT);
  
  digitalWrite(enRegPin, LOW);  
  digitalWrite(enRegPin, HIGH);
}

void loop() {

  //ANIMATIONS!!!!!!!!!!!!!!!!!!!!
  if(counter<500){
    lightLED(face_1);
  }
  if(counter>=500&&counter<550){
    lightLED(face_2);
  }
  if(counter>=550&&counter<1050){
    lightLED(face_3);
  }
  if(counter>=1050&&counter<1100){
    lightLED(face_4);
  }
  if(counter>=1100&&counter<1600){
    lightLED(face_5);
  }
  if(counter>=1600&&counter<1700){
    lightLED(face_6);
  }
  if(counter>=1700&&counter<1750){
    lightLED(face_5);
  }
  if(counter>=1750&&counter<1800){
    lightLED(face_6);
  }
  if(counter>=1800&&counter<2800){
    lightLED(face_5);
  }
  if(counter>=2800&&counter<3000){
    lightLED(face_4);
  }
  if(counter>=3000&&counter<3200){
    lightLED(face_3);
  }
  if(counter>=3200&&counter<3400){
    lightLED(face_2);
  }
  if(counter>=3400&&counter<3600){
    lightLED(face_1);
  }
  if(counter>=3600&&counter<5000){
    lightLED(face_1);
  }  
  if(counter>=5000){
    counter=1;
  } 
 
}

//Lighting the 8x8 Matrix function
void lightLED(int tempLED[8][8]) {
  byte columnbitsToSend = 0;
  byte rowbitsToSend = 0;
  
  int x = 0;
  int y = 0;
  for (x = 0; x < 8; x++) {
    columnbitsToSend = 0;
    rowbitsToSend = 0;
      
    for (y = 0; y < 8; y ++) {
      if (tempLED[y][x] == 0) {   //change to tempLED[x][y] to rotate clockwise
        bitWrite(rowbitsToSend, y, HIGH);
      } 
    }
    
    digitalWrite(latchPin, LOW);
    bitWrite(columnbitsToSend, x, HIGH);
    shiftOut(dataPin, clockPin, MSBFIRST, columnbitsToSend);
    shiftOut(dataPin, clockPin, MSBFIRST, rowbitsToSend);
    digitalWrite(latchPin, HIGH);   
    delay(2);
  }
}

void configure_timers(){
  cli();//stop interrupts
  //set timer1 interrupt at X Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 14;// = (8*10^6) / (0.2*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();//allow interrupts
}
