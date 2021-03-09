%include "io64.inc"

section .text
global CMAIN
CMAIN:
    mov rbp, rsp; for correct debugging
    PRINT_STRING msg
    
    xor rax, rax
    ret
    
    ; 변수의 선언 및 사용
    ; 변수는 그냥 데이터를 저장하는 바구니 [ ]
    ; - 처음에 바구니 사용하겠다 선언 (이름과 크기 지정)
    
    ; 메모리에는 구분할 수 있도록 주소(번지수)가 있다
    
    ; 초기화 된 데이터
    ; [변수이름] [크기] [초기값]
    ; [크기] db(1) dw(2) dd(4) dq(8)  define ~
    
section .data
    a db 0x11, 0x11, 0x11, 0x11    ; [0x11]
    
    b dd 0x12345678 ; 까보면 리틀엔디언 방식으로 저장됨
    ; 장단점이 교차한다
    ; - 리틀 엔디언 : 캐스팅에 유리하다, 예를 들어 1바이트만 추출하려고 하면 맨 앞에 있는 것만 가지고 오면 된다.
    ; - 빅 엔디언 : 숫자 비교에 유리하다
    
    
    ; 초기화 되지 않은 데이터
    ; [변수이름] [크기] [개수]
    ; [크기] resb(1) resw(2) resd(4) resq(8) reserve일 것으로 추정
    
section .bss
    e resb 10