#include "Arduino.h"
#include "ArcadeButton.h"

/*
  Constructor
*/
ArcadeButton::ArcadeButton(int number, String description, int digitalPin) {
  _description = description;
  _digitalPin = digitalPin;
  _number = number;
  
  pinMode(_digitalPin, INPUT);
  init();
}

ArcadeButton::ArcadeButton(int number, String description, int digitalPin, int asciiKeyCode) {
  _asciiKeyCode = asciiKeyCode;
  _description = description;
  _digitalPin = digitalPin;
  _number = number;
  
  pinMode(_digitalPin, INPUT);
  init();
}

void ArcadeButton::init() {
  _buttonState = ArcadeButton::States::UnPressed;
}

int ArcadeButton::GetButtonASCIIKeyCode() {
  return _asciiKeyCode;
}

String ArcadeButton::GetButtonDescription() {
  return _description;
}

int ArcadeButton::GetButtonDigitalPin() {
  return _digitalPin;
}

int ArcadeButton::GetButtonNumber() {
  return _number;
}

ArcadeButton::States ArcadeButton::GetButtonState() {
  return _buttonState;
}

void ArcadeButton::SetButtonStatePressed() {
  TransitionButtonState(ReadInputPinsPressed());
}

void ArcadeButton::SetButtonStateHeld() {
  TransitionButtonState(ReadInputPinsHeld());
}

/*
  Attempts to transition _buttonState to the desired state.

  This function works as a mini-State Machine in that it governs the
  ability states that a button can transition to and from.

  Due to the mechanical nature of a button it is impossible for a 
  particular state to transition to itself so all re-entry
  transitions are denied.

  returns: Boolean representing if the button was transitioned.
*/
bool ArcadeButton::TransitionButtonState(ArcadeButton::States transitionTo) {
  bool isTransitionSuccessful = false;

  switch(transitionTo) {
    /*
      Transition to ArcadeButton::States::UnPressed

      Permitted Transitions:
        Pressed -> UnPressed
        Held    -> UnPressed
      Denied Transitions:
        UnPressed -> UnPressed
    */
    case ArcadeButton::States::UnPressed:
      if(_buttonState == ArcadeButton::States::UnPressed) {
        isTransitionSuccessful = false;
      }
      else {
        _buttonState = transitionTo;
        isTransitionSuccessful = true;
      }
      break;

    /*
      Transition to ArcadeButton::States::Pressed

      Permitted Transitions:
        UnPressed -> Pressed
      Denied Transitions:
        Pressed -> Pressed
        Held    -> Pressed
    */
    case ArcadeButton::States::Pressed:
      if(_buttonState == ArcadeButton::States::Pressed ||
         _buttonState == ArcadeButton::States::Held) {
        isTransitionSuccessful = false;        
      }      
      else if(_buttonState == ArcadeButton::States::UnPressed) {
        _buttonState = transitionTo;
        isTransitionSuccessful = true;
      }
      break;

    /*
      Transition to ArcadeButton::States::Held

      Permitted Transitions:
        Pressed -> Held
      Denied Transitions:
        Unpressed -> Held
        Held      -> Held
    */
    case ArcadeButton::States::Held:
      if(_buttonState == ArcadeButton::States::UnPressed ||
         _buttonState == ArcadeButton::States::Held) {
        isTransitionSuccessful = false;        
      }      
      else if(_buttonState == ArcadeButton::States::Pressed) {
        _buttonState = transitionTo;
        isTransitionSuccessful = true;
      }    
      break;
  }

  return isTransitionSuccessful;
}

/*
  Reads the Digital Pin associated to the Arcade Button

  returns: ArcadeButton::States representing the value
  that is read from the pin as it relates to the Arcade Button's
  current action.
*/
ArcadeButton::States ArcadeButton::ReadInputPinsPressed() {
  if(digitalRead(_digitalPin) != 0) {
    //Was the button held since the last loop?
    if(_buttonState == ArcadeButton::States::Pressed || 
      _buttonState == ArcadeButton::States::Held
    )
    {
      return ArcadeButton::States::Held;
    }    
    else {
      return ArcadeButton::States::Pressed;  
    }
  }
  else {
    return ArcadeButton::States::UnPressed;
  }
}

/*
  Reads the Digital Pin associated to the Arcade Button

  returns: ArcadeButton::States representing the value
  that is read from the pin as it relates to the Arcade Button's
  current action.
*/
ArcadeButton::States ArcadeButton::ReadInputPinsHeld() {
  if(digitalRead(_digitalPin) != 0) {
    //Was the button held since the last loop?
    if(_buttonState == ArcadeButton::States::Pressed) {
      return ArcadeButton::States::Held;
    }
  }
  return _buttonState;
}