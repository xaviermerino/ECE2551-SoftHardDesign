## Lab #6: Hardware Counters and Timers

### Overview
The overall goal of this assignment is to become familiar with the basic use and configuration of timers. You will learn how to configure and access the timer registers to create a simple delay function similar to the `delay()` provided by the Arduino libraries. Throughout this procedure you will apply C++ pointers to access the ATMega328P registers and you will implement your own `pinMode()` and `digitalWrite()` functions.

In the end you will toggle an LED from on to off every second using the functions that you built.

**In this lab you will:**
  * Become familiar with the **Timer/Counter0** registers.
  * Use **pointers** to access registers.
  * Recreate **functions** provided by the Arduino library.

### Introduction to Timers
Timers are used on every digital computer that you have ever used. Without timers, most of today's embedded devices would not be able to perform their functions (such as controlling pool equipment, waking us up in the morning, ...). The range of timers vary widely, from a few microseconds used to delay our programs (based on the ticks of a processor), to minutes used to keep track of our workouts, to hours used to keep track of lecture classes. The support timer operations, hardware circuitry is used to support all sorts of timer ranges. The AVR microcontroller includes a very accurate timer, accurate to the resolution of microseconds! This feature makes them suitable for timer applications.

#### From Pulses to Time

As you remember, everything that occurs in digital computers is driven by some clock, i.e., the system clock. The system clock is characterized by its frequency. Remember that the time it takes the CPU clock signal to repeat itself (i.e., a pulse) is referred to as a period of the signal. In digital computers, time is deduced by relating time (in seconds unit) to number of pulses. To do this, we remember that Hertz is nothing more than the number of pulses per second.

Let's see how we can relate number of pulses to time. Assume that we keep track of pulses on a 4 MHz system so that each pulse takes 1/4 MHz = 0.00025 ms. So, on the first pulse, 0.00025 ms have elapsed; on the second pulse, 0.0005 ms have elapsed, on the third pulse, 0.00075 ms have elapsed, and so on. If we keep counting up, it is clear that it would take 4,000,000 pulses to reach 1 second; 8,000,000 pulses to reach 2 seconds, and so on. Similarly, it is evident that it would take 2,000,000 pulses to reach .5 seconds; 1,000,000 pulses to reach .25 seconds, and so on. This relationship between number of pulses and time is captured in the formula below:

<br>

![calc1](http://mathurl.com/zew9uos.png)

<br>
Now consider an application developed for a 4 MHz system that needs to blink an LED every 10 microseconds. To determine the number of pulses required to reach that delay we would plug in the application's values into the formula as seen below:

<br>

![calc2](http://mathurl.com/jjgfdav.png)

![calc3](http://mathurl.com/jy7etc9.png)

<br>
Now that we understand how to relate pulses to time, creating a timer application is a matter of understanding the registers provided by the ATMega328P to detect clock pulses and to configure desired time values.


#### Timers as Registers
The ATMega328P provides two types of timers: 8-bit and 16-bit timers.

In an 8-bit timer, the register used to store the value of the number of pulses is 8-bit wide whereas in the 16-bit timer, the register width for pulse-count is 16 bits.

This means that the 8-bit timer is capable of counting 256 steps (from 0 to 255) and the 16-bit timer is capable of counting 65536 steps (from 0 to 65535).

Overall, the ATMega328P includes three timers:
* **Timer0**: 8-bit timer
* **Timer1**: 16-bit timer
* **Timer2**: 8-bit timer

In this lab, we will be using **Timer0**. Timers need counter registers to keep track of how many pulses have occurred. When a pulse (from the system clock or an external clock) has occurred the content of the counter gets incremented. The value in the counter represents how many times an event has happened (or in this case, how many clock pulses have occurred). There is also a flag for each counter. This flag is set when the counter overflows. An 8-bit counter will overflow when it goes from `0xFF` to `0x00`.

The counter that we will be working with, since we are using **Timer0**, is `TCNT0`. This is an 8-bit register that contains the number of pulses that have occurred. Let's assume that ATMega328P runs at 4 MHz (the one in the Arduino runs at 16 MHz). From the calculations above we know that we it takes 40 pulses to reach 10 microseconds. So ideally we would need to count for 40 pulses.

A better solution, though, would be to make the counter overflow every 40 pulses. To do this, we set the counter's value to 216 (256 - 40) so that we make sure an overflow occurs right after 40 pulses. We can monitor the overflow flag `TOV0` to determine when the overflow occurred for `TCNT0`.

<br>
<img src="https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Lab-HWTimers/simpleRepresentation.png?raw=true" width="550">

<br>

But in order to tell the microcontroller how to use the **Timer0** we need to specify a mode first. **Timer0** has different modes. We will be using the timer in **Normal Mode**. There are other modes that you can use with this timer. The mode is set up by setting the `WGM0` bits. There are three of these identified as `WGM00`, `WGM01`, and `WGM02`.

| WGM02 | WGM01 | WGM00 | Mode of Operation |
|-------|-------|-------|-------------------|
| 0     | 0     | 0     | Normal            |
| 0     | 0     | 1     | PWM               |
| 0     | 1     | 0     | CTC               |
| 0     | 1     | 1     | Fast PWM          |
| 1     | 0     | 0     | Reserved          |
| 1     | 0     | 1     | PWM               |
| 1     | 1     | 0     | Reserved          |
| 1     | 1     | 1     | Fast PWM          |

<br>

We also need to specify what clock we are using as an input. So far we have assumed that you need to use the system clock as an input. The truth is that you can use external events or even a *slowed-down* version of the system clock. In order to *slow-down* the system clock we use a **prescaler**. A **prescaler** simply divides the system clock by a value and uses that new, *slowed-down*, signal as input. We take the new, slower, frequency and apply the formulas above to determine the number of pulses required to reach the desired time delay.

In order to specify the input we set the `CS0` bits. There are three of these identified as `CS00`, `CS01`, and `CS02`.


| CS02 | CS01 | CS00 | Input                                            |
|------|------|------|--------------------------------------------------|
| 0    | 0    | 0    | No clock source. Timer stopped.                  |
| 0    | 0    | 1    | System Clock. No prescaling.                     |
| 0    | 1    | 0    | System Clock ÷ 8. (From prescaler)               |
| 0    | 1    | 1    | System Clock ÷ 64. (From prescaler)              |
| 1    | 0    | 0    | System Clock ÷ 256. (From prescaler)             |
| 1    | 0    | 1    | System Clock ÷ 1024. (From prescaler)            |
| 1    | 1    | 0    | External clock on T0 pin. Clock on Falling Edge. |
| 1    | 1    | 1    | External clock on T0 pin. Clock on Rising Edge.  |

<br>

For your convenience, the table below lists the effective clock frequency after applying a **prescaler** to the 16 MHz clock in your Arduino.

| Prescaler | Effective Clock Frequency |
|-----------|---------------------------|
| 8         | 2 MHz                     |
| 64        | 250 KHz                   |
| 256       | 62.5 KHz                  |
| 1024      | 15625 Hz                  |

<br>

Once we set these `CS0` bits the timer starts and only stops when we clear them.

#### Timer0: Registers
This section contains information about the registers you will be needing in this lab. These registers contain the flags and bits discussed above. We also discuss the ATMega328P's **Status Register** `SREG`.

* **TCNT0 (TC0 Counter Value Register)**: This register gives access to the 8-bit counter for **Timer0**.

<br>

<img src="https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Lab-HWTimers/TCNT0.png?raw=true" width="400">

<br>

* **TCCR0A (TC0 Control Register A)**: The `WGM00` and `WGM01` bits in this register, along with the remaining `WGM02` bit in `TCCR0B` control the operation mode of the counter.

<br>

<img src="https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Lab-HWTimers/TCCR0A.png?raw=true" width="400">

<br>

* **TCCR0B (TC0 Control Register B)**: The `WGM02` bit in this register, along with the remaining `WGM01` and `WGM00` bits in `TCCR0A` control the operation mode of the counter.

<br>

<img src="https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Lab-HWTimers/TCCR0B.png?raw=true" width="400">

<br>

* **TIFR0 (TC0 Interrupt Flag Register)**:
The `TOV0` bit is set when an overflow occurs in **Timer0**. `TOV0` is cleared by writing a logic one to the flag.

<br>
<img src="https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Lab-HWTimers/TIFR0.png?raw=true" width="400">

<br>

* **SREG (Status Register)**: This register contains information about the result of the the most recently executed arithmetic instruction. It is used to alter the flow of the program by using conditional operations. This register is not automatically saved when entering an interrupt routine and so it must be manually saved. The **Global Interrupt Enable** (I-Flag) must be set for interrupts to be enabled.

<br>

<img src="https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Lab-HWTimers/SREG.png?raw=true" width="400">

<br>

### Getting Started

1. **[Download](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Lab-HWTimers/starter.zip?raw=true)** the starter file. It will contain the following file:
  * `starter.ino`

2. The provided file is a template file that you can use to fill in your code.
3. Fill in the function definitions for each of the classes' methods. You can implement your own, these are just there for reference.

### Functional Requirements
You are required to **recreate** three of the Arduino functions.
* You must be able to set an arbitrary delay (in milliseconds) using your own function, mimicking the behavior of `delay()`.  
* You must be able to replicate the functionality of `pinMode()` and `digitalWrite()`.
* You must be able to turn on and off an LED attached to pin 13. Each second you must toggle the state of the LED.

### Technical Requirements
This section will serve as a guideline of what is necessary for the program to behave correctly.

You need to implement the following functions:

* **void myPinMode(uint8_t pin, Mode mode)**: You must use pointers to recreate the `pinMode()` function. This function takes a pin number (based on the Arduino scheme) and the `Mode`. An `enum` provides the different possible modes that a pin can be in. The pointers should help you choose between ports based on the pin number chosen. For instance, a the variable `ddr` points to either `DDRD` or `DDRB` depending on the chosen pin.  

```c++
typedef enum {M_INPUT, M_OUTPUT, M_INPUT_PULLUP} Mode;

void myPinMode(uint8_t pin, Mode mode) {
  // Depending on the pin number, ddr should point to either DDRD or DDRB
  volatile uint8_t* ddr;
  ...
}
```

<br>

* **void myDigitalWrite(uint8_t pin, bool turnOn)**: You must use pointers to recreate the `digitalWrite()` function. The pointers should help you choose between ports based on the pin number chosen. For instance, a the variable `port` points to either `PORTD` or `PORTB` depending on the chosen pin.  

```c++
void myDigitalWrite(uint8_t pin, bool turnOn){
  // Depending on the pin number, port should point to either DDRD or DDRB
  volatile uint8_t* port;
  ...
}

```

<br>

* **void delay_one_ms()**: This function uses **Timer0** to implement a one millisecond delay. Follow the steps below to get this function working properly:

  * Choose a **prescaler** for the desired delay
  * Disable the **I-Flag** in the `SREG`. Alternatively, save a copy of `SREG` to restore later.
  * Set the proper value in `TCNT0`.
  * Set **Timer0** to **Normal Mode**.
  * Set the **prescaler** bits.
  * Wait until the **overflow** flag `TOV0` is set.
  * **Stop** the clock.
  * **Clear** the `TOV0` flag by setting it.
  * **Restore** the interrupts by setting the I-Flag in the `SREG`. Or load `SREG` from the copy you made before.

```c++
void delay_one_ms(){
  ...
}
```

<br>

* **void delay_generic(unsigned long ms)**: This function calls the `delay_one_ms()` function to implement a delay for an arbitrary amount of milliseconds. This function recreates the behavior of the Arduino `delay()` function.

```c++
void delay_generic(unsigned long ms){
  ...
  // call delay_one_ms()
  ...
}
```
