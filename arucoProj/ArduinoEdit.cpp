#include <Arduino.h>
#include <HardwareSerial.h>

HardwareSerial Serial;

#include <Servo.h>

const int SERVO_PIN_1 = 12;
const int SERVO_PIN_2 = 11;
const int SERVO_INIT1 = 1;
const int SERVO_INIT2 = 1;

int lastVal[2] = {SERVO_INIT1, SERVO_INIT2};

Servo servo[2];
String recvData;

// Socket xxxx,yyyy

void justMov(int servoIdx, int val)
{
    // For security
    val = val > 179 ? 179 : val;
    val = val <   1 ?   1 : val;

    if(lastVal[servoIdx] < val)
        for(int i = lastVal[servoIdx]; i < val; i++)
        {
            servo[servoIdx].write(i);
            delay(2);
        }
    else
        for(int i = lastVal[servoIdx]; i > val; i--)
        {
            servo[servoIdx].write(i);
            delay(2);
        }

    Serial.print(servoIdx);
    Serial.print("       ");
    Serial.println(val);

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
    Serial.println(str1);
    Serial.println(str2);
    Serial.println("=============");
    val1 = str1.toInt();
    val2 = str2.toInt();

    return splitFlag; // Have split successfully
}

void setup()
{
    Serial.begin(9600);
    servo[0].attach(SERVO_PIN_1);
    servo[1].attach(SERVO_PIN_2);

    servo[0].write(SERVO_INIT1);
    servo[1].write(SERVO_INIT2);
    Serial.println("It's ok!");
}

void loop()
{
  recvData = "";
    while (Serial.available())
    {
        recvData += (char)Serial.read();
        delay(2);
    }

    if(recvData.length() > 0)
    {
      Serial.println(recvData);
      Serial.println("********");
        int ang1, ang2;
        if(parseCmd(recvData, ang1, ang2))
        {
            justMov(0, ang1);
            justMov(1, ang2);

            Serial.print(ang1);
            Serial.print("  ");
            Serial.print(ang2);
            Serial.println();
        }
    }
}
