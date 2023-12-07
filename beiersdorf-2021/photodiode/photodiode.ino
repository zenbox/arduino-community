
// My variables
int sensorPin = A0;
int sensorValue;
const int size = 80;
int   valueList[size];
int count = 0;
int sumValue=0;

void setup() {
  Serial.begin(9600);
  Serial.println("hello");

  sensorValue = analogRead(sensorPin);

}

void loop() {
  sensorValue = analogRead(sensorPin);
  // Serial.println(sensorValue);


  valueList[count] = sensorValue;
  count++;
  if (count > size) count = 0;

  //Serial.print(valueList[0]);
  //Serial.print(", ");
  //Serial.print(valueList[1]);
  //Serial.print(", ");
  //Serial.print(valueList[2]);
  //Serial.print(", ");
  //Serial.print(valueList[3]);
  //Serial.print(", ");
  //Serial.print(valueList[4]);
  //Serial.print(", ");
  //Serial.print(valueList[5]);
  //Serial.print(", ");
  //Serial.print(valueList[6]);
  //Serial.print(", ");
  //Serial.print(valueList[7]);
  //Serial.print(", ");
  //Serial.print(valueList[8]);
  //Serial.print(", ");
  //Serial.println(valueList[9]);

  sumValue = 0;
  for (int i = 0; i < size; i++) {
    sumValue += valueList[i];
  }
  
  Serial.println(int(sumValue / size));

  delay(10);

}
