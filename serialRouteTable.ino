#define VERSION "0.0.1"

#define BAUD 115200

#define SIZE_OF_COMMAND 16
#define SIZE_OF_RECEIVE_BUF 256

#define COUNT_OF(X) (sizeof(X) / sizeof(X[0])) 

String inputCommand;
bool commandReady = false;

typedef struct routeTableEntry { 
    char key[SIZE_OF_COMMAND]; 
    void (*controller)();
} routeTableEntry;

void ver_cb() {
  Serial.println("Version: " VERSION);
}

void hi_cb() {
  Serial.println("received hi");
}

void ping_cb() {
  Serial.println("pong");
}

routeTableEntry routeTable[] = {
  {"VERSION", ver_cb},
  {"HI", hi_cb},
  {"PING", ping_cb}
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD, SERIAL_8N1);
  inputCommand.reserve(SIZE_OF_RECEIVE_BUF);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

void readyCb() {
  int i, routeTableSize;

  routeTableSize = COUNT_OF(routeTable);
  for (i=0; i < routeTableSize; i++) {
    if (inputCommand.equalsIgnoreCase(routeTable[i].key)) {
      routeTable[i].controller();
      break;
    }
  }

  //Now that we're done, clear the buffer;
  inputCommand = "";
}

void serialEvent() {
  int newChar;

  newChar = Serial.read();

  if (newChar != '\n' || inputCommand.charAt(inputCommand.length() -1) != '\r') {
    inputCommand += char(newChar);
  } else {
    inputCommand.remove(inputCommand.length() - 1);
    readyCb();
  }
    
}
