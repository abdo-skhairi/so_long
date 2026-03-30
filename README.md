<div align="center">
<pre>
 ██████╗ ██████╗      ██╗      ██████╗ ███╗   ██╗ ██████╗ 
██╔════╝██╔═══██╗     ██║     ██╔═══██╗████╗  ██║██╔════╝ 
╚█████╗ ██║   ██║     ██║     ██║   ██║██╔██╗ ██║██║  ███╗
 ╚═══██╗██║   ██║     ██║     ██║   ██║██║╚██╗██║██║   ██║
██████╔╝╚██████╔╝     ███████╗╚██████╔╝██║ ╚████║╚██████╔╝
╚═════╝  ╚═════╝      ╚══════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ 
</pre>
</div>

# so_long 🕹️

A simple 2D game built in C using the new version of the MLX42 graphics library.


## 📸 Screenshots

![Game Preview](https://github.com/abdo-skhairi/so_long/blob/main/game_image.png?raw=true)



## 🧠 About the Project

**so_long** is a small tile-based game where the player moves through a map, collects all the coins (💰), and heads to the exit (🚪). The game is part of the 42 school curriculum and helps reinforce understanding of parsing, basic game mechanics, memory management, and rendering using MLX42.

## 🎮 Gameplay

- The player (🧍) starts on a 2D grid map.
- The goal is to collect all the coins.
- Once all coins are collected, the exit opens.
- Touching the exit after collecting all coins ends the game.

## ⚙️ Features

- Map parsing from `.ber` files
- Movement using `W`, `A`, `S`, `D` keys
- Coin collection system
- Exit unlocked after collecting all coins
- Real-time rendering with MLX42
- Wall collision detection
- Keyboard input and smooth rendering

## 📦 Installation

### Requirements

- C compiler (GCC/Clang)
- [MLX42](https://github.com/codam-coding-college/MLX42)
- Make

### Setup

```bash
git clone https://github.com/yourusername/so_long.git
cd so_long
make
./so_long maps/map1.ber
🗺️ Map Format
Each map is a .ber file and must follow these rules:

Rectangular shape

Closed by walls (1)

Contains exactly:

One player (P)

One exit (E)

At least one collectible (C)

Example:

Copy
Edit
11111
1P0C1
10001
1C0E1
11111
🛠️ Built With
C Language

MLX42

Makefile
```

---

## 🙌 Final Words

**so_long** was a fun and challenging project that helped me dive deeper into C programming, graphics rendering with MLX42, and game logic design. It’s a great introduction to building something visual from scratch and understanding low-level mechanics behind a simple 2D game.

If you have any feedback, suggestions, or just want to connect—feel free to reach out!

## 📬 Contact Me

- 📧 **Email:** skhairi.abderahmane@gmail.com  
- 📸 **Instagram:** [@abdo.skh](https://instagram.com/abdo.skh)

---

