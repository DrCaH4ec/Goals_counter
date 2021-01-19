#include "libs.h"



static int LED_MATRIX[32] ={
	0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111, //9
	0b01110111, //A(10)
	0b01111100, //b(11)
	0b00111001, //C(12)
	0b01011110, //d(13)
	0b01111001, //E(14)
	0b01110001, //F(15)
	0b01110110, //H(16)
	0b00110000, //I(17)
	0b00011110, //J(18)
	0b00111000, //L(19)
	0b01010100, //n(20)
	0b01110001, //P(21)
	0b01100111, //q(22)
	0b01010000, //r(23)
	0b01101101, //S(24)
	0b01111000, //t(25)
	0b00111110, //U(26)
	0b00011100, //v(27)
	0b01101110, //y(28)
	0x00, // (29)

};

void off_anodes(){
		DIG_1_PORT &= ~(1<<DIG_1_n);
		DIG_2_PORT &= ~(1<<DIG_2_n);
		DIG_3_PORT |= (1<<DIG_3_n);
		DIG_4_PORT |= (1<<DIG_4_n);
		DIG_5_PORT &= ~(1<<DIG_5_n);
		DIG_6_PORT &= ~(1<<DIG_6_n);
}

void WriteMatrixToDIG(unsigned int val){
	if(LED_MATRIX[val]&(1<<0)) SEG_A_PORT |= (1<<SEG_A_n);
	else SEG_A_PORT &= ~(1<<SEG_A_n);
	
	if(LED_MATRIX[val]&(1<<1)) SEG_B_PORT |= (1<<SEG_B_n);
	else SEG_B_PORT &= ~(1<<SEG_B_n);
	
	if(LED_MATRIX[val]&(1<<2)) SEG_C_PORT |= (1<<SEG_C_n);
	else SEG_C_PORT &= ~(1<<SEG_C_n);
	
	if(LED_MATRIX[val]&(1<<3)) SEG_D_PORT |= (1<<SEG_D_n);
	else SEG_D_PORT &= ~(1<<SEG_D_n);
	
	if(LED_MATRIX[val]&(1<<4)) SEG_E_PORT |= (1<<SEG_E_n);
	else SEG_E_PORT &= ~(1<<SEG_E_n);
	
	if(LED_MATRIX[val]&(1<<5)) SEG_F_PORT |= (1<<SEG_F_n);
	else SEG_F_PORT &= ~(1<<SEG_F_n);
	
	if(LED_MATRIX[val]&(1<<6)) SEG_G_PORT |= (1<<SEG_G_n);
	else SEG_G_PORT &= ~(1<<SEG_G_n);
}

void WriteValToDIG(unsigned int val){
	if(val&(1<<0)) SEG_A_PORT |= (1<<SEG_A_n);
	else SEG_A_PORT &= ~(1<<SEG_A_n);
	
	if(val&(1<<1)) SEG_B_PORT |= (1<<SEG_B_n);
	else SEG_B_PORT &= ~(1<<SEG_B_n);
	
	if(val&(1<<2)) SEG_C_PORT |= (1<<SEG_C_n);
	else SEG_C_PORT &= ~(1<<SEG_C_n);
	
	if(val&(1<<3)) SEG_D_PORT |= (1<<SEG_D_n);
	else SEG_D_PORT &= ~(1<<SEG_D_n);
	
	if(val&(1<<4)) SEG_E_PORT |= (1<<SEG_E_n);
	else SEG_E_PORT &= ~(1<<SEG_E_n);
	
	if(val&(1<<5)) SEG_F_PORT |= (1<<SEG_F_n);
	else SEG_F_PORT &= ~(1<<SEG_F_n);
	
	if(val&(1<<6)) SEG_G_PORT |= (1<<SEG_G_n);
	else SEG_G_PORT &= ~(1<<SEG_G_n);
}

void SwitchDIG(unsigned int digit){
	switch(digit){
		case 1:
			DIG_1_PORT |= (1<<DIG_1_n);
		break;
		
		case 2:
			DIG_2_PORT |= (1<<DIG_2_n);
		break;
		
		case 3:
			DIG_3_PORT &= ~(1<<DIG_3_n);
		break;
		
		case 4:
			DIG_4_PORT &= ~(1<<DIG_4_n);
		break;
		
		case 5:
			DIG_5_PORT |= (1<<DIG_5_n);
		break;
		
		case 6:
			DIG_6_PORT |= (1<<DIG_6_n);
		break;
	}
}


void IndGoals1(unsigned int val){
	
	off_anodes();
	
	if(val > 9){
		WriteMatrixToDIG(val/10);
		SwitchDIG(1);
		_delay_ms(TIME_OF_SWITCH_DIGIT);
		off_anodes();
		WriteMatrixToDIG(val%10);
		SwitchDIG(2);
		_delay_ms(TIME_OF_SWITCH_DIGIT);
	}
	else{
		WriteMatrixToDIG(0);
		SwitchDIG(1);
		_delay_ms(TIME_OF_SWITCH_DIGIT);
		off_anodes();
		WriteMatrixToDIG(val);
		SwitchDIG(2);
		_delay_ms(TIME_OF_SWITCH_DIGIT);
	}
	
	off_anodes();
}

void IndGoals2(unsigned int val){
	
	off_anodes();
	
	if(val > 9){
		WriteMatrixToDIG(val/10);
		SwitchDIG(5);
		_delay_ms(TIME_OF_SWITCH_DIGIT);
		off_anodes();
		WriteMatrixToDIG(val%10);
		SwitchDIG(6);
		_delay_ms(TIME_OF_SWITCH_DIGIT);
	}
	else{
		WriteMatrixToDIG(0);
		SwitchDIG(5);
		_delay_ms(TIME_OF_SWITCH_DIGIT);
		off_anodes();
		WriteMatrixToDIG(val);
		SwitchDIG(6);
		_delay_ms(TIME_OF_SWITCH_DIGIT);
	}
	
	off_anodes();
}

void IndWins1(unsigned int val){
	
	off_anodes();
	WriteMatrixToDIG(val);
	SwitchDIG(3);
	_delay_ms(TIME_OF_SWITCH_DIGIT);
	off_anodes();
}

void IndWins2(unsigned int val){
	
	off_anodes();
	WriteMatrixToDIG(val);
	SwitchDIG(4);
	_delay_ms(TIME_OF_SWITCH_DIGIT);
	off_anodes();
}