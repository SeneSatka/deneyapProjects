class RGBStts
{
public:
    int ledR_pin;
    int ledG_pin;
    int ledB_pin;
    RGBStts(int _ledR_pin, int _ledG_pin, int _ledB_pin)
    {
        ledR_pin = _ledR_pin;
        ledG_pin = _ledG_pin;
        ledB_pin = _ledB_pin;
    }

    void closeAll()
    {
        digitalWrite(ledR_pin, LOW);
        digitalWrite(ledG_pin, LOW);
        digitalWrite(ledB_pin, LOW);
    }
    void red()
    {
        closeAll();
        digitalWrite(ledR_pin, HIGH);
    }
    void green()
    {
        closeAll();
        digitalWrite(ledG_pin, HIGH);
    }
    void blue()
    {
        closeAll();
        digitalWrite(ledB_pin, HIGH);
    }

    void success()
    {
        green();
    };
    void error()
    {
        red();
    }
    void signal(int delayMS = 500)
    {
        blue();
    }
};