
/* After Calibration:
 * ------------------
 * Left:   average = 400 for 30cm
 * Middle: average = 316 for 15 cm
 * Right:  average = 405 for 30cm
 */
 
int value; 

void setupIRSensors(){
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (ADPS1) | (ADPS0);
}

int selectLeftIR(){
	ADMUX &= ~ADMUX;
	ADMUX |= (1 << REFS0) | (1 << MUX0); //PIN 1
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADIF));
	value = ADC;
	return value;
}

int selectMiddleIR(){
	ADMUX &= ~ADMUX;
	ADMUX |= (1 << REFS0); //PIN 0
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADIF));
	value = ADC;
	return value;
}

int selectRightIR(){
	ADMUX &= ~ADMUX;
	ADMUX |= (1 << REFS0) | (1 << MUX1); //PIN 2
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADIF));
	value = ADC;
	return value;
}









