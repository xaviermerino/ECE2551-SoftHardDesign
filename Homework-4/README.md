## Assignment #4: Netflix

#### Overview
The overall goal of this assignment is to implement a C++ application that mimics some of Netflix's functionality. This application will store movies and keep track of the year they were released, their rating and their ranking. In this assignment you will refresh your knowledge of control structures, functions, pointers, sorting, dynamic memory management, operator overloading, and exceptions. Additionally, you will be implementing your own **DoublyLinkedList** which will be a subset of the **C++ STL list**. After completion you should feel more comfortable with allocating memory on the heap to create more complex data structures. Specifically, you will learn how to link different objects in the heap together and to bi-directionally traverse through these objects in memory.

<br>
![overview](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-4/list.png?raw=true)

<br>
In the end, you will be storing movie information in this list and sorting it.

#### Functional Requirements
The following requirements are an overview of what is expected of you in this assignment. More details on how to implement the solution can be found in the Technical Requirements section.

* Each movie holds information about its name, year, their rating, and their ranking. The year must be between 1900 and 2100. The ranking can only be a number between 1 and 5. The rating can only be one of these:
  * G
  * PG
  * PG-13
  * R
  * NC-17

* The **DoublyLinkedList** holds these movies in a list-like fashion.
* The **DoublyLinkedList** is a template class. This means it will make a list out of any data type specified. For more information on templates [see this link](https://www.tutorialspoint.com/cplusplus/cpp_templates.htm). The program will test the class using integers and objects of type `Movie`.

* You must be able to sort the elements in the list using **Insertion Sort**.

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

1. **[Download](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-4/starter.zip?raw=true)** the starter file set. It will contain the following files:
  * `catch.hpp`
  * `DoublyLinkedList.hpp`
  * `Movie.hpp`
  * `main.cpp`

2. The provided `main.cpp` file is the test file. You are free to test your own program using your own `main.cpp` file but bear in mind that you will be tested against the provided one.

3. The provided `DoublyLinkedList.hpp` and `Movie.hpp` files contain all of the function prototypes of the functions that are going to be tested. You are free to add any others as you wish. Your main task is to write the C++ implementation code for each of these functions.

4. Use your favorite IDE or editor to modify your files. At first, **the program won't compile** because the functions' implementation are missing.

5. In `DoublyLinkedList.hpp`, write an empty implementation for each of the functions specified.

6. Create a `Movie.cpp` file and write an empty implementation for each of the functions specified.

7. The **program will now compile**. If you try running the program it will tell you that it has **failed all the tests**. Your goal is to make the program pass all the tests by completing the implementation of the methods given to you. You can implement helper functions if needed. See the following section for more information.

#### Technical Requirements
This section will serve as a guideline of what is necessary for the program to pass all the tests. We perform unit testing using the **Catch** framework. Catch is a **header-only** framework which means you just need to drop the header file containing the framework into your project. This is the reason behind the `catch.hpp` file.

You can also see that some code is provided in the `main.cpp` file. This code tests the functions in your program. If your code passes all the tests it is ready for submission and will, most likely **(cheating is heavily penalized)**, receive full credit.

Don't change the function signatures as the testing program relies on this to grade your submission.

**Let's start explaining what each of the functions in the `Movie` class must do:**

* **Movie(std::string name, unsigned short year, std::string rating, unsigned short ranking)**: This constructor creates an object of type `Movie` with a name, a year, a rating, and a ranking. Invalid years, ratings, and rankings must throw an exception of type `std::invalid_argument`.

```c++
Movie movie1("A", 2010, "PG", 1);
Movie movie2("B", 2011, "PG-13", 5);
Movie movie3("C", 2012, "PG", 4);
```

* **std::string getName()**: This function returns the name of the movie stored in an object of type `Movie`.

```c++
Movie movie1("A", 2010, "PG", 1);
movie1.getName();
```

* **std::string getRating()**: This function returns the rating of the movie stored in an object of type `Movie`.

```c++
Movie movie1("A", 2010, "PG", 1);
movie1.getRating();
```

* **unsigned short getYear()**: This function returns the year of the movie stored in an object of type `Movie`.

```c++
Movie movie1("A", 2010, "PG", 1);
movie1.getYear();
```

* **unsigned short getRanking()**: This function returns the ranking of the movie stored in an object of type `Movie`.

```c++
Movie movie1("A", 2010, "PG", 1);
movie1.getRanking();
```

* **Movie& setName(std::string name)**: This function takes as an argument a string that represents a movie name. It sets the name of a movie to the argument provided. Supports method chaining.

```c++
Movie movie1("A", 2010, "PG", 1);
movie1.setName("A2").setYear(2011).setRating("PG").setRanking(2);
```

* **Movie& setYear(unsigned short year)**: This function takes as an argument a year that represents a movie's release year. It sets the year of a `Movie` to the argument provided. It raises an exception of type `std::invalid_argument` if the year is outside the specified range (1900 - 2100). Supports method chaining.

```c++
Movie movie1("A", 2010, "PG", 1);
movie1.setName("A2").setYear(2011).setRating("PG").setRanking(2);
```

* **Movie& setRating(std::string rating)**: This function takes as an argument a rating that represents a movie's rating. It sets the rating of a `Movie` to the argument provided. It raises an exception of type `std::invalid_argument` if the rating is not one of the following options:  G, PG, PG-13, R, and NC-17. Supports method chaining.

```c++
Movie movie1("A", 2010, "PG", 1);
movie1.setName("A2").setYear(2011).setRating("PG").setRanking(2);
```

* **Movie& setRanking(unsigned short ranking)**: This function takes as an argument a ranking that represents a movie's ranking. It sets the ranking of a `Movie` to the argument provided. It raises an exception of type `std::invalid_argument` if the ranking is outside the range 1-5 (endpoints included). Supports method chaining.

```c++
Movie movie1("A", 2010, "PG", 1);
movie1.setName("A2").setYear(2011).setRating("PG").setRanking(2);
```

* **bool operator== (Movie& rhs)**: This function overloads the `==` operator. It allows comparison of two `Movie` objects. Two `Movie` objects are only equal if their name and year are the same.

```c++
Movie movie1("A", 2010, "PG", 1);
Movie movie2("B", 2011, "PG-13", 5);
Movie movie3("C", 2012, "PG", 4);

bool result = (movie1 == movie2);
```

* **bool operator< (Movie& rhs)**: This function overloads the `<` operator. It allows comparison of two `Movie` objects. A `Movie` is lesser than another if its ranking is less.

```c++
Movie movie1("A", 2010, "PG", 1);
Movie movie2("B", 2011, "PG-13", 5);
Movie movie3("C", 2012, "PG", 4);

bool result = (movie1 < movie2);
```

* **bool operator<= (Movie& rhs)**: This function overloads the `<=` operator. It allows comparison of two `Movie` objects. A `Movie` is lesser or equal than another if its ranking is less or equal.

```c++
Movie movie1("A", 2010, "PG", 1);
Movie movie2("B", 2011, "PG-13", 5);
Movie movie3("C", 2012, "PG", 4);

bool result = (movie1 <= movie2);
```

* **bool operator> (Movie& rhs)**: This function overloads the `>` operator. It allows comparison of two `Movie` objects. A `Movie` is greater than another if its ranking is greater.

```c++
Movie movie1("A", 2010, "PG", 1);
Movie movie2("B", 2011, "PG-13", 5);
Movie movie3("C", 2012, "PG", 4);

bool result = (movie1 > movie2);
```

* **bool operator>= (Movie& rhs)**: This function overloads the `>=` operator. It allows comparison of two `Movie` objects. A `Movie` is greater or equal than another if its ranking is greater or equal.

```c++
Movie movie1("A", 2010, "PG", 1);
Movie movie2("B", 2011, "PG-13", 5);
Movie movie3("C", 2012, "PG", 4);

bool result = (movie1 >= movie2);
```

**Let's start explaining what each of the functions in the `DoublyLinkedList` class must do:**

* **DoublyLinkedList()**: This constructor creates an object of type `DoublyLinkedList` of size 0. The `header` and `trailer` are sentinels that point to the first and last element (respectively) of the `DoublyLinkedList`.

```c++
DoublyLinkedList<Movie> list;
```

* **unsigned int size()**: This function returns the size of `DoublyLinkedList`. The size is the number of nodes that exist.

```c++
list.size();
```

* **bool isEmpty()**: This function returns true if the size of the list is zero. Otherwise it returns false.

```c++
list.isEmpty();
```

* **void insert(Type& e)**: This function appends an element of type `Type` to the end of the `DoublyLinkedList`. It updates the `header` and `trailer` sentinels.

The list originally looks like:

<br>

![before](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-4/list-before.png?raw=true)

<br>

Now we are inserting node D.

<br>

![insert](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-4/list-insert.png?raw=true)

<br>

```c++
Movie movie1("A", 2010, "PG", 1);
Movie movie2("B", 2011, "PG-13", 5);
Movie movie3("C", 2012, "PG", 4);
Movie movie4("D", 2013, "R", 3);

DoublyLinkedList<Movie> list;

list.insert(movie1);
list.insert(movie2);
list.insert(movie3);
list.insert(movie4);
```

* **unsigned int find(Type& e)**: This function returns an index equivalent to the position of the object `e` in the list. If the object `e` is not found then it throws an exception `std::exception`.

```c++
Movie movie1("A", 2010, "PG", 1);
Movie movie2("B", 2011, "PG-13", 5);
Movie movie3("C", 2012, "PG", 4);
Movie movie4("D", 2013, "R", 3);

DoublyLinkedList<Movie> list;

list.insert(movie1);
list.insert(movie2);
list.insert(movie3);
list.insert(movie4);

list.find(movie1);
```

* **void erase(unsigned int index)**: This function deletes an object from the list using its associated index. If the list is empty or the index is out of the range of the list the function will just return. It updates the `header` and `trailer` sentinels.

The list originally looks like this:

<br>

![insert](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-4/list-insert.png?raw=true)

<br>

We will now delete node C.

<br>

![erase](https://github.com/xaviermerino/ECE2551-SoftHardDesign/blob/master/Homework-4/list-erase.png?raw=true)

<br>

```c++
Movie movie1("A", 2010, "PG", 1);
Movie movie2("B", 2011, "PG-13", 5);
Movie movie3("C", 2012, "PG", 4);
Movie movie4("D", 2013, "R", 3);

DoublyLinkedList<Movie> list;

list.insert(movie1);
list.insert(movie2);
list.insert(movie3);
list.insert(movie4);

list.erase(0);
```

* **void sort()**: This function sorts the data in the `DoublyLinkedList` in ascending order using insertion sort.

```c++
Movie movie1("A", 2010, "PG", 1);
Movie movie2("B", 2011, "PG-13", 5);
Movie movie3("C", 2012, "PG", 4);
Movie movie4("D", 2013, "R", 3);

DoublyLinkedList<Movie> list;

list.insert(movie1);
list.insert(movie2);
list.insert(movie3);
list.insert(movie4);

list.sort();
```

* **Type& getHead()**: This function returns a reference to the object inside the `header` node.

```c++
Movie movie1("A", 2010, "PG", 1);
Movie movie2("B", 2011, "PG-13", 5);
Movie movie3("C", 2012, "PG", 4);
Movie movie4("D", 2013, "R", 3);

DoublyLinkedList<Movie> list;

list.insert(movie1);
list.insert(movie2);
list.insert(movie3);
list.insert(movie4);

list.getHead();
```

* **Type& getTail()**: This function returns a reference to the object inside the `trailer` node.  

```c++
Movie movie1("A", 2010, "PG", 1);
Movie movie2("B", 2011, "PG-13", 5);
Movie movie3("C", 2012, "PG", 4);
Movie movie4("D", 2013, "R", 3);

DoublyLinkedList<Movie> list;

list.insert(movie1);
list.insert(movie2);
list.insert(movie3);
list.insert(movie4);

list.getTail();
```

* **Type& operator[] (const unsigned int index)**: This function overloads the `[]` operator. It allows access to the list using an index (like an array).

```c++
Movie movie1("A", 2010, "PG", 1);
Movie movie2("B", 2011, "PG-13", 5);
Movie movie3("C", 2012, "PG", 4);
Movie movie4("D", 2013, "R", 3);

DoublyLinkedList<Movie> list;

list.insert(movie1);
list.insert(movie2);
list.insert(movie3);
list.insert(movie4);

list[0];
```

#### Self-Grading and Feedback
Once you have implemented all of the functions your goal is to pass all the tests and obtain this output:

```
All tests passed (96 assertions in 19 test cases)
```

This is provided for you to get feedback on your code. You can attempt to fix it and prepare it for submission once it passes all the tests. Once submitted, a set of similar tests will be run on your solution.

#### Submission
You are expected to submit your zip file in Canvas by the specified deadline. The zip file name must match your Tracks ID. For instance, if your Tracks ID is *aLastname2016* then your zip file should be called **aLastname2016.zip**. Resubmissions are allowed. Canvas will slightly alter the file name to indicate a resubmission with the same file name. This is expected and the grading software will obtain your latest submission as long as you keep submitting files named *aLastname2016.zip*. The zip file should only contain the `DoublyLinkedList.hpp`, `Movie.hpp`, and `Movie.cpp` file.
