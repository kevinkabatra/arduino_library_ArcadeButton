# arduino_library_ArcadeButton
Arduino library that will support physical arcade buttons.

Each instance of a button contains:
1. a human readable description, which can be used for debugging or other reporting purposes,
2. a digital pin that the button will send its input to,
3. and the ASCII Key Code that will represent the key that will be sent to the Keyboard library.
 
## Usage
This libray can be used with or without an interrupt, but only provides examples for setting up the library for usage with interrupts. One thing to note, when using interrupts you must ensure that you handle the switch debouncing if you are using a physical switch / button.
 
## Debouncing
Debouncing can be solved using software, see https://www.arduino.cc/en/Tutorial/Debounce, or hardware, see https://www.youtube.com/watch?v=tmjuLtiAsc0, to ensure the best accuracy I chose to debounce using a Schmitt trigger as shown in the video linked above.

## Interrupt Setup
Interrupts must be setup within the Arduino's sketch file otherwise the interrupt will be unable to access the button's instance variables.
 
## Examples
* Construct a single button
```
  ArcadeButton player1Start("Player 1 Start", 2, 49);
```

* Construct multiple buttons
```
  const short numberOfArcadeButtons = 4;
  ArcadeButton arcadeButtons[numberOfArcadeButtons] = {
    ArcadeButton("Player 1 Start", 2, 49),
    ArcadeButton("Player 2 Start", 3, 50),
    ArcadeButton("Player 1 Coin" , 4, 51),
    ArcadeButton("Player 2 Coin" , 5, 52)
  };
```

* Setup interrupt
```
  attachInterrupt(
    digitalPinToInterrupt(arcadeButtons[0].GetDigitalPin()),
    []() {
          if(digitalRead(arcadeButtons[0].GetDigitalPin())) {
            Keyboard.begin();
            Keyboard.press(arcadeButtons[0].GetASCIIKeyCode());            
          }
          else {
            Keyboard.release(arcadeButtons[0].GetASCIIKeyCode());
            Keyboard.end();
          }
    },
    CHANGE
  );   
```
