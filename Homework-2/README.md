## Assignment: Matrix - Intro to Classes

#### Overview
The overall goal of this assignment is to implement a C++ application that makes use of classes and object-oriented technology to create a user-defined `Matrix` type.

The functional goal is to create a `Matrix` class that supports certain common operations. In the process you will understand how to create user-defined types using C++ classes, initialize objects using an overloaded constructor, apply the principles of encapsulation and abstraction, and refresh (or learn) the basic linear algebra operations on matrices.

A matrix is a rectangular array of numbers arranged in a rows and columns fashion. The number of rows and columns define the dimensions of a matrix. For instance, a matrix that has two rows and three columns is a *two by three* matrix. The picture below illustrates some sample matrices.

![graphic](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-2/matrices.png?raw=true)

In the end, you are tasked with creating a class that will perform certain matrices operations. In the future assignments you will be building extra functionality to this class as you explore other object-oriented principles.

For a brief linear algebra review you can check:
* **Video Lecture:** [Introduction to matrices](https://youtu.be/GguVxHgTv0s) (18 min)
* **Video Lecture:** [Computing Determinants of n-dimensional Matrices](https://youtu.be/nbHdSaQu8BI) (10 min)

For more information about the math behind matrices and their operations you can [check this](https://www.khanacademy.org/math/precalculus/precalc-matrices).

For more information on classes and objects you can follow this [tutorial](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-2/tutorial-classes-objects.pdf?raw=true).

#### Functional Requirements
The following requirements are an overview of what is expected of you in this assignment. More details on how to implement the solution can be found in the Technical Requirements section.

* Each row in the matrix is represented by a `std::vector` of type `double`. The size of the vector will be determined by the required dimensions.
* The matrix itself is represented by a vector of row vectors. The matrix is a `std::vector` of type `vector<double>`.
* Create a variable `rowSize` of type `int` that keeps tract of the number of rows in the matrix.
* Create a variable `colSize` of type `int` that keeps tract of the number of columns in the matrix.
* Create a function `dotProduct` that returns the result of this operation when applied to the two supplied vectors.
* Create a function `add` that can add a matrix to another. The function should perform this addition on the calling object.
* Create a function `subtract` that can subtract a matrix to another. The function should perform the subtraction on the calling object.
* Create a function `multiply` that can multiply a matrix by a scalar. The function should perform this multiplication on the calling object.
* Create another function `multiply` that **overloads** the previous function of this name. This new `multiply` function can multiply a matrix by another. The result should be stored on the the calling object.
* Create a function `transpose` that performs a matrix transpose on the calling object.
* Create a function `zero` that replaces all of the elements in a matrix with zeros. This function should perform this operation on the calling object.
* Create a function `show` that prints all of the contents of the calling matrix.
* Create a **recursive** function `getDeterminant` that returns the determinant of the calling matrix.
  * Remember to identify your recursive and base cases.
  * The **base case** for this function *could* be:
    * The algorithm encountered a matrix with dimensions 2x2.
  * The **recursive case** for this function *could* be:
    * Any matrix with a greater dimension than 2x2.
* Create a function `getAt` that returns the element stored in the specified position of the calling matrix. The position will be specified by a row and column number.
* Create a function `getRowSize` that returns the amount of rows in the calling matrix.
* Create a function `getColSize` that returns the amount of columns in the calling matrix.
* Create a function `isSquare` that returns `true` if the calling matrix is a square matrix or `false` if it is not.
* Create a function `hasSameDimensionsAs` that returns `true` if the calling matrix has the same dimensions as the matrix passed as an argument. It returns `false` otherwise.
* Create a function `getMinor` that returns the minor of the calling matrix based on the specified row and column.  

For more information on `std::vector` you can check [here](http://www.cplusplus.com/reference/vector/vector/).

#### Getting Started

1. **[Download](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-2/starterHwk2.zip?raw=true)** the starter file set. It will contain the following files:
  * `catch.hpp`
  * `Matrix.hpp`
  * `Matrix.cpp`
  * `main.cpp`
2. The provided `main.cpp` file is the test file. You are free to test your own program using your own `main.cpp` file but bear in mind that you will be tested against the provided one.
3. The provided `Matrix.hpp` file is the header file for the `Matrix.cpp` file. It provides the specification of the class. Your main task is to write the C++ implementation code for each of the Matrix class functions in the `Matrix.cpp` file.
4. Use your favorite IDE or editor to modify your files. At first, **the program won't compile**. Follow the steps 5 - 7 below to get it to compile.
5. In `Matrix.hpp`, create an `enum` and create a type alias for it, the type should be `Status`. It should hold the following values:
  * NoError
  * DivideByZeroError
  * DimensionError
6. In `Matrix.cpp`, write an empty implementation for each of the functions in the `Matrix.hpp` file.
7. The **program will now compile**. If you try running the program it will tell you that it has **failed all the tests**. Your goal is to make the program pass all the tests by completing the implementation of the methods given to you. You can implement helper functions if needed. See the following section for more information.

#### Technical Requirements
This section will serve as a guideline of what is necessary for the program to pass all the tests. We perform unit testing using the **Catch** framework. Catch is a **header-only** framework which means you just need to drop the header file containing the framework into your project. This is the reason behind the `catch.hpp` file.

You can also see that some code is provided in the `main.cpp` file. This code tests your `Matrix` class that you placed in the `Matrix.hpp` and `Matrix.cpp` files. If your code passes all the tests it is ready for submission and will, most likely **(cheating is heavily penalized)**, receive full credit.

The only thing that you need to do is to modify the `Matrix.hpp` and `Matrix.cpp` files to get the provided functions working. Don't change the function signature as the testing program relies on this to grade your submission. When you first run your program (and no modifications to the functions have been made) you will see something like this:

```
test cases: 24 | 24 failed
assertions: 24 | 24 failed
```

Let's start explaining what each of the functions defined in the `Matrix.hpp` file must do. Function implementations for **both** classes **must** be placed in the `Matrix.cpp` file.

**The following functions belong to the `Matrix` class:**
* **Matrix()**: Default constructor for the `Matrix` class. It must initialize `rowSize` and `colSize` to zero.

* **Matrix(const std::vector\<std::vector\<double\>\>& data)**: Parametrized constructor for the `Matrix` class. It takes a vector of row vectors (that store data of type double), resizes the `matrix` data member accordingly and copies the information in `data` to `matrix`.

```c++
enum { RowOne, RowTwo };

std::vector<std::vector<double>> data;
const int numberRows = 2;
data.resize(numberRows);

data[RowOne].push_back(9);
data[RowOne].push_back(7);
data[RowTwo].push_back(0);
data[RowTwo].push_back(2);

Matrix sample(data);
```

The sample code above will create the `Matrix` object below.

<br>

![add](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-2/matrix2x2.png?raw=true)

<br>

* **Status add(const Matrix& other)**: Function that takes as an argument a matrix `other` and adds it, element-wise, to the calling object. It returns a value of type `Status` (defined previously). It should return `NoError` if the addition was carried out successfully or `DimensionError` if the matrices' dimensions do not match.

```c++
enum { RowOne, RowTwo, RowThree };
const int numberRows = 3;

std::vector<std::vector<double>> dataOne;
dataOne.resize(numberRows);

dataOne[RowOne].push_back(8);
dataOne[RowOne].push_back(7);
dataOne[RowOne].push_back(5);
dataOne[RowTwo].push_back(0);
dataOne[RowTwo].push_back(2);
dataOne[RowTwo].push_back(4);
dataOne[RowThree].push_back(6);
dataOne[RowThree].push_back(4);
dataOne[RowThree].push_back(2);

std::vector<std::vector<double>> dataTwo;
dataTwo.resize(numberRows);

dataTwo[RowOne].push_back(1);
dataTwo[RowOne].push_back(2);
dataTwo[RowOne].push_back(3);
dataTwo[RowTwo].push_back(4);
dataTwo[RowTwo].push_back(5);
dataTwo[RowTwo].push_back(4);
dataTwo[RowThree].push_back(1);
dataTwo[RowThree].push_back(2);
dataTwo[RowThree].push_back(3);

Matrix one(dataOne);
Matrix two(dataTwo);

one.add(two);
```

The sample code above will result in the matrix addition as pictured below.

<br>

![add](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-2/add.png?raw=true)

<br>

* **Status subtract(const Matrix& other)**: Function that takes as an argument a matrix `other` and subtracts it, element-wise, from the calling object. It returns a value of type `Status` (defined previously). It should return `NoError` if the subtraction was carried out successfully or `DimensionError` if the matrices' dimensions do not match.

```c++
enum { RowOne, RowTwo, RowThree };
const int numberRows = 3;

std::vector<std::vector<double>> dataOne;
dataOne.resize(numberRows);

dataOne[RowOne].push_back(8);
dataOne[RowOne].push_back(7);
dataOne[RowOne].push_back(5);
dataOne[RowTwo].push_back(4);
dataOne[RowTwo].push_back(5);
dataOne[RowTwo].push_back(4);
dataOne[RowThree].push_back(6);
dataOne[RowThree].push_back(4);
dataOne[RowThree].push_back(2);

std::vector<std::vector<double>> dataTwo;
dataTwo.resize(numberRows);

dataTwo[RowOne].push_back(1);
dataTwo[RowOne].push_back(2);
dataTwo[RowOne].push_back(3);
dataTwo[RowTwo].push_back(4);
dataTwo[RowTwo].push_back(5);
dataTwo[RowTwo].push_back(4);
dataTwo[RowThree].push_back(1);
dataTwo[RowThree].push_back(2);
dataTwo[RowThree].push_back(1);

Matrix one(dataOne);
Matrix two(dataTwo);

one.subtract(two);
```

The sample code above will result in the matrix subtraction as pictured below.

<br>

![subtract](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-2/subtract.png?raw=true)

<br>

* **Status multiply(const Matrix& other)**: Function that takes as an argument a matrix `other` and performs a matrix product with the calling object. It must update the `matrix` data member to reflect the new dimension of the resulting matrix. The function returns a value of type `Status` (defined previously). It should return `NoError` if the matrix product was carried out successfully or `DimensionError` if the product for those two matrices is undefined.

```c++
enum { RowOne, RowTwo, RowThree };
const int rowsOne = 2;
const int rowsTwo = 3;

std::vector<std::vector<double>> dataOne;
dataOne.resize(rowsOne);

dataOne[RowOne].push_back(1);
dataOne[RowOne].push_back(2);
dataOne[RowOne].push_back(1);
dataOne[RowTwo].push_back(2);
dataOne[RowTwo].push_back(1);
dataOne[RowTwo].push_back(2);

std::vector<std::vector<double>> dataTwo;
dataTwo.resize(rowsTwo);

dataTwo[RowOne].push_back(1);
dataTwo[RowOne].push_back(2);
dataTwo[RowTwo].push_back(2);
dataTwo[RowTwo].push_back(1);
dataTwo[RowThree].push_back(1);
dataTwo[RowThree].push_back(2);

Matrix one(dataOne);
Matrix two(dataTwo);

one.multiply(two);
```

The sample code above will result in the matrix multiplication as pictured below.

<br>

![multiply](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-2/multiply.png?raw=true)

<br>

* **Status divide(double scalar)**: Function that takes as an argument a value of type `double` and performs an element-wise division on the calling object. The function returns a value of type `Status`. It should return `NoError` if the division was carried out successfully or `DivideByZeroError` if a division by zero was attempted.

```c++
enum { RowOne, RowTwo, RowThree };
const int numberRows = 3;

std::vector<std::vector<double>> dataOne;
dataOne.resize(numberRows);

dataOne[RowOne].push_back(8);
dataOne[RowOne].push_back(6);
dataOne[RowOne].push_back(4);
dataOne[RowTwo].push_back(2);
dataOne[RowTwo].push_back(2);
dataOne[RowTwo].push_back(2);
dataOne[RowThree].push_back(4);
dataOne[RowThree].push_back(6);
dataOne[RowThree].push_back(8);

Matrix one(dataOne);

one.divide(2.0);
```

The sample code above will result in the matrix division as pictured below.

<br>

![divide](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-2/divide.png?raw=true)

<br>

* **void multiply(double scalar)**: Function that takes as an argument a value of type `double` and performs an element-wise multiplication on the calling object.

```c++
enum { RowOne, RowTwo, RowThree };
const int numberRows = 3;

std::vector<std::vector<double>> dataOne;
dataOne.resize(numberRows);

dataOne[RowOne].push_back(1);
dataOne[RowOne].push_back(2);
dataOne[RowOne].push_back(3);
dataOne[RowTwo].push_back(4);
dataOne[RowTwo].push_back(3);
dataOne[RowTwo].push_back(2);
dataOne[RowThree].push_back(1);
dataOne[RowThree].push_back(0);
dataOne[RowThree].push_back(1);

Matrix one(dataOne);

one.multiply(2.0);
```

The sample code above will result in the matrix multiplication as pictured below.

<br>

![divide](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-2/multiplyScalar.png?raw=true)

<br>

* **void transpose()**: The transpose of a matrix is a new matrix whose rows are the columns of the original. This function updates the `matrix` data member with its transpose.

```c++
enum { RowOne, RowTwo };
const int rowsOne = 3;

std::vector<std::vector<double>> dataOne;
dataOne.resize(rowsOne);

dataOne[RowOne].push_back(1);
dataOne[RowOne].push_back(2);
dataOne[RowOne].push_back(1);
dataOne[RowTwo].push_back(2);
dataOne[RowTwo].push_back(1);
dataOne[RowTwo].push_back(2);

Matrix one(dataOne);
one.transpose();
```

The sample code above will result in the transpose of the calling object as pictured below.

<br>

![transpose](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-2/Transpose.png?raw=true)

<br>

* **void zero()**: This function updates the all of the `matrix` data member elements to zero.

```c++
enum { RowOne, RowTwo };
const int rowsOne = 3;

std::vector<std::vector<double>> dataOne;
dataOne.resize(rowsOne);

dataOne[RowOne].push_back(1);
dataOne[RowOne].push_back(2);
dataOne[RowOne].push_back(1);
dataOne[RowTwo].push_back(2);
dataOne[RowTwo].push_back(1);
dataOne[RowTwo].push_back(2);

Matrix one(dataOne);
one.zero();
```

The sample code above will result in the calling object being filled with zeroes.

<br>

![zero](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-2/Zero.png?raw=true)

<br>

* **void show() const**: This function prints the representation of the calling object to the console. The output must be formatted to be aligned.

```c++
sampleMatrix.show();
```

The sample code above will result in displaying a matrix similar to the one shown below.
```
30  24  18
84  69  54
13  14  90
```

* **double getDeterminant()**: This function returns the determinant of the calling object. This recursive function should consider the base and recursive cases explained above to calculate the result. If the calling object is not a square matrix, you must return `NaN` (stands for **not a number**), otherwise return the appropriate result.


* **double getAt(int row, int column) const**: This function returns the element located at the specified row and column within the `matrix` data member. There is no need for bounds checking, although by doing so you may avoid segmentation faults and Index-Out-Of-Bounds errors.

```c++
double number = sampleMatrix.getAt(1,1);
```

The sample code above will result in `number` holding the value 3. You can see this in the picture below.

<br>

![zero](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-2/getAt.png?raw=true)

<br>

* **int getRowSize() const**: This function returns the number of rows in the `matrix` data member. This information is provided by `rowSize`. It basically serves as a get method for the `rowSize` **private** data member.

```c++
int numberOfRows = sampleMatrix.getRowSize();
```

* **int getColSize() const**: This function returns the number of columns in the `matrix` data member. This information is provided by `colSize`. It basically serves as a get method for the `colSize` **private** data member.

```c++
int numberOfCols = sampleMatrix.getColSize();
```

* **bool isSquare() const**: This function returns `true` if the calling object is a square matrix. It returns `false` otherwise.

```c++
bool square = sampleMatrix.isSquare();
```

* **bool hasSameDimensionAs(const Matrix& other)**: This function takes as an argument a matrix `other`. If the calling object and the `other` matrix have the same dimensions it should return `true`. Otherwise, it must return `false`.

```c++
bool sameDim = sampleMatrix.hasSameDimensionAs(otherMatrix);
```

* **Matrix getMinor(int row, int column)**: This function returns a new matrix (submatrix) formed by deleting the specified row and column from the original matrix.

```c++
sampleMatrix.getMinor(0,0);
```

The sample code above will result in generating a submatrix based on the calling object. You can see this in the picture below.

<br>

![zero](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-2/minor.png?raw=true)

<br>

**The following function belongs to the `HelpingFunctions` class.**
* **double dotProduct(const std::vector\<double\>& x, const std::vector\<double\>& y)**: This is a static method that performs the a dot product between two given vectors. If the vectors are not the same size return `NaN`, otherwise return the appropriate result.

```c++
double dot = HelpingFunctions::dotProduct(vector1, vector2);
```

#### Self-Grading and Feedback
Once you have implemented all of the functions your goal is to pass all the tests and obtain this output:

```
All tests passed (182 assertions in 24 test cases)
```

This is provided for you to get feedback on your code. You can attempt to fix it and prepare it for submission once it passes all the tests. Once submitted, a set of similar tests will be run on your solution.

#### Submission
You are expected to submit your zip file in Canvas by the specified deadline. The zip file name must match your Tracks ID. For instance, if your Tracks ID is *aLastname2016* then your zip file should be called **aLastname2016.zip**. Resubmissions are allowed. Canvas will slightly alter the file name to indicate a resubmission with the same file name. This is expected and the grading software will obtain your latest submission as long as you keep submitting files named *aLastname2016.zip*. The zip file should only contain the `Matrix.hpp` and `Matrix.cpp` files.
