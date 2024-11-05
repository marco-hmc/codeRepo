#include <iostream>

enum State {
    STATE_INIT,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_STOPPED,
    STATE_EXIT
};

int main() {
    State currentState = STATE_INIT;
    bool exit = false;

    while (!exit) {
        switch (currentState) {
            case STATE_INIT:
                std::cout << "Initializing...\n";
                currentState = STATE_RUNNING;
                break;

            case STATE_RUNNING:
                std::cout << "Running...\n";
                // Simulate some condition to change state
                currentState = STATE_PAUSED;
                break;

            case STATE_PAUSED:
                std::cout << "Paused...\n";
                // Simulate some condition to change state
                currentState = STATE_STOPPED;
                break;

            case STATE_STOPPED:
                std::cout << "Stopped...\n";
                // Simulate some condition to change state
                currentState = STATE_EXIT;
                break;

            case STATE_EXIT:
                std::cout << "Exiting...\n";
                exit = true;
                break;

            default:
                std::cerr << "Unknown state!\n";
                exit = true;
                break;
        }
    }

    return 0;
}