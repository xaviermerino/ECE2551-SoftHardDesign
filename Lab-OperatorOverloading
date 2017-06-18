## Lab: Operator Overloading

### Overview
In this lab you will become familiar with **operator overloading** while rehearsing the skills obtained in the previous weeks. You will be tasked with two exercises that make use of object-oriented technology.

**In the process you will:**
  * Make use of **control** and **repetition** structures for input validation.
  * Make use of **arrays** to store user-defined types.
  * Sort objects using **bubble sort**.
  * Make use of **function templates** to sort objects.
  * Make use of **cascading function calls** in your classes.
  * Overload operator behavior in your classes.
  * Apply **formatting** rules to console output.

### Lab Task #1
This task consist of creating a simple student roster. In order to accomplish this, you must define and implement a `Student` class. You will use this class to declare an array that is able to hold five instances of the `Student` class.

**Details of the `Student` class:**
* A `Student` has the following **member variables**:
  * `name`
  * `gpa`
  * `financialAidAwarded`

* The constructor makes use of **default arguments**. For `name` the default argument is an empty string. The other member variables must default to zero.

* There are appropriate **member functions** to get and set the member variables in the class. Make sure to declare **member functions** that do not modify an instance as `const`.

* You must allow **cascading function calls** for the the member functions that set the member variables in the class. An example is provided below.

```c++
int main(int argc, const char * argv[]) {
    Student a;
    a.setName("Xavier").setGPA(3.9).setAwardedAid(10000);

    return 0;
}
```

* You must **overload** the `<`, `>`, `<=`, and `>=` operators. This will be used to compare one student to another using the `gpa` as the comparison criteria. An example that compares two students is shown below.

```c++
int main(int argc, const char * argv[]) {
    Student a("Xavier", 3.9, 10000);
    Student b("Curtis", 4.0, 15000);

    if (a < b){
        cout << a.getName() << " has a lesser GPA than " << b.getName() << endl;
    }

    return 0;
}
```

The output results in:

```
Xavier has a lesser GPA than Curtis
```

* You must **overload** the `<<` operator to allow printing a student to the console. Don't forget to include `<iomanip>` to make use of `setw()` and other output manipulation tools. The printing **format** is shown below. The name has a field width of 10 characters and is left aligned.

An example is provided below:

```c++
int main(int argc, const char * argv[]) {
    Student a;
    a.setName("Xavier").setGPA(3.9).setAwardedAid(10000);

    cout << a << endl;

    return 0;
}
```

The output results in:

```
Name: Xavier     GPA: 3.9
```

#### Lab Task #1 Example

After your `Student` class is implemented you must replicate the behavior of the program shown below. Don't forget to use an `array` to store the instances. You must create a function template to implement **bubble sort**. This template will be used to sort the array.

[![asciicast](https://asciinema.org/a/qCrXINJXmWdMHOdI9cBceaKCm.png)](https://asciinema.org/a/qCrXINJXmWdMHOdI9cBceaKCm)

### Lab Task #2
This task consist of creating a simple student roster. In order to accomplish this, you must define and implement a `Student` class. You will use this class to declare an array that is able to hold five instances of the `Student` class.
