# TinyBasicAVR
Wish List:
- Add commands to use Digital Outputs/Inputs
- Add commands to use ADC Inputs
- Add TV Out
- Add timer command
- Add tone command
- Leverage 128K Flash
- Leverage AVR128DB Features

Add docs here along with Business Card PCB Layout

USB Keyboard In: Use PS2KeyAdvanced.
Gnd
D+  - PIN_PA3 (#define IRQPIN  3)
D-  - PIN PA4 (#define DATAPIN 4)
5v 

TVout...need to mod spec/hardware_setup.h
__AVR_DB__

Current Board Connection to FTDI for Programming:
+5V to +5V
Gnd to Gnd
- (2nd Pin from Right) to TXD
Serial (Rightmost Pin) to RXD

http://www.gammon.com.au/forum/?id=11608

After installing DXCore Board Manager:
- Board: DxCore AVR DB Series (no bootloader)
- Chip: AVR128DB28
- Clock: 24MHz Internal
- Timer: Disabled
- BOD Level: 1.9V
- BOD Mode: Disabled
- Save EEPROM: retained
- Reset: Hardware
- Startup Time: 8mS
- Flash: Anywhere
- Multivoltage IO: Enabled
- Attach Interupt: Any
- PrintF: Prints Floats

Programmer: Serial UPDI, 230400 Baud

```
int pixclk = 12;
int pixdata = 0b010101010100;
bool flag = 0;


void setup() {
  //takeOverTCA0();  Don't do this, turns off split mode.
  // We will be outputting PWM on PD2 amd PD3
  // No need to enable split mode - core has already done that for us.
  pinMode(PIN_PD2, OUTPUT); //PD2 - TCA0 WO1 - Horizontal Sync
  pinMode(PIN_PD3, OUTPUT); //PD3 - TCA0 WO2 - Pixel Clock
  pinMode(PIN_PA5, OUTPUT); /// Green Pixel Out
  PORTMUX.TCAROUTEA = (PORTMUX.TCAROUTEA & ~(PORTMUX_TCA0_gm)) | PORTMUX_TCA0_PORTD_gc; // Variety! Also on all parts!
  TCA0.SPLIT.CTRLB  = TCA_SPLIT_LCMP2EN_bm | TCA_SPLIT_HCMP0EN_bm; //PWM on WO2, WO3
  TCA0.SPLIT.CTRLA  = TCA_SPLIT_CLKSEL_DIV8_gc | TCA_SPLIT_ENABLE_bm; //Div8 = .4uSec
  TCA0.SPLIT.LPER   = 0x5F; // 96 times .4uSec on WO0/WO1/WO2 (31.280KHz)
  TCA0.SPLIT.HPER   = 0x07; // Count to 8 WO3/WO4/WO5 (468KHz)
  TCA0.SPLIT.LCMP2  = 0x07; // 4uSec Low Pulse
  TCA0.SPLIT.HCMP0  = 0x04; // 50% duty cycle, this can't be higer than HPER
 
  TCA0.SPLIT.INTCTRL |= TCA_SPLIT_HUNF_bm; 
}

ISR(TCA0_HUNF_vect) {
  TCA0.SPLIT.INTFLAGS = TCA_SPLIT_HUNF_bm;
  //digitalWriteFast(PIN_PA5,CHANGE);
  digitalWriteFast(PIN_PA5, (((pixdata) >> (pixclk)) & 0x01));
  pixclk--;
  if (!pixclk) pixclk = 12;
}

void loop() {
  // put your main code here, to run repeatedly:
}
```
