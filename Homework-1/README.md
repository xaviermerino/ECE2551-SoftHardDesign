## Assignment #1: Maze Solver

### Overview
The overall goal of this assignment is to implement a C++ application that makes use of recursion and bitwise operators.

The functional goal is to traverse a given maze and find a solution. A maze is a 16 x 16 grid. You can keep track of your position in the maze with X and Y coordinates. In the example below (see image on the left) the maze walls are represented with gray squares. The empty spaces or paths are represented by white squares. Once solved (see image on the right), the green squares represent the path taken to solve the maze. Some mazes might not have a solution.

![graphic](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-1/graphicRepresentation.png?raw=true)

You are tasked with creating an algorithm that will solve a binary maze. Take the example above and replace the white squares with zeroes and the gray squares with ones. Your goal is to find a path that will lead you to the exit (which is always located at the bottom right square). The algorithm can traverse through the maze and it can only move to positions where the bit’s value is zero. It can’t move out of the bounds of the maze and it should not be able to move to positions that it already visited.

### Functional Requirements
* Each maze row is represented with a variable of type `short`. These variables are 2 byte long and so can hold **16 bits**.
* Create a **recursive** function `move` that can traverse the maze. The function should keep track of its current position using X and Y coordinates. From the example above, **Y indicates which row and X indicates a specific bit on the row**. For instance X = 2 and Y = 0 is the location of a gray square in the example above.
* The **base cases** for the recursive function `move` are:
  * A dead end has been reached and thus no valid movement options are left.
  * The maze has been completed and the X and Y coordinates match the coordinates of the bottom right square in the maze (see the example above).
* The **recursive cases** for the recursive function `move` are:
  * Move right
  * Move down
  * Move left
  * Move up
* The program **must** attempt to move right, then down, then left, and finally up. In other words, the **priority** of movements is: right, down, left, and up.
* **Diagonal** movements are not allowed.
* Movement is only allowed to positions where the bit's value is zero.
* There can't be any movement outside the **bounds** of the maze.
* The program must not move to positions that it has previously moved to. This is to avoid loops.

### Getting Started

1. **[Download](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-1/starter.zip?raw=true)** the starter file set. It will contain the following files:
  * `catch.hpp`
  * `main.cpp`
  * `solver.h`
2. Use your favorite IDE or editor to modify your files. At first, **the program won't compile**. Follow steps 3 - 7 to below to get it to compile.
3. In `solver.h`, create an **array** of type `short` that holds 16 elements. This array will be named `mazeRows` and each entry will contain a row of the maze itself. Initialize it to zero.
4. In `solver.h`, create an **array** of type `short` that holds 16 elements. This array will be named `pathRows` and as your program finds the solution it will modify it to reflect the path taken to solve the maze. Initialize it to zero.
5. In `solver.h`, create an `enum` and name it `BitType` it should hold the following two values:
  * Maze
  * Path
6. **Uncomment** the implementation of the following methods:
  * `void inputTestData(short data[])`
  * `short getBit(BitType type, int x, int y)`
  * `void setPathBit(int x, int y)`
  * `void clearPath()`
  * `bool move(int x, int y)`
  * `void showMaze()`
7. The **program will now compile**. If you try running the program it will tell you that it has **failed all the tests**. Your goal is to make the program pass all the tests by completing the implementation of the methods given to you. You can implement helper functions if needed. See the following section for more information.

### Technical Requirements
This section will serve as a guideline of what is necessary for the program to pass all the tests. We perform unit testing using the **Catch** framework. Catch is a **header-only** framework which means you just need to drop the header file containing the framework into your project. This is the reason behind the `catch.hpp` file.

You can also see that some code is provided in the `main.cpp` file. This code tests the code that you placed in the `solver.h` file. If your code passes all the tests it is ready for submission and will, most likely **(cheating is heavily penalized)**, receive full credit.

The only thing that you need to do is to modify the `solver.h` file to get the provided functions working. Don't change the function signature as the testing program relies on this to grade your submission. When you first run your program (and no modifications to the functions have been made) you will see something like this:

```
test cases:  4 | 4 failed
assertions: 12 | 8 passed | 4 failed
```

Let's start explaining what each of the functions in the `solver.h` file must do.

* **void inputTestData(short data[])**: This function takes an array of test data and copies all of its elements to the `mazeRows` array. For instance, the test program has some test data (see below) and your `inputTestData` function should copy that array, element-by-element, to the `mazeRows` array.

```c++
short test[16] = {8704, static_cast<short>(43967), static_cast<short>(43904), static_cast<short>(35774), static_cast<short>(54184), 21419, 24456, 18366, 30114, static_cast<short>(55208), 30639, 1967, 32303, 16543, 5824, static_cast<short>(62206)};
```

Once copied, the `mazeRows` should look (when looking at the binary) with zeros and one like the example below (note that this is only an example and not what will exactly happen if you load the test data above!).

```
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 1
0 1 0 0 0 0 0 0 0 0 0 1 0 1 0 1
1 1 1 0 0 0 0 0 0 0 0 1 0 1 0 1
0 1 1 1 0 0 0 0 0 0 1 1 1 1 1 0
1 0 1 1 0 0 0 0 0 0 1 1 1 0 1 0
0 1 1 1 0 1 0 0 1 0 1 1 1 0 1 1
1 0 1 1 0 1 1 0 1 0 1 1 1 0 1 1
0 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0
1 0 1 1 0 1 1 1 1 0 1 0 1 0 1 0
0 1 1 1 0 1 1 1 1 1 0 0 1 0 1 0
1 0 1 1 0 1 0 0 0 0 1 0 1 0 1 0
0 1 1 1 1 1 0 0 0 0 1 1 0 1 1 0
1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 0
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 0
```

* **short getBit(BitType type, int x, int y)**: This function requires you to supply it with the X and Y coordinate of the bit you would like to obtain. You need to specify if you want the bit to be extracted from the `mazeRows` or `pathRows` array by passing `Maze` or `Path` as the first argument. This function makes use of bitwise operators to extract the desired bit. Remember that Y indicates the row and X the desired bit in that row. For instance, the second row, third bit of the `mazeRows` would be obtained by:

```c++
short aBit = getBit(Maze, 2, 1);
```

* **void setPathBit(int x, int y)**: This function requires you to supply it with the X and Y coordinate of the bit you would like to set. This function will set a bit in the specified row of the `pathRows` array. This function makes use of bitwise operators to set the desired bit. Remember that Y indicates the row and X the desired bit in that row. For instance, the second row, third bit of the `pathRows` would be set by:

```c++
setPathBit(2, 1);
```

By the end of your program, if the maze was solved then the `pathRows` array should look like this (where the ones mark the path taken):

```
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 1 1 1 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
```

* **void clearPath()**: This function sets all of the rows in `pathRows` to zero. It clears the path taken by the program to solve the maze.

* **bool move(int x, int y)**: This is the recursive function in the program. It requires you to supply it with a starting X and Y coordinate. After checking each movement option and no more moves are available, the function should return `false`. The function returning `false` is the equivalent of moving back one step. This movement back will allow for the program to move through alternative paths. If the program steps back all the way to the beginning and does not find a path to the end, then the maze is not solvable. If the function returns `true` then the maze is solvable. This function should respect the movement priority. The testing program will always start at coordinates X = 0 and Y = 0. Visit the [Functional Requirements](#functional-requirements)  section for more information on this function.

* **void showMaze()**: This function must print the bit representation of the maze. If invoked before solving the maze then it should print just zeroes and ones representing the maze. If invoked after solving the maze, then it should print the maze (this is the zeroes and ones) and asterisks for the path taken. This is the **only function allowed to print to the console**. This is an example of the output for a solved maze (note that appropriate spacing is necessary to appreciate the solution!):

```
* 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
* * * * * 0 0 0 0 0 0 1 0 1 0 1
0 1 0 0 * 0 0 0 0 0 0 1 0 1 0 1
1 1 1 0 * 0 0 0 0 0 0 1 0 1 0 1
0 1 1 1 * 0 0 0 0 0 1 1 1 1 1 0
1 0 1 1 * * * * 0 0 1 1 1 0 1 0
0 1 1 1 0 1 0 * 1 0 1 1 1 0 1 1
1 0 1 1 0 1 1 * 1 0 1 1 1 0 1 1
0 1 1 1 0 0 0 * * * * * * * * *
1 0 1 1 0 1 1 1 1 0 1 0 1 0 1 *
0 1 1 1 0 1 1 1 1 1 0 0 1 0 1 *
1 0 1 1 0 1 0 0 0 0 1 0 1 0 1 *
0 1 1 1 1 1 0 0 0 0 1 1 0 1 1 *
1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 *
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 *
1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 *
```

You can add extra functions to help you complete the assignment but the testing program will assume that you are following what has been defined here. You can read the tests in the `main.cpp` file and dig deeper on what the testing program demands of you. Notice that the use of `std::bitset` is reserved for the testing program. **You must not modify any of the tests.**

### Self-Grading and Feedback
Once you have implemented all of the functions your goal is to pass all the tests and obtain this output:

```
All tests passed (1740 assertions in 4 test cases)
```

This is provided for you to get feedback on your code. You can attempt to fix it and prepare it for submission once it passes all the tests. Once submitted, a set of similar tests will be run on your solution.

### Submission
You are expected to submit your a zip file in Canvas by the specified deadline. The zip file name must match your Tracks ID. For instance, if your Tracks ID is *aLastname2016* then your zip file should be called **aLastname2016.zip**. The zip file should only contain the `solver.h` file. 
