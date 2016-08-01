#include <Arduino.h>
#include <HardwareSerial.h>

HardwareSerial Serial;

#include <PWM.h>

//#define DEBUG_MODE
//#define HIGHT_SPEED

const int SERVO_PIN_1 = 9;
const int SERVO_PIN_2 = 10;
const int SERVO_INIT1 = 1;
const int SERVO_INIT2 = 1;
const int SERVO_MAX_1 = 120;
const int SERVO_MAX_2 = 120;

const int SERVO_FREQU = 333;    // frequency, 333 Hz

int lastVal[2] = {SERVO_INIT1, SERVO_INIT2};
String recvData;

// Socket xxxx,yyyy

void servoWrite(int pin, int angl, int maxAngl = 120)
{
    int realValue = map(angl, 0, maxAngl, 0, 255);
    pwmWriteHR(pin, realValue);
    delayMicroseconds(100);
}

void justMov(int servoIdx, int val, int maxVal = 120)
{
    // For security
    val = val > maxVal - 1 ? maxVal - 1 : val;
    val = val <   1 ?   1 : val;

    if(lastVal[servoIdx] < val)
        for(int i = lastVal[servoIdx]; i < val; i++)
        {
            servoWrite(SERVO_PIN_1, i, maxVal);
        }
    else
        for(int i = lastVal[servoIdx]; i > val; i--)
        {
            servoWrite(SERVO_PIN_1, i, maxVal);
        }

#ifdef DEBUG_MODE
    Serial.print(servoIdx);
    Serial.print("       ");
    Serial.println(val);
#endif

    lastVal[servoIdx] = val;
}

bool parseCmd(String recv, int &val1, int &val2)
{

    String str1, str2;
    str1 = str2 = "";
    bool splitFlag = false;
    for(int i = 0; i < recv.length(); i++)
    {
        char c = recv[i];
        if(c == ',')
            splitFlag = true;
        else
        {
            if(splitFlag)
                str2 += c;
            else
                str1 += c;
        }
    }
#ifdef DEBUG_MODE
    Serial.println(str1);
    Serial.println(str2);
    Serial.println("=============");
#endif
    val1 = str1.toInt();
    val2 = str2.toInt();

    return splitFlag; // Have split successfully
}

void setup()
{
    InitTimersSafe();
    Serial.begin(9600);

    bool setup1 = SetPinFrequencySafe(SERVO_PIN_1, SERVO_FREQU);
    bool setup2 = SetPinFrequencySafe(SERVO_PIN_2, SERVO_FREQU);

#ifdef DEBUG_MODE
    if(setup1) Serial.println("Servo 1 setup successfully!");
    else       Serial.println("Servo 1 setup failed!");
    if(setup2) Serial.println("Servo 2 setup successfully!");
    else       Serial.println("Servo 2 setup failed!");
#endif

    servoWrite(SERVO_PIN_1, SERVO_INIT1, SERVO_MAX_1);
    servoWrite(SERVO_PIN_2, SERVO_INIT2, SERVO_MAX_2);
}

void loop()
{
    recvData = "";
//    while (Serial.available())
//    {
//        recvData += (char)Serial.read();
//        delay(2);
//    }

//    if(recvData.length() > 0)
    {
#ifdef DEBUG_MODE
        Serial.println(recvData);
        Serial.println("********");
#endif
        int ang1, ang2;
        int angl[4] = {0, 45, 90, 45};
        //if(parseCmd(recvData, ang1, ang2))
        {
            for(int i = 0; i < 4; i++)
            {
            justMov(0, angl[i], SERVO_MAX_1);
            //justMov(1, angl[i], SERVO_MAX_2);
            }
#ifdef DEBUG_MODE
            Serial.print(ang1);
            Serial.print("  ");
            Serial.print(ang2);
            Serial.println();
#endif
        }
    }
}
