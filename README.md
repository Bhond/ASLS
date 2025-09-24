# ASLS ⚙️  
**A Simple Life Simulation**  

ASLS is a 2D life simulation where evolving agents learn survival strategies using NEAT.
It is designed to be modular and extensible, making it a useful foundation for **robotics, AI, and scientific computing** projects.  


## 📖 Overview
- 🏗️ Modular simulation engine  
- ⚡ Built with **modern C++** (C++17/20)  
- 🔄 Extensible architecture for custom modules  
- ⏱️ Focus on performance and real-time execution  
- 🤖 Suitable for robotics & AI experimentation  


## 🚀 Build & Run

### Prerequisites
- CMake ≥ 3.15  
- Compiler with C++17 or newer (GCC, Clang, MSVC)  

### Build
```bash
git clone https://github.com/Bhond/ASLS.git
cd ASLS
mkdir build && cd build
cmake ..
make -j
```

### Run Example

```bash
./asls_core
```


## 📂 Example Usage
Here’s a minimal example of how ASLS can be used:
#include "simulation.hpp"

```cpp
int main() {
    Simulation sim;
    sim.load("config.json");
    sim.run();
    return 0;
}
```

## 🎥 Demo
(TODO: Add a gif or screenshot of the simulation running here)


## 📜 License

This project is licensed under the MIT License – see LICENSE for details.


⭐ If you find this project useful, give it a star!


