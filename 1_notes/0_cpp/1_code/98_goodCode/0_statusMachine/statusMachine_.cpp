#include <iostream>

enum class ElevatorState { IDLE, MOVING_UP, MOVING_DOWN, DOORS_OPEN };

class Elevator {
private:
  ElevatorState currentState;
  int currentFloor;

public:
  Elevator() : currentState(ElevatorState::IDLE), currentFloor(1) {}

  void setState(ElevatorState state) { currentState = state; }

  void setCurrentFloor(int floor) { currentFloor = floor; }

  void processEvent(char event) {
    switch (currentState) {
    case ElevatorState::IDLE:
      if (event == 'u') {
        setState(ElevatorState::MOVING_UP);
        std::cout << "Elevator is moving up" << '\n';
      } else if (event == 'd') {
        setState(ElevatorState::MOVING_DOWN);
        std::cout << "Elevator is moving down" << '\n';
      }
      break;

    case ElevatorState::MOVING_UP:
      if (event == 's') {
        setState(ElevatorState::IDLE);
        std::cout << "Elevator has reached floor " << currentFloor << '\n';
      } else if (event == 'd') {
        setState(ElevatorState::MOVING_DOWN);
        std::cout << "Elevator is changing direction to move down" << '\n';
      }
      break;

    case ElevatorState::MOVING_DOWN:
      if (event == 's') {
        setState(ElevatorState::IDLE);
        std::cout << "Elevator has reached floor " << currentFloor << '\n';
      } else if (event == 'u') {
        setState(ElevatorState::MOVING_UP);
        std::cout << "Elevator is changing direction to move up" << '\n';
      }
      break;

    case ElevatorState::DOORS_OPEN:
      if (event == 'c') {
        setState(ElevatorState::IDLE);
        std::cout << "Elevator doors are closing" << '\n';
      }
      break;
    }
  }
};

int main() {
  Elevator elevator;

  // Simulate events
  elevator.processEvent('u');  // Elevator starts moving up
  elevator.setCurrentFloor(5); // Elevator reaches floor 5
  elevator.processEvent('s');  // Elevator stops at floor 5
  elevator.processEvent('d');  // Elevator changes direction to move down
  elevator.setCurrentFloor(2); // Elevator reaches floor 2
  elevator.processEvent('s');  // Elevator stops at floor 2
  elevator.processEvent('c');  // Elevator doors close

  return 0;
}