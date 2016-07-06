//Tic-Tac-Toe
#include <Key.h>
#include <Keypad.h>

//KEYPAD SETUP
const byte ROWS = 3; //3 ROWS
const byte COLS = 3; //3 COLUMNS
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'}
};
byte rowPins[ROWS] = {4, 3, 2}; //connects to Arduino pinouts
byte colPins[COLS] = {7, 6, 5}; //connects to Arudino pinouts
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//SHIFT REGISTER SETUP
int LatchPin = 8;
int ClockPin = 9;
int DataPin = 10;

byte LEDS;
byte LEDArray[9];


//GAME SETUP
int PlayerNumber = 0;
int Player;

int Space1 = 0;
int Space2 = 0;
int Space3 = 0;
int Space4 = 0;
int Space5 = 0;
int Space6 = 0;
int Space7 = 0;
int Space8 = 0;
int Space9 = 0;

int i;
int k;


void setup() {
  Serial.begin(9600);

  //intialize array----------------------------------------------------------------make into function
  for(i=0;i<9;i++) {
    LEDArray[i] = B00000000;
  }

  //Sets SHIFT REGISTER pins and CATHODE pins (11,12,13) as OUTPUTs
  for (i = 13; i > 7; i--) {
    pinMode(i, OUTPUT);
  } 
}

void loop() {   
  char key = keypad.getKey();

  Display();
 
  if (PlayerNumber % 2 == 0) {
    Player = 1;
    digitalWrite(14,LOW);
    digitalWrite(15,HIGH);
  }
  else {
    Player = 2;
    digitalWrite(15,LOW);
    digitalWrite(14,HIGH);
  }

  if (key != NO_KEY) {
    //Serial.println(key);  //Used for debugging
    if ((key == '1') && (Space1 == 0)) {      
      Space1 = Player;
      k = 0; //Addresses first value in array
      if(Player == 1) {
        LEDArray[k] = B00000001;        
      }
      else {
        LEDArray[k] = B00000010;        
      }      
      LEDS = LEDArray[k]; //Turns on first bit in Shift Register
      //UpdateShiftRegister();

    }
    if ((key == '2') && (Space2 == 0)) {
      Space2 = Player;
      k=1;
      if(Player == 1) {
        LEDArray[k] = B00000100;        
      }
      else {
        LEDArray[k] = B00001000;        
      } 
      LEDS = LEDArray[k]; 
      //UpdateShiftRegister();

    }
    if ((key == '3') && (Space3 == 0)) {
      Space3 = Player;
      k=2;
      if(Player == 1) {
        LEDArray[k] = B00010000;        
      }
      else {
        LEDArray[k] = B00100000;        
      } 
      LEDS = LEDArray[k]; 
      //UpdateShiftRegister();
    }
    if ((key == '4') && (Space4 == 0)) {
      Space4 = Player;
      k=3;
      if(Player == 1) {
        LEDArray[k] = B00000001;        
      }
      else {
        LEDArray[k] = B00000010;        
      } 
      LEDS = LEDArray[k]; 
      //UpdateShiftRegister();
    }
    if ((key == '5') && (Space5 == 0)) {
      Space5 = Player;
      k=4;
      if(Player == 1) {
        LEDArray[k] = B00000100;        
      }
      else {
        LEDArray[k] = B00001000;        
      } 
      LEDS = LEDArray[k]; 
    }
    if ((key == '6') && (Space6 == 0)) {
      Space6 = Player;
      k=5;
      if(Player == 1) {
        LEDArray[k] = B00010000;        
      }
      else {
        LEDArray[k] = B00100000;        
      } 
      LEDS = LEDArray[k]; 
    }
    if ((key == '7') && (Space7 == 0)) {
      Space7 = Player;
      k=6;
      if(Player == 1) {
        LEDArray[k] = B00000001;        
      }
      else {
        LEDArray[k] = B00000010;        
      }      
      LEDS = LEDArray[k]; 
    }
    if ((key == '8') && (Space8 == 0)) {
      Space8 = Player;
      k=7;
      if(Player == 1) {
        LEDArray[k] = B00000100;        
      }
      else {
        LEDArray[k] = B00001000;        
      } 
      LEDS = LEDArray[k]; 
    }
    if ((key == '9') && (Space9 == 0)) {
      Space9 = Player;
      k=8;
      if(Player == 1) {
        LEDArray[k] = B00010000;        
      }
      else {
        LEDArray[k] = B00100000;        
      } 
      LEDS = LEDArray[k]; 
    }

    PlayerNumber++;
    PrintMatrix();
  }

  //WIN TEST
  //Player1 WINS
  if (((Space1 + Space2 + Space3 == 3) && (Space1 != 0) && (Space2 != 0) && (Space3 != 0))
      || ((Space4 + Space5 + Space6 == 3) && (Space4 != 0) && (Space5 != 0) && (Space6 != 0))
      || ((Space7 + Space8 + Space9 == 3) && (Space7 != 0) && (Space8 != 0) && (Space9 != 0))
      || ((Space1 + Space4 + Space7 == 3) && (Space1 != 0) && (Space4 != 0) && (Space7 != 0))
      || ((Space2 + Space5 + Space8 == 3) && (Space2 != 0) && (Space5 != 0) && (Space8 != 0))
      || ((Space3 + Space6 + Space9 == 3) && (Space3 != 0) && (Space6 != 0) && (Space9 != 0))
      || ((Space1 + Space5 + Space9 == 3) && (Space1 != 0) && (Space5 != 0) && (Space9 != 0))
      || ((Space3 + Space5 + Space7 == 3) && (Space3 != 0) && (Space5 != 0) && (Space7 != 0))
     )
  {
    Serial.println("Player1 WINS");    
    //FlASH ALL LEDS PLAYER1 COLOR
    for(i=0;i<100;i++) {
      for(k=0;k<9;k++) {      
      LEDArray[0] = B00000001;    
      LEDArray[1] = B00000100;
      LEDArray[2] = B00010000;
      LEDArray[3] = B00000001;    
      LEDArray[4] = B00000100;
      LEDArray[5] = B00010000;
      LEDArray[6] = B00000001;    
      LEDArray[7] = B00000100;
      LEDArray[8] = B00010000;
      Display();  
      LEDArray[k] = B00000000;    
      Display();
      }          
    }    
    delay(500);
    Reset();
  }

  //Player2 WINS
  if ((Space1 + Space2 + Space3 == 6)
      || (Space4 + Space5 + Space6 == 6)
      || (Space7 + Space8 + Space9 == 6)
      || (Space1 + Space4 + Space7 == 6)
      || (Space2 + Space5 + Space8 == 6)
      || (Space3 + Space6 + Space9 == 6)
      || (Space1 + Space5 + Space9 == 6)
      || (Space3 + Space5 + Space7 == 6)
     )
  {
    Serial.println("Player2 WINS");
    for(i=0;i<100;i++) {
      for(k=0;k<9;k++) {      
      LEDArray[0] = B00000010;    
      LEDArray[1] = B00001000;
      LEDArray[2] = B00100000;
      LEDArray[3] = B00000010;    
      LEDArray[4] = B00001000;
      LEDArray[5] = B00100000;
      LEDArray[6] = B00000010;    
      LEDArray[7] = B00001000;
      LEDArray[8] = B00100000;
      Display();  
      LEDArray[k] = B00000000;    
      Display();
      }          
    }    
    delay(500);
    Reset();
  }


  //Draw Test
  if((Space1 != 0) && (Space2 != 0) && (Space3 != 0)
  && (Space4 != 0) && (Space5 != 0) && (Space6 != 0)
  && (Space7 != 0) && (Space8 != 0) && (Space9 != 0))
  {
    Serial.println("Draw");
    //Flash Shared Color
    for(i=0;i<100;i++) {
      for(k=0;k<9;k++) {      
      LEDArray[0] = B00000011;    
      LEDArray[1] = B00001100;
      LEDArray[2] = B00110000;
      LEDArray[3] = B00000011;    
      LEDArray[4] = B00001100;
      LEDArray[5] = B00110000;
      LEDArray[6] = B00000011;    
      LEDArray[7] = B00001100;
      LEDArray[8] = B00110000;
      Display();  
      LEDArray[k] = B00000000;    
      Display();
      }          
    }    
    delay(500);
    Reset();    
  }
}


void Display()//
{
  for(k=0;k<=2;k++){ //for spaces 1,2,3
    LEDS = LEDArray[k];
    UpdateShiftRegister();  
    digitalWrite(11,LOW); //Path to ground is LOW (unobstructed) for ROW 1
    digitalWrite(12,HIGH);//Path to ground is HIGH (obstructed) for ROW 2
    digitalWrite(13,HIGH);//Path to ground is HIGH (obstructed) for ROW 3
    delay(3);  
  }
  for(k=3;k<=5;k++){ //for spaces 4,5,6
    LEDS = LEDArray[k];
    UpdateShiftRegister();  
    digitalWrite(11,HIGH);
    digitalWrite(12,LOW);
    digitalWrite(13,HIGH);
    delay(3);
  }
  for(k=6;k<=8;k++){ //for spaces 7,8,9
    LEDS = LEDArray[k];
    UpdateShiftRegister();  
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(13,LOW);
    delay(3);
  }
}


void UpdateShiftRegister() //function to update SHIFT REGISTER
{
  digitalWrite(LatchPin, LOW);
  shiftOut(DataPin, ClockPin, MSBFIRST, LEDS);
  digitalWrite(LatchPin, HIGH);
}


//print matrix for debugging
void PrintMatrix()
{
  Serial.print(Space1);
  Serial.print(" ");
  Serial.print(Space2);
  Serial.print(" ");
  Serial.print(Space3);
  Serial.println("");
  Serial.print(Space4);
  Serial.print(" ");
  Serial.print(Space5);
  Serial.print(" ");
  Serial.print(Space6);
  Serial.println("");
  Serial.print(Space7);
  Serial.print(" ");
  Serial.print(Space8);
  Serial.print(" ");
  Serial.print(Space9);
  Serial.println("");
  Serial.println("");
}


void Reset()
{
  Space1 = 0;
  Space2 = 0;
  Space3 = 0;
  Space4 = 0;
  Space5 = 0;
  Space6 = 0;
  Space7 = 0;
  Space8 = 0;
  Space9 = 0;

  PlayerNumber = 0;

  //Resets Shift Register
  for(i=0;i<9;i++) {
    LEDArray[i] = B00000000;
  }

  Serial.println("New Game");

}

