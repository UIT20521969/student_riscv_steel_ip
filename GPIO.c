#include "rvsteel_gpio.h"

#define LED_MASK GPIO_PIN0_MASK
#define BUTTON_MASK GPIO_PIN1_MASK

int main() {
    GpioDevice gpio; // Khai báo một biến GPIO
    gpio_enable_output(&gpio, LED_MASK); // Cấu hình LED là đầu ra
    gpio_enable_input(&gpio, BUTTON_MASK); // Cấu hình nút bấm là đầu vào

    while (1) {
        if (gpio_is_set(&gpio, BUTTON_MASK)) { // Nếu nút bấm được nhấn
            gpio_set(&gpio, LED_MASK); // Bật LED
        } else {
            gpio_clear(&gpio, LED_MASK); // Tắt LED
        }
    }

    return 0;
}
