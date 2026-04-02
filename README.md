# 🎮 GameBoys — Arduino Nano Game Console (Snake / Tetris / Arkanoid / Race)

GameBoys — це міні ігрова консоль на базі **Arduino Nano + MAX7219 LED matrix**, яка містить кілька класичних ігор:

* 🐍 Snake
* 🧱 Tetris
* 🏓 Arkanoid
* 🏎 Race
* 📋 Menu system
* 🔊 Sound effects (buzzer)

Проєкт побудований з використанням **C++ модульної архітектури**, де кожна гра винесена в окремий файл.

---

# 🧩 Hardware

Схема підключення (як на зображенні):

* Arduino Nano
* MAX7219 8x16 LED Matrix (2 modules)
* 6 кнопок
* Buzzer
* GND shared

---

# 🔌 Pinout

## MAX7219

| MAX7219 | Arduino Nano |
| ------- | ------------ |
| DIN     | D12          |
| CS      | D10          |
| CLK     | D11          |
| VCC     | 5V           |
| GND     | GND          |

---

## Buttons

| Button | Pin | Function |
| ------ | --- | -------- |
| BTN1   | D2  | A        |
| BTN2   | D3  | B        |
| BTN3   | D4  | RIGHT    |
| BTN4   | D7  | LEFT     |
| BTN5   | D6  | UP       |
| BTN6   | D5  | DOWN     |

---

## Buzzer

| Buzzer | Arduino |
| ------ | ------- |
| +      | D4      |
| -      | GND     |

---

# 🎮 Controls

| Key   | Action           |
| ----- | ---------------- |
| LEFT  | move left        |
| RIGHT | move right       |
| UP    | move up / rotate |
| DOWN  | fast drop        |
| A     | select           |
| B     | back             |

---

# 🧠 Menu System

Menu відображає вибір гри на правій половині матриці.
Іконки гри малюються як bitmap масиви.

Реалізація меню знаходиться в:

* Menu.cpp
* Menu.h

Menu перемикає режим через кнопки LEFT / RIGHT.


---

# 🐍 Snake

Файл:

* SnakeGame.cpp
* SnakeGame.h

Механіка:

* рух змійки
* генерація їжі
* збільшення довжини
* collision detection
* wrap screen

Рух змійки реалізований через масив координат:



---

# 🧱 Tetris

Файли:

* Tetris.cpp
* Tetris.h
* Blocks.h

Підтримує:

* падіння блоків
* rotation
* collision
* line clear
* game over

Генерація випадкового блоку:



Типи блоків визначені у:

Blocks.h


---

# 🏓 Arkanoid

Файли:

* Arcanoid.cpp
* Arcanoid.h
* Arcanoid_blocks.h

Механіка:

* платформа
* м'яч
* блоки
* рівні
* collision

Ігрове поле:

```
8 x 16
```

Логіка руху м’яча:



Рівні визначені тут:



---

# 🏎 Race

Файли:

* RaceGame.cpp
* RaceGame.h

Механіка:

* машина гравця
* машина ворога
* collision
* speed increase
* score

Рух машини гравця:



---

# 📁 Project Structure

```
GameBoys
│
├── GameBoys.ino
│
├── Menu.cpp
├── Menu.h
│
├── SnakeGame.cpp
├── SnakeGame.h
│
├── Tetris.cpp
├── Tetris.h
├── Blocks.h
│
├── Arcanoid.cpp
├── Arcanoid.h
├── Arcanoid_blocks.h
│
├── RaceGame.cpp
├── RaceGame.h
│
└── GameBoy library
```

---

# 🖥 Display

Display:

```
MAX7219 chained
resolution: 8x16
```

Використовується для:

* ігор
* меню
* анімацій
* score
* game over

---

# 🔊 Sound

Buzzer використовується для:

* collision
* score
* game over
* button press

---

# 🧠 Architecture

Проєкт використовує:

* OOP design
* modular games
* menu system
* game loop
* shared display buffer
* input handler

Flow:

```
Menu
 ↓
Select game
 ↓
Game loop
 ↓
Game over
 ↓
Menu
```

---

# ▶️ Run

### Arduino IDE

Open:

```
GameBoys.ino
```

Upload to:

```
Arduino Nano
```

---

# 🚀 Features

✔ Multiple games
✔ LED matrix graphics
✔ Button controls
✔ Sound effects
✔ Menu system
✔ Modular architecture
✔ Embedded friendly code

---

# 👨‍💻 Author

Vadym Dziuba

---

# 📜 License

MIT
