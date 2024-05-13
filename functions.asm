global f1, f2, f3
section .data
const1_1 dq 0.6
const1_2 dq 3.0
const2_1 dq 2.0
const3_1 dq 3.0
section .text
f1: ;f1 = 0.6x + 3
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp+8]
    fld qword[const1_1]
    fmulp
    fld qword[const1_2]
    faddp
    leave
    ret


f2: ;f2 = (x - 2)^3 - 1
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp+8]
    fld qword[const2_1]
    fsubp
    fst qword[ebp-8]
    fld qword[ebp-8]
    fld qword[ebp-8]
    fmulp
    fmulp
    fld1
    fsubp
    leave
    ret

f3: ;f3 = 3/x
    push ebp
    mov ebp, esp
    finit
    fld qword[const3_1]
    fld qword[esp+8]
    fdivp
    leave
    ret