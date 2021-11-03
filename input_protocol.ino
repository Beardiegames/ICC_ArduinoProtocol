
const int BUTTON_COUNT = 5;
const int OUT_COUNT = BUTTON_COUNT - 1;

const int BUTTON[BUTTON_COUNT] = { A0, A1, A2, A3, A4 };

bool state[BUTTON_COUNT] = { false, false, false, false, false };
bool data_out[BUTTON_COUNT] = { false, false, false, false, false };

int iter = 0;
bool state_changed = true;
char data_str[9] = "0,0,0,0,0";


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
  for (iter = 0; iter < 7; iter += 2) {
    data_str[iter] = data_out[iter] ? "1" : "0";
    data_str[iter + 1] = ",";
  }
  data_str[9] = data_out[9] ? "1" : "0";
  
  Serial.flush();
  Serial.println(data_str);
  state_changed = false;
}
