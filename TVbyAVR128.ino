/* This sketch creates loop that sends the correct signal to 
 * create an NTSC white line on the left and right of the screen 
 * Timing is very raw and unpredictable. No vertical sync either.
 */
const int tvsync = PIN_PD4; //1K resistor
const int tvcomp = PIN_PD5; //470 resistor



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
}

ISR(TCA0_OVF_vect)  {
      //Clear the OVF Flag...
      TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
      vsync++;
      if /* (vsync>2 && vsync<509) */ (HIGH) {     
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
        }  /* else if ((vsync>507) && (vsync<511))  {
             //Vertical Blanking Interval - Equal
             digitalWriteFast(tvsync, HIGH);
             digitalWriteFast(tvcomp, LOW);
             delayMicroseconds(32);
             digitalWriteFast(tvsync, LOW);
             digitalWriteFast(tvcomp, LOW);
             delayMicroseconds(2);
             digitalWriteFast(tvsync, HIGH);
             digitalWriteFast(tvcomp, LOW);             
        } else if (vsync>510 && vsync<514) {
             //Vertical Blanking Interval - Sync
             digitalWriteFast(tvsync, LOW);
             digitalWriteFast(tvcomp, LOW);
             delayMicroseconds(32);
             digitalWriteFast(tvsync, HIGH);
             digitalWriteFast(tvcomp, LOW);
             delayMicroseconds(2);
             digitalWriteFast(tvsync, LOW);
             digitalWriteFast(tvcomp, LOW);
        } else if ((vsync>513) && (vsync<517))  {
             //Vertical Blanking Interval - Equal
             digitalWriteFast(tvsync, HIGH);
             digitalWriteFast(tvcomp, LOW);
             delayMicroseconds(32);
             digitalWriteFast(tvsync, LOW);
             digitalWriteFast(tvcomp, LOW);
             delayMicroseconds(2);
             digitalWriteFast(tvsync, HIGH);
             digitalWriteFast(tvcomp, LOW);             
        } else if ((vsync>517) && (vsync<525))  {
            //Vertical Blanking Interval - Retrace
            digitalWriteFast(tvsync, LOW);
            digitalWriteFast(tvcomp, LOW);
            delayMicroseconds(5);
            digitalWriteFast(tvsync, HIGH);
            digitalWriteFast(tvcomp, LOW);  
         } */ else if (vsync=525) {
                vsync=0;
                digitalWriteFast(PIN_PA0,CHANGE);
             }
}

void loop() {
  // put your main code here, to run repeatedly:

}
