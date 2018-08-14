/*

*/
#ifndef ArcadeButton_h
#define ArcadeButton_h

#include "Arduino.h"

class ArcadeButton {
  public:
    /* Constructor */
    ArcadeButton(int number, String description, int digitalPin);

    typedef  enum States { UnPressed, Pressed, Held };

    void init();
    void SetButtonStatePressed();
    void SetButtonStateHeld();
    States GetButtonState();
    int GetButtonNumber();

  private:
    States ReadInputPinsPressed();
    States ReadInputPinsHeld();
    bool TransitionButtonState(States transitionTo);

    int _number;
    String _description;
    int _digitalPin;

    States _buttonState;
};

#endif