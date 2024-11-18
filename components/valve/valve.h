#ifndef VALVE_CONTROL_H
#define VALVE_CONTROL_H

#include <stdint.h>

// 电磁阀状态枚举
typedef enum {
    VALVE_STATE_PURE_WATER,      // 制水（纯水）
    VALVE_STATE_ULTRAFILTRATION, // 制水（超滤）
    VALVE_STATE_FLUSH_F1,        // 冲刷-F1（WSP前置冲洗）
    VALVE_STATE_FLUSH_F2,        // 冲刷-F2（超滤膜冲洗）
    VALVE_STATE_FLUSH_F3,        // 冲刷-F3（RO膜冲洗）
    VALVE_STATE_FLUSH_F4,        // 冲刷-F4（反冲洗）
    VALVE_STATE_FLUSH_F5,        // 冲刷-F5（反冲洗）
    VALVE_STATE_FLUSH_F6,        // 冲刷-F6（反冲洗）
    VALVE_STATE_DEFAULT          // 默认状态
} valve_state_t;

// 电磁阀编号枚举
typedef enum {
    FV1 = 0,
    FV2,
    FV3,
    FV4,
    FV5,
    FV6,
    FV7,
    FV_COUNT = 7
} valve_id_t;

// 初始化电磁阀模块
void valve_control_init(void);

// 设置电磁阀状态
void valve_control_set_state(valve_state_t state);

// 获取当前电磁阀状态
valve_state_t valve_control_get_state(void);

// 电磁阀控制函数
void valve_control(uint8_t state);

#endif // VALVE_CONTROL_H