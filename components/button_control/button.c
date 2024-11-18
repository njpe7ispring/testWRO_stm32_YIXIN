#include "button.h"
#include "driver/gpio.h"
#include "esp_intr_alloc.h"

#define BUTTON1_GPIO 4  // 假设按键1连接到GPIO 4
#define BUTTON2_GPIO 5  // 假设按键2连接到GPIO 5

#ifndef IRAM_ATTR
#define IRAM_ATTR __attribute__((section(".iram1")))
#endif
// 按键中断服务程序
static void IRAM_ATTR button_isr_handler(void* arg) {
    int io_num = (int)arg;
    if (io_num == BUTTON1_GPIO || io_num == BUTTON2_GPIO) {
        // 读取按键状态
        int level = gpio_get_level(io_num);
        // 根据按键状态调用回调函数
        if (level == 0) {  // 假设低电平为按下
            button_event_callback((button_id_t)io_num, BUTTON_PRESSED);
        } else {
            button_event_callback((button_id_t)io_num, BUTTON_RELEASED);
        }
    }
}

// 按键初始化函数
void button_init(void) {
    // 配置按键1
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_NEGEDGE,  // fu边沿触发
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = (1ULL << BUTTON1_GPIO),
        .pull_down_en = 0,
        .pull_up_en = 1
    };
    gpio_config(&io_conf);

    // 安装GPIO中断服务
    gpio_install_isr_service(0);

    // 添加GPIO中断处理程序
    gpio_isr_handler_add(BUTTON1_GPIO, button_isr_handler, (void*)BUTTON1_GPIO);

    // 配置按键2
    io_conf.intr_type = GPIO_INTR_NEGEDGE;  // fu边沿触发
    io_conf.pin_bit_mask = (1ULL << BUTTON2_GPIO);
    gpio_config(&io_conf);
    gpio_isr_handler_add(BUTTON2_GPIO, button_isr_handler, (void*)BUTTON2_GPIO);
}