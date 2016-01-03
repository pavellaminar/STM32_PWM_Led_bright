#include "stm32f0xx.h"       

//--------- PWM INI ----------
void pwm_ini(){
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;  
  TIM3->ARR = 47999;
  TIM3->CR1 |= TIM_CR1_ARPE;
  // TIM3 Chanel 3 for led PC8 (blue)
  TIM3->CCR3 = 2400;
  TIM3->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
  TIM3->CCMR2 |= TIM_CCMR2_OC3PE;  
  // TIM3 Chanel 4 for led PC9 (green)
  TIM3->CCR4 = 48000;
  TIM3->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;
  TIM3->CCMR2 |= TIM_CCMR2_OC4PE;
  
  TIM3->EGR |= TIM_EGR_UG;  
  TIM3->CCER |= TIM_CCER_CC3E;
  TIM3->CCER |= TIM_CCER_CC4E;
  
  TIM3->CR1 |= TIM_CR1_CEN;       
}

//--------- LED INI ----------
void led_ini() {
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
  GPIOC->MODER |= GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1;
  GPIOC->OTYPER = 0;
  GPIOC->OSPEEDR = 0;
}

//--------- BUTTON INI ----------
void button_ini() {
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
}

int main(void) {
  led_ini();
  button_ini();
  pwm_ini();
  uint8_t i = 0;
  uint8_t level = 0;
  
  while(1){
    if ((GPIOA->IDR & GPIO_IDR_0)){
      i++;
      if (i == 10){
        stat++;
          switch(level){
            case 1:
              TIM3->CCR3 = 14400;
              TIM3->CCR4 = 33600;
              break;
            case 2:
              TIM3->CCR3 = 26400;
              TIM3->CCR4 = 26400;
              break;
            case 3:
              TIM3->CCR3 = 33600;
              TIM3->CCR4 = 14400;
              break;
            case 4:
              TIM3->CCR3 = 48000;
              TIM3->CCR4 = 2400;
              break;
            case 5:
              TIM3->CCR3 = 2400;
              TIM3->CCR4 = 48000;
              stat = 0;
          }
        i = 0;
        while ((GPIOA->IDR & GPIO_IDR_0));
      }
    }else{
      i = 0;
    }
  }
}
