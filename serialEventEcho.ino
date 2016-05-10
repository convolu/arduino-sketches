String inputCommand;
bool commandReady = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  inputCommand.reserve(256);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}


void readyCb() {
  String printStr("Received: " + inputCommand);
  
  Serial.println(printStr);
  inputCommand = "";
}


void serialEvent() {
  int newChar;

  newChar = Serial.read();

  if (newChar != '\n') {
    inputCommand += char(newChar);
  } else {
    readyCb();
  }
  
    
}
