#include "stm32f4xx.h"
#define ARM_MATH_CM4

void GPIO_Init(void);
void ADC1_Init(void);
void TIM2_Init(void);
void TIM4_ms_Delay(uint32_t delay);
int u;

void GPIO_Init(){
	//PC0 is connected to ADC1 IN10
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;// Enable GPIOC clock
	GPIOC->MODER |= GPIO_MODER_MODER0; // Set PC0 to Analog mode

	RCC->AHB1ENR |= 1; //Enable GPIOA clock
	GPIOA->AFR[0] |= 0x00100000; // Select the PA5 pin in alternate function mode
	GPIOA->MODER |= 0x00000800; //Set the PA5 pin alternate function
}

void ADC1_Init(){
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;//Enable ADC clock
	//APB2 clock is not divided so it runs at 16MHz
	ADC->CCR |= 0<<16; // PCLK2 divide by 2, so the clock frequency is 8MHz
	ADC1->CR2 |= ADC_CR2_CONT; // Setting the Continuous Conversion Mode
	ADC1->CR2 |= ADC_CR2_ADON; // Enabling the ADC
	ADC1->CR2 &= ~ADC_CR2_ALIGN; //setting the alignment to the right
	ADC1->CR1 &= ~ADC_CR1_RES; // Selecting 12-bit resolution
	ADC1->SMPR1 |= (ADC_SMPR2_SMP0_0 | ADC_SMPR2_SMP0_2); // 112 Sampling cycle selection
	ADC1->SQR3 |= 10<<0; // Selecting channel 10
}
void TIM2_Init(){
	RCC->APB1ENR |=1;
	TIM2->PSC = 16-1; //Setting the clock frequency to 1MHz.
	TIM2->ARR = 20000; // Total period of the timer
	TIM2->CNT = 0;
	TIM2->CCMR1 = 0x0060; //PWM mode for the timer
	TIM2->CCER |= 1; //Enable channel 1 as output
	TIM2->CCR1 = 500; // Pulse width for PWM
}

void TIM4_ms_Delay(uint32_t delay){
	RCC->APB1ENR |= 1<<2; //Start the clock for the timer peripheral
	TIM4->PSC = 16000-1; //Setting the clock frequency to 1kHz.
	TIM4->ARR = (delay); // Total period of the timer
	TIM4->CNT = 0;
	TIM4->CR1 |= 1; //Start the Timer
	while(!(TIM4->SR & TIM_SR_UIF)){} //Polling the update interrupt flag
	TIM4->SR &= ~(0x0001); //Reset the update interrupt flag
}

int main(void){
	RCC->CFGR |= 0<<10; // set APB1 = 16 MHz
	GPIO_Init();
	ADC1_Init();
	TIM2_Init();
	TIM2->CR1 |= 1;
	while(1){
		ADC1->CR2 |= ADC_CR2_SWSTART; //Starting ADC conversion
		while (!(ADC1->SR & ADC_SR_EOC)){}
		u = ADC1->DR;
		TIM2->CCR1 = (int)(((u/4095)*2000)+500);
		TIM4_ms_Delay(50);
	}
}
