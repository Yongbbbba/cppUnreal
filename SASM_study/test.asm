%include "io64.inc"

section .text
global CMAIN
CMAIN:
    mov rbp, rsp; for correct debugging
    
    ; 쉬프트(shift) 연산, 논리(logical) 연산
    mov eax, 0x12345678
    PRINT_HEX 4, eax
    NEWLINE
    shl eax, 8
    PRINT_HEX 4, eax
    NEWLINE
    shr eax, 8
    PRINT_HEX 4, eax
    NEWLINE
    ; 곱셈/나눗셈에 사용 가능
    ; 게임서버에서 objectID를 만들어줄 때
    
    ;논리 연산
    ; not and or xor
    
    ; 조건A : 잘생겼다
    ; 조건B : 키가 크다 
    
    ; not A : 잘 생겼다의 반대
    ; A and B : 잘생겼고 키도 크고
    ; A or B : 잘생겼거나 키가 크거나 
    ; A xor B : 잘생기고 작거나 or 못생기고 크거나 = 1 -> 둘다 1이거나 둘다 0이면 0, 아니면 1
    
    mov al, 0b10010101
    mov bl, 0b01111100
    
    ; 0b0001 0100 = 0x14
    and al, bl ; al = al and bl
    PRINT_HEX 1, al
    NEWLINE
    
    ; 0b1110 1011 = 0xeb
    not al
    PRINT_HEX 1, al
    NEWLINE
    
    ; 응용 사례 : bitflag(특정 비트를 검사하는 방법)
    mov al, 0b10010101
    mov bl, 0b01111100
    
    NEWLINE
    PRINT_HEX 1, al
    NEWLINE
    xor al, bl
    PRINT_HEX 1, al
    NEWLINE
    xor al, bl
    PRINT_HEX 1, al
    NEWLINE
    ; 동일한 값으로 xor 두 번하면 자기 자신으로 되돌아오는 특성이 있다.
    ; 암호학에서 유용하다! (대칭키 방식)
    
    ; mov al, 0
    xor al, al
    PRINT_HEX 1, al ; 무조건 0이 나옴
    
    
    
    xor rax, rax
    ret
    
    ; 변수의 선언 및 사용
    ; 변수는 그냥 데이터를 저장하는 바구니 [ ]
    ; - 처음에 바구니 사용하겠다 선언 (이름과 크기 지정)
    
    ; 메모리에는 구분할 수 있도록 주소(번지수)가 있다
    
    ; 초기화 된 데이터
    ; [변수이름] [크기] [초기값]
    ; [크기] db(1) dw(2) dd(4) dq(8)  define ~
    
; section .data
   
    
    ; 초기화 되지 않은 데이터
    ; [변수이름] [크기] [개수]
    ; [크기] resb(1) resw(2) resd(4) resq(8) reserve일 것으로 추정
    
section .bss
    num resb 1