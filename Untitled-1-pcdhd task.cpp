const int pirSensorPin = 10;
const int irSensorPin = 8;
const int pushbuttonPin = 9;
const int pirLedPin = 4;
const int irLedPin = 2;
const int pushbuttonLedPin = 3;
const int buzzerPin = 6;

volatile boolean pirTriggered = false;
volatile boolean irTriggered = false;
volatile boolean pushbuttonTriggered = false;
volatile boolean buzzerState = false;
volatile uint8_t priorPinStates = 0;

void configureSystem() {
  Serial.begin(9600);
  
  pinMode(pirSensorPin, INPUT);
  pinMode(irSensorPin, INPUT);
  pinMode(pushbuttonPin, INPUT_PULLUP);
  pinMode(pirLedPin, OUTPUT);
  pinMode(irLedPin, OUTPUT);
  pinMode(pushbuttonLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Set up PCINT0 for D8 (PCINT0), D9 (PCINT1), D10 (PCINT2)
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2);
  priorPinStates = PINB & 0x07; // Mask for D8-D10
  
  // Configure Timer1 for 2-second buzzer
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 31250; // 2 seconds at 16MHz, 1024 prescaler
  TCCR1B |= (1 << WGM12); // CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // 1024 prescaler
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
  
  Serial.println("System Initialized: PIR, IR, Pushbutton, Buzzer");
}

ISR(PCINT0_vect) {
  uint8_t nowPinStates = PINB & 0x07; // Read D8-D10
  uint8_t changedBits = nowPinStates ^ priorPinStates;
  
  // D10 (PCINT2) for PIR
  if (changedBits & (1 << 2) && digitalRead(pirSensorPin)) {
    pirTriggered = true;
  }
  // D8 (PCINT0) for IR
  if (changedBits & (1 << 0) && digitalRead(irSensorPin)) {
    irTriggered = true;
  }
  // D9 (PCINT1) for Pushbutton
  if (changedBits & (1 << 1) && !digitalRead(pushbuttonPin)) {
    pushbuttonTriggered = true;
  }
  
  priorPinStates = nowPinStates;
}

ISR(TIMER1_COMPA_vect) {
  buzzerState = !buzzerState;
  if (buzzerState) {
    tone(buzzerPin, 800); // 800Hz tone
    Serial.println("[TIMER] Buzzer activated.");
  } else {
    noTone(buzzerPin);
    Serial.println("[TIMER] Buzzer deactivated.");
  }
}

void managePir() {
  static uint32_t lastPirEvent = 0;
  static boolean ledIsActive = false;
  
  if (pirTriggered && !ledIsActive && (millis() - lastPirEvent > 500)) {
    digitalWrite(pirLedPin, HIGH);
    Serial.println("[PCI] PIR sensor triggered.");
    lastPirEvent = millis();
    ledIsActive = true;
  }
  
  if (ledIsActive && (millis() - lastPirEvent >= 200)) {
    digitalWrite(pirLedPin, LOW);
    pirTriggered = false;
    ledIsActive = false;
  }
}

void manageIr() {
  static uint32_t lastIrEvent = 0;
  static boolean ledIsActive = false;
  
  if (irTriggered && !ledIsActive && (millis() - lastIrEvent > 500)) {
    digitalWrite(irLedPin, HIGH);
    Serial.println("[PCI] IR sensor triggered.");
    lastIrEvent = millis();
    ledIsActive = true;
  }
  
  if (ledIsActive && (millis() - lastIrEvent >= 200)) {
    digitalWrite(irLedPin, LOW);
    irTriggered = false;
    ledIsActive = false;
  }
}

void managePushbutton() {
  static uint32_t lastPushbuttonEvent = 0;
  static boolean ledIsActive = false;
  
  if (pushbuttonTriggered && !ledIsActive && (millis() - lastPushbuttonEvent > 500)) {
    digitalWrite(pushbuttonLedPin, HIGH);
    Serial.println("[PCI] Pushbutton pressed.");
    lastPushbuttonEvent = millis();
    ledIsActive = true;
  }
  
  if (ledIsActive && (millis() - lastPushbuttonEvent >= 200)) {
    digitalWrite(pushbuttonLedPin, LOW);
    pushbuttonTriggered = false;
    ledIsActive = false;
  }
}

void setup() {
  configureSystem();
}

void loop() {
  managePir();
  manageIr();
  managePushbutton();
}