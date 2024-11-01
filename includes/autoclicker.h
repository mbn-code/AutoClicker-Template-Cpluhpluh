#ifndef AUTOCLICKER_H
#define AUTOCLICKER_H

#include <chrono>
#include <thread>

class AutoClicker {
public:
    AutoClicker(int interval_ms);
    void start();
    void stop();
    bool isRunning() const;

private:
    void clickLoop();

    int interval_ms;
    bool running;
    std::thread clickerThread;
};

#endif // AUTOCLICKER_H