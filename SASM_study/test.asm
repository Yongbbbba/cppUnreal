%include "io64.inc"

section .text
global CMAIN
CMAIN:
    mov rbp, rsp; for correct debugging
    
    ; 분기문 (if)
    ; 특정 조건에 따라서 코드 흐름을 제어하는 것
    ; ex) 스킬 버튼 눌렀는가? YES -> 스킬 사용
    ; 조건 -> 흐름
    
    ; CMP dst, src (dst가 기준), compare
    ; 비교를 한 결과물은 Flag Register 저장
    
    ; JMP [label] 시리즈, jump
    ; JMP : 무조건 jump
    ; JE : JumpEquals 같으면 jump
    ; JNE : JumpNotEquals 다르면 jump
    ; JG : JumpGreater 크면 jump
    ; JGE : JumpGreaterEquals 크거나 같으면 jump
    ; JL
    ; JLE
    
    ; 두 숫자가 같으면 1, 아니면 0을 출력하는 프로그램
    mov rax, 10
    mov rbx, 10
    
    cmp rax, rbx
    
    je LABEL_EQUAL
    
    ; je에 의해 점프를 안했다면, 같지 않다는 의미
    mov rcx, 0
    jmp LABEL_EQUAL_END
    
LABEL_EQUAL: 
    mov rcx, 1
LABEL_EQUAL_END:
    PRINT_HEX 1, rcx
    NEWLINE
    
    ; 연습 문제 : 어떤 숫자(1~100)가 짝수면 1, 홀수면 0을 출력하는 프로그램
    mov ax, 91
    
    ;  나누기 연산
    ; div reg
    ; - div bl => ax / bl (al몫 ah나머지)
    
    mov bl, 2
    div bl
    cmp ah, 0
    je L1
    mov rcx, 0
    jmp L2
    
L1:
    mov rcx, 1
L2: 
    PRINT_HEX 1, rcx
    NEWLINE




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