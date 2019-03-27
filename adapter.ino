/*
This code snippet is the arduino adapter needed between ClearControl signals and
ThorLabs OSW12-488E Fiber Optic Switch Kit. This optic switch kit requires a TTL
to toggle between its states. However, ClearControl handles optic switches in a
different way. Gives HIGH or LOW to set active channel. Hence, this program below
forms the bridge in between. It reads the current active channel from optic switch
and it checks what ClearControl signal wants, in case of need arduino sends a TTL
to toggle to optical switch.
Setup:

CC signal for OS -> Arduino -> Optic Switch

03/27/19
*/

// setup Serial and pins for reading state and giving TTL back to optical switch:
void setup() {

  // Set the data rate in bps for serial transmission
  Serial.begin(9600);

  // input from optical switch board
  pinMode(2, INPUT);  // connect to C19
  pinMode(3, INPUT);  // connect to C18

  // output to optical switch board to change the active optical path
  pinMode(4, OUTPUT);  // connect to C10

  // for testing
  pinMode(LED_BUILTIN, OUTPUT);
}

// constantly listen ClearControl input and check current state from optical switch board:
// depending on input combination send TTL to optical switch board to change the optical path:
// do not forget to connect positive end of ClearControl signal to A1 and negative end of the
// ClearControl signal to A0 analog inputs.
void loop() {
  if (( (analogRead(A1) - 100 > analogRead(A0)) && digitalRead(2))) {
    Serial.println("case0");
    digitalWrite(4, LOW);    // turn the trigger off by making the voltage LOW
    delay(50);
    digitalWrite(4, HIGH);   // turn the trigger on (HIGH is the voltage level)
    delay(500);
  } else if (( (analogRead(A1) <= analogRead(A0)) && digitalRead(3))) {
    Serial.println("case1");
    digitalWrite(4, LOW);    // turn the trigger off by making the voltage LOW
    delay(50);
    digitalWrite(4, HIGH);   // turn the trigger on (HIGH is the voltage level)
    delay(500);                       // wait for a half second
  }

  digitalWrite(4, LOW);    // turn the trigger off by making the voltage LOW
  delay(200);
}
