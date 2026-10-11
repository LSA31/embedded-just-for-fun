#include "mission.h"
#include "fake_platform.h"
#include "test_support.h"

void run_student_tests(void)
{
    /* Case 1: 100 Hz도 두 주기를 정확한 정수 Tick으로 표현합니다.
     * 10 ms -> 1 Tick, 250 ms -> 25 Tick. 임의의 1 kHz 하한을 넣은 오답을 검출합니다.
     */
    CollectorState state = {0};
    fake_platform_reset();
    CHECK(collector_init(&state, 100U, 77U));
    CHECK(state.sample_period == 1U);
    CHECK(state.led_period == 25U);
    fake_set_enabled(true);
    collector_step(&state, 78U);
    CHECK(state.sample_count == 1U);
    CHECK(state.last_sample == 78U);

    /* Case 2: 긴 비활성 구간에서도 기준 시각과 LED는 진행합니다.
     * 한 Tick 뒤 재개해도 과거 Sample을 몰아서 읽지 않는지 확인합니다.
     */
    CHECK(collector_init(&state, 1000U, 0U));
    fake_set_enabled(false);
    fake_platform_clear_log();
    collector_step(&state, 999U);
    CHECK(state.sample_count == 0U);
    CHECK(state.last_sample == 999U);
    CHECK(state.last_led == 999U);
    CHECK(fake.sensor_calls == 0U);
    CHECK(fake.toggle_calls == 1U);
    fake_set_enabled(true);
    fake_platform_clear_log();
    collector_step(&state, 1000U);
    CHECK(fake.sensor_calls == 0U);
    CHECK(fake.toggle_calls == 0U);
    collector_step(&state, 1009U);
    CHECK(state.sample_count == 1U);
    CHECK(state.last_sample == 1009U);

    /* Case 3: 입력 초기화가 ENABLE Port의 출력 Latch나 다른 Mode Bit를 바꾸지 않습니다. */
    fake_platform_reset();
    fake.output[PORT_ENABLE] = UINT32_MAX;
    fake.direction[PORT_ENABLE] = UINT32_MAX;
    board_io_init();
    CHECK(fake.output[PORT_ENABLE] == UINT32_MAX);
    CHECK(fake.direction[PORT_ENABLE] == (UINT32_MAX & ~ENABLE_MASK));
}
