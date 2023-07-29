# C++ Module 09

The ultimate use of STL, algorithm, and templates. (Not really)

* [Exercise 00](#exercise-00-bitcoin-exchange)
* [Exercise 01](#exercise-01-reverse-polish-notation)
* [Exercise 02](#exercise-02-pmergeme)

## Rules of CPP09
* Each exercise must implement the use of at least 1 container.
* Containers used in previous exercises cannot be used for the remaining exercises.

## Exercise 00: Bitcoin Exchange

A relatively simple exercise. Calculating bitcoin exchange rate.

**The rules are:**
* The program takes a file as argument.
* The content of the file follow the format "Date | Value"
* A valid date follows the format: "YYYY-MM-DD"
* A valid value must be a positive float or int.
* Errors should be handled appropriately.
* The program should display on output, the result of the value multiplied by the exchange rate.

![btc](https://media.discordapp.net/attachments/989407433858375683/1134704689087250474/Screenshot_2023-07-29_at_12.27.31.png?width=1580&height=1020)

## Exercise 01: Reverse Polish Notation.

First of all, who tf came up with this?

**Reverse Polish Notation (a.k.a postfix notation)**. I referred to [this guide](https://notation-visualizer.ajayliu.com/) to come up with the code implementation. Helped a lot. :thumbs_up:

**The rules are:**
* The program takes an inverted Polish mathematical expression (a.k.a PRE-fix notation) as argument.
* The program must process the expression and output the correct result.
* The program must be able to handle these operations: "+-*/"

![RPN](https://media.discordapp.net/attachments/989407433858375683/1134704689460563988/Screenshot_2023-07-29_at_12.29.08.png?width=1924&height=788)
## Exercise 02: PmergeMe

Horrific. I would fight whoever decided to put this in the pdf.

Here we are forced to learn the Ford-Johnson Merge Insertion sort (FJMI). I had a really hard time understanding this stuff until I was suggested to refer to [this very helpful guide.](https://github.com/PunkChameleon/ford-johnson-merge-insertion-sort)

I did not enjoy this. 0/10.

**The rules are:**
* The program takes an unsorted positive integer sequence as argument. (Whether the program takes the sequence as a single string or as multiple arguments is kind of up to you).
* You must use the FJMI sort to sort this sequence.
* You **must** use two containers to complete this exercise. So each container has it's own algorithm.
* On output, the first line must display the unsorted sequence.
* Followed by the sorted sequence, and the time used by the algo to sort it.

![bullshit](https://media.discordapp.net/attachments/989407433858375683/1134704688839807016/Screenshot_2023-07-29_at_12.31.02.png?width=2198&height=1498)