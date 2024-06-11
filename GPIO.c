#include "rvsteel_soc.h"

// Địa chỉ base của GPIO
#define GPIO_BASE_ADDRESS ((GpioDevice *)0x80020000U)

// Định nghĩa các chân GPIO cho nút bấm và LED
#define BUTTON_PIN GPIO_PIN0_MASK
#define LED_PIN GPIO_PIN1_MASK

int main() {
    // Khởi tạo con trỏ GPIO với địa chỉ base
    GpioDevice *GPIO = GPIO0_BASE;
    
    // Cấu hình chân LED là output và chân nút bấm là input
    gpio_enable_output(GPIO, LED_PIN);
    gpio_enable_input(GPIO, BUTTON_PIN);
    
    while (1) {
        // Đọc trạng thái của nút bấm
        if (gpio_is_set(GPIO, BUTTON_PIN)) {
            // Nếu nút bấm được nhấn, bật LED
            gpio_set(GPIO, LED_PIN);
        } else {
            // Nếu nút bấm không được nhấn, tắt LED
            gpio_clear(GPIO, LED_PIN);
        }
    }
    
    return 0;
}
