# A* Algorithm Visualizer

## Project Description

This project implements the **A* pathfinding algorithm** with a **graphical interface**.
The environment is represented as a **discrete grid (matrix)**, where cells can be empty, obstacles, start, or goal.
The application supports **desktop GUI** and **web (WASM) GUI** using Rust.

---

## Project Structure

hw1/
└─ astar_workspace/
├─ astar_core/ # Shared logic (A* algorithm, grid structures)
├─ astar_desktop/ # Desktop GUI (eframe/egui)
└─ astar_web/ # Web GUI (WASM)


- **astar_core**: contains the pathfinding algorithm and grid logic.
- **astar_desktop**: desktop GUI app using `eframe/egui`.
- **astar_web**: web GUI app using `eframe` WASM.

---

## Requirements

- Rust (1.80+)
- Cargo
- Trunk (for web)

---

## Running the Project

### 1. Desktop Version

1. Navigate to the workspace:

```bash
cd astar_workspace
```

2. Run the desktop GUI

```bash
cargo run -p astar_desktop
```

### 2. Web Version (WASM)

1. Add the WASM target (only once):

```bash
rustup target add wasm32-unknown-unknown
```

2. Install Trunk (if not already installed):

```bash
cargo install trunk
```

3. Navigate to web crate:

```bash
cd astar_workspace/astar_web
```

4. Serve the web app:

```
trunk serve
```

- Open your browser at `http://127.0.0.1:8080` to see the A* visualization

## How to Use

- The grid is represented as a 2D matrix.
- Set start, goal, and obstacles in the GUI.
- Run the algorithm to visualize the pathfinding step by step.
- Both desktop and web versions share the same A* logic from *astar_core*.

### Notes

- The project uses *Rust 2021/2024* edition and *eframe/egui* for GUI.
- Desktop and web versions share *one library crate (`astar_core`)* for the algorithm.
- You can expand the project with:
 - Different heuristics (Manhattan, Euclidean)
 - Animated visualization of the open/closed sets
 - Adjustable grid size

### License

This project is for educational purposes. No license is assigned.



