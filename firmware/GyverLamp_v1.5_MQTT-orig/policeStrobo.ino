bool sw = false;

void pattern_1()  {

  EVERY_N_MILLIS(modes[currentMode].speed) {
    FastLED.clear(); sw = !sw;

    if (sw) {
      for (int x = 1; x < round(WIDTH/2); x++) {
        for (int y = 0; y < HEIGHT; y++) {
          drawPixelXY(x, y, CRGB::Red);
        }
      }
     } else {

     for (int x = round(WIDTH/2); x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
          drawPixelXY(x, y, CRGB::Blue);
        }
      } 
     }
  }
}

void pattern_2()  {

  EVERY_N_MILLIS(modes[currentMode].speed) {
    FastLED.clear(); sw = !sw;

    if (sw) {
      for (int x = 1; x < WIDTH; x++) {
        for (int y = 0; y <  round(HEIGHT/2); y++) {
          drawPixelXY(x, y, CRGB::Red);
        }
      }
     } else {

     for (int x = 1; x < WIDTH; x++) {
        for (int y = round(HEIGHT/2); y < HEIGHT; y++) {
          drawPixelXY(x, y, CRGB::Blue);
        }
      } 
    }
  }
}

void pattern_3() {

  EVERY_N_MILLIS(modes[currentMode].speed) {
    FastLED.clear(); 
    sw = !sw;

    for (int x = 1; x < WIDTH; x++) {
      drawPixelXY(x, round(HEIGHT/2), CRGB::White);
    }

    if (sw) {
      for (int x = 1; x < WIDTH; x++) {
        for (int y = 0; y <=  round(HEIGHT/3); y++) {
          drawPixelXY(x, y, CRGB::Red);
        }
      }
     } else {

     for (int x = 1; x < WIDTH; x++) {
        for (int y = round(HEIGHT*2/3); y < HEIGHT; y++) {
          drawPixelXY(x, y, CRGB::Blue);
        }
      }
    }  
  }
}

void pattern_4() {

  EVERY_N_MILLIS(modes[currentMode].speed) {
    FastLED.clear(); sw = !sw;

    if (sw) {
      for (int x = 1; x < WIDTH; x++) {
        for (int y = 0; y <  HEIGHT; y++) {
          drawPixelXY(x, y, CRGB::Red);
        }
      }
     } else {

     for (int x = 1; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
          drawPixelXY(x, y, CRGB::Blue);
        }
      } 
    }
  }  
}

void policeStroboRoutine() {

  if ((modes[currentMode].scale >= 0) && (modes[currentMode].scale < 25)) pattern_1();
  if ((modes[currentMode].scale >= 25) && (modes[currentMode].scale < 50)) pattern_2();
  if ((modes[currentMode].scale >= 50) && (modes[currentMode].scale < 75)) pattern_3();
  if (modes[currentMode].scale >= 75) pattern_4();

}
