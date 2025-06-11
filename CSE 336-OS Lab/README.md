# 🖥️ CSE 336 - Operating Systems Lab

This repository contains C++ and Python implementations of various classical algorithms and problems from the **Operating Systems Lab (CSE 336)** at **Shahjalal University of Science and Technology (SUST)**.

---

## 📁 Files & Descriptions

| Filename                                             | Description |
|------------------------------------------------------|-------------|
| `2020331057_priority_scheduling.cpp`                | Implements **Priority Scheduling** algorithm for process management. |
| `2020331057_rr_scheduling.cpp`                      | Implements **Round Robin Scheduling** algorithm. |
| `Bankers_Algorithm.cpp`                             | Implementation of the **Banker's Algorithm** for deadlock avoidance. |
| `Binary_Semaphore.cpp`                              | Demonstrates a **Binary Semaphore** implementation. |
| `FCFS.cpp`                                           | Simulates **First-Come, First-Served (FCFS)** scheduling. |
| `SJF.cpp`                                            | Simulates **Shortest Job First (SJF)** scheduling algorithm. |
| `Semaphore_no_busy_waiting.cpp`                     | Demonstrates **semaphores with no busy waiting**. |
| `Producer_Consumer_Bounded_Buffer_Scheme.cpp`       | Implements the **Producer-Consumer Problem** using bounded buffer. |
| `Producer_Consumer_Using_Semaphore.cpp`             | Solves the **Producer-Consumer Problem** using **semaphores**. |
| `dinning_philosopher.cpp`                           | Implementation of the **Dining Philosophers Problem** to handle concurrency and avoid deadlock. |
| `client.py`                                          | Python client for inter-process communication (IPC) using sockets. |
| `server.py`                                          | Python server for IPC using sockets. |
| `topic.txt`                                          | Contains the list of assigned lab problems/topics. |
| `README.md`                                          | This documentation file. |

---

## 🛠 Technologies Used

- **C++** (for system-level simulations and scheduling algorithms)
- **Python** (for socket programming)
- Standard I/O, multithreading, and process synchronization techniques

---

## 🚀 How to Run

### 🧾 Requirements
- C++ Compiler (e.g., `g++`)
- Python 3.x

### ▶️ Run C++ Files
```bash
g++ filename.cpp -o output
./output
```
Example:

```bash
g++ FCFS.cpp -o fcfs
./fcfs
```
▶️ Run Python Files
Start the server:

```bash
python server.py
```
Then, run the client:

```bash
python client.py
```
### 📌 Topics Covered
CPU Scheduling (FCFS, SJF, RR, Priority)

Process Synchronization (Semaphores, Busy Waiting)

Classic Synchronization Problems (Producer-Consumer, Dining Philosophers)

Deadlock Avoidance (Banker's Algorithm)

Inter-Process Communication (Socket Programming)

### 👨‍🏫 Course Info
Course: CSE 336 - Operating Systems Lab
University: Shahjalal University of Science and Technology (SUST)
Department: Computer Science and Engineering

### 📄 License
This project is for educational purposes only.

### 🙌 Contributions
Feel free to fork the repository and submit pull requests for improvements or alternative implementations.
