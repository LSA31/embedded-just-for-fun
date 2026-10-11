# Timing 분석 기록

## 학습 목표와 공식 근거

`REFERENCES.md`의 자료 ID를 사용해 **학습 목표 → 자료의 위치·조건 → 찾은 사실 → 설계 → Test**를 연결합니다. 제품 사양 비교 대상은 TC387QP-160F300S, PG-LFBGA-292입니다. 실제 사용한 제품·Board Revision·Clock 설정이 다르면 차이를 기록하세요.

자료 ID: D0 Addendum, D1 Datasheet, U1 TC38x Appendix, U2 STM 설명, U3 Family Part 1, U4 Family Part 2, B1 Board, S1 Blinky 예제, S2 STM Header, S3 Port Header, S4 Scu Header. 상세 제목·Version·링크는 배포된 자료 안내를 기준으로 합니다.

| 학습 목표·확인 질문 | 자료 ID·Version·절/표/페이지 또는 File·Symbol | 적용 제품·조건 | 찾은 사실 | 설계·변경한 함수 | 검증 입력·예상 결과·실행 증거 |
| --- | --- | --- | --- | --- | --- |
| 목표 1 / GPIO Mode·Pin·극성 | | | | | |
| 목표 1 / STM Clock·Counter | | | | | |
| 목표 2 / 주기 수집·만료 판정 | | | | | |
| 목표 3 / 대기·Polling·처리 시간 | | | | | |

- 공식 자료가 정한 사실과 과제에서 정한 정책을 구분한 설명:
- 아직 확인하지 못한 조건과 추가로 필요한 근거:

## Tick 계산

100 MHz는 과제에서 제공하는 `fSTM` 조건입니다. **200 MHz는 고정값 사용을 검출하는 범용 산술의 Host 가상 입력**이며, TC387QP의 허용 STM 설정이나 실제 Board Clock을 뜻하지 않습니다. 두 입력을 실제 제품 사양으로 해석하지 마세요.

| STM Frequency | 10 ms Tick | 250 ms Tick | 계산 과정 |
| --- | --- | --- | --- |
| 100 MHz | | | |
| 200 MHz | | | |

- CPU Clock과 STM Clock을 같은 값으로 가정해도 되는가? 근거:
- `hz × ms`를 32-bit로 먼저 계산했을 때의 실패 입력·실제 값:
- 정수가 아닌 Tick 또는 표현 범위를 벗어난 값의 처리:

## 주기 판단

아래는 1 Tick = 1 ms인 별도 분석 입력입니다. 시작 기준 시각은 0, 주기는 10 Tick입니다.

| now | 실행 여부 | 호출 이후 last | 판단 근거 |
| --- | --- | --- | --- |
| 9 | | | |
| 10 | | | |
| 35 | | | |
| 36 | | | |
| 45 | | | |

- Counter Wrap 직전·직후에 비교할 값:
- 관측을 Counter 한 바퀴보다 오래 중단하면 알 수 없는 정보:
- Disabled 중 기준 시각을 갱신하는 이유:
- 250 ms Toggle 간격과 LED ON/OFF 전체 주기의 차이:
- Polling 호출이 늦어질 때 보장되는 것과 보장되지 않는 것:

## 실제 Demo 결과

`make demo` 실행 후 `make -s demo > timing.csv`로 CSV를 저장하고, 위 분석과 결과를 비교합니다.

- CSV:
- 불일치가 있었다면 근본 원인과 수정한 함수:
- 실제 시간 측정인지, 입력 시각을 넣은 Host Simulation인지:
