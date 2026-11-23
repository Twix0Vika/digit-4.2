const int DATA_PIN  = 2; 
const int LATCH_PIN = 3; 
const int CLOCK_PIN = 4; 
const int STEP_DELAY = 150;

const bool INVERT_ROWS = false;
const bool INVERT_COLS = true;
const int CENTER_ROW = 3; 
const int CENTER_COL = 3; 
const int MATRIX_SIZE = 8;
const byte START_PATTERN = 0b00000001;

void SetPin() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
}

void sendByte(byte val) {
  for (int i = 7; i >= 0; i--) {
    digitalWrite(DATA_PIN, (val >> i) & 1);
    digitalWrite(CLOCK_PIN, HIGH);
    digitalWrite(CLOCK_PIN, LOW);
  }
}

void showLed(int row, int col) {
  byte rowsByte = START_PATTERN << row;
  byte colsByte = START_PATTERN << col;
  if (INVERT_ROWS) rowsByte = ~rowsByte;
  if (INVERT_COLS) colsByte = ~colsByte;
  digitalWrite(LATCH_PIN, LOW);
  sendByte(colsByte); 
  sendByte(rowsByte); 
  digitalWrite(LATCH_PIN, HIGH);
}

void Vertical(){
  for (int r = 0; r < MATRIX_SIZE; r++) {
    showLed(r, CENTER_COL);
    delay(STEP_DELAY);
  }
}

void Horizontal(){
    for (int c = 0; c < MATRIX_SIZE; c++) {
    showLed(CENTER_ROW, c);
    delay(STEP_DELAY);
  }
}

void setup() {
  SetPin();
}

void loop() {
  Vertical();
  Horizontal();
}