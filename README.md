# AVR_Atmega32_Schedulers
This repository for schedulers based on Atmega32

<img src="https://github.com/rxtxinv/AVR_Atmega32_Schedulers/raw/master/Images/Kit.jpg" height="500" width="900">

## Getting Started
In this repository, I will work on modifying all the scheduler codes in the [Patterns for time triggered embedded system]'s reference to work on Atmega32 instead of the 8051.

### Prerequisites
* Eclipse IDE with AVR plugin installed.
* Extreme burner software (optional: for editing the fuses for the first time).
* USBASP programmer (or any AVR programmer).
* [Atmega32 Datasheet](https://github.com/rxtxinv/AVR_Atmega32_Schedulers/blob/master/Atmega32.pdf) (Optional).

### ATmega32 Fuse Settings
I have used custom AVR Fuses for my projects. These Fuses are as follows:

```
High Fuse: 0xAF
Low Fuse: 0xD9
```

<img src="https://github.com/rxtxinv/AVR_Atmega32_Schedulers/raw/master/Images/Fuses.PNG" height="600" width="800">

```
* The Fuses makes the AVR runs with external crystal oscillator ( I am using 8MHz crystal oscillator ).
```

#### Projects contained
* [Atmega32_Co_Sch](https://github.com/rxtxinv/AVR_Atmega32_Schedulers/tree/master/Atmega32_Co_Sch) Simple Co-operative scheduler based on [Patterns for time triggered embedded systems] Reference's exmple.
*  
