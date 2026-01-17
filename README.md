# Hybrid CPU Scheduler Simulation

A C-based simulation of a hybrid CPU scheduling system that implements three different scheduling algorithms based on process types. This project demonstrates operating system concepts including process scheduling, multithreading, and inter-process communication.

## Project Overview

This project simulates a hybrid CPU scheduler that classifies processes into three categories and applies different scheduling algorithms:

- **SYSTEM processes** → **Priority Scheduling** (Non-preemptive)
- **INTERACTIVE processes** → **Round Robin Scheduling** (Time quantum = 2 seconds)
- **BACKGROUND processes** → **First Come First Serve (FCFS)**

### Key Features

- **Multi-level scheduling**: Different algorithms for different process types
- **Process creation**: Uses `fork()` to create child processes
- **Thread management**: Each process runs in its own pthread within the child process
- **Synchronization**: Mutex-protected shared resources for execution counting
- **Realistic simulation**: Uses `sleep()` to simulate actual CPU burst times

## Project Structure

```
hybrid_scheduler/
├── Makefile                 # Build configuration
├── README.md               # This file
├── include/                # Header files
│   ├── common.h           # Common definitions and PCB structure
│   ├── process.h          # Process execution interface
│   ├── scheduler.h        # Scheduling algorithms interface
│   └── sync.h             # Synchronization utilities
└── src/                   # Source files
    ├── main.c             # Main program entry point
    ├── process.c          # Process execution implementation
    ├── scheduler.c        # Scheduling algorithms implementation
    └── sync.c             # Synchronization implementation
```

## System Requirements

### Prerequisites

- **Operating System**: Unix-like system (Linux, macOS, WSL on Windows)
- **Compiler**: GCC with C99 support
- **Libraries**: POSIX threads (pthread)
- **Build Tool**: Make utility

### Dependencies

- Standard C libraries: `stdio.h`, `stdlib.h`, `unistd.h`, `sys/wait.h`
- POSIX threads: `pthread.h`

## Getting Started

### 1. Clone the Repository

```bash
git clone <repository-url>
cd hybrid_scheduler
```

### 2. Build the Project

```bash
make
```

This will compile all source files and create the `hybrid_scheduler` executable.

### 3. Run the Simulation

```bash
./hybrid_scheduler
```

### 4. Clean Build Files

```bash
make clean
```

## Sample Process Configuration

The simulation starts with a predefined set of processes:

| Process ID | Priority | Burst Time | Type        | Scheduling Algorithm |
|------------|----------|------------|-------------|---------------------|
| P1         | 1        | 5s         | SYSTEM      | Priority            |
| P2         | 3        | 8s         | INTERACTIVE | Round Robin         |
| P3         | 4        | 6s         | INTERACTIVE | Round Robin         |
| P4         | 7        | 10s        | BACKGROUND  | FCFS               |
| P5         | 8        | 4s         | BACKGROUND  | FCFS               |

## Scheduling Algorithms

### 1. Priority Scheduling (SYSTEM processes)
- **Non-preemptive** scheduling
- Lower priority number = Higher priority
- Processes sorted by priority before execution
- System processes get highest priority in the overall execution order

### 2. Round Robin (INTERACTIVE processes)
- **Preemptive** scheduling with time quantum = 2 seconds
- Each process gets equal CPU time slices
- If process doesn't complete in one quantum, it's moved to back of queue
- Continues until all processes complete

### 3. First Come First Serve (BACKGROUND processes)
- **Non-preemptive** scheduling
- Processes executed in the order they arrive
- Simple and fair for background tasks
- Executed after system and interactive processes

## Technical Architecture

### Process Control Block (PCB)
```c
typedef struct {
    int pid;              // Process ID
    int priority;         // Priority level (lower = higher priority)
    int burst_time;       // Total CPU burst time required
    int remaining_time;   // Remaining time for Round Robin
    int type;             // Process type (SYSTEM/INTERACTIVE/BACKGROUND)
} PCB;
```

### Execution Flow
1. **Initialization**: Set up synchronization primitives
2. **Process Loading**: Load predefined process set
3. **Classification**: Separate processes by type into different queues
4. **Scheduling**: Execute each queue with its respective algorithm:
   - System processes (Priority Scheduling)
   - Interactive processes (Round Robin)
   - Background processes (FCFS)
5. **Process Execution**: For each scheduled process:
   - Fork a child process
   - Create a pthread within the child
   - Simulate CPU execution with sleep()
   - Track execution with mutex-protected counters
6. **Cleanup**: Destroy synchronization resources

### Synchronization
- **Mutex**: `exec_mutex` protects shared execution counter
- **Process Synchronization**: Parent processes wait for children using `wait()`
- **Thread Synchronization**: Processes wait for their threads using `pthread_join()`

## Sample Output

```
Hybrid CPU Scheduler Simulation
--------------------------------

Loaded Processes:
P1 | Priority=1 | Burst=5 | Type=0
P2 | Priority=3 | Burst=8 | Type=1
P3 | Priority=4 | Burst=6 | Type=1
P4 | Priority=7 | Burst=10 | Type=2
P5 | Priority=8 | Burst=4 | Type=2

--- Priority Scheduling ---
Child Process Created: P1 (OS PID=12345)
Thread started for P1 | Execution Count = 1
Executing P1 for 5 seconds
Thread completed for P1
Process P1 completed execution

--- Round Robin Scheduling (Quantum = 2) ---
Child Process Created: P2 (OS PID=12346)
Thread started for P2 | Execution Count = 2
Executing P2 for 2 seconds
Thread completed for P2
Process P2 completed execution
Scheduler: P2 remaining time = 6
...

--- FCFS Scheduling ---
Child Process Created: P4 (OS PID=12350)
...

All processes completed successfully.
```

## Customization

### Adding New Processes
Modify the `processes[]` array in [src/main.c](src/main.c):

```c
PCB processes[] = {
    {pid, priority, burst_time, remaining_time, type},
    // Add more processes here
};
```

### Changing Time Quantum
Modify `TIME_QUANTUM` in [include/common.h](include/common.h):

```c
#define TIME_QUANTUM 3   // Change to desired quantum (seconds)
```

### Process Types
Available process types in [include/common.h](include/common.h):
```c
#define SYSTEM 0        // Priority Scheduling
#define INTERACTIVE 1   // Round Robin
#define BACKGROUND 2    // FCFS
```

## Troubleshooting

### Common Issues

1. **Compilation Errors**
   ```bash
   # Ensure pthread library is linked
   gcc -pthread -o hybrid_scheduler src/*.c -Iinclude
   ```

2. **Permission Denied**
   ```bash
   chmod +x hybrid_scheduler
   ```

3. **Make Command Not Found**
   ```bash
   # Install build tools (Ubuntu/Debian)
   sudo apt-get install build-essential
   
   # Install build tools (macOS)
   xcode-select --install
   ```

### Debug Mode
Compile with debug flags for troubleshooting:
```bash
gcc -Wall -g -pthread -Iinclude src/*.c -o hybrid_scheduler_debug
gdb ./hybrid_scheduler_debug
```

## Learning Objectives

This project demonstrates:

- **CPU Scheduling Algorithms**: Implementation of multiple scheduling strategies
- **Process Management**: Creating and managing processes using system calls
- **Thread Programming**: Multi-threaded execution within processes
- **Synchronization**: Mutex-based protection of shared resources
- **System Programming**: Low-level system calls and POSIX compliance
- **Modular Design**: Clean separation of concerns across multiple files

## References

- Operating System Concepts by Silberschatz, Galvin, and Gagne
- POSIX Programmer's Manual
- GCC Compiler Documentation
- Linux/Unix System Programming

---

**Note**: This simulation is designed for educational purposes to demonstrate scheduling concepts. In real operating systems, scheduling is handled by the kernel with much more complexity and optimization.
