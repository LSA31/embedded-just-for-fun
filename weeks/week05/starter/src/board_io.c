#include "mission.h"
#include "platform.h"

void board_io_init(void)
{
    platform_port_output_pushpull(PORT_LED, LED_MASK);
    platform_port_write(PORT_LED, 0U, LED_MASK);
    platform_port_input(PORT_ENABLE, ENABLE_MASK, false);
}

bool board_collection_enabled(void)
{
    return platform_port_read(PORT_ENABLE, ENABLE_MASK);
}

void board_led_toggle(void)
{
    platform_port_toggle(PORT_LED, UINT32_MAX);
}
