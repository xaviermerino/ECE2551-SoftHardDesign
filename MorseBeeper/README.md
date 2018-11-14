## Morse Beeper

#### Overview
The overall goal of this project is to build a beeper (or pager). A beeper is a wireless communication device that receives and sends messages to others using its internal transceiver. In this project, we design and prototype a beeper that sends and receives Morse code. 

**In the process you will:**
* Interface with a **Liquid Crystal Display** (LCD) component.
* Use a voltage divider as an **analog input** to detect button presses.
* Interface with an **NRF2401L+** module via SPI to communicate with other modules.
* Interface with a piezo **buzzer** to notify user of events.
* Interface with the Arduino’s **EEPROM** to store long-term data that can be retrieved after a power cycle.
* Use the **Watchdog Timer**'s jitter to generate random byte sequences.
* Implement a beeper as a **state machine**.
* Apply the concept of abstractions in C++ by defining **classes** and instantiating **objects** from those classes to promote re-usability and increased efficiency.
* Use **inheritance** to extend Arduino’s classes.
* Use **pointers** to handle dynamic memory allocation.

#### nRF2401L+
The `nRF24L01+` is a single chip radio transceiver that operates in the 2.4 - 2.5 GHz band. It features ultra low power consumption and speeds up to 2 Mbps. We need to use a microcontroller to configure this radio through a Serial Peripheral Interface (SPI). You can download the datasheet [here](https://www.sparkfun.com/datasheets/Components/SMD/nRF24L01Pluss_Preliminary_Product_Specification_v1_0.pdf).

The `nRF24L01+` implements the concept of data pipes. Pipes are logical channels in the physical RF channel. Each pipe is assigned its own physical address for subsequent write or read operations. Each address is 40-bit long. This radio is able to write data to one pipe or to listen for data from up to six pipes. 

Imagine that your phone number is `321-123-4567`. If you were not guaranteed that this number belonged **only** to you, then someone else (who shares your number) could be getting your calls and texts. For this same reason, it is important to ensure that the address that you assign to the radio's receiving data pipe is unique. 

We use the term **universally unique identifier (UUID)** to refer to a number that is used to uniquely identify some entity. The probability that a UUID will be duplicated is not zero but it is low enough to be considered negligible. We need to generate a 40-bit UUID to assign to our radio's receiving data pipe to minimize the chances of two radios having the same address during lab. 

We are going to use the `Entropy` class to generate random bytes using the `Watchdog Timer`'s natural jitter. You can find the class [here](https://sites.google.com/site/astudyofentropy/file-cabinet/Entropy-v1.0.2.zip?attredirects=0&d=1).

We will use the [`NR24` library](https://github.com/nRF24/RF24) to control the radio. Documentation for the library can be found [here](http://tmrh20.github.io/RF24/classRF24.html).

The following table describes how to wire your `NRF24L01+` module. **Please note that the module can not operate at 5V.**

| Name 	| Description           	| Connected To 	|
|------	|-----------------------	|--------------	|
| CE   	| Chip Enable (RX / TX) 	| A1           	|
| CSN  	| SPI Chip Select       	| A2           	|
| MOSI 	| SPI Slave Data Input  	| 11 or ICSP-4 	|
| MISO 	| SPI Slave Data Output 	| 12 or ICSP-1 	|
| SCK  	| SPI Clock             	| 13 or ICSP-3 	|
| IRQ  	| Maskable Interrupt    	| 2            	|
| VCC  	| Power (1.9V - 3.6V)   	| 3.3 V        	|
| GND  	| Ground (0V)           	| GND          	|

#### LCDKeypad Class
The LCD library, [`LiquidCrystal`](https://www.arduino.cc/en/Reference/LiquidCrystal), allows you to control displays that are compatible with the **Hitachi HD 44780** driver. 

The LCD Keypad Shield provided looks like this:

![lcdkeypad](https://raw.githubusercontent.com/xaviermerino/ECE2551-SoftHardDesign/master/MorseBeeper/lcdkeypadshield.png)

The following table describes which pins are used by the shield.

| Arduino Pin 	| Description     	|
|-------------	|-----------------	|
| A0          	| Buttons         	|
| 4           	| LCD DB4         	|
| 5           	| LCD DB5         	|
| 6           	| LCD DB6         	|
| 7           	| LCD DB7         	|
| 8           	| LCD RS          	|
| 9           	| LCD Enable      	|
| 10          	| Backlit Control 	|

From the picture above you can see that the shield is equipped with the following buttons:
* Select
* Left
* Right
* Up
* Down
* Reset

These buttons (with the exception of the reset button) are wired to pin `A0` using a **voltage divider**. The Arduino reads the value at the pin and provides a number ranging from `0 - 1023` corresponding to the input voltage. The value read depends on which button was pressed. A portion of the schematic is presented below. 

The resistances used in your shield might vary depending on the manufacturer. You will need this information when calculating the expected value for a button press. Alternatively, you can obtain this information with a multimeter or by reading the value at the pin when a button is pressed. The complete schematic can be found [here](http://image.dfrobot.com/image/data/DFR0009/LCDKeypad%20Shield%20V1.0%20SCH.pdf). 

You will be extending this class using **inheritance** to create an `LCDKeypad` class which will:
* Extend the `LiquidCrystal` class.
* Define the following `enum` to make your code more readable:

```
typedef enum {LEFT, RIGHT, UP, DOWN, SELECT, NONE} Button;
```

* Implement **debouncing** for the analog input wired at pin `A0`. Define and implement the function `getButtonPress()` which returns the button that was pressed. The function prototype is provided below.

```
Button getButtonPress();
```




#### Memory Class
In embedded systems where no disk drive exists, non-volatile memory is typically a variant of Read-Only Memory (ROM). The **ATMega328P** follows a Harvard architecture, where program code and data are separated. Program code is stored in Flash. Data, on the other hand, can be found in both **SRAM** and **EEPROM**. The microcontroller on the Arduino Uno board has 1KiB of EEPROM memory.

You will be using the EEPROM to store configuration information, contacts, and messages. The table below describes the memory map implemented for this system. 

| Address       	| Value          	| Purpose                               	|
|---------------	|----------------	|---------------------------------------	|
| 0x000 - 0x002 	| 0xC0FFEE       	| Initialization Flag                   	|
| 0x003 - 0x017 	| Contact Object 	| Node's Contact: UUID and Name                  	|
| 0x018 - 0x019 	| 0xFACE         	| Contact List Flag                     	|
| 0x020         	| Counter        	| Number of Contacts                    	|
| 0x021 - 0x035 	| Contact Object 	| Contact #1: UUID and Name             	|
| 0x036 - 0x050 	| Contact Object 	| Contact #2: UUID and Name             	|
| 0x051 - 0x065 	| Contact Object 	| Contact #3: UUID and Name             	|
| 0x066 - 0x080 	| Contact Object 	| Contact #4: UUID and Name             	|
| 0x081 - 0x095 	| Contact Object 	| Contact #5: UUID and Name             	|
| 0x096 - 0x110 	| Contact Object 	| Contact #6: UUID and Name             	|
| 0x111 - 0x125 	| Contact Object 	| Contact #7: UUID and Name             	|
| 0x126 - 0x140 	| Contact Object 	| Contact #8: UUID and Name             	|
| 0x141 - 0x155 	| Contact Object 	| Contact #9: UUID and Name             	|
| 0x156 - 0x170 	| Contact Object 	| Contact #10: UUID and Name            	|
| 0x171 - 0x172 	| 0xCA11         	| Message List Flag                     	|
| 0x173         	| Counter        	| Number of Messages                    	|
| 0x174 - 0x186 	| Message Object 	| Message #1                            	|
| 0x187 - 0x199 	| Message Object 	| Message #2                            	|
| 0x200 - 0x212 	| Message Object 	| Message #3                            	|
| 0x213 - 0x225 	| Message Object 	| Message #4                            	|
| 0x226 - 0x238 	| Message Object 	| Message #5                            	|
| 0x239 - 0x251 	| Message Object 	| Message #6                            	|
| 0x252 - 0x264 	| Message Object 	| Message #7                            	|
| 0x265 - 0x277 	| Message Object 	| Message #8                            	|
| 0x278 - 0x290 	| Message Object 	| Message #9                            	|
| 0x291 - 0x303 	| Message Object 	| Message #10                           	|
| 0x304 - 0x316 	| Message Object 	| Message #11                           	|
| 0x317 - 0x329 	| Message Object 	| Message #12                           	|
| 0x330 - 0x342 	| Message Object 	| Message #13                           	|
| 0x343 - 0x355 	| Message Object 	| Message #14                           	|
| 0x356 - 0x368 	| Message Object 	| Message #15                           	|
| 0x369 - 0x381 	| Message Object 	| Message #16                           	|
| 0x382 - 0x394 	| Message Object 	| Message #17                           	|
| 0x395 - 0x407 	| Message Object 	| Message #18                           	|
| 0x408 - 0x420 	| Message Object 	| Message #19                           	|
| 0x421 - 0x433 	| Message Object 	| Message #20                           	|
| 0x434         	| Offset         	| Next available spot @ <Base + Offset> 	|

The memory map consists of the following sections: 

1. **Flags:** There are three flags in the memory map that get verified at every boot for **integrity** and **schema**.

   - **Initialization Flag:** Consists of three bytes (0x00 - 0x02) that spell `0xC0FFEE`. These bytes are set during the device's configuration stage. 

   - **Contact List Flag:** Consists of two bytes (0x18 - 0x19) that spell `0xFACE`. These bytes are set during the device's configuration stage and mark the beginning of the contact list related entries in the EEPROM.

   - **Message List Flag:** Consists of two bytes (0x171 - 0x172) that spell `0xCA11`. These bytes are set during the device's configuration stage and mark the beginning of the message list related entries in the EEPROM.

2. **Counters:** There are two counter entries in the EEPROM. 

   * **Contact Counter**: Keeps track the number of contacts stored in the EEPROM. May hold values from 0 to 10. 

   * **Message Counter**: Keeps track the number of messages stored in the EEPROM. May hold values from 0 to 20. 

3. **Offsets:** There is one offset entry in the EEPROM. According to the memory table above, the base address for the messages (or the address for the first message) is `0x174`. By adding an offset to this base address we can obtain the position of any message element relative to the first one. The offset entry (0x434) can store up to 8-bits of information allowing you to traverse from location `0x174` all the way to location `0x429`. This is useful to point to the next location available for saving a message. 

4. **Contact Objects:** The EEPROM stores up to 10 contact objects. These objects are 15 bytes long and contain the contact's name and radio's UUID. The object located at address `0x003` contains information regarding the node and is set during configuration time. Since we only have room for ten contacts, additional contacts must not be allowed. See the `Contact` class for more information. 

5. **Message Objects:** The EEPROM stores up to 20 message objects. These objects are 13 bytes long and contain information on the sender, the receiver, the payload, and the payload's length. Since we only have room for twenty messages in the given design, we may need to reuse EEPROM locations if we receive more than twnety messages. See the `Message` class for more information. 

You will be implementing the `Memory` class that handles writing and reading data to the EEPROM. A template is provided below.

```c++
class Memory {
  public:
    Memory();
    Memory(Contact node);
    unsigned char* getNodeUUID();
    char* getNodeName();
    unsigned short getNumberContacts();
    unsigned short getNumberMessages();
    Contact getContact(unsigned short index);
    Message getMessage(unsigned short index);
    bool saveContact(Contact contact);
    void saveMessage(Message message);
    void saveNodeInformation(Contact contact);
    // Add as you see fit

  protected:
    bool hasSchema();
    void setSchema();
    void clearMessages();
    void clearContacts();
    unsigned short getMessagePointerOffset();
    // Add as you see fit

  private:
    const unsigned short MAX_CONTACTS = 10;
    const unsigned short MAX_MESSAGES = 20;
    // Add as you see fit

};
```

Let's start explaining what each of the functions must do.

* **`Memory()`:** Default constructor for the `Memory` class. Makes sure that the **schema** is set up by verifying the flag bytes. If the **schema** is corrupted or has never been set up, we:
   - Set the flag bytes in their appropriate location.
   - Clear the locations reserved for contacts and messages.
   - Reset the contact and messages counters.
   - Reset the offset entry. 

* **`Memory(Contact node)`:** Parametrized constructor for the `Memory` class. Takes a `Contact` object as an argument. The contact object contains the information on the node's name and UUID. This performs the same operations as the default constructor plus saving the `Contact` object in the space reserved for the node's name and UUID. 

* **`unsigned char* getNodeUUID()`:** Returns the node's 40-bit UUID.

* **`char* getNodeName()`:** Returns the node's name.

* **`unsigned short getNumberContacts()`:** Returns the contents of contact counter entry. 

* **`unsigned short getNumberMessages()`:** Returns the contents of messages counter entry. 

* **`Contact getContact(unsigned short index)`:** Returns the `Contact` object specified by the `index`. If `index` points to an unsaved location, return an empty `Contact`. 

* **`Message getMessage(unsigned short index)`:** Returns the `Message` object specified by the `index`. If `index` points to an unsaved location, return an empty `Message`. 

* **`bool saveContact(Contact contact)`:** Saves the given `Contact` object into an empty location in the EEPROM and returns `true`. If no more empty locations are available, returns `false`.

* **`void saveMessage(Message message)`:** Saves the given `Message` object into the next available location in the EEPROM. Note that this location might have a previous message that will get overwritten if there are no more empty message locations. In other words, after the twenty messages have been saved, the system will overwrite older messages to make room for the new ones.

* **`void saveNodeInformation(Contact contact)`:** Saves the given `Contact` object into the node's contact location.

* **`bool hasSchema()`:** Verifies that the flag bytes and schema are set for the node. Returns `true` if that's the case, `false` otherwise.

* **`void setSchema()`:** Sets the flag bytes and schema for the node. 

* **`void clearMessages()`:** Clears the EEPROM locations associated with `Message` entries. Resets the messages counter.

* **`void clearContacts()`:** Clears the EEPROM locations associated with `Contact` entries. Resets the contacts counter.

* **`unsigned short getMessagePointerOffset()`:** Returns the value of the message pointer offset entry from the EEPROM.

#### Contact Class

A `Contact` object stores information on a contact's name and UUID. The UUID is 40-bit long and the contact's name is up to ten characters long. This gives a `Contact` object a size of **15 bytes**. 

1. **Contact's UUID:** The contact's 40-bit UUID.

2. **Contact's name:** The contact's name. This can hold up to ten characters. 

A template is provided below.

```c++
class Contact {
  public:
    Contact();
    Contact(unsigned char* givenUUID, char const* givenName);
    Contact(unsigned char* givenUUID, char givenName);
    void setUUID(unsigned char* givenUUID);
    void setName(char const* givenName);
    void setName(char givenName);
    unsigned char* getUUID();
    char* getName();
    // Add as you see fit

  private:
    // ...
    // ...
    // ...
};
```

Let's start explaining what each of the functions must do.

* **`Contact()`:** Default constructor for the `Contact` class. Creates an empty contact with an empty name and empty UUID. 

* **`Contact(unsigned char* givenUUID, char const* givenName)`:** Parametrized constructor for the `Contact` class. Takes a given 40-bit UUID and a C-style string as parameters to initialize the object's data members. 

* **`Contact(unsigned char* givenUUID, char givenName)`:** Parametrized constructor for the `Contact` class. Takes a given 40-bit UUID and a character as parameters to initialize the object's data members. 

* **`void setUUID(unsigned char* givenUUID)`:** Default constructor for the `Contact` class. Creates an empty contact with an empty name and empty UUID. 

* **`void setName(char const* givenName)`:** Saves the given C-style string as the contact's name. Enforces that the contact's name is up to ten characters long by truncating the excess characters.

* **`void setName(char givenName)`:** Saves the given character as the contact's name. 

* **`unsigned char* getUUID()`:** Returns the contact's 40-bit UUID. 

* **`char* getName()`:** Returns the contact's name as a C-style string. 

#### Message Class

A `Message` object stores the UUID of the sender and the receiver, alongside with the payload and its length. This gives a `Message` object the size of **13 bytes**.

1. **Sender's UUID:** The sender's 40-bit UUID.

2. **Receivers's UUID:** The receiver's 40-bit UUID. Used to verify that message was received by the intended party.

3. **Payload:** The payload consists of morse code messages that may vary in size. Their size cannot exceed 16 characters (since that's the maximum amount we can display in the LCD screen). Morse code uses the `'.'` and the `'-'` symbols and we will represent these with zeroes and ones respectively. This allows us to represent each character with a bit instead of a byte. We need 2 bytes to represent up to 16 characters.

4. **Payload Length:** Since a message can vary in length, the payload length tells us how many bits are valid to be interpreted as part of the message. We use 1 byte to store the payload's length.

A template is provided below.

```c++
class Message {
  public:
    Message();
    Message(unsigned char* from, unsigned char* to, unsigned short payload, unsigned char length);
    Message(unsigned char* from, unsigned char* to, char const* message);
    void setLength(unsigned char length);
    void setTo(unsigned char* to);
    void setFrom(unsigned char* from);
    void setPayload(unsigned short payload);
    unsigned char getLength();
    unsigned char* getTo();
    unsigned char* getFrom();
    unsigned short getPayload();
    char* getPayloadString();

  protected:
    unsigned short stringToPayload(char const* message);
    char* payloadToString(unsigned short payload, unsigned char length);

  private:
    // ...
    // ...
    // ...
};
```

Let's start explaining what each of the functions must do.

* **`Message()`:** Default constructor for the `Message` class. Creates an empty message. 

* **`Message(unsigned char* from, unsigned char* to, unsigned short payload, unsigned char length)`:** Parametrized constructor for the `Message` class. Takes the sender and receiver's UUIDs, the payload, and its length. 

* **`Message(unsigned char* from, unsigned char* to, char const* message)`:** Parametrized constructor for the `Message` class. Takes the sender and receiver's UUIDs. Additionally, it takes a message in a C-style string. The payload length is calculated after the conversion from a C-style string to the payload bits. 

* **`void setLength(unsigned char length)`:** Sets the length of the payload for the `Message` object.

* **`void setTo(unsigned char* to)`:** Sets the receiver's UUID for the `Message` object.

* **`void setFrom(unsigned char* from)`:** Sets the sender's UUID for the `Message` object.

* **`void setPayload(unsigned short payload)`:** Sets the payload for the `Message` object.

* **`unsigned char getLength()`:** Returns the payload's length.

* **`unsigned char* getTo()`:** Returns the receiver's UUID.

* **`unsigned char* getFrom()`:** Returns the sender's UUID.

* **`unsigned short getPayload()`:** Returns the payload.

* **`char* getPayloadString()`:** Returns the decoded version of the payload in a C-style string. 

* **`unsigned short stringToPayload(char const* message)`:** Encodes up to a 16 character Morse code string into a 16 bit buffer. Returns the result of this encoding.

* **`char* payloadToString(unsigned short payload, unsigned char length)`:** Decodes a payload into a C-style string. Uses the payload's length to determine the size of the resulting string. Returns the decoded string.

#### State Machine

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
