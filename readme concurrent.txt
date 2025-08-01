Arduino Sensor System with Buzzer
Summary
This Arduino project integrates a PIR motion sensor, an IR sensor, a pushbutton, three LEDs, and a buzzer to create an interactive system. The PIR sensor (D10), IR sensor (D8), and pushbutton (D9) trigger their respective LEDs (D4, D2, D3) for 200ms upon activation, with a 500ms debounce to prevent false triggers. A 2-second timer interrupt toggles an 800Hz buzzer on D6. Pin Change Interrupts (PCINT0) monitor sensor inputs, while Timer1 controls the buzzer, ensuring efficient, non-blocking operation. Serial output at 9600 baud provides real-time feedback for debugging.
Hardware Requirements

Arduino board (e.g., Uno)
PIR motion sensor (e.g., HC-SR501)
IR sensor (digital output, e.g., IR photodiode)
Pushbutton (momentary switch)
3 LEDs (e.g., red for PIR, green for IR, blue for pushbutton)
3 resistors (220Ω or 330Ω for LEDs)
Passive or active buzzer (5V compatible)
Breadboard and jumper wires

Connections

PIR Sensor (D10):
VCC to Arduino 5V
GND to Arduino GND
OUT to D10


IR Sensor (D8):
VCC to Arduino 5V
GND to Arduino GND
OUT to D8
Note: Add a 10kΩ pull-up resistor if required by the sensor.


Pushbutton (D9):
One terminal to D9
Other terminal to Arduino GND


PIR LED (D4):
Anode to D4 via 220Ω resistor
Cathode to Arduino GND


IR LED (D2):
Anode to D2 via 220Ω resistor
Cathode to Arduino GND


Pushbutton LED (D3):
Anode to D3 via 220Ω resistor
Cathode to Arduino GND


Buzzer (D6):
Positive pin to D6
Negative pin to Arduino GND


Power/Ground:
Connect all GNDs to a common Arduino GND
Connect sensor VCCs to Arduino 5V



Setup Instructions

Connect Hardware: Wire components as described above, ensuring correct LED orientation and secure connections.
Upload Code: Open modified_pir_ir_buzzer_pins.ino in the Arduino IDE, connect your Arduino via USB, and upload the code.
Power On: Allow 30–60 seconds for the PIR sensor to stabilize.
Monitor Output: Open the Serial Monitor (9600 baud) to view messages like "[PCI] PIR sensor triggered" or "[TIMER] Buzzer activated."

Usage

PIR Sensor: Detects motion, lights D4 LED for 200ms.
IR Sensor: Detects IR signal, lights D2 LED for 200ms.
Pushbutton: When pressed, lights D3 LED for 200ms.
Buzzer: Toggles an 800Hz tone every 2 seconds on D6.
Serial Output: Displays trigger events and buzzer state.

Troubleshooting

No LED Response: Check pin connections and resistor values. Ensure sensors are powered (5V/GND).
Buzzer Issues: Use a passive buzzer for 800Hz tone; active buzzers may produce a fixed tone.
False Triggers: Adjust PIR/IR sensitivity or verify debounce timing in code.
Serial Lag: Reduce Serial prints if needed for performance.