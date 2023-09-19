# Philosophers
## The Dining philosophers problem
This project shows the notions of execution threads in a program,
and the sharing of resources between different threads using mutexes.
Deadlock and data race problems will have to be dealt with.
***
To create this version of Edsger Dijkstra's problem I used two structures,
One for the Main thread where the forks are located (variables shared by different Threads) 
and one structure for the scope of each routine executed by pthread_create() inside the main thread.
Once the variables have been initialised by the parameter input, the pair philos 
will have a delay in coordinating the taking of the forks. 
So the odd philosophers will try to pick up the forks, eat, put the forks down, sleep and then think.
Concurrently (thanks to the mutex), the even-numbered philosophers will do the same.
The main thread (which launched all the philosophers) continues execution until it reaches pthread_join, 
except that this instance will be used to monitor the philosophers, so before the pthread_join the main thread will be in a continuous loop checking (with the mutex since the philo is also accessing its variables) the death variables, the number of times a philo has eaten and whether the philo is starving by looking at the time variable.

## Installation

```bash
git clone git@github.com:Aggyx/philo
cd philo/
make
```
## Usage

```bash
./philo philo_number time_to_die time_to_eat time_to_sleep [number_of_meals]
```

> [!NOTE]  
> All times passed as arguments should be in milliseconds, that way you won't have to wait ages to see the output :). In the example below, No one shoud die (see below): <br />
> ```bash
> ./philo 2 401 200 200 [5]
> ```
## Thanks !
Thanks to @PGCL1 to answer every question i had.
Thanks to CodeVault for his amazing C channel.
 