#include <msp430.h> 
#define COL1 BIT6		//PORT3
#define COL2 BIT7		//PORT2
#define COL3 BIT0		//PORT1
#define BTG BIT5
#define BTR BIT4
#define BTB BIT3
#define MG BIT2
#define MR BIT1
#define MB BIT0
#define BTW BTG+BTR+BTB
#define BTY BTR+BTG
#define BTP BTB+BTR
#define MW MG+MR+MB
#define MY MR+MG
#define MP MB+MR
/*
 * main.c
 */

void col1_en(void){
	P2OUT &=~ COL1;
	P2OUT |= COL2;
	P1OUT |= COL3;
}

void col2_en(void){
	P2OUT &=~ COL2;
	P2OUT |= COL1;
	P1OUT |= COL3;
}

void col3_en(void){
	P1OUT &=~ COL3;
	P2OUT |= (COL1 + COL2);
}

void reset_cl(void){
    P1OUT &=~ 0xFF;
    P2OUT &=~ 0xFF;
	P1OUT |= COL3;
	P2OUT |= (COL1 + COL2);
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    P2SEL &=~ (BIT6 + BIT7);
    P2SEL2 &=~ (BIT6 + BIT7);
    P1SEL &=~ BIT0;
    P1SEL2 &=~ BIT0;
    P1OUT &=~ 0xFF;
    P2OUT &=~ 0xFF;
	P1OUT |= COL3;
	P2OUT |= (COL1 + COL2);
	P1DIR |= (COL3 + BTB + BTR + BTG);
	P2DIR |= (COL1 + COL2 + BTR + BTG + BTB + MR + MG + MB);
//	BLUE, RED, WHITE, RED, BLUE, GREEN, YELLOW, GREEN, CYAN
	while(1){
		reset_cl();
		col1_en();
		P1OUT |= BTP;
		P2OUT |= (BTR + MG);
		__delay_cycles(300);
		reset_cl();
		col2_en();
		P1OUT |= BTY;
		P2OUT |= (BTW+MB);
		__delay_cycles(300);
		reset_cl();
		col3_en();
		P1OUT |= BTP;
		P2OUT |= (BTR + MG);
		__delay_cycles(300);
	}

	return 0;
}
