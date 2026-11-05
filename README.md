# Philosophers

The **dining philosophers problem**, solved in C with POSIX threads and mutexes. 42 project.

![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)
![pthreads](https://img.shields.io/badge/POSIX-threads_%26_mutexes-555)

## The problem

N philosophers sit around a round table with one fork between each pair. To eat, a philosopher needs both forks next to them. Each one eats, sleeps, then thinks, in a loop. The simulation stops as soon as one of them starves, or when every philosopher has eaten a given number of times.

The hard parts are concurrency problems: no deadlock, no data race, and a death detected and printed within a few milliseconds.

## How it works

- **One thread per philosopher**, and **one mutex per fork**
- **No deadlock**: neighbouring philosophers don't pick up their forks in the same order, so they can never all hold one fork and wait for the other
- **A monitor** in the main thread checks every philosopher's last meal time, which is protected by a mutex, and stops the simulation on a death or once everyone has eaten enough
- **Clean output**: printing goes through its own mutex, so lines never overlap
- **Precise timing**: a custom sleep loop based on `gettimeofday` instead of a single long `usleep`, to keep delays accurate

## Usage

```bash
cd philo
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_per_philosopher]
```

Times are in milliseconds. Examples:

```bash
./philo 5 800 200 200       # nobody should die
./philo 5 800 200 200 7     # stops once each philosopher has eaten 7 times
./philo 4 310 200 100       # a philosopher dies
```

Each event is printed with a timestamp:

```
0 Philo 1 has taken a fork
0 Philo 1 is eating
200 Philo 1 is sleeping
```

## Structure

```
philo/
├── philo.c, philo.h        entry point, setup and monitor
├── thread.c                philosopher routine
├── forks_utils.c           taking and releasing forks, eating
├── checker_args*.c         argument checks and time helpers
├── dest_init.c             cleanup of mutexes and memory
└── philo_utils.c
```
