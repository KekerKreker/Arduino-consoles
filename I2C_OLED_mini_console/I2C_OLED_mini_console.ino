/*
Console
OLED I2C 128x64
6 buttons
arduino board
blutooth module hc-05
UP-up button
Сl CL-Enter
FI - fi
DO - вниз
RI - вправо
LE - ліво



*/



//librares


#include <OLED_I2C.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
//pins
#define UP 5
#define CL 3

#define RI 6
#define LE 7
#define DO 4
#define FI 2
#define BL 7
#define TX 11
#define RX 12
#define dela 50

SoftwareSerial mySerial(TX, RX);
OLED myOLED(SDA, SCL, 8);

extern uint8_t SmallFont[];
//vars
//flappy bird
byte bird_y = 37, bird_s = 0, bird_fs = 1, bird_js = 2, bird_wx = 124, bird_wy, bird_ws = 1;
//arcanoidanoid
char arcanoidu[4][5]{ { 4, 4, 4, 4, 4 },
                      { 3, 3, 3, 3, 3 },
                      { 2, 2, 2, 2, 2 },
                      { 1, 1, 1, 1, 1 } };
char arcanoidbx;
char arcanoidw = 0;
char arcanoids;
char arCLiv = 3;
char arcanoidres = 3;
char arcanoidbsx = 0;
char arcanoidbsy = -1;
char arcanoidx = 60;
char arcanoidby = 59;
//sleep
byte tsleep = 0;
bool sleep = 0;
char sleepx = 50;
char sleepy = 19;
char sleepxs = 1;
char sleepys = 1;
//paint
char paintx = 0;
char painty = 16;
//ping pong
char bsx = -2;
char bsy = 0;
byte pl1 = 38;
byte pc = 38;
byte bx = 62;
byte by = 40;
byte ax = 0;
byte ay = 0;
byte sp1y = 46;
byte sp1x = 1;
byte sp2y = 50;
byte sp2x = 127;
//score for all games
byte s1 = 0;
byte s2 = 0, fti = 0;
//fishing
char fsx = 0, fsy = 0, fx = 16, fy = 17, fmx = 19, fmy = 20;
char fpsx = 58, fpsy = 48, fpy = 48, fpx = 58, fpod = 0;
//menu
char slct = 0;
char sx = 0;
char sy = 0;
char game = -1;
char val = 0;
//tic tac toe
char px;
char py;
char xx = 0;
char yy = 0;
char hod = 1;
char XOm = 0;
char Map[3][3] = {
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 }
};
//3d
const PROGMEM char mapa[8][8] = {
  { 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 1, 0, 1 },
  { 1, 1, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 1, 0, 1 },
  { 1, 1, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1 },

};

byte blA = 1;
//images
extern uint8_t pp[];
extern uint8_t bl[];
extern uint8_t Xo[];

extern uint8_t sn[];
extern uint8_t Se[];
extern uint8_t Pa[];
extern uint8_t arc[];
void setup() {
  sleep = EEPROM.read(100);
  //  begin display and serial
  randomSeed(analogRead(A0));
  mySerial.begin(9600);
  myOLED.begin();
  //font
  myOLED.setFont(SmallFont);
  // aple for snake
  ax = random(2, 125);
  ay = random(17, 62);
  bird_wy = random(22, 57);
  noTone(8);
}

void loop() {


  if (mySerial.available()) {
    val = mySerial.read();
  }
  if (game == 0) {
    if (mySerial.available()) { game = -1; }
  }
  if (game == -2) {
    slep();
  }
  if (game == -1) {

    myOLED.update();
    delay(100);
    if (sleep == 1) {
      tsleep++;
      if (tsleep == 100) { game = -2; }
    }
    myOLED.clrScr();

    bitmap(bl, 256, 16, 0, 16);
    bitmap(pp, 256, 16, 16, 16);
    bitmap(sn, 256, 16, 32, 16);
    myOLED.print("3d", 18, 36);
    bitmap(pp, 256, 16, 32, 32);
    myOLED.print("2", 32, 32);
    bitmap(Xo, 256, 16, 48, 16);
    bitmap(Xo, 256, 16, 64, 16);
    myOLED.print("2", 64, 16);
    bitmap(Se, 256, 16, 80, 16);
    bitmap(Pa, 256, 16, 96, 16);
    bitmap(arc, 256, 16, 112, 16);
    myOLED.drawRoundRect(16 * sx, 16 * sy + 16, 16 * sx + 15, 16 * sy + 31);
    if (digitalRead(CL) == 1 || val == '5') {
      myOLED.clrScr();

      menumus();
      game = slct;
    }
    if (digitalRead(RI) == 1 && slct < 23) {

      sx++;
      slct++;
      if (sx > 7) {
        sy++;
        sx = 0;
      }
    }


    if (digitalRead(LE) == 1 && slct > 0) {

      sx--;
      slct -= 1;
      if (sx < 0) {
        sx = 7;
        sy--;
      }
    }
    if (slct != 0 && slct != 5) {
      myOLED.print("HI-score:", 3, 3);
      myOLED.printNumI(EEPROM.read(slct), 56, 3);
    }
  }
  if (game == 1) {
    PingPong();
  }
  if (game == 10) {
    PingPong2();
  }
  if (game == 11) {
    bird();
  }
  if (game == 2) {
    Snake();
  }
  if (game == 4) {
    Xo2();
  }
  if (game == 3) {
    Xo1();
  }
  if (game == 5) {
    seting();
  }
  if (game == 6) {
    paint();
  }
  if (game == 7) {
    arcanoid();
  }
  if (game == 9) {
    g3d();
  }
  if (game == 8) {
    fish();
  }
}
void pingpongarduinomove() {
  if (bx > 63) {
    if (pc + 1 > by && pc > 17) {
      pc--;
    }

    if (pc + 1 < by && pc < 57) {
      pc++;
    }
  }
}
void menumus() {

  for (byte strt = 0; strt < 3; strt++) {
    tone(8, 500, 300);
    delay(200);

    tone(8, 700, 200);
    delay(200);

    tone(8, 600, 340);
    delay(200);
  }
}
void XOpc() {

  py = random(0, 3);
  px = random(0, 3);
  mapread();

  if (Map[py][px] == 0) {
    Map[py][px] = -1;

  } else {
    if (XOm == 0) {
      xoCLr();
    }
    if (XOm == 1) {
      XOpc();
      XOm = 0;
    }
  }
}
void PingPong2() {

  if (digitalRead(CL) == 1 || val == '5') {
    gameCLer();
  }
  myOLED.drawRoundRect(0, 16, 127, 63);
  myOLED.drawLine(5, pl1, 5, pl1 + 5);
  myOLED.drawLine(122, pc, 122, pc + 5);
  for (byte l = 17; l < 62; l += 2) {
    myOLED.setPixel(63, l);
  }
  myOLED.setPixel(bx, by);
  myOLED.printNumI(s1, 63 - 18, 2);
  myOLED.print(":", 63, 2);
  myOLED.printNumI(s2, 63 + 18, 2);
  myOLED.update();
  delay(dela);
  bx += bsx;
  by += bsy;
  if (digitalRead(LE) == 1 || val == '4') {
    if (pl1 > 17) {
      pl1--;
    }
  }

  if (digitalRead(FI) == 1 && pl1 < 57) {
    pl1++;
  }
  if (digitalRead(UP) == 1 || val == '4') {
    if (pc > 17) {
      pc--;
    }
  }

  if (digitalRead(RI) == 1 && pc < 57) {
    pc++;
  }

  if (bx == 6 || bx == 5 || bx == 7) {

    if (by == pl1) {
      bsx = 1;
      bsy = -2;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
    if (by == pl1 + 1) {
      bsx = 1;
      bsy = -1;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
    if (by == pl1 + 4) {
      bsx = 1;
      bsy = 2;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
    if (by == pl1 + 3) {
      bsx = 1;
      bsy = 1;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
    if (by == pl1 + 2) {
      bsx = 2;
      bsy = 0;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
  }
  if (bx == 123 || bx == 122 || bx == 121 || bx == 124) {

    if (by == pc) {
      bsx = -1;
      bsy = -2;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
    if (by == pc + 3) {
      bsx = -1;
      bsy = 1;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
    if (by == pc + 1) {
      bsx = -1;
      bsy = -1;

      tone(8, 200);
      delay(50);
      noTone(8);
    }
    if (by == pc + 2) {
      bsx = -2;
      bsy = 0;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
    if (by == pc + 4) {
      bsx = -1;
      bsy = 2;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
  }
  if (by < 18 || by > 62) {
    bsy *= -1;
    tone(8, 200);
    delay(50);
    noTone(8);
  }
  if (bx > 126) {
    s1++;
    bx = 63;
    by = 31;
    bsy = 0;
    bsx = -2;
    tone(8, 500);
    delay(dela);
    noTone(8);
    myOLED.invert(true);
    myOLED.update();
    tone(8, 500);
    delay(300);
    noTone(8);
    myOLED.invert(false);
    myOLED.update();
  }
  if (bx < 2) {
    s2++;
    bx = 63;
    by = 31;
    bsy = 0;
    bsx = 2;
    tone(8, 500);
    delay(dela);
    noTone(8);
    myOLED.invert(true);
    myOLED.update();
    tone(8, 500);
    delay(300);
    noTone(8);
    myOLED.invert(false);
    myOLED.update();
  }

  myOLED.clrScr();
}
void PingPong() {

  if (digitalRead(CL) == 1 || val == '5') {
    gameCLer();
  }
  myOLED.drawRoundRect(0, 16, 127, 63);
  myOLED.drawLine(5, pl1, 5, pl1 + 5);
  myOLED.drawLine(122, pc, 122, pc + 5);
  for (byte l = 17; l < 62; l += 2) {
    myOLED.setPixel(63, l);
  }
  myOLED.setPixel(bx, by);
  myOLED.printNumI(s1, 63 - 18, 2);
  myOLED.print(":", 63, 2);
  myOLED.printNumI(s2, 63 + 18, 2);
  myOLED.update();
  delay(dela);
  bx += bsx;
  by += bsy;
  if (digitalRead(UP) == 1 || val == '4') {
    if (pl1 > 17) {
      pl1--;
    }
  }

  if (digitalRead(DO) == 1 || val == '2') {
    if (pl1 < 57) {
      pl1++;
    }
  }

  if (bx == 6 || bx == 5 || bx == 7) {

    if (by == pl1) {
      bsx = 1;
      bsy = -2;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
    if (by == pl1 + 1) {
      bsx = 1;
      bsy = -1;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
    if (by == pl1 + 4) {
      bsx = 1;
      bsy = 2;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
    if (by == pl1 + 3) {
      bsx = 1;
      bsy = 1;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
    if (by == pl1 + 2) {
      bsx = 2;
      bsy = 0;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
  }
  if (bx == 123 || bx == 122 || bx == 121 || bx == 124) {

    if (by == pc) {
      bsx = -1;
      bsy = -2;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
    if (by == pc + 3) {
      bsx = -1;
      bsy = 1;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
    if (by == pc + 1) {
      bsx = -1;
      bsy = -1;

      tone(8, 200);
      delay(50);
      noTone(8);
    }
    if (by == pc + 2) {
      bsx = -2;
      bsy = 0;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
    if (by == pc + 4) {
      bsx = -1;
      bsy = 2;
      tone(8, 200);
      delay(50);
      noTone(8);
    }
  }
  if (by < 18 || by > 62) {
    bsy *= -1;
    tone(8, 200);
    delay(50);
    noTone(8);
  }
  if (bx > 126) {
    s1++;
    bx = 63;
    by = 31;
    bsy = 0;
    bsx = -2;
    tone(8, 500);
    delay(dela);
    noTone(8);
    myOLED.invert(true);
    myOLED.update();
    tone(8, 500);
    delay(300);
    noTone(8);
    myOLED.invert(false);
    myOLED.update();
  }
  if (bx < 2) {
    s2++;
    bx = 63;
    by = 31;
    bsy = 0;
    bsx = 2;
    tone(8, 500);
    delay(dela);
    noTone(8);
    myOLED.invert(true);
    myOLED.update();
    tone(8, 500);
    delay(300);
    noTone(8);
    myOLED.invert(false);
    myOLED.update();
  }

  myOLED.clrScr();
  pingpongarduinomove();
}
void Snake() {
  if (EEPROM.read(1) < s1) {
    EEPROM.update(2, s1);
  }
  delay(dela);
  myOLED.clrScr();
  if (s1 < 126 && s2 < 126) {
    if (digitalRead(CL) == 1 || val == '5') {
      gameCLer();
    }
    myOLED.drawRoundRect(0, 16, 127, 63);
    myOLED.setPixel(sp1x, sp1y);
    myOLED.printNumI(s1, 4, 4);
    myOLED.printNumI(s2, 105, 4);
    myOLED.setPixel(sp2x, sp2y);

    myOLED.setPixel(ax, ay);

    myOLED.update();
    delay(dela);

    if (ax < sp2x) {
      sp2x--;
    }
    if (ax > sp2x) {
      sp2x++;
    }
    if (digitalRead(CL) == 1) {
      sp1x--;
    }
    if (digitalRead(RI) == 1) {
      sp1x++;
    }
    if (digitalRead(LE) == 1) {
      sp1x--;
    }
    if (sp1x > 126) {
      sp1x = 1;
    }
    if (sp2x > 190) {
      sp2x = 126;
    }
    if (sp2y == ay && sp2x == ax) {
      ax = random(2, 125);
      ay = random(17, 62);
      s2++;
      tone(8, 800);
    }
    if (sp1y == ay && sp1x == ax) {
      ax = random(2, 125);
      ay = random(17, 62);
      s1++;
      tone(8, 800);
    }
  }
  if (digitalRead(UP) == HIGH && sp1y > 17) {
    sp1y--;
  }

  if (digitalRead(DO) == HIGH && sp1y < 62) {
    sp1y++;
  }
  if (sp2y > ay && sp2y > 17) {
    sp2y--;
  }

  if (sp2y < ay && sp2y < 62) {
    sp2y++;
  }


  if (s1 > 224 || s2 > 224) {
    gameCLer();
  }
}
void xoCLr() {
  myOLED.invert(true);
  myOLED.update();
  delay(dela);
  myOLED.invert(false);
  myOLED.update();
  delay(dela);
  Map[0][0] = 0;
  Map[0][1] = 0;
  Map[0][2] = 0;
  Map[1][0] = 0;
  Map[1][1] = 0;
  Map[1][2] = 0;
  Map[2][0] = 0;
  Map[2][1] = 0;
  Map[2][2] = 0;
}
void mapread() {
  for (byte x = 0; x < 3; x++) {
    for (byte y = 0; y < 3; y++) {
      if (Map[x][y] == 0) {
        XOm = 1;
        break;
      }
    }
  }
}
void drawmapXo() {

  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      myOLED.drawRect(40 + y * 15, 17 + x * 15, (40 + y * 15) + 15, (17 + x * 15) + 15);
      if (x == yy && y == xx) {
        myOLED.drawRoundRect(40 + y * 15 + 1, 17 + x * 15 + 1, (40 + y * 15) + 14, (17 + x * 15) + 14);
        if (Map[yy][xx] == 0) {
          if (hod == 1) {
            myOLED.drawCircle(40 + y * 15 + 8, 17 + x * 15 + 8, 5.5);
          }
          if (hod == -1) {
            myOLED.drawLine(40 + y * 15 + 2, 17 + x * 15 + 2, 40 + y * 15 + 13, 17 + x * 15 + 13);
            myOLED.drawLine(40 + y * 15 + 13, 17 + x * 15 + 2, 40 + y * 15 + 2, 17 + x * 15 + 13);
          }
        }
      }
      if (Map[x][y] == 1) {

        myOLED.drawCircle(40 + y * 15 + 8, 17 + x * 15 + 8, 5.5);
      }
      if (Map[x][y] == -1) {

        myOLED.drawLine(40 + y * 15 + 2, 17 + x * 15 + 2, 40 + y * 15 + 13, 17 + x * 15 + 13);
        myOLED.drawLine(40 + y * 15 + 13, 17 + x * 15 + 2, 40 + y * 15 + 2, 17 + x * 15 + 13);
      }
    }
  }
}
void gameCLer() {
  if (EEPROM.read(slct) < s1) {
    EEPROM.update(slct, s1);
  }
  for (byte x = 0; x < 4; x++) {
    for (byte y = 0; y < 5; y++) {
    }
  }
  arcanoidbx = 63;
  arcanoids = 0;
  arCLiv = 3;
  arcanoidbsx = 0;
  arcanoidbsy = -1;
  arcanoidx = 60;
  arcanoidby = 59;
  paintx = 0;
  painty = 16;
  pl1 = 38;
  pc = 38;
  bx = 62;
  by = 40;
  ax = random(2, 125);
  ay = random(17, 62);
  sp1y = 46;
  sp1x = 1;
  sp2y = 50;
  sp2x = 127;
  bsx = -2;
  bsy = 0;
  s1 = 0;
  s2 = 0;
  sx = 0;
  sy = 0;
  game = -1;
  px = 0;
  py = 0;
  slct = 0;
  xx = 0;
  yy = 0;
  hod = 1;
  XOm = 0;
  xoCLr();
}

void paint() {

  myOLED.clrScr();

  for (byte d = 0; d != 4;) {
    if (mySerial.available()) {
      String ss = mySerial.readString();
      char buffer[24];
      ss.toCharArray(buffer, 11);


      char pax, pay;


      pax = atoi(strtok(buffer, " "));
      pay = atoi(strtok(NULL, " "));
      myOLED.invPixel(pax, pay + 16);
    }
    if (painty == 15) {
      if (digitalRead(FI) == 1) {
        myOLED.clrScr();
      }
      myOLED.print("CLear screan", CENTER, 4);
    }


    if (digitalRead(LE) == 1) {

      if (paintx > 0) {
        paintx -= 1;
      }
    }

    if (digitalRead(UP) == 1) {
      if (painty > 15) {

        painty -= 1;
      }
    }
    if (digitalRead(RI) == 1) {

      if (paintx < 127) {

        paintx += 1;
      }
    }
    if (digitalRead(DO) == 1) {

      if (painty < 63) {
        painty += 1;
      }
    }
    if (digitalRead(FI) == 1) {

      myOLED.invPixel(paintx, painty);
    }

    myOLED.update();
    delay(100);

    if (digitalRead(CL) == 1) {
      gameCLer();
      d = 4;
    }
  }
}
void arcanoid() {
  for (byte x = 0; x < 4; x++) {
    for (byte y = 0; y < 5; y++) {
      arcanoidu[x][y] = random(0, 5);
      if (arcanoidu[x][y] == 0) { arcanoidu[x][y] = -1; }
    }
  }
  while (game == 7) {
    if (arCLiv == 0 || digitalRead(CL) == 1) {
      myOLED.clrScr();
      myOLED.print("Game Over", 63 - ((9 * 6) / 2), 8 + (48 / 2));
      myOLED.update();
      delay(500);
      if (s1 > EEPROM.read(7)) {
        myOLED.print("New Hi-score", 63 - ((12 * 6) / 2), 17 + (48 / 2));
        myOLED.update();
        tone(8, 300);
        delay(100);
        tone(8, 400);
        delay(100);
        tone(8, 500);
        delay(700);
      }
      noTone(8);
      gameCLer();
    }
    if (digitalRead(FI) == 1) {
      if (arcanoids == 0) {
        arcanoids = 1;
      } else {
        if (arcanoidres > 0 && s1 > 0 && arcanoidby < 48) {
          arcanoids = 0;
          arcanoidres--;
          s1--;
        }
      }
    }
    if (arcanoidby > 62) {
      arcanoidbx = arcanoidx + 4;
      arcanoidbsx = 0;
      arcanoidbsy = -1;
      arcanoidby = 59;
      arCLiv--;
      arcanoids = 0;
    }
    if (arcanoids == 0) {
      arcanoidbx = arcanoidx + 4;
      arcanoidby = 59;
    }
    if (arcanoids == 1) {

      arcanoidby += arcanoidbsy;
      arcanoidbx += arcanoidbsx;


      if (arcanoidby < 18) {
        arcanoidbsy *= -1;
        tone(8, 400);
        delay(50);
        noTone(8);
        if (arcanoidbsx != 1 && arcanoidbsx != -1) {
          if (random(0, 2) == 1) {
            arcanoidbsx = 1;
          } else {
            arcanoidbsx = -1;
          }
        }
      }
    }
    if (arcanoidby > 59 && arcanoidbx > arcanoidx && arcanoidbx < arcanoidx + 9) {
      arcanoidbsy *= -1;
      tone(8, 400);
      delay(50);
      noTone(8);
    }


    myOLED.clrScr();
    myOLED.printNumI(s1, 4, 4);
    myOLED.printNumI(arCLiv, 117, 4);
    myOLED.printNumI(arcanoidres, 100, 4);
    myOLED.drawRoundRect(0, 16, 127, 63);
    myOLED.drawLine(arcanoidx, 60, arcanoidx + 9, 60);
    myOLED.setPixel(arcanoidbx, arcanoidby);
    if (digitalRead(LE) == 1 && arcanoidx > 1) {
      arcanoidx--;
    }
    if (digitalRead(RI) == 1 && arcanoidx + 9 < 126) {
      arcanoidx++;
    }
    if (arcanoidbx <= 1) {
      arcanoidbsx *= -1;
    }
    if (arcanoidbx >= 126) {
      arcanoidbsx *= -1;
    }
    arcanoidw = 1;
    for (byte x = 0; x < 4; x++) {
      for (byte y = 0; y < 5; y++) {
        if (arcanoidu[x][y] > 0) {
          arcanoidw = 0;
          break;
        }
      }
    }
    if (arcanoidw == 1) {
      myOLED.clrScr();
      tone(8, 700);
      delay(60);
      tone(8, 800);
      myOLED.print("Game Win", 63 - ((8 * 6) / 2), 8 + (48 / 2));
      myOLED.update();
      delay(500);
      if (s1 > EEPROM.read(7)) {
        myOLED.print("New Hi-score", 63 - ((12 * 6) / 2), 17 + (48 / 2));
        myOLED.update();
        tone(8, 300);
        delay(100);
        tone(8, 400);
        delay(100);
        tone(8, 500);
        delay(700);
      }
      noTone(8);
      gameCLer();
    }
    for (byte x = 0; x < 4; x++) {
      for (byte y = 0; y < 5; y++) {
        if (arcanoidu[x][y] != 0) {
          if (arcanoidbx >= y * 24 + 5 && arcanoidbx <= y * 24 + 24 && arcanoidby >= 17 + (x * 5) && arcanoidby <= 17 + (x * 5) + 5) {
            if (arcanoidbsx != 1 && arcanoidbsx != -1) {
              if (random(0, 2) == 1) {
                arcanoidbsx = 1;
              } else {
                arcanoidbsx = -1;
              }
            }

            arcanoidbsy *= -1;
            if (arcanoidu[x][y] > 0) {
              s1++;
              tone(8, 400);
              delay(50);
              noTone(8);
            }
            arcanoidu[x][y]--;

            if (arcanoidby >= 18 + (x * 5) && 17 + (x * 5) + 4) { arcanoidbsx *= -1; }
          }
          if (arcanoidu[x][y] > 2) {
            myOLED.drawLine(y * 24 + 5 + 4, 17 + (x * 5), y * 24 + 5 + 4, 17 + (x * 5) + 5);
          }
          if (arcanoidu[x][y] > 0) { myOLED.drawLine(y * 24 + 5 + 7, 17 + (x * 5), y * 24 + 5 + 7, 17 + (x * 5) + 5); }
          if (arcanoidu[x][y] > 1) { myOLED.drawLine(y * 24 + 5 + 10, 17 + (x * 5), y * 24 + 5 + 10, 17 + (x * 5) + 5); }
          if (arcanoidu[x][y] > 3) { myOLED.drawLine(y * 24 + 5 + 13, 17 + (x * 5), y * 24 + 5 + 13, 17 + (x * 5) + 5); }
          myOLED.drawRoundRect(y * 24 + 5, 17 + (x * 5), y * 24 + 24, 17 + (x * 5) + 5);
        }
      }
    }
    delay(dela);
    myOLED.update();
  }
}
void slep() {
  sleepx += sleepxs;
  sleepy += sleepys;
  if (sleepx == 127 - (8 * 6) || sleepx == 0) {
    sleepxs *= -1;
    tone(8, 400);
    delay(50);
    noTone(8);
  }
  if (sleepy == 63 - 8 || sleepy == 16) {
    sleepys *= -1;
    tone(8, 400);
    delay(50);
    noTone(8);
  }
  myOLED.clrScr();
  if (digitalRead(CL) == 1) {
    tsleep = 0;
    game = -1;
  }
  myOLED.print("Andruino", sleepx, sleepy);
  myOLED.update();
  delay(25);
}
void bitmap(char ssw[256], int longimg, byte dow, char posx, char posy) {
  int y = 0;
  int xd = 0;
  for (int x = 0; x < longimg; x++) {
    if (xd == dow) {
      xd = 0;
      y++;
    }
    if (pgm_read_byte(&ssw[x]) == 1) {
      myOLED.setPixel(posx + xd, posy + y);
    }
    xd++;
  }
}
void fish() {
  myOLED.clrScr();
  myOLED.setPixel(fpsx, fpsy);
  if (fpod == 1) {
    if (fy < fpy + 2) { fy++; }
    if (fy > fpy + 2) { fy--; }
    if (fx < fpx) { fx++; }
    if (fx > fpx) { fx--; }
    myOLED.setPixel(fpx, fpy + 2);
    myOLED.setPixel(fpx - 1, fpy + 3);
    myOLED.setPixel(fpx + 1, fpy + 3);
    myOLED.setPixel(fpx, fpy + 3);
    myOLED.drawLine(63, 63, 60, 46);
    myOLED.drawLine(60, 46, 56, 38);
  }

  if (fpod == 0) {
    myOLED.setPixel(fpx, fpy);
    myOLED.setPixel(fpx - 1, fpy + 1);
    myOLED.setPixel(fpx, fpy + 1);
    myOLED.setPixel(fpx + 1, fpy + 1);
    myOLED.setPixel(fpx, fpy + 3);
    myOLED.setPixel(fpx - 1, fpy + 3);
    myOLED.setPixel(fpx + 1, fpy + 3);
    myOLED.drawLine(63, 63, 60, 38);
    if (fy == fmy) { fmy = random(17, 62); }
    if (fy < fmy) { fy++; }
    if (fy > fmy) { fy--; }
    if (fx == fmx) { fmx = random(1, 108); }
    if (fx < fmx) { fx++; }
    if (fx > fmx) { fx--; }
  }
  if (floor(sqrt(((fx - fpx) * (fx - fpx)) + ((fy - fpy) * (fy - fpy)))) < 10) {

    if (random(-1, floor(sqrt(((fx - fpx) * (fx - fpx)) + ((fy - fpy) * (fy - fpy))))) >= floor(sqrt(((fx - fpx) * (fx - fpx)) + ((fy - fpy) * (fy - fpy)))) - 1 && fti > random(10, 200)) {
      fpod = 1;
      fti = 0;
    }
  }

  myOLED.drawRoundRect(0, 0, 127, 15);

  myOLED.drawRoundRect(0, 16, 127, 63);
  myOLED.printNumI(s1, 4, 4);
  myOLED.update();
  delay(50);
  if (digitalRead(FI) == 1 && fpod == 1) {
    if (fpx > 60) { fpx--; }
    if (fpx < 60) { fpx++; }
    if (fpy > 58) { fpy--; }
    if (fpy < 58) { fpy++; }
    if (fpx == 60 && fpy == 58) {
      fpod = 0;
      s1++;
      tone(8, 400);
      delay(50);
      noTone(8);
    }
  }
  fti++;
  if (fti == 254) {
    fti = 0;
    fpod = 0;
  }
  if (digitalRead(LE) == 1) { fpsx--; }
  if (digitalRead(DO) == 1) { fpsy++; }
  if (digitalRead(UP) == 1) { fpsy--; }
  if (digitalRead(RI) == 1) { fpsx++; }
  if (digitalRead(CL) == 1 && fpod == 0) {
    fpx = fpsx;
    fpy = fpsy;
  }
}
void g3d() {

  char CASTED_RAYS = 64;
  float STEP_ANGLE = (M_PI / 3) / CASTED_RAYS;
  float player_angle = M_PI;
  char x3d = 63, y3d = 32;
  while (game == 9) {
    myOLED.clrScr();
    float start_angle = player_angle - ((M_PI / 3) / 2);
    for (char ray = 0; ray < CASTED_RAYS; ray++) {
      for (char depth = 0; depth < 100; depth += 1) {
        char target_x = x3d - floor(sin(start_angle) * depth);
        char target_y = y3d + floor(cos(start_angle) * depth);

        if (pgm_read_byte(&mapa[target_y / 8][target_x / 16]) == 1) {
          for (int g = 0; g < 2; g++) {
            myOLED.drawLine(ray * 2 + g, (63 - (depth)) / 2, ray * 2 + g, 63 - ((63 - (depth)) / 2));
          }
          break;
        }
      }
      start_angle += STEP_ANGLE;
    }
    if (digitalRead(4) == 1) {
      x3d = x3d - floor(sin(player_angle) * 2);
      y3d = y3d + floor(cos(player_angle) * 2);
    }
    if (digitalRead(5) == 1) {
      x3d = x3d + floor(sin(player_angle) * 2);
      y3d = y3d - floor(cos(player_angle) * 2);
    }
    if (digitalRead(6) == 1) {
      player_angle += 0.1;
    }
    if (digitalRead(7) == 1) {
      player_angle -= 0.1;
    }
    myOLED.update();
  }
}
void bird() {
  delay(50);
  myOLED.clrScr();
  myOLED.drawRoundRect(bird_wx, 16, bird_wx + 6, bird_wy);
  myOLED.drawRoundRect(bird_wx, bird_wy + 16, bird_wx + 6, 63);
  myOLED.printNumI(s1, 4, 4);
  bird_wx--;
  if (bird_wx == 0) {
    if (bird_y > bird_wy && bird_y + 6 < bird_wy + 16) {
      tone(8, 500);
      delay(50);
      noTone(8);
      s1++;
    } else {
      tone(8, 100);
      delay(50);
      tone(8, 110);
      delay(50);
      tone(8, 90);
      delay(50);
      noTone(8);
      gameCLer();
      bird_wx = 124;
      bird_wy = random(22, 57);
    }
  }
  myOLED.drawRoundRect(2, bird_y, 8, bird_y + 6);
  myOLED.drawRoundRect(0, 16, 127, 63);
  myOLED.update();
  if (bird_y + 6 < 62) {
    bird_y += bird_fs;
  }
  if (digitalRead(FI) == 1 && bird_y > 17) {
    bird_y -= bird_js;
  }
}
void seting() {
  char ss = 0;
  while (game == 5) {
    myOLED.clrScr();

    myOLED.print("CLear score", CENTER, 17);
    myOLED.print("Sleep", CENTER, 25);
    if (digitalRead(DO) == 1) {
      ss++;
      if (ss > 3) { ss = 0; }
    }
    if (digitalRead(UP) == 1) {
      ss--;
      if (ss < 0) { ss = 3; }
    }
    if (ss == 0 && digitalRead(CL) == 1) {
      for (char i = 0; i < 400; i++) {
        EEPROM.update(i, 0);
      }
    }
    if (ss == 1 && digitalRead(CL) == 1) {
      sleep = !sleep;
      EEPROM.update(100, sleep);
    }
    myOLED.update();
    delay(dela);
  }
}
void Xo1() {
  delay(dela);
  myOLED.clrScr();

  if (digitalRead(UP) == HIGH && yy > 0) {
    yy--;
  }
  if (digitalRead(DO) == HIGH && yy < 2) {
    yy++;
  }
  if (digitalRead(LE) == 1 && xx > 0) {
    xx--;
  }
  if (digitalRead(RI) == HIGH && xx < 2) {
    xx++;
  }
  if (digitalRead(FI) == 1) {


    if (Map[yy][xx] == 0) {
      Map[yy][xx] = 1;
      tone(8, 400);
      delay(50);
      noTone(8);
      XOpc();
    }
  }
  Xowin();
  myOLED.printNumI(s1, 4, 4);
  myOLED.printNumI(s2, 109, 4);
  drawmapXo();
  myOLED.update();


  if (digitalRead(CL) == HIGH) { gameCLer(); }
}
void Xo2() {
  delay(dela);
  myOLED.clrScr();
  Xowin();
  myOLED.printNumI(s1, 4, 4);
  myOLED.printNumI(s2, 109, 4);
  drawmapXo();
  if (digitalRead(UP) == 1 && yy > 0) {
    yy--;
  }
  if (digitalRead(DO) == 1 && yy < 2) {
    yy++;
  }
  if (digitalRead(LE) == 1 && xx > 0) {
    xx--;
  }
  if (digitalRead(RI) == HIGH && xx < 2) {
    xx++;
  }
  if (digitalRead(FI) == 1) {


    if (Map[yy][xx] == 0) {
      Map[yy][xx] = hod;
      hod *= -1;
      tone(8, 400);
      delay(50);
      noTone(8);
    }
  }
  myOLED.update();
  XOm = 0;
  mapread();
  if (XOm == 0) {
    xoCLr();
  }
  if (digitalRead(CL) == 1 || val == '5') { gameCLer(); }
}
void Xowin() {
  if (Map[0][0] == Map[0][1] && Map[0][1] == Map[0][2]) {
    if (Map[0][0] == 1) {
      s1++;
      xoCLr();
    }
    if (Map[0][0] == -1) {
      s2++;
      xoCLr();
    }
  }
  if (Map[0][0] == Map[1][1] && Map[1][1] == Map[2][2]) {
    if (Map[1][1] == 1) {
      s1++;
      xoCLr();
    }
    if (Map[1][1] == -1) {
      s2++;
      xoCLr();
    }
  }
  if (Map[0][2] == Map[1][1] && Map[1][1] == Map[2][0]) {
    if (Map[1][1] == 1) {
      s1++;
      xoCLr();
    }
    if (Map[1][1] == -1) {
      s2++;
      xoCLr();
    }
  }
  if (Map[0][0] == Map[1][0] && Map[1][0] == Map[2][0]) {
    if (Map[0][0] == 1) {
      s1++;
      xoCLr();
    }
    if (Map[0][0] == -1) {
      s2++;
      xoCLr();
    }
  }
  if (Map[0][1] == Map[1][1] && Map[1][1] == Map[2][1]) {
    if (Map[0][1] == 1) {
      s1++;
      xoCLr();
    }
    if (Map[0][1] == -1) {
      s2++;
      xoCLr();
    }
  }
  if (Map[0][2] == Map[1][2] && Map[1][2] == Map[2][2]) {
    if (Map[0][2] == 1) {
      s1++;
      xoCLr();
    }
    if (Map[0][2] == -1) {
      s2++;
      xoCLr();
    }
  }
  if (Map[1][0] == Map[1][1] && Map[1][1] == Map[1][2]) {
    if (Map[1][0] == 1) {
      s1++;
      xoCLr();
    }
    if (Map[1][0] == -1) {
      s2++;
      xoCLr();
    }
  }

  if (Map[2][0] == Map[2][1] && Map[2][1] == Map[2][2]) {
    if (Map[2][0] == 1) {
      s1++;
      xoCLr();
    }
    if (Map[2][0] == -1) {
      s2++;
      xoCLr();
      d
    }
  }
}