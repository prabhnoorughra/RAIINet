# RAIINet  

A full-featured implementation of the **RAIInet** game (CS246, Fall 2024). This project was completed as part of the University of Waterloo’s CS246 course.  

We achieved **full marks** on the project with a complete and polished implementation, making use of **modern C++ practices (smart pointers, RAII, and no memory leaks)** as well as an **Observer design pattern** to synchronize the graphical and text displays.  

---

## Game Demo
https://www.youtube.com/watch?v=tQVERa7B7sA&ab_channel=Prabh

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
- **Movement** - players cannot move other players' links, cannot move links off the edge and cannot move links into their own server ports. Links that are moved into the opponent's server port are downloaded by the opponent.
- **Battles & Captures** – when links collide, higher strength wins; loser is downloaded. In the case of links having the same strength, the initiator of the battle wins.
- **Ability Cards** – players start with 5 special abilities by default (Firewall, Link Boost, Download, Scan, Polarize), but can choose up to 5 abilities total and a max of 2 of the same card from the 8 abilities implemented (details on this later)
- **Victory Conditions** – download 4 data to win, or 4 viruses to lose.  

---

### Ability Overview
Each ability can be accessed with `ability <N>` where N is an integer between 0-7 representing an ability. The abilities can be used as follows:

Link Boost: `ability 0 <link>`, where link is a character representing a piece on the board
- Example: `ability 0 b` would make it so the b link now moves 2 places on the board for the rest of the game

Firewall: `ability 1 x y`, where x and y are coordinates representing a space on the board (rows/cols begin at 0), where the firewall is placed
- Example: `ability 1 3 3` would place a firewall link on coordinates 3,3. When the opponent's link steps on the firewall, the link is revealed, and if the link is a virus, it's downloaded by the opponent

Download: `ability 2 <link>`, this would immediately download whichever link is supplied in the command
- Example: `ability 2 b` would make it so the b link is downloaded

Scan: `ability 3 <link>`, this ability will reveal any of your opponent's links currently on the board
- Example: `ability 3 b` would reveal the value of link b

Polarize: `ability 4 <link>`, this ability will change any of the links currently on the board from a data to a virus or vice-versa
- Example: `ability 4 b` would change link b from data to virus or virus to data, the strength remains the same

Stun: `ability 5 <link>`, this ability will stun an opponent's link without them knowing, making it so the next time they try moving the link, nothing happens, essentially wasting a turn
- Example: `ability 5 b` would stun link b so that the next time the player tries moving it, the turn is wasted

Barrier: `ability 6 x y`, where x and y are coordinates representing a space on the board (rows/cols begin at 0), where the barrier is placed
- Example: `ability 6 3 3` would place a firewall link on coordinates 3,3. When any link tries moving onto the barrier, the link remains in the same position, but the barrier collapses and is removed from the board

Strength Boost: `ability 7 <link>`, this ability will give the link specified a strength of 5 (strengths are normally 1-4), so this link will win any battle it engages in
- Example: `ability 0 b` would make it so the b link now has a strength of 5 for the rest of the game

---

## Features Implemented  

- **Text Display**: Fully interactive command-line interface to play and test the game.  
- **Graphical Display**: Built using X11, updated via an **Observer pattern** for clean synchronization.  
- **Smart Pointer Management**: All dynamic memory handled with `std::unique_ptr` / `std::shared_ptr`. Verified no leaks with Valgrind.  
- **Command System**:  
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




