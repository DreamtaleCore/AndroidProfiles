#include <Arduino.h>
#include <HardwareSerial.h>
HardwareSerial Serial;

#include <SoftwareSerial.h>

String sendMsg, recvMsg;
SoftwareSerial mySerial1(5, 6), mySerial2(12, 13);

void setup()
{
    Serial.begin(9600);
    mySerial1.begin(9600);
    mySerial2.begin(9600);
}

void loop()
{
    sendMsg = "";
    recvMsg = "";
    while (Serial.available()) {
        sendMsg += (char)Serial.read();
        delay(2);
    }

    if(sendMsg.length() > 0)
    {
        mySerial1.println(sendMsg);
        Serial.print("I send: ");
        Serial.println(sendMsg);
    }
    while (mySerial2.available()) {
        recvMsg += (char)mySerial2.read();
        delay(2);
    }
    if(recvMsg.length() > 0)
    {
        Serial.print("I recv: ");
        Serial.println(recvMsg);
    }
    //delay(20);
}
