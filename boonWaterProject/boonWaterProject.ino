int sensorPin = A0;
int sensorValue = 0;
int relayPin = 7;
int endValue = 0;
int startValue = 0;
String inPutStr = "";
int Mode = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue,0,1023,100,0);
  if (Mode == 1) {
    if (sensorValue >= endValue) {
      digitalWrite(relayPin, LOW);
    } else if (sensorValue <= startValue) {
      digitalWrite(relayPin, HIGH);
    }
  }
  delay(100);
}

void serialEvent() {
  String inputValue = "";
  while (Serial.available()) {
    char inChar = Serial.read();
    if (inChar == 0x0D) {
      inputValue = inPutStr.substring(1);
      if (inPutStr[0] == 'S') {
        startValue = inputValue.toInt();
      } else if (inPutStr[0] == 'E') {
        endValue = inputValue.toInt();
      } else if (inPutStr[0] == 'V') {
        Serial.print("V-");
        Serial.print(sensorValue);
        Serial.print("-");
        Serial.print(startValue);
        Serial.print("-");
        Serial.print(endValue);
        Serial.print("-");
        Serial.print(Mode);
        Serial.print("\r");
      } else if (inPutStr[0] == 'M') {
        Mode = inputValue.toInt();
      }
      inPutStr = "";
    } else {
      inPutStr += inChar;
    }
  }
}

