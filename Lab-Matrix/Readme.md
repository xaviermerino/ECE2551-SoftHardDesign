## Lab: Matrix - Operator Overloading and Exceptions

#### Overview
The overall goal of this assignment is to implement a C++ application that makes use of classes and object-oriented technology to create a user-defined `Matrix` type.

A matrix is a rectangular array of numbers arranged in a rows and columns fashion. The number of rows and columns define the dimensions of a matrix. For instance, a matrix that has two rows and three columns is a *two by three* matrix. The picture below illustrates some sample matrices.

![graphic](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-2/matrices.png?raw=true)

In the end, you are tasked with creating a class that will perform certain matrices operations. You already worked on this for a homework so feel free to reuse your code and adapt it to use **operator overloading** and **exceptions**.

For a brief linear algebra review you can check:
* **Video Lecture:** [Introduction to matrices](https://youtu.be/GguVxHgTv0s) (18 min)
* **Video Lecture:** [Computing Determinants of n-dimensional Matrices](https://youtu.be/nbHdSaQu8BI) (10 min)

For more information about the math behind matrices and their operations you can [check this](https://www.khanacademy.org/math/precalculus/precalc-matrices).

For more information on classes and objects you can follow this [tutorial](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-2/tutorial-classes-objects.pdf?raw=true).

#### Getting Started

1. **[Download](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Lab-Matrix/starter.zip?raw=true)** the starter file set. It will contain the following files:
  * `catch.hpp`
  * `Matrix.hpp`
  * `Matrix.cpp`
  * `MatrixException.hpp`
  * `MatrixException.cpp`
  * `main.cpp`

2. The provided `main.cpp` file is the test file. You are free to test your own program using your own `main.cpp` file but bear in mind that you will be tested against the provided one.

3. The provided `Matrix.hpp` file is the header file for the `Matrix.cpp` file. It provides the specification of the class. Your main task is to write the C++ implementation code for each of the Matrix class functions in the `Matrix.cpp` file. You can reuse your homework code to help you complete the task. **New functions were added to address operator overloading**. Follow the comments on the `Matrix.cpp` file for more details.

3. The provided `MatrixException.hpp` file is the header file for the `MatrixException.cpp` file. Your task is to write the implementation code for each of the functions defined in `MatrixException.hpp`.  

5. ~~In `Matrix.hpp`, create an `enum` and create a type alias for it, the type should be `Status`.~~ In `MatrixException.hpp` you will find an enum with all of the error codes possible. Your job is to use the enum as a key to obtain the description of the error found at `eventTable` in the  `MatrixException.cpp` file. Once this is done you will be able to throw `MatrixException` with an error key, the file path, and the line number in the program that caused the exception. You can use the standard predefined macros `__FILE__` to obtain the file path and `__LINE__` for the line number. Follow the comments on the `MatrixException.cpp` file for more details.


#### Self-Grading and Feedback
Once you have implemented all of the functions your goal is to pass all the tests and obtain this output:

```
All tests passed (83 assertions in 10 test cases)
```

This is provided for you to get feedback on your code. You can attempt to fix it and prepare it for submission once it passes all the tests.
