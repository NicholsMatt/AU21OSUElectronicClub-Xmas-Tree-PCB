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

int buzzer   = 12;
int topPad   = 14;
int leftPad  = 15;
int rightPad = 16;

int LEDs[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

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
 

//Plays the melody on the buzzer
//Passed the song name of the integer array for the desired song and the tempo
void playSong(int songName[], int tempo, int notes, int wholenote);


void defaultLights();





void setup() {

pinMode(topPad, INPUT);
pinMode(leftPad, INPUT);
pinMode(rightPad, INPUT);

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
 SoftPWMSet(11, 0);
 SoftPWMSetFadeTime(ALL, 500, 500);
*/
}

void loop() {

Serial.println(analogRead(topPad));

  if(analogRead(topPad) <= 100 || analogRead(topPad) > 500){
    playSong(carolOfTheBells, carolOfTheBellsTempo, notesCoB, wholenoteCoB);
    delay(100);
  }else if(analogRead(leftPad) <= 100 || analogRead(leftPad) > 500){
    playSong(weWishYouAMerryChristmas, weWishYouAMerryChristmasTempo, notesWYAMC, wholenoteWYAMC);
    delay(100);
  }else if(analogRead(rightPad) <= 100 || analogRead(rightPad) > 500){
    playSong(jingleBells, jingleBellsTempo, notesJB, wholenoteJB);
    delay(100);
  }else{
    defaultLights();
  }

  delay(50);
 
}



void playSong(int songName[], int tempo, int notes, int wholenote){



  //Actually plays the song
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

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
  /*
    SoftPWMSet(ALL, 255);
  // Wait for the fade-up and some extra delay.
  delay(1000);
  
  // Turn off WLED
  SoftPWMSet(ALL, 0);
  // Wait for the fade-down, and some extra delay.

  delay(1000);
 */
  
}
