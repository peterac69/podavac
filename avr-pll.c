// Clock Settings
    OSC.XOSCCTRL = 0x4B;    // 2-9 MHz XTAL - 16K CLK Start Up
    OSC.PLLCTRL = 0xC2;     // XOSC is PLL Source - 4x Factor (4x8MHz = 32MHz)
    OSC.CTRL = 0x18;        // Enable PLL & External Oscillator
    while (!(OSC.STATUS & OSC_PLLRDY_bm));  // wait until PLL stable    
    // Select the system clock source: Phase Locked Loop
    n = CLK_SCLKSEL_gm & CLK_SCLKSEL_PLL_gc;    
    CCP = CCP_IOREG_gc;
    CLK.CTRL = n; 
***************************************************************************

void init_main_clock_pll() {

OSC.XOSCCTRL |= OSC_FRQRANGE_2TO9_gc | 
                OSC_XOSCSEL_XTAL_256CLK_gc;

OSC.CTRL |= OSC_XOSCEN_bm;
do {
    ;
} while (!(OSC.STATUS & OSC_XOSCRDY_bm));
//  now ext oscillator ready

CCP = CCP_IOREG_gc;
CLK.CTRL = CLK_SCLKSEL_XOSC_gc; // 0x03;
// now sys clocked ext osc, for you 8Mhz

CCP = CCP_IOREG_gc;
CLK.PSCTRL = CLK_PSADIV_1_gc  | CLK_PSBCDIV_1_2_gc;
// setup clk prescalers

OSC.CTRL &= OSC_RC2MEN_bm;
// stop internal osc 2Mhz

OSC.PLLCTRL = OSC_PLLSRC_XOSC_gc | ((0x08 & 
              OSC_PLLFAC_gm) << OSC_PLLFAC_gp);
// setup pll

OSC.CTRL |= OSC_PLLEN_bm; //
do {
    ;
} while (!(OSC.STATUS & OSC_PLLRDY_bm));
// now pll ready

CCP = CCP_IOREG_gc;
CLK.CTRL = CLK_SCLKSEL_PLL_gc;
// now sys clocked from pll

OSC.CTRL &= OSC_XOSCEN_bm;


*******************************************************************************8

void setup_pwm(void){
    // Do all the bit twiddling magic to activate hardware PWM (only using pwmb for this test)
    int i;
    // First setup the pll (Fast Peripheral Clock)
    PLLCSR = BIT(PLLE);
    _delay_ms(0.1); // Datasheet
    for (i=0;i<255;i++) { // timeout at 256 trys
        if (~bit_get(PLLCSR, 0x01)) { // Wait for the PLOCK bit to be set
            break;
        }
    }
    PLLCSR = BIT(PCKE);
    // Set clock rate prescaler for 250kHz (From datasheet)
    TCCR1 = 0x01;
    // Setup timer1b for PWM on pb4
    GTCCR = BIT(PWM1B) | BIT(COM1B1);
    // Set the Output Compare Register for 50% duty cycle
    OCR1B = BIT(7);
}


}
