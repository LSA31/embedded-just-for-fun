#include "mission.h"
#include "platform.h"
#include <stddef.h>

bool collector_init(CollectorState *state, uint32_t stm_hz, uint32_t now)
{
    if (state == NULL || stm_hz == 0U) {
        return false;
    }
    board_io_init();
    if (!ticks_from_ms(100000000U, 10U, &state->sample_period) ||
        !ticks_from_ms(100000000U, 250U, &state->led_period)) {
        return false;
    }
    state->last_sample = now;
    state->last_led = now;
    state->ready = true;
    return true;
}

void collector_step(CollectorState *state, uint32_t now)
{
    if (state == NULL) {
        return;
    }
    if (!board_collection_enabled()) {
        return;
    }
    if (period_due(now, state->sample_period, &state->last_sample)) {
        state->last_value = platform_sensor_read();
        state->sample_count = 1U;
        if (period_due(now, state->led_period, &state->last_led)) {
            board_led_toggle();
        }
    }
    platform_delay_ms(250U);
}
