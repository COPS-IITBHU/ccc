dec a 12.6
; Expected output: 12.6
io nlout a

sdec string "Test"
; Expected output: Test
io nlout string

idec b 25
; Expected output: 25
io nlout b

cdec c 'c'
; Expected output: c
io nlout c

fdec d 7.8
; Expected output: 7.8
io nlout d

ddec e 8.42
; Expected output: 8.42
io nlout e

bdec f false
; Expected output: false
io nlout f

mov e g
; Expected output: 8.42
io nlout g

sdec h "a"
cat h "b"
cat h "c"
; Expected output: abc
io nlout h

dec i 6
add i 9
; Expected output: 15
io nlout i

dec j 10
sub j 4
; Expected output: 6
io nlout j

dec k 3
mul k 2
; Expected output: 6
io nlout k

dec l 26
div l 2
; Expected output: 13
io nlout l

dec m 77
mod m 77
; Expected output: 0
io nlout m

dec n 77
mod n 13
; Expected output: 3
io nlout n

io out ">>"
io input "Write Something"
; Expected output: What the user types
io nlout DEF