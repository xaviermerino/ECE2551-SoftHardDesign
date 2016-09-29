## Assignment #3: Pointer Arithmetic and Sorting

#### Overview
The overall goal of this assignment is to implement a C++ application that makes use of pointers to access data contained in arrays. Throughout this assignment you will refresh your knowledge of control structures, functions, one and two dimensional arrays, and pointer arithmetic. As a bonus, you will be implementing the insertion sort to sort the data in the given array.

The functional goal is to sort the 2D array given to you. You will use **insertion sort** to perform sorting column or row wise.

<br>
![overview](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-3/overview.png?raw=true)

<br>
In the end, your goal is to sort the array and use pointers to traverse through the given data.

#### Functional Requirements
The following requirements are an overview of what is expected of you in this assignment. More details on how to implement the solution can be found in the Technical Requirements section.

* Each given data set will have five rows and five columns. The given data set will be a 2D array of type `char`.
* Pointers should be used to retrieve data from the arrays.
* You must be able to sort rows and columns of the given data set using insertion sort.
* Insertion sort can be applied row-wise or column-wise.
* Insertion sort is a simple sorting algorithm with **time complexity O(n^2)**. It is efficient with small data sets and as such it is a good match for our assignment. It also sorts **in-place** which means it only requires **O(1) of additional memory space**.

<br>
The following snippet is **pseudocode** for the insertion sort algorithm:

```
for i ← 1 to length(A)-1
    j ← i
    while j > 0 and A[j-1] > A[j]
        swap A[j] and A[j-1]
        j ← j - 1
    end while
end for
```
<br>
Which behaves as presented below:

![insertionSortGIF](https://upload.wikimedia.org/wikipedia/commons/0/0f/Insertion-sort-example-300px.gif)

For more information on insertion sort check this [video](https://www.youtube.com/watch?v=DFG-XuyPYUQ).

#### Getting Started

1. **[Download](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-3/Starter.zip?raw=true)** the starter file set. It will contain the following files:
  * `catch.hpp`
  * `functions.h`
  * `main.cpp`

2. The provided `main.cpp` file is the test file. You are free to test your own program using your own `main.cpp` file but bear in mind that you will be tested against the provided one.

3. The provided `functions.h` file contains all of the function prototypes of the functions that are going to be tested. You are free to add any others as you wish. Your main task is to write the C++ implementation code for each of these functions.

4. Use your favorite IDE or editor to modify your files. At first, **the program won't compile** because the functions' implementation are missing.

5. In `functions.h`, write an empty implementation for each of the functions specified.

7. The **program will now compile**. If you try running the program it will tell you that it has **failed all the tests**. Your goal is to make the program pass all the tests by completing the implementation of the methods given to you. You can implement helper functions if needed. See the following section for more information.

#### Technical Requirements
This section will serve as a guideline of what is necessary for the program to pass all the tests. We perform unit testing using the **Catch** framework. Catch is a **header-only** framework which means you just need to drop the header file containing the framework into your project. This is the reason behind the `catch.hpp` file.

You can also see that some code is provided in the `main.cpp` file. This code tests the functions in your `functions.h` file. If your code passes all the tests it is ready for submission and will, most likely **(cheating is heavily penalized)**, receive full credit.

The only thing that you need to do is to modify the `functions.h` files to get the provided functions working. Don't change the function signature as the testing program relies on this to grade your submission.

Let's start explaining what each of the functions must do.

* **char getCharacter(char array[][arraySize], int row, int column)**: This function takes as an argument a 2D array. The size of the array is fixed by `arraySize`. It also takes a `row` and a `column` that allows you to tap into that specific location in the provided `array`. You must use pointers to get the character. **You MUST use pointer notation.**

```c++
const unsigned int rows = 4;
const unsigned int columns = 4;

char first[rows][columns] = {
    {'z', 'c', 'a', 'f'},
    {'a', 'q', 'w', 'e'},
    {'y', 'a', 'b', 'z'},
    {'n', 'e', 'i', 'o'}
};

// Looks at position (0,0) for 'z'
getCharacter(first, 0, 0);  
```

<br>
The code snippet performs the following:

<br>
![getcharacter](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-3/getCharacter.png?raw=true)

<br>
* **char* getCharacterAddress(char array[][arraySize], int row, int column)**: This function takes as an argument a 2D array. The size of the array is fixed by `arraySize`. It also takes a `row` and a `column` that allows you to tap into that specific location in the provided `array`. You must return a character pointer that points to the address of the character. **You MUST use pointer notation.**

```c++
const unsigned int rows = 4;
const unsigned int columns = 4;

char first[rows][columns] = {
    {'z', 'c', 'a', 'f'},
    {'a', 'q', 'w', 'e'},
    {'y', 'a', 'b', 'z'},
    {'n', 'e', 'i', 'o'}
};

// Looks at the address of the character in position (0,1).
// address should be something like 0x7fff5fbfe281
void* address = getCharacterAddress(first, 0, 1);

// We are using void* to be able to print the address.
// Printing a char* will print the string instead.
```

<br>
The code snippet performs the following:

<br>
![getcharacteraddress](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-3/getCharacterAddress.png?raw=true)

<br>
* **void getRow(char array[][arraySize], int row, char* resultArray)**: This function takes as an argument a 2D array. The size of the array is fixed by `arraySize`. It also takes a `row` parameter that allows you to tap into that specific row in the provided `array`. One of the nice things about pointers is that they allow functions to alter variables outside of their scope. To do this, you pass a pointer and so you allow that function to read and write to the data. This function takes a third argument, `char* resultArray`, so you can modify `resultArray` from the function itself. Use `resultArray` to hold the values in the extracted row. **You MUST use pointer notation.**

```c++
const unsigned int rows = 4;
const unsigned int columns = 4;

char first[rows][columns] = {
    {'z', 'c', 'a', 'f'},
    {'a', 'q', 'w', 'e'},
    {'y', 'a', 'b', 'z'},
    {'n', 'e', 'i', 'o'}
};

const unsigned int size = 5;
const unsigned int rowNumber = 3;
char row[size];

getRow(first, rowNumber, row);
```

<br>
The code snippet performs the following:

<br>
![getRow](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-3/getRow.png?raw=true)

<br>
* **void getColumn(char array[][arraySize], int column, char* resultArray)**: This function takes as an argument a 2D array. The size of the array is fixed by `arraySize`. It also takes a `row` parameter that allows you to tap into that specific row in the provided `array`. This function takes a third argument, `char* resultArray`, so you can modify `resultArray` from the function itself. Use `resultArray` to hold the values in the extracted column. **You MUST use pointer notation.**

```c++
const unsigned int rows = 4;
const unsigned int columns = 4;

char first[rows][columns] = {
    {'z', 'c', 'a', 'f'},
    {'a', 'q', 'w', 'e'},
    {'y', 'a', 'b', 'z'},
    {'n', 'e', 'i', 'o'}
};

const unsigned int size = 5;
const unsigned int columnNumber = 3;
char column[size];

getColumn(first, columnNumber, column);
```

<br>
The code snippet performs the following:

<br>
![getRow](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-3/getColumn.png?raw=true)

<br>
* **void insertionSort(char data[], int size)**: This function takes as an argument an array of type `char`. It also takes as an argument the `size` or length of the array. This function implements **insertion sort** which is a simple (quadratic) sorting algorithm. It is not the most efficient when it comes to performance but is efficient enough for small data sets. This function should perform in-place sorting. **It is acceptable not to use pointer notation here.**

```c++
char test[4] = {'z', 'c', 'a', 'f'};
insertionSort(test, 4);
```

<br>
The code snippet performs the following:

<br>
![insertionSort](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-3/insertionSort.png?raw=true)

<br>
* **void sortRow(char array[][arraySize], int row)**: This function takes as an argument a 2D array. It also takes a `row` as an argument that specifies which row should be sorted. The sorting algorithm should be insertion sort. **It is acceptable not to use pointer notation here.**

```c++
const unsigned int rows = 4;
const unsigned int columns = 4;

char first[rows][columns] = {
    {'z', 'c', 'a', 'f'},
    {'a', 'q', 'w', 'e'},
    {'y', 'a', 'b', 'z'},
    {'n', 'e', 'i', 'o'}
};

sortRow(first, 0);
```

<br>
The code snippet performs the following:

<br>
![sortRow](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-3/sortRow.png?raw=true)

<br>
* **void sortColumn(char array[][arraySize], int column)**: This function takes as an argument a 2D array. It also takes a `column` as an argument that specifies which column should be sorted. The sorting algorithm should be insertion sort. **It is acceptable not to use pointer notation here.**

```c++
const unsigned int rows = 4;
const unsigned int columns = 4;

char first[rows][columns] = {
    {'z', 'c', 'a', 'f'},
    {'a', 'q', 'w', 'e'},
    {'y', 'a', 'b', 'z'},
    {'n', 'e', 'i', 'o'}
};

sortColumn(first, 0);
```

<br>
The code snippet performs the following:

<br>
![sortColumn](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-3/sortColumn.png?raw=true)

<br>
#### Self-Grading and Feedback
Once you have implemented all of the functions your goal is to pass all the tests and obtain this output:

```
All tests passed (206 assertions in 18 test cases)
```

This is provided for you to get feedback on your code. You can attempt to fix it and prepare it for submission once it passes all the tests. Once submitted, a set of similar tests will be run on your solution. **Please notice that points will be deducted even if you pass all the tests but did not use pointer notation for the functions that required it.**

#### Submission
You are expected to submit your zip file in Canvas by the specified deadline. The zip file name must match your Tracks ID. For instance, if your Tracks ID is *aLastname2016* then your zip file should be called **aLastname2016.zip**. Resubmissions are allowed. Canvas will slightly alter the file name to indicate a resubmission with the same file name. This is expected and the grading software will obtain your latest submission as long as you keep submitting files named *aLastname2016.zip*. The zip file should only contain the `functions.h` file.
