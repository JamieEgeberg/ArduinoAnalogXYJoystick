/* 
Analog X/Y joystick
*/

int joyPin1 = 0;     //X pin (analog)
int joyPin2 = 1;     //Y pin (analog)
int joySW = 5;       //SW pin (digital)
int value1 = 0;      //X value
int value2 = 0;      //Y value
int switchState = 0; //State of the SW
bool clicked = false;

void setup()
{
    pinMode(joyPin1, INPUT);
    pinMode(joyPin2, INPUT);
    pinMode(joySW, INPUT);
    digitalWrite(joySW, HIGH); //bad fix, but it twerks.. Should of course be done with a pull-up resistor. Usually you would never write to an input.
    Serial.begin(9600);
}

int treatValue(int data)
{
    return (data / 4); //mapping from 1024 to 256, just because
}

void loop()
{
    // reads the value of the variable resistor
    value1 = analogRead(joyPin1);
    // this small pause is needed between reading
    // analog pins, otherwise we get the same value twice
    delay(100);
    // reads the value of the variable resistor
    value2 = analogRead(joyPin2);
    delay(100);

    switchState = digitalRead(joySW); //Active low, meaning it will be 0 when clicked
    // When clicked, the reading is paused until another click
    if (!switchState) //Check if 0, and change clicked
    {
        Serial.println("You just clicked! ");
        clicked = !clicked;
        delay(25); //simple 'debounce', so it doens't register 2 clicks when only clicking once
    }

    if (clicked) //if clicked, write X/Y values to Serial
    {
        Serial.print("X/Y: ");
        Serial.print(treatValue(value1));
        Serial.print(' ');
        Serial.print(treatValue(value2));
        Serial.println(' ');
    }
}