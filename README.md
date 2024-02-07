# Philosophers
The dining philosophers problem is a clasic example of a computer science and concurrent programming. It illustrates syncronization issues and methods of resolving them in a multi-process or multi-threaded program.

## Instructions
- One or more philosophers sit at a round table.
- There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively eat, think, or sleep.
- While they are eating, they are not thinking nor sleeping.
- While thinking, they are not eating nor sleeping.
- While sleeping, they are not eating nor thinking.
- There are also forks on the table. There are as many forks as philosophers.
- Because serving and eating spaghetti with only one fork is very inconvenient,
  a philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and
  start sleeping. Once awake, they start thinking again. The simulation stops when
  a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- Philosophers should avoid dying


## Key Concepts
- Multithreading
- Synchronization mechanisms
- Concurrency
- Parrallel programming
- Mutexes and deadlocks

## How To Use
Clone the repository:
```
git clone 
```
Move inside the directory:
```
cd 
```
Compile:
```
makez
```
This will create an executable called ``.

Run it:
```
./
```
