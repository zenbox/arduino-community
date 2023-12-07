/*
   Script to control photodiade and potentiometer values
   @version 1.0.0
   @author Michael
*/

// 1. Declaration of variables
const int PHOTODIODE_PIN = A0;
const int POTENTIOMETER_PIN = A1;
//int photodiodePin
//int potentiometerPin

// Primitive value
// value = 42

// Array, list
// valuelist = [42, 43, 108, 209]
// int newlist[10];

const int photodiodeValuelistSize = 100;
int photodiodeValuelist[photodiodeValuelistSize];

int photodiodeValuesSum = 0;
int photodiodeValuesMedium = 0;
int index = 0;

int photodiodeValue;
int potentiometerValue;

// const float PI = 3.14159;


// 2. Setup while board starts
void setup() {
  // Using the serial monitor ot serial plotter
  // 9600 BAUD is a good value for most purposes
  Serial.begin(9600);
  // Serial.println("hello serial");

  // No pinMode() required for analog pins
  // First reading of sensor values while setting up
  photodiodeValue = analogRead(PHOTODIODE_PIN);
  potentiometerValue = analogRead(POTENTIOMETER_PIN);

}

// 3. Code runs while board has current
void loop() {
  // - - - - - - - - - -
  // PHOTODIODE
  // - - - - - - - - - -
  // Permanently reading the sensor values.
  // Collect values into the list,
  // use index as counter and proof for the index limit

  photodiodeValue = analogRead(PHOTODIODE_PIN);

  photodiodeValuelist[index] = photodiodeValue;

  index = index + 1;
  if (index >= photodiodeValuelistSize) {
    index = 0;
  }
  // - - - - - - - - - -
  // Reset the old sum value,
  // calculate the sum of the last 100 values
  // calculate the medium value
  // show/plot in serial monitor/plotter

  photodiodeValuesSum = 0;

  for (int i = 0; i <= photodiodeValuelistSize; i = i + 1) { // i += 1; i++
    photodiodeValuesSum  = photodiodeValuesSum + photodiodeValuelist[i];
  }

  photodiodeValuesMedium = int(photodiodeValuesSum / photodiodeValuelistSize);

  Serial.print(0);
  Serial.print(" ");
  Serial.print(1023);
  Serial.print(" ");
  Serial.print(photodiodeValuesMedium);


  // - - - - - - - - - -
  // POTENTIOMETER
  // - - - - - - - - - -
  potentiometerValue = analogRead(POTENTIOMETER_PIN);
  Serial.print(" ");
  Serial.println(potentiometerValue);

}
