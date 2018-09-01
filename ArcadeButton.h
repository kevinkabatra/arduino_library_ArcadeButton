/**
 * @Purpose 
 *   Arduino library that will support physical arcade buttons.
 * 
 * @Description
 *   Each instance of a button contains:
 *   1. a human readable description, which can be used for debugging or 
 *      other reporting purposes,
 *   2. a digital pin that the button will send its input to,
 *   3. and the ASCII Key Code that will represent the key that will be
 *      sent to the Keyboard library.
 * 
 *  This libray can be used with or without an interrupt, but only provides
 *  examples for setting up the library for usage with interrupts. One thing
 *  to note, when using interrupts you must ensure that you handle the switch
 *  debouncing if you are using a physical switch / button. 
 * 
 *  Debouncing can be solved using software, see 
 *  https://www.arduino.cc/en/Tutorial/Debounce, or hardware, see
 *  https://www.youtube.com/watch?v=tmjuLtiAsc0, to ensure the best
 *  accuracy I chose to debounce using a Schmitt trigger as shown in the
 *  video linked above. 
 * 
 *  Interrupts must be setup within the Arduino's sketch file otherwise
 *  the interrupt will be unable to access the button's instance variables.
 * 
 * @Example
 *  // Construct a single button
 *  ArcadeButton player1Start("Player 1 Start", 2, 49);
 * 
 *  // Construct multiple buttons
 *  const short numberOfArcadeButtons = 4;
 *  ArcadeButton arcadeButtons[numberOfArcadeButtons] = {
 *    ArcadeButton("Player 1 Start", 2, 49),
 *    ArcadeButton("Player 2 Start", 3, 50),
 *    ArcadeButton("Player 1 Coin" , 4, 51),
 *    ArcadeButton("Player 2 Coin" , 5, 52)
 *  };
 * 
 * // Setup interrupt
 *  attachInterrupt(
 *    digitalPinToInterrupt(arcadeButtons[0].GetDigitalPin()),
 *    []() {
 *          if(digitalRead(arcadeButtons[0].GetDigitalPin())) {
 *            Keyboard.begin();
 *            Keyboard.press(arcadeButtons[0].GetASCIIKeyCode());            
 *          }
 *          else {
 *            Keyboard.release(arcadeButtons[0].GetASCIIKeyCode());
 *            Keyboard.end();
 *          }
 *    },
 *    CHANGE
 *  );   
 * 
 * @LICENSE 
 *   MIT License
 *   Copyright (c) 2018 Kevin Kabatra
 * 
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 * 
 *   The above copyright notice and this permission notice shall be included in all
 *   copies or substantial portions of the Software.
 * 
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *   SOFTWARE.
*/

#ifndef ArcadeButton_h
#define ArcadeButton_h

#include "Arduino.h"

class ArcadeButton {
  public:
    /* The button */
    ArcadeButton(
      String description,
      byte digitalPin, 
      byte asciiKeyCode 
    );

    /* Extended ASCII Codes have up to 255 key code, so byte covers this range for us */
    byte GetASCIIKeyCode();
    void SetASCIIKeyCode(byte& asciiKeyCode);

    /* Description is useful for debugging purposes, but not for anything else */
    String GetDescription();
    void   SetDescription(String& description);

    /* Arduinos do not have enough pins to fill up a byte. */
    byte GetDigitalPin();
    void SetDigitalPin(byte& digitalPin);

  private:
    byte   _asciiKeyCode; //A byte stores an 8-bit unsigned number, from 0 to 255.
    String _description;
    byte   _digitalPin;
};

#endif