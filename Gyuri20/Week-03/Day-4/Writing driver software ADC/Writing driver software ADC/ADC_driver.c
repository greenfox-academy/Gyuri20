#include "ADC_driver.h"
#include <avr/io.h>
#include <stdint.h>

void ADC_Init() {
    // TODO:
    // Set the reference voltage to AVcc.
	ADMUX |= (1 << REFS0);
    // TODO:
    // Set the data format to right adjusted, so the bottom 8bits will be in ADCL register
	//ADLAR = 0; default 
	 
    // TODO:
    // Set the used channel. Use the definitions from ADC_driver.h!
	ADMUX = (0xF0 & ADMUX) | ADC_CH; // MUX = 0000; default;

    // TODO:
    // Set the prescaler. Use the definitions from ADC_driver.h!
	ADCSRA |= ADC_ADPS;
	
    // TODO:
    // Enable the ADC peripheral
	ADCSRA |= 1 << ADEN; 
}

uint16_t ADC_Read() {
    // TODO:
    // Start a conversion with ADSC bit setup
	ADCSRA |= 1 << ADSC;

    // TODO:
    // Wait for the conversion to finish by checking ADSC bit
	while(ADCSRA & (1<<ADSC));

    // TODO:
    // return with the read data, use the "ADC" register!
	return ADC;
}