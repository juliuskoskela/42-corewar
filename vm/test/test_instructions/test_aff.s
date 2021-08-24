.name "TEST_AFF"
.comment "test afffff"

# aff chr

# Makes this process' champion talk by displaying chr's values

# x cycles

# { T_REG }

aff r1			; player ID
aff r2			; 0

# load character values in registers; assumes load works
# and that REG_NUMBER is 16

ld 42 r3		; '*'
ld 48 r4		; '0'
ld 49 r5		; '1'
ld 50 r6		; '2'
ld 65 r7		; 'A'
ld 66 r8		; 'B'
ld 67 r9		; 'C'
ld 42 r10		; '4'
ld 42 r11		; '2'
ld 42 r12		; '\n'
ld 42 r13		; ' '
ld 123 r14		; '{' 
ld 124 r15		; '|'
ld 125 r16		; '}'

aff r3
aff r4
aff r5
aff r6
aff r7
aff r8
aff r9
aff r10
aff r11
aff r12
aff r13
aff r14
aff r15
aff r16
