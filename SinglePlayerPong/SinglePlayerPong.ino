#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_1_HW_I2C myOled(U8G2_R0);

// Declaration
int potPin = A1;
int potValue;

int paddleX = 5;
int paddleY;
int paddleHeight = 30;

int ballX = 100;
int ballY = 31;

int dirX = 1; // +1 , -1
int dirY = 1;
int baseSpeed = 2;

void setup() {
  myOled.begin();
  Serial.begin(9600);

  // init the potentiometer
  // an initial value reading
  potValue = analogRead(potPin);
}

void loop() {
  // Potentiometer values to paddle
  potValue = analogRead(potPin);
  paddleY = map(potValue, 0, 1023, 0, 64 - paddleHeight); // 0, 1023, -> 0, 63

  // - - - - - - - - - -
  // Kollision mit den Spielfeldrändern
  // - - - - - - - - - -
  if ( ballX > 127 || ballX < 0) {
    dirX = dirX * -1;
  }


  if ( ballY > 63 || ballY < 0) {
    dirY = dirY * -1;
  }

  // - - - - - - - - - -
  // Kollision mit dem Paddle
  // - - - - - - - - - -
  if (ballX < paddleX+5) {
    // x-Kollision
    if ( ballY > paddleY  &&  ballY < (paddleY + paddleHeight) ) {
      // Y-Kollision im Bereich des Paddle
      dirX *= -1;    // dirX = dirX*-1
      dirY *= -1;
    }
  }

  // Setze den Ball
  ballX = ballX + ( baseSpeed * dirX );
  ballY = ballY + ( baseSpeed * dirY );
  // - - - - - - - - -
  // Bildschirmausgabe
  // - - - - - - - - -
  myOled.firstPage();
  do {
    // Ab hier: Bildschirmausgabe
    // - - - - - - - - - -
    // Draw the field
    myOled.drawFrame(0, 0, 128, 64);

    // Draw the paddle
    myOled.drawBox(paddleX, paddleY, 5, paddleHeight);

    // Draw the ball
    myOled.drawBox(ballX, ballY, 4, 4);
    // - - - - - - - - - -
  } while ( myOled.nextPage() );

}
