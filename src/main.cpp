#include <Arduino.h>

#define RELAY_PIN A0

#define FLOW_SENSOR_PIN 2

#define COVER_SW_PIN    3

#define SPK_PIN_A       4
#define SPK_PIN_B       5

#define FLOW_THRESHOLD_MS 500

uint8_t flowPhase;
int flowPhaseCounterMs = 0;
uint8_t spkPhase = 0;


void init_relay()
{
    digitalWrite(RELAY_PIN, LOW);
    pinMode(RELAY_PIN, OUTPUT);
}
void init_sound()
{
    digitalWrite(SPK_PIN_A, HIGH);
    digitalWrite(SPK_PIN_B, HIGH);
    pinMode(SPK_PIN_A, OUTPUT);
    pinMode(SPK_PIN_B, OUTPUT);
}

void init_sensors()
{
    pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);
    pinMode(COVER_SW_PIN, INPUT_PULLUP);
}

void setup() {
    init_relay();
    init_sensors();
    init_sound();
    pinMode(LED_BUILTIN, OUTPUT);
}

void sound_loop(bool alarm) {
    if (alarm)
    {
        digitalWrite(SPK_PIN_A, spkPhase);
        spkPhase = !spkPhase;
        digitalWrite(SPK_PIN_B, spkPhase);
    } else
    {
        digitalWrite(SPK_PIN_A, HIGH);
        digitalWrite(SPK_PIN_B, HIGH);
    }
}

void loop() {
    bool alarm = digitalRead(COVER_SW_PIN) == HIGH;
    uint8_t newFlowPhase = digitalRead(FLOW_SENSOR_PIN);
    if (flowPhase == newFlowPhase)
    {
        if (flowPhaseCounterMs > FLOW_THRESHOLD_MS)
        {
            alarm = true;
        } else
        {
            flowPhaseCounterMs ++;
        }
    } else
    {
        flowPhase = newFlowPhase;
        flowPhaseCounterMs = 0;
    }

    digitalWrite(RELAY_PIN, alarm ? LOW : HIGH);
    digitalWrite(LED_BUILTIN, alarm ? HIGH : LOW);
    sound_loop(alarm);
    delay(1);
}