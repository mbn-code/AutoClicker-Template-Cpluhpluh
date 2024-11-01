#include "autoclicker.h"
#include <ApplicationServices/ApplicationServices.h>
#include <stdio.h>

AutoClicker::AutoClicker(int interval_ms) : interval_ms(interval_ms), running(false) {}

void AutoClicker::start() {
    if (running) return;
    running = true;
    clickerThread = std::thread(&AutoClicker::clickLoop, this);
}

void AutoClicker::stop() {
    if (!running) return;
    running = false;
    if (clickerThread.joinable()) {
        clickerThread.join();
    }
}

bool AutoClicker::isRunning() const {
    return running;
}

void AutoClicker::clickLoop() {
    while (running) {
        // Simulate mouse click
        CGEventRef click_down = CGEventCreateMouseEvent(
            NULL, kCGEventLeftMouseDown,
            CGEventGetLocation(CGEventCreate(NULL)),
            kCGMouseButtonLeft
        );
        CGEventRef click_up = CGEventCreateMouseEvent(
            NULL, kCGEventLeftMouseUp,
            CGEventGetLocation(CGEventCreate(NULL)),
            kCGMouseButtonLeft
        );

        CGEventPost(kCGHIDEventTap, click_down);
        CGEventPost(kCGHIDEventTap, click_up);

        CFRelease(click_down);
        CFRelease(click_up);

        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
    }
}