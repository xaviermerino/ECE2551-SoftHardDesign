## Lab #2: Hardware Authentication Token

#### Overview
The overall goal of this assignment is to build a very simple authentication token device. This device consists of an LCD screen and a push button interfacing with the Arduino platform. It generates an authentication code at fixed intervals and shows it when the push button has been pressed.

**In the process you will:**
  * Construct the circuit that controls the **LCD** component using hardware and software.
  * Review how to **interface** with push buttons.
  * Review and understand how to **debounce** a push button.
  * Interface with **non-volatile memory** such as the **EEPROM** to store long-term data that can be retrieved after a power cycle.
  * To apply the concept of abstractions in C++ by defining **classes** and instantiating **objects** from those classes to promote re-usability and increased efficiency.

#### Introduction to EEPROM
Every computer system needs non-volatile memory; that is, memory that persists between power cycles.  In embedded systems where no disk drive exists, this non-volatile memory is typically a variant of Read-Only Memory (ROM).  All sorts of ROM variants are available, as seen below.

| Type | Description |
|-------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **ROM** | Data written at semiconductor factory when ROM is built. After that, it cannot be changed. |
| **Programmable ROM (PROM)** | Blank chip that can be written to by using a “PROM programmer” or “PROM burner.” |
| **Erasable PROM (EPROM)** | Like PROM, except that it can be erased and re-written to. Requires an EPROM eraser, which shines a strong ultraviolet light into a window on top of the EPROM to erase the memory contents. |
| **Flash Memory** | Like PROM, except that it can be erased and re-written to by presenting certain signals to the Flash input. You can only write to flash a certain number of times and it is typically very slow. Also, single-bytes cannot be written to flash, instead writing occurs by the blocks (e.g., 256 byte blocks). |
| **Electrically Erasable PROM (EEPROM)** | Similar to Flash, but even though the number of writing times is limited, the limit is much higher than Flash (on the order of millions of times). Slow to write and to read, but useful for storing configuration information. Usually less than 1K bytes in size. |

<br>

The ATMega 328P follows a Harvard architecture, where program code and data are separated. Program code is stored in Flash. Data, on the other hand, can be found in both **SRAM** and **EEPROM** for long term storage, as seen below. The microcontroller on the Arduino Uno board has 1K bytes of EEPROM.

![block](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Lab-2/block-diagram.JPG?raw=true)

<br>

In this lab, we will experiment with writing and reading to and from the **EEPROM**.  

The process of working with **EEPROM** in the **ATMega328p** can be easily done via three registers:
* **EEAR:** EEPROM Address Register
* **EECR:** EEPROM Control Register
* **EEDR:** EEPROM Data Register

**To write to the EEPROM:**

1. Set the value of the address register to the address in the EEPROM that you want to write to.
2. Set the value of the data register (1 byte) to the data that you want to write.
3. Set the appropriate bits in the control register to begin the writing process.

**To read from the EEPROM:**

1. Set the value of the address register to the EEPROM address you want to read.
2. Set the appropriate bits in the control register to initiate the read.
3. Retrieve the value read by reading the contents in the data register.  

See the [video lecture](https://www.youtube.com/watch?v=Hbrh6Cq6A8s) for details on which bits to set. (8 mins)

#### Introduction to the Liquid Crystal Display (LCD)
In this lab, we will be leveraging of the power of abstractions and code reuse to interface with an LCD.  The LCD class made for the Arduino platform allows you to control LCD displays that are compatible with the Hitachi HD 44780 driver. But before we write any code, we need to properly set-up the hardware. Our system interfaces with the LCD component as seen below.

![lcd](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Lab-2/lcd-pinout.JPG?raw=true)

See the table below for information on how to connect the LCD pins to the Arduino pins.

| LCD Pin | Arduino Pin | LCD Pin | Arduino Pin |
|---------|-------------|---------|-------------|
| **1**       | GND         | **11**      | 5           |
| **2**       | +5V         | **12**      | 4           |
| **3**       | GND         | **13**      | 3           |
| **4**       | 12          | **14**      | 2           |
| **5**       | GND         | **15**      | +5V         |
| **6**       | 11          | **16**      | GND         |

Once the hardware is properly connected, we will use the `LiquidCrystal` class provided by the Arduino framework to reuse functionality that allows us to control the LCD. The `LiquidCrystal` class has many overloaded constructors, but we will be using the following one:

```c++
LiquidCrystal(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
```

If you look carefully, you will see a correlation between the interfacing diagram above and the names of the constructor parameters. That is, the first parameter, `rs`, of the constructor refers to the Arduino pin that is connected to the **RS** pin of the LCD; the `enable` parameter refers to the Arduino pin connected to the **enable** pin of the LCD; and finally, the `d0`, `d1`, `d2`, and `d3` parameters refer to the Arduino pins connected to the **DB4-DB7** pins of the LCD.  With this information in place, we can instantiate an object of the `LiquidCrystal` class as follows:

```c++
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
```

Once an object has been created, you can set up the LCD's number of columns and rows with the following code:

```c++
lcd.begin(16, 2);
```

This would set the lcd object ready for 2 rows and 16 columns, which can be used to print characters. You would only need to do this one time in your program. Once initialized, you can call the following function to position the LCD cursor and print characters, where the parameters of the setCursor set the position of the cursor in terms of col and row number.

```c++
lcd.setCursor(0,0); // (Column, Row)
```

For more information and examples visit the [Arduino LiquidCrystal Library Reference](https://www.arduino.cc/en/Reference/LiquidCrystal).

#### Getting Started

1. **[Download](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Lab-2/lab2.ino?raw=true)** the starter file. It will contain the following file:
  * `lab2.ino`

2. The provided file is a template file that you can use to fill in your code.
3. Fill in the function definitions for each of the classes' methods. You can implement your own, these are just there for reference.

#### Functional Requirements
You are required to build the circuit that makes this hardware token device possible.

**When turned on for the first time the device must:**
* Generate ten random numbers between `10000` and the limit given by `USHRT_MAX` defined in `<limits.h>`.
* These numbers must be saved to the **EEPROM** so they can be retrieved after a **power cycle**.

**After the numbers are loaded in the EEPROM the device must**:
* Keep a timer.
* The timer will help select an address to read from the EEPROM.
* A new address should be selected every ten seconds.
* The LCD should not display anything until the push button is pressed.
* Once the button is pressed the device will get an address based on the time.
* Once the button is pressed the LCD will display (the token will change accordingly):

```
Hardware Token
35469
```
* After three seconds the LCD must should go blank.
* The device follows this behavior until turned off.


#### Technical Requirements
This section will serve as a guideline of what is necessary for the program to behave correctly.
* The token you generate randomly should be of type `unsigned short` and hold values from `10000` to `USHRT_MAX`.
* The token is made up of **16 bits**.

<br>

![token](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Lab-2/token.png?raw=true)

<br>

* Each entry in the **EEPROM** can only hold 1 byte of data, therefore, you must break up the token into its first eight bits and its second eight bits. We will call the first eight bits the **high bits** and those will be bits 8-15. The **low bits** will be bits 0-7. You will save the high and low bits in the **EEPROM** and when a read is requested you must combine those two to obtain the original token.

![broken](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Lab-2/tokenbreak.png?raw=true)

<br>

* Internally, your device should keep track of time. Every ten seconds it should read a different entry from the **EEPROM**. This is, every ten seconds the token will be different. Since you are only implementing ten tokens. You must wrap around to keep on showing tokens on the screen. This is, after you have read all the tokens, start from the first token saved in the **EEPROM** again.

<br>

![timer](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Lab-2/pattern.png?raw=true)

<br>
* Once you press the button, the device must show the current token on the screen.

```
Hardware Token
33333
```

* After showing the token, the screen must go blank in three seconds.
* You are free to use any available pin to connect the push button. For more information check the Arduino [Example on Buttons](https://www.arduino.cc/en/Tutorial/Button).

Let's start explaining what each of the functions defined in given classes file must do.

**The following functions belong to the `Eeprom` class:**
* **Eeprom()**: Default constructor for the `Eeprom` class.
* **byte read(unsigned int uiAddress)**: This function returns a byte of data read from the **EEPROM** at the specified address `uiAddress`. It's implementation is similar to the code snippet below.

```c++
byte read(unsigned int uiAddress) {
  // Wait for completion of previous write
  while (EECR & (1 << EEPE));

  // Fill in with the appropriate code

  return 1; // Change to return byte
}

```

* **void write(unsigned int uiAddress, byte data)**: This function writes a byte of data read to the **EEPROM** at the specified address `uiAddress`. It's implementation is similar to the code snippet below.

```c++
void write(unsigned int uiAddress, byte data) {
  // Wait for completion of previous write
  while (EECR & (1 << EEPE));

  // Fill in with the appropriate code
}

```

**The following functions belong to the `Button` class:**
* **Button(unsigned short pin)**: Constructor for the `Button` class.
* **bool hasBeenPushed()**: This function returns `true` if the button has been pushed. It performs debouncing to avoid bogus readings.
