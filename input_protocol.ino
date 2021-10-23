
const int BUTTON_COUNT = 5;
const int OUT_COUNT = BUTTON_COUNT - 1;

const int BUTTON[BUTTON_COUNT] = { A0, A1, A2, A3, A4 };

bool state[BUTTON_COUNT] = { false, false, false, false, false };
bool data_out[BUTTON_COUNT] = { false, false, false, false, false };

int iter = 0;
bool state_changed = true;


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
  iter = 0;
  while (iter < OUT_COUNT) {
    Serial.print(data_out[iter]);
    Serial.print(",");
    iter ++;
  }
  Serial.println(data_out[OUT_COUNT]);
  state_changed = false;
}
