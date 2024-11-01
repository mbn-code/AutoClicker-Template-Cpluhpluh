// main file for autoclicker program

#include "main.h"

AutoClicker autoClicker(1); // 1 ms interval

void keybindListener() {
    while (true) {
        if (CGEventSourceKeyState(kCGEventSourceStateHIDSystemState, kVK_ANSI_Y)) { // 'Y' key to start
            if (!autoClicker.isRunning()) {
                autoClicker.start();
                std::cout << "AutoClicker started" << std::endl;
            }
        }
        if (CGEventSourceKeyState(kCGEventSourceStateHIDSystemState, kVK_ANSI_B)) { // 'B' key to stop
            if (autoClicker.isRunning()) {
                autoClicker.stop();
                std::cout << "AutoClicker stopped" << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::thread listenerThread(keybindListener);
    listenerThread.join();
    return 0;
}