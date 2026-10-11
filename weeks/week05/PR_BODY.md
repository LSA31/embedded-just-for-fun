# [05회차] YOUR_GITHUB_ID TC387QP 주기 수집 개선

05회차에 한해 공개된 [한국어 해설 코드](https://github.com/zinee-u/embedded-just-for-fun/tree/main/weeks/week05/reference)를 참고할 수 있습니다. 아래 내용은 자신의 제출 코드와 실제 실행 결과를 기준으로 작성합니다. 경로는 과제 폴더 `weeks/week05/`를 기준으로 합니다.

## 요청을 해석한 내용

- GPIO의 극성·Mode·Bit 보존:
- 사용한 `stm_hz` 조건과 10 ms·250 ms의 Tick:
- 지연·비활성·Wraparound·재초기화 정책:

## 학습 목표에서 설계와 Test까지

사양 비교 대상은 TC387QP-160F300S, PG-LFBGA-292입니다. 제품·Board Revision·Clock 조건이 달라지면 적용 가능성을 따로 설명합니다. 자료의 상세 위치와 Version은 `TIMING.md`에 기록하고 아래 표에서 변경 및 검증과 연결해 주세요.

| 학습 목표·확인 질문 | 자료 ID·Version·절/표/페이지 또는 File·Symbol | 적용 조건·찾은 사실 | 설계·변경한 함수 | 검증 입력·예상 결과·Log 위치 |
| --- | --- | --- | --- | --- |
| 목표 1 / GPIO·STM 설정 | | | | |
| 목표 2 / 주기 수집 | | | | |
| 목표 3 / 지연·검증 범위 | | | | |

자료 ID는 `REFERENCES.md`를 따릅니다: D0 Addendum, D1 Datasheet, U1 TC38x Appendix, U2 STM 설명, U3 Family Part 1, U4 Family Part 2, B1 Board, S1 Blinky 예제, S2 STM Header, S3 Port Header, S4 Scu Header.

- 공식 자료가 정한 사실과 과제의 제품 정책을 구분한 설명:
- 확인하지 못한 근거 또는 실제 Board에서 추가 검증할 조건:

## 발견한 모든 근본 원인

| File과 함수 | 실패 입력 또는 호출 순서 | 초안의 실제 결과 | 근본 원인 | 변경 내용 | 확인한 Test |
| --- | --- | --- | --- | --- | --- |
| 직접 작성 | | | | | |

한 행의 수정으로 다른 원인을 가리지 않았는지 전체 초안을 다시 확인했습니다.

## 공개 해설을 활용해 확인한 내용

- 참고한 해설 File·함수와 이해한 동작:
- 직접 고른 실패 입력 또는 호출 순서, 예상 결과와 초안의 실제 결과:
- 수정이 필요한 이유와 연결한 공식 자료 또는 제품 요구사항:
- 해설을 읽은 뒤 추가로 확인하고 싶었던 조건:

해설과 코드의 모양을 비교하는 데 그치지 않고, 각 변경이 어떤 실패를 막는지 근거와 실행 결과로 설명합니다.

## 직접 추가한 Test

해설의 Test를 그대로 복사하는 대신 자신이 확인하려는 조건을 선택해 최소 2개 작성합니다. 제공 Test의 계약은 유지합니다.

| Test 이름·위치 | 선택한 입력·호출 순서 | 이 조건을 고른 이유 | 예상 결과 | 실제 결과·Log 위치 |
| --- | --- | --- | --- | --- |
| Test 1 | | | | |
| Test 2 | | | | |

## Timing과 검증

- `make test` 결과와 Exit code:
- `make demo` 결과: 가상 시각을 주입한 Host 결과입니다.
- 추가 Test 최소 2개의 목적:
- Timing 시나리오의 센서 읽기 시작 간격과 처리 시간의 합:
- 예상 주기와 측정값을 구분한 설명:
- 실행하지 않은 범위: 실제 TC387QP Build, Flash, 실측 등 해당 사항을 정확히 기재

## Commit과 Review

- 구현 Commit SHA와 목적:
- 검증·문서 Commit SHA와 목적:
- 변경 경로가 `submissions/week05/YOUR_GITHUB_ID/` 안인지 확인:
- 같은 Branch에 수정 Commit을 추가해 Review에 대응합니다.
