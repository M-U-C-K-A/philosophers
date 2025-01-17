                       +-------------------------------+
                       |          PHILOSOPHERS         |
                       |           SIMULATION          |
                       +-------------------------------+
                                  |
       +-------------------------------------------------------+
       |                                                       |
+-------------------+                               +-------------------------+
| ** INITIALIZATION ** |                            |     ** PHILOSOPHERS **   |
|---------------------|                            |-------------------------|
| [init_semaphore]    |                            | [philo_eats]            |
| [init_philosophers] |                            | [death_checker]         |
| [init_all]          |                            | [p_process]             |
|---------------------|                            | [launcher]              |
| Initializes all     |                            | [exit_launcher]         |
| resources:          |                            | Handles philosopher     |
| semaphores, forks,  |                            | behavior: eating,       |
| philosophers array. |                            | thinking, and dying.    |
+---------------------+                            +-------------------------+
                                  |
                          SIMULATION FLOW
                                  |
      +------------------------------------------------------------+
      |                                                            |
+------------------+                                  +---------------------+
| ** MESSAGE LOGS ** |                                  |  ** UTILITIES **  |
|-------------------|                                  |-------------------|
| [write_error]     |                                  | [ft_atoi]         |
| [error_manager]   |                                  | [timestamp]       |
| [action_print]    |                                  | [smart_sleep]     |
|-------------------|                                  |-------------------|
| Logs and prints   |                                  | Helper functions  |
| philosopher       |                                  | for parsing,      |
| actions: eating,  |                                  | timing, and       |
| sleeping, etc.    |                                  | controlled delays.|
+-------------------+                                  +-------------------+

                          +------------------------------+
                          |     ** STRUCTURES **         |
                          +------------------------------+
                                  |
    +--------------------------------------------------------------+
    |                                                              |
+-----------------------+                              +-------------------------+
|  ** t_rules **        |                              |   ** t_philosopher **   |
|-----------------------|                              |-------------------------|
| @nb_philo            |                              | @id                     |
| @time_death          |                              | @x_ate                  |
| @time_eat            |                              | @left_fork_id           |
| @time_sleep          |                              | @right_fork_id          |
| @nb_eat              |                              | @t_last_meal            |
| @dieded              |                              | @rules                  |
| @first_timestamp     |                              | @death_check            |
| @meal_check (sem)    |                              | @proc_id                |
| @forks (sem)         |                              |-------------------------|
| @writing (sem)       |                              | Tracks individual       |
| @philosophers[250]   |                              | philosopher stats and   |
|-----------------------|                              | actions.                |
| Stores global rules  |                                                      |
| and shared resources.|                                                      |
+-----------------------+                                                      |

# SIMULATION LIFECYCLE
1. **Initialization**:
   - Semaphores, forks, and philosopher threads/processes are created.
2. **Behavior Execution**:
   - Philosophers alternately eat, think, and sleep.
   - Death is monitored in real-time.
3. **Logging**:
   - Actions are printed to the console for traceability.
4. **Termination**:
   - Simulation ends when conditions are met (all have eaten or one dies).
