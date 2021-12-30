/* This sketch creates loop that sends the correct signal to 
 * create an NTSC white line in the middle of the screen. 
 * Timing is very raw and unpredictable. No vertical sync either.
 */
 

const int tvsync = PIN_PD4; //1K resistor
const int tvcomp = PIN_PD5; //470 resistor
byte scrnmem [526][1];
/* 1,2,3,7,8,9,263,264,265,269,270,271 = Equalize
4,5,6,266,267,268 = Sync
10-20,272-282 = Blanking
*/

int vsync = 0;

void setup() {
  // put your setup code here, to run once:
    pinMode(tvsync, OUTPUT);
    pinMode(tvcomp, OUTPUT);
    takeOverTCA0();
    TCA0.SINGLE.PER    = 0x05E0;            // 256 Ticks to TCA0_OVF_vect
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;    // enable overflow interrupt
    TCA0.SINGLE.CTRLA   = TCA_SINGLE_ENABLE_bm; // enable the timer with no prescaler

    pinMode(PIN_PA0,OUTPUT);

    // Screen memory setup
    scrnmem[1][1] = 0x01;
    scrnmem[2][1] = 0x01;
    scrnmem[3][1] = 0x01;
    scrnmem[263][1] = 0x01;
    scrnmem[264][1] = 0x01;
    scrnmem[265][1] = 0x01;
    scrnmem[7][1] = 0x01;
    scrnmem[8][1] = 0x01;
    scrnmem[9][1] = 0x01;
    scrnmem[269][1] = 0x01;
    scrnmem[270][1] = 0x01;
    scrnmem[271][1] = 0x01;
    scrnmem[4][1] = 0x02;
    scrnmem[5][1] = 0x02;
    scrnmem[6][1] = 0x02;
    scrnmem[266][1] = 0x02;
    scrnmem[267][1] = 0x02;
    scrnmem[268][1] = 0x02;
    for (int i = 10; i <= 20; i++) {
      scrnmem[i][1]=0x03;
    }
    for (int i = 272; i <= 282; i++) {
      scrnmem[i][1]=0x03;
    }

}

ISR(TCA0_OVF_vect)  {
      //Clear the OVF Flag...
      TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
      vsync++;
      if (scrnmem[vsync][1] == 0) {     
        //Normal Video Line        
        //Start of HSync 4.7uSec
        digitalWriteFast(tvsync, LOW);
        digitalWriteFast(tvcomp, LOW);
        delayMicroseconds(5);
        //Breezeway, CBurst, Back Porch 4.7uSec
        digitalWriteFast(tvsync, HIGH);
        digitalWriteFast(tvcomp, LOW);
        delayMicroseconds(1);
        //End Back Porch - Up to Black Level
        digitalWriteFast(tvsync, LOW);
        digitalWriteFast(tvcomp, HIGH);
        delayMicroseconds(6);
        //Begin Picture      

        //Start Left White Bar
        digitalWriteFast(tvsync, HIGH);
        digitalWriteFast(tvcomp, HIGH);
        delayMicroseconds(2);
        //End Left White Bar
        digitalWriteFast(tvsync, HIGH);
        digitalWriteFast(tvcomp, LOW);

        delayMicroseconds(43);
        //Start Right White Bar
        digitalWriteFast(tvsync, HIGH);
        digitalWriteFast(tvcomp, HIGH);
        delayMicroseconds(2);
        //End Right White Bar
        digitalWriteFast(tvsync, HIGH);
        digitalWriteFast(tvcomp, LOW);

        //End of Scan
        } else if (scrnmem[vsync][1] == 1)  {
             //Vertical Blanking Interval - Equal
             digitalWriteFast(tvsync, LOW);
             digitalWriteFast(tvcomp, LOW);
             delayMicroseconds(5);
             digitalWriteFast(tvsync, HIGH);
             digitalWriteFast(tvcomp, LOW);
             delayMicroseconds(30);
             digitalWriteFast(tvsync, LOW);
             digitalWriteFast(tvcomp, LOW);
             delayMicroseconds(5);
             digitalWriteFast(tvsync, HIGH);
             digitalWriteFast(tvcomp, LOW);                          
        } else if (scrnmem[vsync][1] == 2) {
             //Vertical Blanking Interval - Sync
             digitalWriteFast(tvsync, LOW);
             digitalWriteFast(tvcomp, LOW);
             delayMicroseconds(30);
             digitalWriteFast(tvsync, HIGH);
             digitalWriteFast(tvcomp, LOW);
             delayMicroseconds(5);
             digitalWriteFast(tvsync, LOW);
             digitalWriteFast(tvcomp, LOW);
        } else if (scrnmem[vsync][1] == 3)  {
            //Vertical Blanking Interval - Blanking
            digitalWriteFast(tvsync, LOW);
            digitalWriteFast(tvcomp, LOW);
            delayMicroseconds(5);
            digitalWriteFast(tvsync, HIGH);
            digitalWriteFast(tvcomp, LOW);  
         } else if (vsync==526) {
            vsync=0;
            digitalWriteFast(tvsync, LOW);
            digitalWriteFast(tvcomp, LOW);
            delayMicroseconds(5);
            digitalWriteFast(tvsync, HIGH);
            digitalWriteFast(tvcomp, LOW);  
             }
}

void loop() {
  // put your main code here, to run repeatedly:

}
