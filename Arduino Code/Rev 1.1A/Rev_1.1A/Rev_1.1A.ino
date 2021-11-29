#include "pitches.h"
#include "SoftPWM.h"

/*
//Rev 1.1A
//Autumn 2021
//The Ohio State University Electronics Club Christmas Tree PCB workshop code
//Program written by Matt Nichols


//CREDITS!!!
Most if not all of the code for the song playback was taken from the wonderful project on GitHub by robsoncouto
https://github.com/robsoncouto/arduino-songs

Also special thanks to the officers of the OSU Electronics Club. Without your support this wouldn't have been possible!
*              President:   Eddy Lui
*         Vice President:   Connor Beheydt
*              Treasurer:   Max Fojtik
*               Lab Tech:   Chris Murray
*              Webmaster:   Jason Jiang
*   Workshop Coordinator:   Siddharth Venkatesan



//CHANGELOG:

*November 26, 2021 - First initial working version completed.
*/

/*GLOBAL VARIABLES*/
int buzzer   = 12;  //Buzzer pin

int topPad   = 14;  //Top touch pad
bool top = false;   //Global for detecting if top touch pad is pressed
int leftPad  = 15;  //Left touch pad
bool left = false;  //Global for detecting if left touch pad is pressed
int rightPad = 16;  //Right touch pad
bool right = false; //Global for detecting if right touch pad is pressed

int LEDs[9]  = {2, 3, 4, 5, 6, 7, 8, 9, 10}; //All the LEDs except the star since I want that on all the time






// notes of the melody followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!


//CAROL OF THE BELLS
int carolOfTheBellsTempo = 85;
int carolOfTheBells[]{
  NOTE_C5,8, NOTE_B4,16, NOTE_C5,16, NOTE_A4,16, REST,16,
  NOTE_C5,8, NOTE_B4,16, NOTE_C5,16, NOTE_A4,16, REST,16,
  NOTE_C5,8, NOTE_B4,16, NOTE_C5,16, NOTE_A4,16, REST,16,
  NOTE_C5,8, NOTE_B4,16, NOTE_C5,16, NOTE_A4,16, REST,16,

  NOTE_E5,8, NOTE_D5,16, NOTE_E5,16, NOTE_C5,16, REST,16,
  NOTE_E5,8, NOTE_D5,16, NOTE_E5,16, NOTE_C5,16, REST,16,
  NOTE_E5,8, NOTE_D5,16, NOTE_E5,16, NOTE_C5,16, REST,16,
  NOTE_E5,8, NOTE_D5,16, NOTE_E5,16, NOTE_C5,16, REST,16,

  NOTE_A5,8, NOTE_A5,16, NOTE_A5,16, NOTE_G5,16, NOTE_F5,16, //Triplet thing
  NOTE_E5,8, NOTE_E5,16, NOTE_E5,16, NOTE_D5,16, NOTE_C5,16,
  NOTE_D5,8, NOTE_D5,16, NOTE_D5,16, NOTE_E5,16, NOTE_D5,16, NOTE_C5,8, NOTE_B4, 16, NOTE_C5,16, NOTE_A4,16, REST,16,

  NOTE_E4,16, NOTE_FS4,16, NOTE_GS4,16, NOTE_A4,16, NOTE_B4,16, NOTE_C5,16, NOTE_D5,16, NOTE_E5,16, NOTE_D5,8, NOTE_C5,8,
  NOTE_E4,16, NOTE_FS4,16, NOTE_GS4,16, NOTE_A4,16, NOTE_B4,16, NOTE_C5,16, NOTE_D5,16, NOTE_E5,16, NOTE_D5,8, NOTE_C5,8,
};
int notesCoB = sizeof(carolOfTheBells) / sizeof(carolOfTheBells[0]) / 2;
int wholenoteCoB = (60000 * 4) / carolOfTheBellsTempo;

//WE WISH YOU A MERRY CHRISTMAS
int weWishYouAMerryChristmasTempo = 140;
int weWishYouAMerryChristmas[] = { 
  NOTE_C5,4, //1
  NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8,
  NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,
  NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
  NOTE_E5,4, NOTE_C5,4, NOTE_C5,4,
  NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8,
  NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, NOTE_C5,8,
  NOTE_D5,4, NOTE_G5,4, NOTE_E5,4, NOTE_F5,2
};
int notesWYAMC = sizeof(weWishYouAMerryChristmas) / sizeof(weWishYouAMerryChristmas[0]) / 2;
int wholenoteWYAMC = (60000 * 4) / weWishYouAMerryChristmasTempo;

//JINGLE BELLS
int jingleBellsTempo = 104;
int jingleBells[] = {
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,4,
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,4,
  NOTE_E5,8, NOTE_G5,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,2,
  
  NOTE_F5,8, NOTE_F5,8, NOTE_F5,8, NOTE_F5,8,
  NOTE_F5,8, NOTE_E5,8, NOTE_E5,8, NOTE_E5,16, NOTE_E5,16,
  NOTE_E5,8, NOTE_D5,8, NOTE_D5,8, NOTE_E5,8,
  NOTE_D5,4, NOTE_G5,4
};
int notesJB = sizeof(jingleBells) / sizeof(jingleBells[0]) / 2;
int wholenoteJB = (60000 * 4) / jingleBellsTempo;

int divider = 0, noteDuration = 0; //Necessary for song playback






/*
 * FUNCTION DEFINITIONS
*/

void checkInput();

//Plays the melody on the buzzer
//Passed the song name of the integer array for the desired song and the tempo
void playSong(int songName[], int tempo, int notes, int wholenote);


void defaultLights();

void initSongLights();



void setup() {


pinMode(topPad, INPUT);
pinMode(leftPad, INPUT);
pinMode(rightPad, INPUT);

for(int i(0); i < sizeof(LEDs); ++i){
  pinMode(LEDs[i], OUTPUT);
}
//Keep the star on all the time
digitalWrite(11, HIGH);

/*
SoftPWMBegin();
SoftPWMSet(2, 0);
SoftPWMSet(3, 0);
SoftPWMSet(4, 0);
SoftPWMSet(5, 0);
SoftPWMSet(6, 0);
SoftPWMSet(7, 0);
SoftPWMSet(8, 0);
SoftPWMSet(9, 0);
SoftPWMSet(10, 0);
SoftPWMSet(11, 255); //Keep the star on

 
 SoftPWMSetFadeTime(2, 500, 500);
 SoftPWMSetFadeTime(3, 500, 500);
 SoftPWMSetFadeTime(4, 500, 500);
 SoftPWMSetFadeTime(5, 500, 500);
 SoftPWMSetFadeTime(6, 500, 500);
 SoftPWMSetFadeTime(7, 500, 500);
 SoftPWMSetFadeTime(8, 500, 500);
 SoftPWMSetFadeTime(9, 500, 500);
 SoftPWMSetFadeTime(10, 500, 500);
 */
}

void loop() {
  
  
  if(top == true){
    playSong(carolOfTheBells, carolOfTheBellsTempo, notesCoB, wholenoteCoB);
    top = false;
    left = false;
    right = false;
  }else if(left == true){
    playSong(weWishYouAMerryChristmas, weWishYouAMerryChristmasTempo, notesWYAMC, wholenoteWYAMC);
    top = false;
    left = false;
    right = false;
  }else if(right == true){
    playSong(jingleBells, jingleBellsTempo, notesJB, wholenoteJB);
    top = false;
    left = false;
    right = false;
  }else{
    defaultLights();
  }

  delay(50);
}

//Checks to see if any of the pads are pressed
void checkInput(){
  if(analogRead(topPad) <= 40 || analogRead(topPad) > 650){
   // playSong(carolOfTheBells, carolOfTheBellsTempo, notesCoB, wholenoteCoB);
    top = true;
    left = false;
    right = false;
    loop();
  }else if(analogRead(leftPad) <= 100 || analogRead(leftPad) > 500){
   // playSong(weWishYouAMerryChristmas, weWishYouAMerryChristmasTempo, notesWYAMC, wholenoteWYAMC);
    top = false;
    left = true;
    right = false;
    loop();
  }else if(analogRead(rightPad) <= 100 || analogRead(rightPad) > 450){
   // playSong(jingleBells, jingleBellsTempo, notesJB, wholenoteJB);
    top = false;
    left = false;     
    right = true;
    loop();
  }else{
    top = false;
    left = false;
    right = false;
  }
}

void initSongLights(){
  
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
}

void playSong(int songName[], int tempo, int notes, int wholenote){

  initSongLights();

  //Actually plays the song
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

  //Just kinda randomly sets the lights on or off
  for(int i(0); i < 9; ++i){
    digitalWrite(LEDs[i], !digitalRead(LEDs[i])); //Should flip the direction of the LED (high/low)
  }
  
    // calculates the duration of each note
    divider = songName[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, songName[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}


void defaultLights(){
  //Could not get the soft pwm to behave with the buzzer
/*
  //Set all LEDs to 100%
  for(int i(0); i < sizeof(LEDs); ++i){
    SoftPWMSetPercent(LEDs[i], 100);
    checkInput();
  }

  // Wait for the fade-up and some extra delay.
  delay(1000);

  //Set all LEDs (except for 11/the star) to 0%
  for(int i(0); i < sizeof(LEDs) - 1; ++i){
    SoftPWMSetPercent(LEDs[i], 0);
    checkInput();
  }
  SoftPWMSetPercent(11, 100);

  delay(1000);
  */
  //Keep the star on all the time
  digitalWrite(11, HIGH);
  for(int i(0); i < 9; ++i){
    digitalWrite(LEDs[i], HIGH);
    delay(100);
    checkInput();
  }
  
  delay(1000);
  for(int i(0); i < 9; ++i){
    digitalWrite(LEDs[i], 0);
    delay(100);
    checkInput();
  }
  
}
