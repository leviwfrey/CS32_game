# CS32_game

A simple arcade game

To play:

clone this repo into your local machine using `git clone`

run `cmake . && make && bash play.sh` inside of the directory with the file `CMakeLists.txt` for first time compilation

to start the game, run `bash play.sh`

to kill the current instance use the top right corner of the game window or in the terminal use `ctrl + C` or `cmd + C`

use WASD controls to move around the screen

use the spacebar to shoot a projectile

avoid colliding with an enemy or being shot to survive

may you reach the highest difficulty!

press `k` to restart the game if you die

dark green squares will follow the player

white squares will follow you until they are in range, and then will stop and shoot the player

