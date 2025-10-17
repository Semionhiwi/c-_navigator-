# C++ Germany Navigator

A high-performance desktop navigation tool for exploring and planning optimal routes within Germany.  
Built from scratch as a semester-long university project, demonstrating proficiency in modern C++ development, algorithm implementation, and Qt UI design.

![C++](https://img.shields.io/badge/C++-78%25-00599C?logo=cplusplus)
![Qt](https://img.shields.io/badge/Qt-Widgets-41CD52?logo=qt)

---

## Project Overview

This application provides efficient route planning across Germany using custom-implemented graph algorithms and an intuitive desktop interface. The project emphasizes performance optimization, clean architecture, and user experience.

**Development Time:** One semester (approx. 4 months)  
**Project Type:** University coursework

---

## Key Features

- **Dijkstra's Algorithm Implementation** – Custom pathfinding engine guaranteeing optimal route calculation
- **Custom Graph Data Structure** – Adjacency list representation optimized for sparse road networks
- **Interactive Qt UI** – Responsive widget-based interface with real-time route visualization
- **Lightweight Performance** – Minimal memory footprint with fast route computation
- **Cross-Platform Support** – Builds seamlessly on Linux, macOS, and Windows

---

## Tech Stack

| Technology | Purpose |
|------------|---------|
| **C++** (78%) | Core navigation logic, graph algorithms, data structures |
| **Qt Widgets** | Desktop UI framework and event handling |
| **CMake/Makefile** | Cross-platform build system configuration |

---

## Technical Highlights

### Algorithm Implementation
- **Dijkstra's Shortest Path** – Priority queue-based implementation for optimal route finding
- **Graph Representation** – Adjacency list structure for efficient neighbor traversal
- **Time Complexity** – O((V + E) log V) using binary heap optimization

### Code Quality
- **Modern C++ Practices** – RAII principles, smart pointers, const correctness
- **Modular Architecture** – Clear separation between navigation engine and UI layer
- **Performance-Focused** – Memory-efficient data structures and optimized algorithms

### UI Design
- **Qt Widgets Framework** – Custom-designed interface components
- **Responsive Layout** – Adaptive UI scaling for different screen sizes

---

## Prerequisites

- **C++ Compiler** – GCC 7.0+, Clang 5.0+, or MSVC 2017+
- **Qt Framework** – Qt 5.12 or higher
- **CMake** (optional) – Version 3.10+ for CMake build

---

## Build & Run

### Using Makefile
```bash
make
./navigator
```

### Using CMake
```bash
mkdir build && cd build
cmake ..
make
./navigator
```

---


---

## What I Learned

This project significantly expanded my development skillset:

- **Algorithm Implementation** – Translated theoretical knowledge of Dijkstra's algorithm into production-ready C++ code
- **Qt Framework Mastery** – Gained hands-on experience with Qt Widgets, signals/slots, and event-driven programming
- **Performance Optimization** – Learned to write memory-efficient, lightweight code through profiling and iteration
- **Software Architecture** – Designed modular systems with clear separation of concerns
- **Build Systems** – Configured both Makefile and CMake for cross-platform compatibility

