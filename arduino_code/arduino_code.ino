
// SET BUTTON PINOUT HERE..
const int LEFT_BUTTON_PIN = A0;
const int UP_BUTTON_PIN = A1;
const int DOWN_BUTTON_PIN = A2;
const int RIGHT_BUTTON_PIN = A3;
const int START_BUTTON_PIN = A4;


const int BUTTON_COUNT = 5;
const int OUT_COUNT = BUTTON_COUNT - 1;
const int BUTTON[BUTTON_COUNT] = { 
  LEFT_BUTTON_PIN,
  UP_BUTTON_PIN,
  DOWN_BUTTON_PIN,
  RIGHT_BUTTON_PIN,
  START_BUTTON_PIN,
};

bool state[BUTTON_COUNT] = { false, false, false, false, false };
bool data_out[BUTTON_COUNT] = { false, false, false, false, false };
int iter = 0;
bool state_changed = true;
char data_str[] = "0,0,0,0,0";

void setup() {
  setupButtons();
  Serial.begin(9600);
}

void loop() {
  readButtonStates();
  if (state_changed) sendData();
}

void setupButtons() {
  for (iter = 0; iter < BUTTON_COUNT; iter ++) {
    pinMode(BUTTON[iter], INPUT);
  }
}

void readButtonStates() {
  iter = 0;
  while (iter < BUTTON_COUNT) {
    state[iter] = digitalRead(BUTTON[iter]);
    
    if (state[iter] != data_out[iter]) {
      data_out[iter] = state[iter];
      state_changed = true;
    } 
    iter ++;
  }
}

void sendData() {
  Serial.flush();
  Serial.print(data_out[0]);
  Serial.print(",");
  Serial.print(data_out[1]);
  Serial.print(",");
  Serial.print(data_out[2]);
  Serial.print(",");
  Serial.print(data_out[3]);
  Serial.print(",");
  Serial.println(data_out[4]);
  state_changed = false;
  delay(20);
}
