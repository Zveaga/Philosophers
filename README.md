# Philosophers
The dining philosophers problem is a clasic example of a computer science and concurrent programming. It illustrates syncronization issues and methods of resolving them in a multi-process or multi-threaded program.

## Key Concepts
- Multithreading
- Synchronization mechanisms
- Concurrency
- Parrallel programming
- Mutexes and deadlocks


## How To Run
Clone the repository:
```
git clone git@github.com:Zveaga/Philosophers.git
```
Move inside the directory:
```
cd Philosophers
```
Compile:
```
make
```
This will create an executable called `philo`.

The program takes must take 4 or 5 arguments:
- `number_of_philosophers`: The number of philosophers and also the number
of forks.
- `time_to_die` (in milliseconds): If a philosopher didn’t start eating `time_to_die`
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat` (optional argument): If all
philosophers have eaten at least `number_of_times_each_philosopher_must_eat
times`, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

Example of the program can be ran (you can modify the value of the arguments):
Without the optional argument:
```
./philo 10 500 200 200
```
With the optional argument:
```
./philo 10 500 200 200 5
```

## Program Instructions
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
