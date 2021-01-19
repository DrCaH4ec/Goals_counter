/*
 * main.c
 *
 * Created: 03.01.2019 15:22:52
 * Author : Shlikhta Alexandr
 */ 

#include "libs.h"

int GameMode;
bool PitchedTeam, FirstPitchTeam;
int Goals_1, Goals_2, common_count;
int Wins_1, Wins_2;
int StartAnimation;

void init();
void Pitch(bool team);
void IndAll();
void beep();
void ButtonBeep();
void swap(int *x, int *y);
void ind_delay_ms(int time_d);

ISR(INT0_vect){
	
	EIMSK &= ~(1<<INT0);
	EIMSK &= ~(1<<INT1);
	
	ButtonBeep();
	
	while(!(PIND&(1<<2)))
		IndAll();
	
	common_count = 0;
	
	if(GameMode == 0){
		GameMode = 1;
		PitchedTeam = 1;
		FirstPitchTeam = 1;
	}
	else{
		if(Goals_1 < 100)
			Goals_1++;	
	}
	
	if((Goals_1+Goals_2)%2 == 0 && GameMode == 1)
		PitchedTeam = !PitchedTeam;
	
	Pitch(PitchedTeam);
}

ISR(INT1_vect){
	
	EIMSK &= ~(1<<INT1);
	EIMSK &= ~(1<<INT0);
	
	ButtonBeep();
	
	while(!(PIND&(1<<3)))
		IndAll();
	
	common_count = 0;
	
	if(GameMode == 0){
		GameMode = 1;
		PitchedTeam = 0;
		FirstPitchTeam = 0;
	}
	else{
		if(Goals_2 < 100)
			Goals_2++;	
	}
	
	if((Goals_1+Goals_2)%2 == 0 && GameMode == 1)
		PitchedTeam = !PitchedTeam;
	
	Pitch(PitchedTeam);
}



int main(void){
	
	ReStart:
	
	init();
	
	GameMode = 0;
	
	Goals_1 = Goals_2 = Wins_1 = Wins_2 = 0;
	
	ButtonBeep();
	ButtonBeep();
	ButtonBeep();
	ButtonBeep();
	ButtonBeep();
	ButtonBeep();
	
	SwitchDIG(1);
	SwitchDIG(2);
	SwitchDIG(5);
	SwitchDIG(6);
	
	PITCH_1_LED_PORT &= ~(1<<PITCH_1_LED_n);
	PITCH_2_LED_PORT &= ~(1<<PITCH_2_LED_n);
	
	sei();
	
    while (1) {
		switch(GameMode){
			
			case 0:
				StartAnimation = 1;
				
				for(int i = 0; i < 6; i++){
					
					if(GameMode == 1)
						break;
					
					WriteValToDIG((StartAnimation<<i));
					_delay_ms(300);
				}			
			break;
			
			case 1:
				if(common_count == 0)
					for(; common_count < TIME_OF_BUTTON_PAUSE/(TIME_OF_SWITCH_DIGIT * 6); common_count++)
						IndAll();
				else
					IndAll();
					
				if(common_count == TIME_OF_BUTTON_PAUSE/(TIME_OF_SWITCH_DIGIT * 6)){
					common_count++;
					EIMSK |= (1<<INT1) | (1<<INT0);
				}
					
				if(!(MINUS_2_BUTTON_PIN&(1<<MINUS_2_BUTTON_n))){
					ButtonBeep();
					int RST = 0;
					
					while(!(MINUS_2_BUTTON_PIN&(1<<MINUS_2_BUTTON_n)) && RST != TIME_OF_RST/(TIME_OF_SWITCH_DIGIT * 6)){
						IndAll();
						RST++;
					}
							
					if(RST != TIME_OF_RST/(TIME_OF_SWITCH_DIGIT * 6) && Goals_2 > 0){
						
						Goals_2--;
							
						if((Goals_1+Goals_2)%2 != 0){
							PitchedTeam = !PitchedTeam;
							Pitch(PitchedTeam);
						}
					}
					else if(RST == TIME_OF_RST/(TIME_OF_SWITCH_DIGIT * 6)){
						
						ButtonBeep();
						ButtonBeep();
						ind_delay_ms(200);
						ButtonBeep();
						ButtonBeep();
						
						if(Goals_1 > Goals_2)
							Wins_1++;
						else
							Wins_2++;
						
						Goals_1 = 0;
						Goals_2 = 0;
						
						PitchedTeam = !FirstPitchTeam;
						Pitch(PitchedTeam);
						
						ind_delay_ms(2000);
						
						ButtonBeep();
						ButtonBeep();
						ind_delay_ms(200);
						ButtonBeep();
						ButtonBeep();
						ind_delay_ms(200);
						ButtonBeep();
						ButtonBeep();
						
						swap(&Wins_1, &Wins_2);
					}	
				}
					
				if(!(MINUS_1_BUTTON_PIN&(1<<MINUS_1_BUTTON_n))){
					ButtonBeep();
					int RST = 0;
					
					while(!(MINUS_1_BUTTON_PIN&(1<<MINUS_1_BUTTON_n)) && RST != TIME_OF_RST/(TIME_OF_SWITCH_DIGIT * 6)){
						IndAll();
						RST++;
					}
						
					if(RST != TIME_OF_RST/(TIME_OF_SWITCH_DIGIT * 6) && Goals_1 > 0){
						
						Goals_1--;
							
						if((Goals_1+Goals_2)%2 != 0){
							PitchedTeam = !PitchedTeam;
							Pitch(PitchedTeam);
						}
					}
					else if(RST == TIME_OF_RST/(TIME_OF_SWITCH_DIGIT * 6))
						goto ReStart;
				}	
					
			break;
		}	
    }
}

void init(){
	
	PORTB = 0b111110;
	DDRB = 0xff;
	
	PORTC = 0xff;
	DDRC = 0b001111;
	
	PORTD = 0b00000000;
	DDRD = 0b11110011;
	
	EIMSK |= (1<<INT1) | (1<<INT0);
}

void Pitch(bool team){
	if(team == true){
		PITCH_2_LED_PORT &= ~(1<<PITCH_2_LED_n);
		PITCH_1_LED_PORT |= (1<<PITCH_1_LED_n);
	}
	else{
		PITCH_1_LED_PORT &= ~(1<<PITCH_1_LED_n);
		PITCH_2_LED_PORT |= (1<<PITCH_2_LED_n);
	}
}

void beep(){
	BOOZER_PORT &= ~(1<<BOOZER_n);
	_delay_ms(200);
	BOOZER_PORT |= (1<<BOOZER_n);
}

void IndAll(){
	IndGoals1(Goals_1);
	IndWins1(Wins_1);
	IndWins2(Wins_2);
	IndGoals2(Goals_2);
}

void ButtonBeep(){
	for(int i = 0; i < TIME_OF_BUTTON_BEEP/(TIME_OF_SWITCH_DIGIT*6); i++){
		BOOZER_PORT &= ~(1<<BOOZER_n);
		IndAll();
	}
	
	BOOZER_PORT |= (1<<BOOZER_n);
}

void swap(int *x, int *y){
	int z = *y;
	*y = *x;
	*x = z;
}

void ind_delay_ms(int time_d){
	
	for(int i = 0; i < time_d/(TIME_OF_SWITCH_DIGIT * 6); i++)
		IndAll();
}