%include "io64.inc"

section .text
global CMAIN
CMAIN:
    mov rbp, rsp; for correct debugging
    
    GET_DEC 1, al
    GET_DEC 1, num
    
    ;PRINT_DEC 1, al
    ;NEWLINE
    ;PRINT_DEC 1, num
    
    ; 더하기 연산
    ; add a,b ( a = a + b)
    ; a는 레지스터 or 메모리
    ; b는 레지스터 or 메모리 or 상수
    ; 단, a,b 모두 메모리여서는 안된다
    
    ; 빼기 연산
    ; sub a,b ( a = a - b)
    ; 더하기와 동일
    
    ; 곱하기 연산
    ; 곱하기 연산은 더하기 빼기보다 훨씬 복잡한 연산임
    ; 곱하기 연산에 사용되는 레지스터가 따로 있음
    ; mul reg
    ; - mul bl => al * bl
    ; -- 연산 결과를 ax에 저장
    ; - mul bx => ax * bx
    ; -- 연산 결과는 dx(상위 16비트) ax(하위 16비트)에 저장
    ; -- mul ebx => eax * ebx
    
    ; ex ) 5 * 8은?
    mov ax, 0
    mov al, 5
    mov bl, 8
    mul bl
    PRINT_DEC 2, ax
    NEWLINE
    
    ; 나누기 연산
    ; div reg
    ; - div bl = > ax / bl
    ; -- 연산 결과는 al(몫) ah(나머지)
    
    ; ex) 100 /3 은? 
    mov ax, 100
    mov bl, 3
    div bl
    
    PRINT_DEC 1, al
    NEWLINE
    mov al, ah ; ah는 PRINT_DEC로 출력을 못해서 al로 옮겨서 출력 
    PRINT_DEC 1, al
    NEWLINE
    
    add al, 1; ; 레지스터 + 상수
    PRINT_DEC 1, al 
    
    add al, [num] ; 레지스터 + 메모리, 괄호 안하면 메모리 주소임
    PRINT_DEC 1, al
    NEWLINE
    
    mov bl,3 
    add al, bl ; 레지스터 + 레지스터
    PRINT_DEC 1, al
    NEWLINE
    
    add [num], byte 1
    
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