# CPU Scheduling Simulator

## Description
This project simulates multiple CPU scheduling algorithms used in operating systems.  
It calculates scheduling behavior based on arrival time, burst time, and priority, and outputs metrics such as completion time.

## Algorithms Implemented
- Shortest Job First (SJF)
- Shortest Remaining Time First (SRTF)
- Priority Scheduling (Non-Preemptive)
- Priority Scheduling with Round Robin (Preemptive Hybrid)

## Features
- Supports multiple scheduling strategies
- Handles arrival time, burst time, and priority
- Preemptive and non-preemptive scheduling
- Tie-breaking based on arrival time and process ID
- Calculates completion time for each process

## Tech Stack
- C
- Linux

## Key Concepts
- CPU Scheduling
- Process management
- Preemption vs non-preemption
- Scheduling fairness
- Algorithm design

## How to Run
Compile using:

```bash
gcc *.c -o scheduler
./scheduler input.txt
```

## What I Learned
- How different scheduling algorithms affect process execution.
- How preemption changes system behavior.
- How to implement tie-breaking rules correctly.
- How real operating systems manage CPU scheduling.
- This project demonstrates how operating systems make CPU scheduling decisions in real-world environments.











