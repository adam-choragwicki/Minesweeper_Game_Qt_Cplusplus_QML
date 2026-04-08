[![Tests](https://github.com/adam-choragwicki/Minesweeper_Game_Qt_Cplusplus_QML/actions/workflows/tests-workflow.yml/badge.svg)](https://github.com/adam-choragwicki/Minesweeper_Game_Qt_Cplusplus_QML/actions/workflows/tests-workflow.yml)

# Minesweeper

C++ implementation of the classic Minesweeper game using Qt 6.9.2.

Frontend is rendered using QML engine.

**Windows executable is provided.**

## Play online

You can play the WebAssembly build here:

https://adam-choragwicki.github.io/games/minesweeper/index.html

![screenshot.png](screenshot.png)

## Controls

| Input | Action |
| --- | --- |
| **Left Mouse Button** | Uncover tile |
| **Right Mouse Button** | Place or remove flag |
| **Escape** | Open escape menu |
| **F11** | Toggle fullscreen |

## Changing game parameters

During the game, press **Escape** to open the escape menu, then choose **Change Game Parameters** to change:
- **Rows**
- **Columns**
- **Mine percentage**

## Tests

Unit tested using Google Test 1.17.0

## How to run on Windows

1. Download release zip from:  
   https://github.com/adam-choragwicki/Minesweeper_Game_Qt_Cplusplus_QML/releases/latest/download/executable_windows.zip
2. Unzip
3. Run **executable_windows/Minesweeper.exe**
