// include the library code:
#include <LiquidCrystal.h>

// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Clears the LCD screen
  lcd.clear();
}

void loop() {
  // Print a message to the LCD.
  lcd.print(" Happy Birthday");


 lcd.setCursor(0, 0);

  // set the cursor to column 0, line 1
// (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
   //Print a message to the LCD.
  lcd.print(".....DANIELO.....");

}
