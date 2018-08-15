/*
  Arduino library that will support physical arcade buttons.
*/

#ifndef ArcadeButton_h
#define ArcadeButton_h

#include "Arduino.h"

class ArcadeButton {
  public:
    /* Constructor */
    ArcadeButton(int number, String description, int digitalPin);
    ArcadeButton(int number, String description, int digitalPin, int asciiKeyCode);

    enum States { UnPressed, Pressed, Held };

    void init();
    void SetButtonStatePressed();
    void SetButtonStateHeld();
    
    // Getter methods
    int    GetButtonASCIIKeyCode();
    String GetButtonDescription();
    int    GetButtonDigitalPin();
    int    GetButtonNumber();
    States GetButtonState();

  private:
    States ReadInputPinsPressed();
    States ReadInputPinsHeld();
    bool TransitionButtonState(States transitionTo);

    int _number;
    String _description;
    int _digitalPin;
    int _asciiKeyCode;

    States _buttonState;
};

#endif