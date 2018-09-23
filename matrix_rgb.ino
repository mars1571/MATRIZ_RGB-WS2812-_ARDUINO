#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN            6
#define NUMPIXELS      64
#define BRIGHTNESS 1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//COLOURS
uint32_t pixel_off = pixels.Color(0, 0, 0);
uint32_t white = pixels.Color(255, 255, 255);
uint32_t red = pixels.Color(255, 0, 0);

//FONTS MATRIXES
int blank_space[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};
int A[8][8] = {{0, 0, 0, 1, 1, 1, 1, 0}, {0, 0, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 0, 0, 1, 1, 0}, {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 0, 0, 1, 1, 0}, {0, 1, 1, 0, 0, 1, 1, 0}
};
int C[8][8] = {{0, 0, 0, 1, 1, 1, 0, 0}, {0, 0, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 0, 0, 1, 1, 0}, {0, 1, 1, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 0, 0, 0}, {0, 1, 1, 0, 0, 1, 1, 0}, {0, 0, 1, 1, 1, 1, 1, 0}, {0, 0, 0, 1, 1, 1, 0, 0}
};
int O[8][8] = {{0, 0, 0, 1, 1, 0, 0, 0}, {0, 0, 1, 1, 1, 1, 0, 0}, {0, 1, 1, 0, 0, 1, 1, 0}, {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0}, {0, 1, 1, 0, 0, 1, 1, 0}, {0, 0, 1, 1, 1, 1, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0}
};
int D[8][8] = {{0, 1, 1, 1, 1, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 0, 0}, {0, 1, 1, 0, 0, 1, 1, 0}, {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0}, {0, 1, 1, 0, 0, 1, 1, 0}, {0, 1, 1, 1, 1, 1, 0, 0}, {0, 1, 1, 1, 1, 0, 0, 0}
};
int I[8][8] = {{0, 0, 1, 1, 1, 1, 0, 0}, {0, 0, 1, 1, 1, 1, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0}, {0, 0, 1, 1, 1, 1, 0, 0}, {0, 0, 1, 1, 1, 1, 0, 0}
};
int N[8][8] = {{0, 1, 1, 0, 0, 1, 1, 0}, {0, 1, 1, 0, 0, 1, 1, 0}, {0, 1, 1, 1, 0, 1, 1, 0}, {0, 1, 1, 1, 0, 1, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 0, 1, 1, 1, 0}, {0, 1, 1, 0, 0, 1, 1, 0}, {0, 1, 1, 0, 0, 1, 1, 0}
};
int G[8][8] = {{0, 0, 1, 1, 1, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 0, 0}, {0, 1, 1, 0, 0, 0, 0, 0}, {0, 1, 1, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0}, {0, 1, 1, 0, 0, 0, 1, 0}, {0, 1, 1, 1, 1, 1, 1, 0}, {0, 0, 1, 1, 1, 1, 1, 0}
};

void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.setBrightness(BRIGHTNESS);
  pixels.begin();
  Serial.begin(9600);
}


void loop() {
  WordSpeller("CODING", 1000);
}


void FontRenderizer (int font[8][8], uint32_t color, uint32_t background_color) {
  int count = -1;
  for (int i = 0 ; i <= 7 ; i++) {
    for (int j = 0 ; j <= 7 ; j++) {
      if (font[i][j] == 1) {
        count = count + 1;
        pixels.setPixelColor(count, color);
      } else {
        count = count + 1;
        pixels.setPixelColor(count, background_color);
      }
    }
  }
  pixels.show();
}


void WordSpeller (String words, int time_interval) {
  for (int i = 0 ; i <= words.length() - 1 ; i++) {
    switch (words[i]) {
      case 'C':
        FontRenderizer(C, white, red);
        break;
      case 'O':
        FontRenderizer(O, red, white);
        break;
      case 'D':
        FontRenderizer(D, white, red);
        break;
      case 'I':
        FontRenderizer(I, red, white);
        break;
      case 'N':
        FontRenderizer(N, white, red);
        break;
      case 'G':
        FontRenderizer(G, red, white);
        break;
    }
    delay(time_interval);
  }
}
