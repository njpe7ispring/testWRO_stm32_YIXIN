#include "valve.h"
#include "driver/gpio.h"
#include "esp_log.h"

// 电磁阀引脚定义
const uint8_t valve_pins[FV_COUNT] = {41, 40, 39, 38, 48, 47, 21};

// 电磁阀状态表
const uint8_t valve_states_table[9][FV_COUNT] = {
    {1, 1, 0, 0, 0, 0, 0}, // 制水（纯水）
    {1, 1, 1, 0, 0, 0, 0}, // 制水（超滤）
    {1, 1, 0, 0, 0, 1, 0}, // 冲刷-F1（WSP前置冲洗）
    {1, 1, 0, 0, 1, 0, 0}, // 冲刷-F2（超滤膜冲洗）
    {1, 1, 0, 1, 0, 0, 0}, // 冲刷-F3（RO膜冲洗）
    {1, 1, 0, 0, 0, 0, 1}, // 冲刷-F4（反冲洗）
    {1, 1, 0, 0, 0, 0, 1}, // 冲刷-F5（反冲洗）
    {1, 1, 0, 0, 0, 0, 1},  // 冲刷-F6（反冲洗）
    {0, 1, 0, 0, 0, 0, 0}   //默认状态
};

// 默认状态
const uint8_t default_valve_states[FV_COUNT] = {0, 1, 0, 0, 0, 0, 0};

// 当前状态
static valve_state_t current_state = VALVE_STATE_DEFAULT;

// 初始化电磁阀模块
void valve_control_init(void)
{
    gpio_config_t io_conf;
    for (int i = 0; i < FV_COUNT; i++)
    {
        // 禁用中断
        io_conf.intr_type = GPIO_INTR_DISABLE;
        // 设置为输出模式
        io_conf.mode = GPIO_MODE_OUTPUT;
        // 设置引脚位掩码
        io_conf.pin_bit_mask = (1ULL<<valve_pins[i]);
        // 禁用上拉
        io_conf.pull_down_en = 0;
        // 禁用下拉
        io_conf.pull_up_en = 0;
        // 应用配置
        gpio_config(&io_conf);
        // 设置GPIO的初始电平状态
        gpio_set_level(valve_pins[i], default_valve_states[i]);
    }
}

// 设置电磁阀状态
void valve_control_set_state(valve_state_t state)
{
    if (state == VALVE_STATE_DEFAULT)
    {
        for (int i = 0; i < FV_COUNT; i++)
        {
            gpio_set_level(valve_pins[i], default_valve_states[i]);
        }
    }
    else
    {
        for (int i = 0; i < FV_COUNT; i++)
        {
            gpio_set_level(valve_pins[i], valve_states_table[state][i]);
        }
    }
    current_state = state;
}

// 获取当前电磁阀状态
valve_state_t valve_control_get_state(void)
{
    return current_state;
}