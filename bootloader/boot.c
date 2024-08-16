#include <stdint.h>
#include "uart.h"  // Bao gồm thư viện UART

#define UART_BASE 0x80000000  // Địa chỉ cơ sở của UART
#define RAM_BASE  0x00000000  // Địa chỉ bắt đầu của RAM
#define RAM_SIZE  1024        // Kích thước RAM là 1KB

#define UART ((UartDevice *) UART_BASE)

// Hàm đọc byte từ UART
uint8_t uart_read_byte() {
    return uart_read(UART);
}

// Hàm gửi thông báo lỗi qua UART
void uart_send_error(const char *message) {
    uart_send_string(UART, message);
}

// Hàm nạp chương trình vào RAM
void load_program_into_ram() {
    uint32_t *ram_ptr = (uint32_t *)RAM_BASE;
    uint32_t size = 0;

    // Đọc kích thước chương trình từ UART (giả sử truyền kích thước trước)
    size |= uart_read_byte() << 24;
    size |= uart_read_byte() << 16;
    size |= uart_read_byte() << 8;
    size |= uart_read_byte();

    // Kiểm tra kích thước chương trình
    if (size > RAM_SIZE) {
        // Gửi thông báo lỗi qua UART
        uart_send_error("Error: Program size exceeds RAM capacity.\n");

        // Dừng lại để tránh nạp chương trình không hợp lệ
        while (1);
    }

    // Nhận dữ liệu chương trình và nạp vào RAM
    for (uint32_t i = 0; i < size; i += 4) {
        uint32_t word = 0;
        word |= uart_read_byte() << 24;
        word |= uart_read_byte() << 16;
        word |= uart_read_byte() << 8;
        word |= uart_read_byte();
        *ram_ptr++ = word;
    }

    // Chuyển điều khiển đến chương trình vừa nạp
    void (*program_start)() = (void (*)())RAM_BASE;
    program_start();  // Nhảy đến chương trình tại địa chỉ RAM_BASE
}

__attribute__((section(".boot")))
void _start() {
    uart_send_string(UART, "Startup RISC-V");
    // Gọi hàm nạp chương trình vào RAM
    load_program_into_ram();

    // Bootloader không nên trở lại đây
    while (1);
}
