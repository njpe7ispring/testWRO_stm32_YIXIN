#ifndef BUTTON_H
#define BUTTON_H

typedef enum {
    BUTTON1,  // 按键1
    BUTTON2,  // 按键2
    BUTTON_MAX
} button_id_t;

typedef enum {
    BUTTON_RELEASED,
    BUTTON_PRESSED
} button_state_t;

// 按键事件回调函数类型定义
typedef void (*button_event_callback_t)(button_id_t button, button_state_t state);

// 外部声明按键事件回调函数
extern void button_event_callback(button_id_t button, button_state_t state);

// 按键初始化函数
void button_init(void);

#endif // BUTTON_H