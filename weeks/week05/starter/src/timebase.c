#include "mission.h"
#include <stddef.h>

/* Review draft: builds successfully but does not meet the requirements. */
bool ticks_from_ms(uint32_t hz, uint32_t ms, uint32_t *out)
{
    if (out == NULL || hz == 0U || ms == 0U) {
        return false;
    }
    *out = (hz * ms) / 1000U;
    return *out != 0U;
}

bool period_due(uint32_t now, uint32_t period, uint32_t *last)
{
    if (last == NULL || period == 0U) {
        return false;
    }
    if (now > *last + period) {
        *last += period;
        return true;
    }
    return false;
}
