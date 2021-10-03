# Servo-Motor-Control-Using-Potentiometer-with-STM32F407-Discovery-Kit

![image](https://user-images.githubusercontent.com/56625259/130080296-e2cd51da-600a-4584-85c7-ff7283a5eb2a.png)


![image](https://user-images.githubusercontent.com/56625259/130080344-4e280f41-d8cb-43d3-a9fe-013cfe64d3b6.png)


![image](https://user-images.githubusercontent.com/56625259/135755327-879ed144-c964-4cb3-ad20-47ece0046ca3.png)


The servo motor is controlled by sending a PWM pulse through the orange wire, which is known as the control signal. The duty cycle of the PWM pulse determines the position of the servo motor. At 0.5 ms the servo motor is at a position of '0' degrees, at 1 ms duty cycle the servo motor moves to '90' degrees and so on upto 2.5ms. This principle is used in the bare metal code written for the stm32f407 Discovery Board. The pulse-wdith is varied by taking in the input from the potentiometer which is converted into a digital value by using an ADC.


The connections made here are as follows,
| sg90 | STM32F407 |
|---|---|
| VCC | 5V |
| Control Signal | PA5 |
| GND | GND |

| Pot | STM32F407 |
|---|---|
| VCC | 5V |
| Middle Terminal | PC0 |
| GND | GND |
