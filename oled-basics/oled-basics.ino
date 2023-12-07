#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_1_HW_I2C myOled(U8G2_R0);

int potPin = A3, potValue = 0;

int screenW = 128, screenH = 64;

int ballW = 4, ballH = 4;
int ballX = screenW / 2, ballY = screenH / 2;
int ballStepX = 4, ballStepY = 4;

int paddleH = 30, paddleW = 4;
int paddleX = 110, paddleY = screenH / 2;

void setup() {
  myOled.begin();

  pinMode(potPin, INPUT);
  potValue = analogRead(potPin);
}

void loop() {
  // delay(10);

  // - - - - - - - - - -
  // SIMPLE NUMBER TO STRING
  // - - - - - - - - - -
  //  value = value + 1;
  //  if (value > 128) value = 0;
  //  /* Convert m to a string with two digits */
  //  char value_string[3];
  //  strcpy(value_string, u8x8_u8toa(value, 3));

  // - - - - - - - - - -
  // MINI PONG
  // - - - - - - - - - -
  // Get the potentiometer value
  // and calc a valid screen position
  // - - - - - - - - - -
  potValue = analogRead(potPin);
  paddleY = map(potValue, 0, 1023, 0, 63);

  // Ball boundaries
  if (ballX > screenW - ballW - 1 ) {
    ballStepX = -ballStepX;
  }
  if (ballX < 0 + ballW) {
    ballStepX = -ballStepX;
  }
  if (ballY > screenH - ballH - 1 ) {
    ballStepY = -ballStepY;
  }
  if (ballY < 0 + ballH) {
    ballStepY = -ballStepY;
  }

  // - - - - - - - - - -
  // Paddle-ball collision?
  // - - - - - - - - - -
  int flag = 0;
  int collisionX = ballX + ballW;
  int collisionYmin = ballY;
  int collisionYmax = ballY + ballH;

  if (
    collisionX >= paddleX
    && collisionX < paddleX + paddleW
  ) {
    flag++;
  }
  if (
    collisionYmin > (paddleY - paddleH / 2)
    && collisionYmax < (paddleY + paddleH / 2)
  ) {
    flag++;
  }
  if (flag == 2) {
    ballStepX = -ballStepX;
    ballStepY = -ballStepY + random(0.5, 2);
  }

  ballX = ballX + ballStepX;
  ballY = ballY + ballStepY;
  // - - - - - - - - - -


  myOled.firstPage();
  do {

    // Draw some tests
    // myOled.drawLine(0, paddleY, screenW, paddleY);
    // Write the flag
    // myOled.setFont(u8g2_font_6x13_te);
    // myOled.setCursor(24, 24);
    // myOled.print(flag);

    // Draw the field
    myOled.drawFrame(0, 0, screenW, screenH);

    // Draw the paddle
    myOled.drawBox(paddleX, paddleY - paddleH / 2, paddleW, paddleH);

    // Draw the pong ball
    myOled.drawBox(ballX, ballY, ballW, ballH);

    // Write a text
    // myOled.setFont(u8g2_font_logisoso24_tr);
    // myOled.drawStr(0, 63, value_string);
    // myOled.drawStr(42, 63, "%");

    // Write the paddle y-position
    // myOled.setFont(u8g2_font_6x13_te);
    // myOled.setCursor(0, 24);
    // myOled.print(y);

  } while ( myOled.nextPage() );

  // Reset
  flag = 0;
}
