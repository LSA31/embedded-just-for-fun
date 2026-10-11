# 05회차 공개 코드 검증

2026-10-11, macOS arm64 / Apple clang 21.0.0 / GNU Make 3.81에서 공개 폴더의 파일을 직접 Build하고 실행했습니다.

| 대상 | Build | Test 실행 파일 결과 | Demo |
| --- | --- | --- | --- |
| `reference/` | Exit 0 | 372 checks, 0 failures / Exit 0 | Exit 0 |
| `starter/` | Exit 0 | 355 checks, 167 failures / Exit 1 | Exit 0 |

Starter의 실패는 원본에 남긴 의도된 결함을 검출한 결과입니다. 실패 Test를 `make test`로 실행하면 Make는 Exit 2를 반환할 수 있습니다. Demo 실행 성공은 요구사항 충족과 별개입니다.

각 폴더에서 실행한 명령:

```sh
make -B all
./build/mission-tests
./build/mission-demo
```

기본 Compile 옵션은 `-std=c11 -Wall -Wextra -Wpedantic -Werror -O2`입니다. 고정 Test 355개 검사와 해설의 추가 예시 17개 검사를 함께 실행했습니다. 실제 수집이 없는 호출, 실패 출력 보존, 정확한 경계, Wraparound, 재초기화, GPIO Bit 보존, 비활성 입력, 지연 후 재개를 검증합니다.

해설 Demo의 마지막 행은 `500,1,5,109,0,0`입니다. 입력한 시각에 따른 Host 모델의 결과이며 실제 500 ms를 기다려 측정한 값이 아닙니다.

실제 TC387QP Build·Flash·Clock·Pin 파형은 검증하지 않았습니다. Windows와 Linux에서도 실행하지 않았습니다. 제출에는 각자 실제로 사용한 환경과 실행 결과를 기록합니다.
