
#include "MODULE_DUALKMETER.h"
#include <M5GFX.h>
#include <M5Stack.h>

M5GFX display;
M5Canvas canvas(&display);
MODULE_DUALKMETER d_kmeter;
uint8_t error_status  = 0;
uint8_t kmeter_switch = 0;

char temp_celsius[9]          = {0};
char temp_fahrenheit[9]       = {0};
char inter_temp_celsius[9]    = {0};
char inter_temp_fahrenheit[9] = {0};

long delay_time = 0;

void setup() {
    M5.begin();
    display.begin();
    canvas.setColorDepth(8);
    canvas.setFont(&fonts::efontCN_12);
    canvas.setTextSize(2);
    canvas.setTextColor(ORANGE);
    canvas.createSprite(display.width(), display.height());
    canvas.pushSprite(0, 0);
    d_kmeter.begin(&Wire, 0x11, 21, 22, 100000L);
    delay_time = millis() + 1000;
}

void loop() {
    if (millis() > delay_time) {
        canvas.fillSprite(0);
        canvas.setTextColor(ORANGE);
        if (kmeter_switch == 0)
            canvas.drawString("DualKmeter (Kmeter:1)", 40, 0);
        else if (kmeter_switch == 1)
            canvas.drawString("DualKmeter (Kmeter:2)", 40, 0);
        canvas.setCursor(10, 50);
        error_status = d_kmeter.getReadyStatus();
        if (error_status == 0) {
            canvas.printf("Temp: %.2fC; %.2fF",
                          ((float)(d_kmeter.getCelsiusTempValue())) / 100,
                          ((float)(d_kmeter.getFahrenheitTempValue())) / 100);
            canvas.setCursor(10, 80);
            canvas.printf(
                "SocTemp: %.2fC; %.2fF",
                ((float)(d_kmeter.getInternalCelsiusTempValue())) / 100,
                ((float)(d_kmeter.getInternalFahrenheitTempValue())) / 100);
            canvas.setCursor(10, 110);
            d_kmeter.getCelsiusTempString(temp_celsius);
            d_kmeter.getFahrenheitTempString(temp_fahrenheit);
            canvas.printf("Temp(str): %sC; %sF", temp_celsius, temp_fahrenheit);
            canvas.setCursor(10, 170);
            d_kmeter.getInternalCelsiusTempString(inter_temp_celsius);
            d_kmeter.getInternalFahrenheitTempString(inter_temp_fahrenheit);
            canvas.printf("SocTemp(str): %sC; %sF", inter_temp_celsius,
                          inter_temp_fahrenheit);
        } else
            canvas.printf("Error detected: %d", error_status);
        canvas.drawString("Kmeter1", 30, 210);
        canvas.drawString("Kmeter2", 230, 210);
        canvas.pushSprite(0, 0);
        delay_time = millis() + 200;
    }

    M5.update();
    if (M5.BtnA.wasPressed()) {
        d_kmeter.setKmeter(0);
        kmeter_switch = 0;
    } else if (M5.BtnB.wasPressed()) {
        d_kmeter.setKmeter(1);
        kmeter_switch = 1;
    }
}
