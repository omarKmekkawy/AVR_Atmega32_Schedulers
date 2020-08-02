# Atmega32_Co_Sch [03/08/2020]
Simple Co-operative scheduler based on [Patterns for time triggered embedded systems]

<img src="https://github.com/rxtxinv/AVR_Atmega32_Schedulers/raw/master/Images/Kit.jpg" height="500" width="900">

## Getting Started

The scheduler uses Timer1 as a Ticking source, the timer ticks every 1ms @ F_CPU = 8,000,000 MHz. Every tick, the scheduler updates the tasks defined data structure with timing and the dispatcher loops until the task is about to run.

In the [main.c](https://github.com/rxtxinv/AVR_Atmega32_Schedulers/blob/master/Atmega32_Co_Sch/main.c) file, I have created 3 tasks as follows:

<img src="https://github.com/rxtxinv/AVR_Atmega32_Schedulers/raw/master/Images/Tasks1.PNG" height="300" width="600">

The task LED_Flash_Update1 toggles the LED on PortD bit 7, the task LED_Flash_Update2 toggles the LED on PortD bit 6, and task LED_Flash_Update3 toggles the LED on PortD bit 5.

The first line runs LED_Flash_Update1 every 50ms, the second line runs the LED_Flash_Update2 every 500ms, and the last line runs the LED_Flash_Update3 every 1s.

<img src="https://github.com/rxtxinv/AVR_Atmega32_Schedulers/raw/master/Images/Tasks.PNG" height="300" width="600">



### The timing results
I have connected the Saleae logic analyzer to each of the 3 LEDs to capture the waveform of the tasks.

<img src="https://github.com/rxtxinv/AVR_Atmega32_Schedulers/raw/master/Images/Capture.PNG" height="600" width="800">

```
* 
```
