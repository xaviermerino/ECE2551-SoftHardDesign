## Lab #2: Hardware Authentication Token

#### Overview
The overall goal of this assignment is to build a very simple authentication token device. This device consists of an LCD screen and a push button interfacing with the Arduino platform. It generates an authentication code at fixed intervals. 

In the process you will:
  * Construct the circuit that controls the **LCD** component using hardware and software.
  * Review how to **interface** with push buttons.
  * Review and understand how to **debounce** a push button.
  * Interface with **non-volatile memory** such as the **EEPROM** to store long-term data that can be retrieved after a power cycle.
  * To apply the concept of abstractions in C++ by defining **classes** and instantiating **objects** from those classes to promote re-usability and increased efficiency. 

Every computer system needs non-volatile memory; that is, memory that persists between power cycles.  In embedded systems where no disk drive exists, this non-volatile memory is typically a variant of Read-Only Memory (ROM).  All sorts of ROM variants are available, as seen below.

| Type | Description |
|-------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **ROM** | Data written at semiconductor factory when ROM is built. After that, it cannot be changed. |
| **Programmable ROM (PROM)** | Blank chip that can be written to by using a “PROM programmer” or “PROM burner.” |
| **Erasable PROM (EPROM)** | Like PROM, except that it can be erased and re-written to. Requires an EPROM eraser, which shines a strong ultraviolet light into a window on top of the EPROM to erase the memory contents. |
| **Flash Memory** | Like PROM, except that it can be erased and re-written to by presenting certain signals to the Flash input. You can only write to flash a certain number of times and it is typically very slow. Also, single-bytes cannot be written to flash, instead writing occurs by the blocks (e.g., 256 byte blocks). |
| **Electrically Erasable PROM (EEPROM)** | Similar to Flash, but even though the number of writing times is limited, the limit is much higher than Flash (on the order of millions of times). Slow to write and to read, but useful for storing configuration information. Usually less than 1K bytes in size. |

<br>
The ATMega 328P follows a Harvard architecture, where program code and data are separated; program code is stored in Flash and data in both SRAM and EEPROM for long term storage, as seen below.  The microcontroller on the Arduino Uno board has 1K bytes of EEPROM.
