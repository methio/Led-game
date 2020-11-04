#include <Adafruit_NeoPixel.h>
#define PIN 4
# define NUMPIXELS 12
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int player1Pin = 11;
int player1Val = 1;
int player2Pin = 12;
int player2Val= 1;

bool play = false;
int victoryPin = 1;
int i = 11;

void setup() {
  Serial.begin(9600);

  pinMode(player1Pin, INPUT_PULLUP);
  pinMode(player2Pin, INPUT_PULLUP);

  pixels.begin();
  pixels.setBrightness(35);
  pixels.show();
}

void loop() {
  pixels.clear();
  
    //tcheck if we can start the game
  doWeStart();

  if (play) {
    /*
      Serial.print("play : ");
      Serial.println(play);
      Serial.print("valeur de I : ");
      Serial.println(i);
    */
    pixels.setPixelColor(i, 255, 0, 255);

    player1Val = digitalRead(player1Pin);
    player2Val = digitalRead(player2Pin);
    if (player1Val == 0 && i+1 == victoryPin){
      victory(255, 0);
    } else if (player2Val == 0 && i+1 == victoryPin){
      victory(0, 255);
    }

    if (i <= 0) {
      i = NUMPIXELS;
    } else {
      i--;
    }
  } else {
    for (int o = 0; o < NUMPIXELS; o++) {
      pixels.setPixelColor(o, 0, 100, 200);
    }
  }
  pixels.show();
  delay(20);
}

void doWeStart() {
  player1Val = digitalRead(player1Pin);
  player2Val = digitalRead(player2Pin);
  if (player1Val == 0 && player2Val == 0 && play == false) { //&& player 2 aussi
    play = true;
  }
}

void victory(int ColorR, int ColorG) {
  for (int u = 0; u < NUMPIXELS; u++) {
    pixels.setPixelColor(u, ColorR, ColorG, 0);
  }
  pixels.show();
  delay(1000);
  pixels.clear();
  play = false;
}
