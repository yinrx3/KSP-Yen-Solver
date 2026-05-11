# K-Shortest Path Solver (Yen's Algorithm)

This is the implementation for the second Data Structures and Algorithms (DSA) course project (Fall 2024).  
It solves the **K-Shortest Path (KSP)** problem in undirected graphs using **Yen's Algorithm**, supporting common real-world constraints.

---

## Repository Structure

| File | Description |
|---|---|
| `safety.cpp` | The main solver code (final submission). Implements Yen's algorithm and handles all query commands. |
| `project_2_ds25.pdf` | Original assignment description / problem statement. |
| `DSA.project2.pdf` | Final technical report, including algorithm design, optimizations, and analysis. |
| `input1.txt`, `sample.txt` | Test cases and sample inputs. |

---

## About the Project

This project implements Yen's K-Shortest Path algorithm, which finds the top-K shortest loopless paths between two nodes in a graph.  
Key features include:
- Support for node blacklisting (`ban`/`unban` commands)
- Path length constraints (maximum number of intermediate nodes)
- Interactive command-line interface for dynamic queries

---

## Yen's Algorithm Overview

Yen's algorithm generates K shortest paths by iteratively finding "spur paths" from previously found shortest paths:
1.  **Find the 1st shortest path** using Dijkstra's algorithm.
2.  For each node on the path (except the end), treat it as a "spur node":
    -   Create a "root path" from the start to the spur node.
    -   Temporarily remove edges that would repeat previous paths.
    -   Run Dijkstra again from the spur node to the end to get the "spur path".
    -   Combine the root and spur paths to form a candidate path.
3.  Collect all candidate paths, sort them by cost, and select the next shortest one.
4.  Repeat until K paths are found or no more valid paths exist.

---

## Compile & Run

```bash
g++ safety.cpp -o ksp_solver
./ksp_solver
