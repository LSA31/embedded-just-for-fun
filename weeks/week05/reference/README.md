# 05회차 한국어 해설 코드

05회차는 코드와 주석을 읽으며 스스로 학습할 수 있도록 해설 구현을 함께 공개합니다. 각 주석은 **근본 원인 → 수정 원리 → 경계 조건과 근거**를 연결합니다. 실제 TC387QP Firmware가 아니라, 동일한 과제 API를 사용하는 C11 Host 모델입니다.

## 읽는 순서

1. [과제 요구사항](../README.md)과 [공식 자료](../REFERENCES.md)에서 목표·조건·근거를 확인합니다.
2. 아래 세 C 파일을 읽고 같은 이름의 [원본 Starter](../starter/) 함수와 비교합니다.
3. 실패하는 입력과 수정 이유를 자신의 말로 정리하고, 경계에서 어떤 결과가 나올지 먼저 예상합니다.
4. 해설 구현을 실행해 예상과 비교한 뒤, Starter를 자기 제출 폴더에 복사해 개선합니다.
5. 직접 선정한 조건으로 Test를 최소 2개 추가하고, 자기 환경의 실행 결과를 [기존 PR 방식](../SUBMISSION.md)으로 제출합니다.

해설과 비슷한 구현을 사용해도 됩니다. 다만 코드 복사만으로 완료되는 과제가 아니며, 왜 필요한 수정인지와 어떤 입력으로 확인했는지를 PR에서 설명해야 합니다. 해설의 추가 Test나 Log를 자신의 검증 결과로 그대로 제출하지 않습니다.

| File | 확인할 내용 |
| --- | --- |
| [src/timebase.c](src/timebase.c) | 64-bit 곱셈, 정수 Tick, 실패 출력 보존, Wraparound와 정확한 경계 |
| [src/board_io.c](src/board_io.c) | Active LOW, HIGH Latch와 Output 순서, Pull-up, 다른 Bit 보존 |
| [src/collector.c](src/collector.c) | 상태 초기화, ENABLE 판정, 비활성 중 기준 갱신, 독립적인 LED 주기 |
| [tests/test_student.c](tests/test_student.c) | 추가 Test 세 Case의 목적과 검증식 |
| [host/demo.c](host/demo.c) | 호출 시각과 입력을 주입해 동작을 관찰하는 방법 |

`starter/`와 이 `reference/`는 과제 원본입니다. 풀이 PR에서는 자기 `submissions/week05/YOUR_GITHUB_ID/`만 수정합니다.

## 실행

저장소 루트에서 아래 명령을 실행합니다. C11 Compiler와 GNU Make가 필요합니다.

```sh
cd weeks/week05/reference
make test
make demo
```

제공 고정 Test 355개 검사와 추가 예시 Test 17개 검사가 모두 통과하면 `372 checks, 0 failures`를 출력합니다. 이는 해설 구현의 결과이며 자기 풀이에서는 추가 Test에 따라 검사 수가 달라질 수 있습니다. Starter는 의도된 결함 때문에 처음에는 실패합니다.

Windows에서는 GCC·Make를 설치한 환경에서 `make CC=gcc EXEEXT=.exe test`와 `make CC=gcc EXEEXT=.exe demo`를 사용할 수 있습니다. Git Bash만으로 Compiler가 설치되는 것은 아닙니다. 아래 기록은 macOS 실행 결과이며 Windows에서 실행한 기록은 아닙니다.

## 주석 번호와 근본 원인

| 번호 | 초안의 근본 원인 | 수정 원리 |
| --- | --- | --- |
| T1 | 곱셈 중간값의 32-bit Overflow | 곱셈 전에 uint64_t로 Cast |
| T2 | 소수 Tick을 버리고 성공 처리 | 1000으로 나눈 나머지 검사 |
| T3 | 허용 Tick 상한 검사 누락 | 넓은 값에서 1~INT32_MAX 검사 |
| T4 | 실패 시에도 출력값 변경 | 모든 검사 후 out에 저장 |
| P1 | 정확한 만료 시각을 제외하는 `>` | `>=`로 경계 포함 |
| P2 | `last + period`의 Wraparound | unsigned 경과 차이 비교 |
| P3 | `last += period`로 과거 기한 유지 | 현재 now부터 재시작 |
| P4 | 무효한 큰 period 허용 | API 상한을 먼저 검사 |
| G1 | Latch 준비 전 Output 전환 | HIGH를 먼저 준비 |
| G2 | Active LOW LED를 LOW로 초기화 | OFF에 해당하는 HIGH 선택 |
| G3 | ENABLE Pull-up 비활성 | Input Pull-up 설정 |
| G4 | HIGH를 수집 허용으로 해석 | LOW를 true로 변환 |
| G5 | 전체 Port Bit Toggle | LED_MASK만 변경 |
| I1 | 전달된 stm_hz 대신 고정값 사용 | 실제 인자로 두 주기 계산 |
| I2 | 재초기화에서 과거 상태 유지 | 매 시도 전체 Field 초기화 |
| I3 | 주기 검증 전 GPIO 호출 | 두 계산의 성공 후 I/O |
| C1 | ready 확인 없이 I/O | 준비되지 않은 상태에서 즉시 반환 |
| C2 | 비활성일 때 전체 함수 종료 | 기준 시각은 갱신하고 센서 읽기만 제한 |
| C3 | 수집 분기에 LED 판정 종속 | 별도의 LED 만료 판정 |
| C4 | 횟수에 1을 대입 | 실제 읽기마다 1 증가 |
| C5 | 매번 250 ms Delay 요청 | 대기 없이 이번 Step의 작업 후 반환 |

`NULL` 검사처럼 초안에서 이미 옳았던 부분까지 결함으로 세지 않습니다. 요구사항을 읽고 각 변경을 실제 반례와 연결해 설명합니다.

## 근거와 검증 범위

[공식 자료 안내](../REFERENCES.md)의 ID·Version·절·인쇄 페이지를 사용합니다.

- D1의 Package별 Pin 정보와 B1 §3.15의 Board 배선을 함께 읽습니다. P13.0/D107의 Active LOW는 참조 Board의 연결입니다.
- U3 §10.5.1.3의 STM Clock 경로와 U4 §27.4.2의 TIM0 하위 32-bit 읽기를 시간 계산에 연결합니다.
- 정수 Tick·INT32_MAX 상한·실패 출력 보존·지연 후 한 번 처리 정책은 과제의 Software 요구사항입니다.
- 100 MHz는 과제 입력이며 200 MHz는 가상 산술 Test입니다. 실제 부품의 허용 STM Clock이나 Reset 기본값을 뜻하지 않습니다.
- 경과 차이는 실제 경과가 `2^32` Tick 미만이고 같은 Counter와 일정한 Clock을 사용하는 조건에서 해석합니다.
- Host Demo는 정해진 시각을 주입합니다. 실제 Board의 Clock·전압·Pin 파형을 측정하지 않습니다. Startup·Watchdog·Interrupt·Multi-core·Debounce·ADC는 이번 범위 밖입니다.

공개본의 실행 기록은 [VERIFICATION.md](VERIFICATION.md)에 있습니다.
