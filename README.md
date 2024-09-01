# Philosophers dining problem
![Philosophers](https://github.com/YusuCoder/philosophers/blob/master/test_pics/philo.png)

> Philosophers is a 42 school project designed around Edsger Dijkstra's famous dining philosophers problem. For this project, we must learn about concurrent programming. For projects mandatory part we must find the solution to the problem using only thrads and mutexes.

> [!NOTE]
> Each philospher should be a thread and number of forks are equal to number of philosphers ex: if there are 5 philos there will be 5 forks, but each philo can eat only with two forks.

# General description
### The subject describes the problem as follows:
- One or more philosophers sit at a round table.
- There is a large bowl of spaghetti in the middle of the table.
- The spaghetti can only be eaten with two forks.
- There are only as many forks as there are philosophers.
- Each philospher successively eats, sleeps and thinks.
- If a philospher hasn't eaten in a certain timeframe, he will die of starvation.
- Philosphers cannot communicate with each other.
>[!CAUTION]
>If any of the philosophers die other philosopher should not know about it.

### In this project we must create an algorythm that keeps the philosphers alive as far as possible. The programs must take several arguments:
- `number_of_pilosophers` : the number of philosphers around the table.
- `time_to_die` : a number of representing the time in milliseconds a philospher has to alive after eating, if a philospher hasn't started eating between `time_to_die` milleseconds after the beginning of his last meal or the beginning of the simulation, he will die and program should stop here.
- `time_to_eat` : a number representing the time in milleseconds a philospher takes to finish his meal. During that time, the philospher keeps his two forks in hand.
- `tiime_to_sleep` : the time in milleseconds that a philospher spends to sleeping.
- `number_of_time_each_philo_must_eat` : an optional argument that allows the program to stop the simulation if all philosphers have eaten at least that many times. If this argument is not specified, the simulation should stop when any of philosphers dies.

### The programs outpit message each time a philospher takes a fork an action, which is formatted this way:
```
  [timestamp_in_ms] [x] has taken a fork
  [timestamp_in_ms] [x] is eating
  [timestamp_in_ms] [x] is sleeping
  [timestamp_in_ms] [x] is thinking
  [timestamp_in_ms] [x] died
```

# Threads and Mutexes
> Each philospher is a thread and each fork is protected by a mutex. There is exactly one fork between each philosphers and a philospher must take the fork to his immediate left and right in order to eat.


# Usage

1. Clone the project
```

git clone https://github.com/YusuCoder/philosophers.git

```
2. Go to root directory and compile the program:
```

cd ./philo/philo && make

```
3. Run the programm with the following arguments:
```

./philo <number_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]

```
> The arguments must be integers between 0 and INT_MAX representing a time in milleseconds. For example:
```

./philo 4 800 200 200 10

```
> If the arguments are valid, the programm will output the actions of each philospher utill one of them dies or untill all of them have eaten number_of_times_each_philo_must_eat, if specified
