/*
 ******************************************************************************
 *  Copyright (c) 2015 Particle Industries, Inc.  All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************
 */

/* HC-SR04 Ping / Range finder wiring:
 * -----------------------------------
 * Particle - HC-SR04
 *      GND - GND
 *      VIN - VCC
 *       D2 - TRIG
 *       D6 - ECHO
 */

 #include "application.h"

const int cmLowLevel = 6;
const int cmHopperDepth = 12;
const int hopperLowLED = D1;
const int markPin = A1;
const int twainPin = A2;

void setup() {
    Serial.begin(115200);
    pinMode(hopperLowLED, OUTPUT);
}

void loop() {
    // Trigger pin, Echo pin, delay (ms), visual=true|info=false
    int cmDist = ping(markPin, twainPin);
    if (cmDist > cmLowLevel && cmDist < cmHopperDepth) {
      digitalWrite(hopperLowLED, HIGH);
    } else {
      digitalWrite(hopperLowLED, LOW);
    };

    Serial.println(cmDist);

    delay(1000);
}

int ping(pin_t trig_pin, pin_t echo_pin)
{
    uint32_t duration;
    int cm;
    static bool init = false;
    if (!init) {
        pinMode(trig_pin, OUTPUT);
        digitalWriteFast(trig_pin, LOW);
        pinMode(echo_pin, INPUT);
        delay(50);
        init = true;
    }

    /* Trigger the sensor by sending a HIGH pulse of 10 or more microseconds */
    digitalWriteFast(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWriteFast(trig_pin, LOW);

    duration = pulseIn(echo_pin, HIGH);

    /* Convert the time into a distance */
    // Sound travels at 1130 ft/s (73.746 us/inch)
    // or 340 m/s (29 us/cm), out and back so divide by 2
    // Ref: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf

    cm = duration / 29 / 2;
    //Serial.println(cm);
    return cm;

    //delay(wait); // slow down the output
}
