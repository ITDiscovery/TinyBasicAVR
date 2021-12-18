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
