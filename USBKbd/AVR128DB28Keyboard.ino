#define BUFFER_SIZE 55
const int DataPin = PIN_PA2;
const int IRQpin =  PIN_PA3;
uint8_t irq_num=254;
static volatile uint8_t bitcount = 0;
static volatile uint8_t buffer[BUFFER_SIZE];

void usbinterrupt(void) {
  
  val = digitalRead(DataPin);

}


void setup() {
  Serial.begin(115200);
  Serial.println("Keyboard Test:");
  pinMode(DataPin, INPUT_PULLUP);
  pinMode(IRQpin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRQpin),usbinterrupt,FALLING);
  head = 0;
  tail = 0;
}

void loop() {

  int count = sizeof(buffer) / sizeof(buffer[0]);
  for (int i = 0; i < count; i++) {
      Serial.print(buffer[i]);
   }
   Serial.println();
  
}
