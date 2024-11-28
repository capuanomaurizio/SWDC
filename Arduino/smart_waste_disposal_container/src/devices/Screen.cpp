#include "Screen.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C* lcd;

Screen::Screen(int cols, int rows){
    lcd = new LiquidCrystal_I2C(0x27,cols, rows);
    lcd->init();
    lcd->backlight();
    clear();
}

void Screen::write(int cols, int rows, String text){
    lcd->setCursor(cols, rows);
    lcd->print(text);
}

void Screen::clear(){
    lcd->clear();
}
