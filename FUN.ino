#include <LiquidCrystal.h>

#define joyX A0
#define joyY A1

int  xValue, yValue;

int newPositionX, newPositionY;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const int numRows = 2;
const int numCols = 16;

int Friend = '.';
int obstacle='|';
int space=' ';
int counter = 0;
int randNumber = 0;
int movement = 15;
int obstacleExists = 0;
int buttonPin = 8;

void setup() {
  Serial.begin(9600);
  lcd.begin(numCols, numRows);
  randomSeed(42);  // for randomly making obstacles
  pinMode(buttonPin, INPUT);
}

void loop() {
  
  newPositionX=0;
  newPositionY=1;
  if (counter>20){
    counter = 0;
    randNumber = random(0, 2);
    if (randNumber==1){
         movement=15;
         randNumber = random(0, 2);
         lcd.setCursor(movement, randNumber);
         lcd.write(obstacle);
         obstacleExists=1;
    }
  }

  //move the obstacle
  if(movement>=0 && obstacleExists==1){
    lcd.setCursor(movement, randNumber);
    lcd.write(space);
    movement--;
  }
  if(movement<0){
    movement=15;
    obstacleExists=0;
  }
 
  if (obstacleExists==1){
     lcd.setCursor(movement, randNumber);     
     lcd.write(obstacle);
  }
  
  //delay(150); // sweet spot of speed 
  delay(500);
  
  counter++;
  
  if(analogRead(0)< 500 && newPositionY==1){ //make friend jump 
    //delete friend
    newPositionY=1;
    lcd.setCursor(newPositionX, newPositionY);
    lcd.write(space);
    //friend will jump
    newPositionY=0;
    lcd.setCursor(newPositionX, newPositionY);
    lcd.write(Friend);
  }
  else{
    //delete friend
    newPositionY=0;
    lcd.setCursor(newPositionX, newPositionY);
    lcd.write(space);
    //friend will fall
    newPositionY=1;
    lcd.setCursor(newPositionX, newPositionY);
    lcd.write(Friend);
  }
  Serial.print("button:");
  Serial.print(digitalRead(7));
  Serial.print("\n");
  //check to see if we hit friend
  if (movement==0 && randNumber==newPositionY && obstacleExists==1){
    lcd.setCursor(0, 0);
    lcd.print("GAME OVER");
    lcd.setCursor(0, 1);
    lcd.print("START AGAIN?");
    //while(analogRead(0) > 515 && analogRead(0) < 525 ){
    while(digitalRead(buttonPin)==LOW){
      //tested range for do nothing 
      //tone(8, 400, 200);
    }
    // restart the game
    for (int i=0; i<16; i++){ // clear the screen 
      for (int j= 0; j<2; j++){
        lcd.setCursor(i, j);
        lcd.write(space);
      }
    }
    // place friend
    newPositionY=1;
    lcd.setCursor(newPositionX, newPositionY);
    lcd.write(Friend);
    
    counter = 0;
    movement = 15;
    obstacleExists = 0;
  }
  
 
}
