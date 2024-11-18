#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <oled.h>
#include "esp_log.h"
#include "valve.h"
#include "button.h"


// 按键事件回调函数
void button_event_callback(button_id_t button, button_state_t state)
{
    if (button == BUTTON1 && state == BUTTON_PRESSED)
    {
        // 按键1被按下，切换状态
        valve_control_set_state((valve_state_t)((valve_control_get_state() + 1) % VALVE_STATE_DEFAULT));
    }
    else if (button == BUTTON2 && state == BUTTON_PRESSED)
    {
        // 按键2被按下，开启或关闭当前状态
        if (valve_control_get_state() == VALVE_STATE_DEFAULT)
        {
            // 开启当前状态
            valve_control_set_state((valve_state_t)((valve_control_get_state() + 1) % VALVE_STATE_DEFAULT));
        }
        else
        {
            // 关闭当前状态
            valve_control_set_state(VALVE_STATE_DEFAULT);
        }
    }
}
void app_main(void)
{
    // IIC总线主机初始化
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");

    
    // 初始化按键模块
    button_init();

    // 初始化电磁阀模块
    valve_control_init();
    // OLED屏幕初始化
    OLED_Init();


    // 显示汉字
    // OLED_ShowCHinese(0 * 18, 0, 0);
    // OLED_ShowCHinese(1 * 18, 0, 1);
    // OLED_ShowCHinese(2 * 18, 0, 2);

    // 显示单个字符
    // OLED_ShowChar(0, 2, 'A', 16);

    // 显示字符串
    OLED_ShowString(0, 0, "Haoshui TestWRO", 16);
        OLED_ShowString(0, 2, "CrState:", 16);
    OLED_ShowString(0, 4, "Power:", 16);

    // 显示数字
    OLED_ShowNum(0, 6, 8300, 6, 16);
   // OLED_ShowNum(0, 6, 8300, 6, 16);

      // 循环更新 OLED 显示状态
    while (1) {
        // 获取当前电磁阀状态并显示
        char state_str[16];
        snprintf(state_str, sizeof(state_str), "%d", valve_control_get_state());
        OLED_ShowString(72, 2, state_str, 16);

        // 延时一段时间再更新，这里假设为1秒
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    // 删除IIC设备
    // ESP_ERROR_CHECK(i2c_driver_delete(I2C_MASTER_NUM));
    // ESP_LOGI(TAG, "I2C unitialized successfully");
}