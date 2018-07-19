
// Replace with your remote codes
// Emotiva Power Button = NEC: 9E01FE
// Samsung Power = E0E040BF
// Samsung STB = E0E007F8
// Samsung A = E0E036C9

#include <IRremote.h>

int RECV_PIN = 11;
int STATUS_PIN = 13;
int powerPressed = 0;

unsigned long emotivaPower = 0x9E01FE;
unsigned long samsungButton = 0xE0E036C9;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;

void setup()
{
  Serial.begin(9600);
  
  // Start the receiver
  irrecv.enableIRIn();
  
  pinMode(BUTTON_PIN, INPUT);
  pinMode(STATUS_PIN, OUTPUT);
}

void sendCode() {
  irsend.sendNEC(emotivaPower, 32);
  Serial.print("Sent NEC ");
  Serial.println(emotivaPower, HEX);
}

void loop() {
  
  if (powerPressed) {
    powerPressed = 0;
    digitalWrite(STATUS_PIN, HIGH);
    irrecv.enableIRIn();
    delay(50);
    sendCode();
    digitalWrite(STATUS_PIN, LOW);
    irrecv.enableIRIn();
  } 
  
  if (irrecv.decode(&results)) {
    digitalWrite(STATUS_PIN, HIGH);
    
    if(results.value == samsungButton) {
      Serial.println("Samsung button pressed");
      powerPressed = 1;
      delay(100);
    }
    
    irrecv.resume();
    digitalWrite(STATUS_PIN, LOW);
  }
}
