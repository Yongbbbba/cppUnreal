%include "io64.inc"

section .text
global CMAIN
CMAIN:
    mov rbp, rsp; for correct debugging
    
    ; 배열과 주소
    
    ; 배열 : 동일한 타입의 데이터 묶음
    ; - 배열을 구성하는 각 값을 배열 요소(element)라고 함
    ; - 배열의 위치를 가리키는 숫자를 인덱스(index)라고 함
    
    mov rax, a
    
    ; 연습문제 : a배열의 모든 데이터 출력해보기
    xor ecx, ecx
LABEL_PRINT_A:
    PRINT_HEX 1, [a+ecx] ; a 배열의 첫 번째 원소를 추출
    NEWLINE
    inc ecx ; add ecx, 1
    cmp ecx, 5
    jne LABEL_PRINT_A

 
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
   msg db 'Hello World', 0x00
   a db 0x01, 0x02, 0x03, 0x04, 0x05 ; 5 * 1 = 5바이트
   b times 5 dw 1 ; 5 * 2 = 10바이트
    
    ; 초기화 되지 않은 데이터
    ; [변수이름] [크기] [개수]
    ; [크기] resb(1) resw(2) resd(4) resq(8) reserve일 것으로 추정
    
section .bss
    num resb 10 ; 바이트가 10개 있음