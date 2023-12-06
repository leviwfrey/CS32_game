#ifndef TIMERHALDNER_H
#define TIMERHANDLER_H
#include <functional>
#include <vector>
#include <chrono>


template<typename T>
class TimerHandler {

    using functionCall = std::function<void()>;

    struct Timer {
        Timer(T& instance, void (T::*function)(), std::chrono::milliseconds duration) {
            functionCall = [&instance, function]() {
                (instance.*function)();
            };
            this->duration = duration;
            startTime = std::chrono::high_resolution_clock::now();
        }

        bool update() {
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);
            if(elapsedTime >= duration) {
                functionCall();
                return true;
            }
            return false;
        }


        std::chrono::milliseconds duration;
        std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
        function<void()> functionCall;
    };
    public:

    void addTimer(T& instance, void (T::*function)(), std::chrono::milliseconds duration) {
        Timer t = Timer(instance, function, duration);
        allTimers.push_back(t);
    }   

    void update() {
        for(size_t i = 0; i < allTimers.size(); i++) {
            if(allTimers[i].update()) {
                allTimers.erase(allTimers.begin() + i);
            }
        }
    }

    private:
        std::vector<Timer> allTimers = std::vector<Timer>();
};


#endif