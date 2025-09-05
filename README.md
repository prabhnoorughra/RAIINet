# RAIInet  

A full-featured implementation of the **RAIInet** game (CS246, Fall 2024). This project was completed as part of the University of Waterloo’s CS246 course.  

We achieved **full marks** on the project with a complete and polished implementation, making use of **modern C++ practices (smart pointers, RAII, and no memory leaks)** as well as an **Observer design pattern** to synchronize the graphical and text displays.  

---

## Game Overview  

RAIInet is a two-player strategy game inspired by *Stratego*. Each player controls **eight hidden pieces (links)**:  
- **Data links** (goal: download four to win)  
- **Virus links** (goal: force opponent to download four to make them lose)  

Gameplay occurs on an **8×8 board** with server ports and hidden information mechanics. Each turn, players:  
1. Optionally use an ability card.  
2. Move one of their links in a cardinal direction.  

### Key Features
- **Hidden Information** – players only see their own link types; opponents’ pieces remain unknown until revealed.  
- **Battles & Captures** – when links collide, higher strength wins; loser is downloaded.  
- **Ability Cards** – players start with 5 special abilities by default (Firewall, Link Boost, Download, Scan, Polarize), but can choose up to 5 abilities total and a max of 2 of the same card from the 8 abilities implemented (details on this later)
- **Victory Conditions** – download 4 data to win, or 4 viruses to lose.  

---

## How to Play


---

## Features Implemented  

- **Text Display**: Fully interactive command-line interface to play and test the game.  
- **Graphical Display**: Built using X11, updated via an **Observer pattern** for clean synchronization.  
- **Smart Pointer Management**: All dynamic memory handled with `std::unique_ptr` / `std::shared_ptr`. Verified no leaks with Valgrind.  
- **Robust Command System**:  
  - `move`, `board`, `abilities`, `ability <N>`, `sequence <file>`, `quit`.  
- **Custom Abilities**: In addition to required abilities, we designed and implemented new mechanics for extended play.  
- **Configurable Setup**:  
  - Command-line options for player abilities, randomized or file-based piece placement, and graphics toggle.  

---

## Design Decisions  

- **Observer Pattern** – Decoupled game logic from both text and graphical displays, ensuring they are always in sync.  
- **RAII & Smart Pointers** – Eliminated manual memory management headaches and ensured a leak-free, safe implementation.  
- **Modular OOP Design** – Core components (Board, Link, Player, Abilities, Display) were designed for extensibility (e.g., easily adding new abilities or even a 4-player mode).  

---

## Teamwork & Collaboration  

This was a **group project** completed over two weeks. Working as a team taught us:  
- **Version control workflows** for collaborative coding.  
- **Dividing responsibilities** (board mechanics, abilities, displays, testing).  
- **Code reviews and debugging together** to ensure memory safety and consistency.  
- **Communication & planning** – balancing parallel work with integration.  

Beyond the technical learning, this project helped us **grow as collaborators**, preparing us for future teamwork in software engineering.  

---

## How to Run  

### Compile  
```bash
g++20 -std=c++20 -Wall -Werror *.cc -o raiinet -lX11


### Run Examples
Default Game with CLI commands + graphical display
./raiinet -graphics

Custom Link Placement with graphical display
./raiinet -link1 sampleLink1Placement -link2 sampleLink2Placement -graphics

Custom Ability Usage with graphical display
./raiinet -ability1 sampleAbilities1 -ability2 sampleAbilities2 -graphics

Fully customized game with graphical display
./raiinet -link1 sampleLink1Placement -link2 sampleLink2Placement -ability1 sampleAbilities1 -ability2 sampleAbilities2 -graphics


