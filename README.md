# Solving Dining Philosopher Problem

![Dining Philosopher Problem](https://user-images.githubusercontent.com/12528718/123442516-9ccb7400-d5dd-11eb-9e3d-314feffdb5fd.jpg)

Three different way to solve problem:

## philo_one

philosopher with threads and mutex

* One fork between each philosopher, therefore there will be a fork at the right and at the left of each philosopher.
* To avoid philosophers duplicating forks, you should protect the forks state with a mutex for each of them.
* Each philosopher should be a thread.

## philo_two

philosopher with threads and semaphore

* All the forks are in the middle of the table.
* They have no states in memory but the number of available forks is represented by a semaphore.
* Each philosopher should be a thread.

## philo_three

philosopher with processes and semaphore

* All the forks are in the middle of the table.
* They have no states in memory but the number of available forks is represented by a semaphore.
* Each philosopher should be a process and the main process should not be a philosopher.

# Useful links
* http://www.stolyarov.info/books/programming_intro/vol3 (page 553)
