extern volatile unsigned long timer0_millis;
void setup(){
    Serial.begin(9600);
    
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    pinMode(11, INPUT);
  
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
}

const int WAITING = 1;
const int LOCKED = 2;
const int UNLOCKED = 3;
int state = LOCKED;

int movement = 0;
long timer = 0;
int digitinput = 0;

String correctPass = "0101";
String current = "";

void loop()
{
    int btn1 = digitalRead(6);
    int btn2 = digitalRead(7);

    int sensor = digitalRead(11);

    if (sensor == LOW)
    movement = 0;

    switch (state)
    {
    case LOCKED:
        digitalWrite(10, HIGH);  //ROD PAA
        if ((sensor == HIGH) && (!movement))
        {	
          	movement = 1;
          	delay(1000);
            state = WAITING;
            digitalWrite(10, LOW);  //ROD AV
        }
        break;
    
    case WAITING:
        digitalWrite(9, HIGH);  //GUL PAA
        timer = millis();
        if (timer > 10000)
        {
            if (digitinput < 2)
            {
                digitalWrite(9, LOW);  //GUL AV
                movement = 0;
                digitinput = 0;
            
                //reset millis()
                noInterrupts ();
                timer0_millis = 0;
                interrupts ();

                state = LOCKED;
            }
            
        }
        else if (btn1 == HIGH)
        {
            current += "0";
            digitinput++;

            digitalWrite(9, LOW);  //GUL AV
            delay(500);
            digitalWrite(9, HIGH);  //GUL PAA
        }
        else if (btn2 == HIGH)
        {
            current += "1";
            digitinput++;

            digitalWrite(9, LOW);  //GUL AV
            delay(500);
            digitalWrite(9, HIGH);  //GUL PAA
        }
        else if (current.equals(correctPass))
        {
            state = UNLOCKED;
            current = "";
          	digitinput = 0;
        }

        else if ((digitinput >= 4) && !(current.equals(correctPass))){
            digitalWrite(9, LOW);  //GUIL AV
            digitalWrite(10, HIGH);  //ROD PAA
            delay(500);
            digitalWrite(10, LOW);  //ROD AV
            delay(500);
            current = "";
            digitinput = 0;
            movement = 0;
            state = LOCKED;
        }
        
        break;

    case UNLOCKED:

        digitalWrite(9, LOW);  //GUL AV
        digitalWrite(8, HIGH);  //GRONN PAA

        delay(7000);

        digitalWrite(8, LOW);  //GRONN AV
      	movement = 0;
        state = LOCKED;
        break;

    default:
        break;
    }//end switch
    
}//end loop
