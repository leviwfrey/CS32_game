#ifndef GAME_H
#define GAME_H

class Game {
    public:
        Game(int width, int height);
    private:
        void init();
        void start();

        //member variables
        int screen_width;
        int screen_height;
};

#endif