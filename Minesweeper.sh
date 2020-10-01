if [ ! -d "executable_linux" ]; then
    wget https://github.com/adam-choragwicki/Minesweeper_Game_Qt_Cplusplus/releases/latest/download/executable_linux.zip
    unzip executable_linux.zip && rm executable_linux.zip
    chmod +x executable_linux/Minesweeper.sh executable_linux/Minesweeper
fi

./executable_linux/Minesweeper
