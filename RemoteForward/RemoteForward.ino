
// Replace with your remote codes
// Emotiva Power Button = NEC: 9E01FE
// Samsung Power = E0E040BF
// Samsung STB = E0E007F8
// Samsung A = E0E036C9

#include <IRremote.h>

int RECV_PIN = 11;
int STATUS_PIN = 13;

unsigned long code = 0;

unsigned long emotivaPower = 10355198;
unsigned long emotivaLeft = 10361318;
unsigned long emotivaRight = 10378148;
unsigned long emotivaMute = 10393958;

unsigned long samsungButtonA = 3772790473;
unsigned long samsungButtonB = 3772786903;
unsigned long samsungButtonC = 3772819543;
unsigned long samsungButtonD = 3772803223;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;

void setup()
{
  Serial.begin(9600);
  
  // Start the receiver
  irrecv.enableIRIn();
  
  pinMode(STATUS_PIN, OUTPUT);
}

void sendCode(unsigned long code) {
  digitalWrite(STATUS_PIN, HIGH);
  irrecv.enableIRIn();
  delay(50);
  irsend.sendNEC(code, 32);
  irrecv.enableIRIn();  
  Serial.print("Sent NEC ");
  Serial.println(code);
  digitalWrite(STATUS_PIN, LOW);
}

void loop() {
  
  if (code) {    
    sendCode(code);    
    code = 0;
  }
  
  if (irrecv.decode(&results)) {
    digitalWrite(STATUS_PIN, HIGH);

    Serial.println(results.value);
    
    if (results.value == samsungButtonA) {
      Serial.println("Samsung button A pressed");
      code = emotivaPower;
    }
    else if (results.value == samsungButtonB) {
      Serial.println("Samsung button B pressed");
      code = emotivaLeft;
    }
    else if (results.value == samsungButtonC) {
      Serial.println("Samsung button C pressed");
      code = emotivaRight;
    }
    else if (results.value == samsungButtonD) {
      Serial.println("Samsung button D pressed");
      code = emotivaMute;
    }

    if (code) delay(100);
    
    irrecv.resume();
    digitalWrite(STATUS_PIN, LOW);
  }
}
