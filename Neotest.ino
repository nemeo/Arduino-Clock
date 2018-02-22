#include <Adafruit_NeoPixel.h>  //nos LED

#define PIN     50
#define NUM_LEDS 6
#define BRIGHTNESS 10


static int test = LED_BUILTIN; // "static" to prevent modifying it in the code
int t=0, countLoop=0, choice=0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

// Couleurs pour les feux
//static uint32_t Vert = strip.Color(0, 255, 0);
static uint32_t Vert = strip.Color(127, 255, 0);
static uint32_t Orange = strip.Color(255,165, 0);
static uint32_t Rouge = strip.Color(255, 0, 0);
static uint32_t Eteint =strip.Color(0, 0, 0);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  t=100;
  pinMode(test, OUTPUT);
  Serial.begin(9600);// initialisationde la communication
  Serial.println("Communication initialisée");// envoi d'un message
}

// the loop function runs over and over again forever
 
void loop() {
  if (!countLoop++){
    Serial.println("Initialisation des couleurs"); 
    initMiche(25);// init Miche
    Serial.println("Possibilité porposée:\n1- Feux de signalisation\n2- Arc en ciel"); // choix
    darkIt();
  }
  if (countLoop == 1000){
    countLoop = 1;
    choice = 42;
  }
  if (choice!=42){
    digitalWrite(test, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(t);                       // wait for a second
    digitalWrite(test, LOW);    // turn the LED off by making the voltage LOW
    delay(t);                       // wait for a second
  }
  //réception du choix fait par l'utilisateur
  if (Serial.available()) {
    choice = Serial.parseInt(); // pour lire comme un entier et pas en ascii
  }
  switch (choice){
    case 0:
      break;
    case 1:
      Serial.println("Bon choix, voyons les feux de signalisation"); 
      colorSign(1000);
      choice=0;
      countLoop=0;
      break;
    case 2:
      Serial.println("Bon choix, voyons l'arc en ciel"); // choix fait
      rainbowCycle(10);
      choice=0;
      countLoop=0;
      break;
    case 42:
      rainbowCycle(10);
      break;
    default:
      Serial.println("Mauvais choix, essaie encore"); // choix faux
      choice=0;
      break;
  }
}

void initMiche(uint16_t wait){
  for (int i = 0 ; i<5;i++){
    colorWipe(strip.Color(255, 0, 0), wait); // Red
    colorWipe(strip.Color(0, 255, 0), wait); // Green
    colorWipe(strip.Color(0, 0, 255), wait); // Blue
    colorWipe(strip.Color(0, 0, 0, 255), wait); // White
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint16_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
void darkIt(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
  }
  strip.show();
}
// Fill the dots one after the other with a color
void colorSign(uint16_t wait) {
  darkIt();
  delay(2*wait);
  strip.setPixelColor(0, Vert);
  strip.setPixelColor(1, Eteint);
  strip.setPixelColor(2, Eteint);
  strip.show();
  delay(2*wait);
  strip.setPixelColor(0, Eteint);
  strip.setPixelColor(1, Orange);
  strip.setPixelColor(2, Eteint);
  strip.show();
  delay(wait/2);
  strip.setPixelColor(0, Eteint);
  strip.setPixelColor(1, Eteint);
  strip.setPixelColor(2, Rouge);
  strip.show();
  delay(2*wait);
  strip.setPixelColor(0, Eteint);
  strip.setPixelColor(1, Orange);
  strip.setPixelColor(2, Rouge);
  strip.show();
  delay(wait/2);
  strip.setPixelColor(0, Vert);
  strip.setPixelColor(1, Eteint);
  strip.setPixelColor(2, Eteint);
  strip.show();
  delay(2*wait);
  darkIt();
}
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256 * 5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}
