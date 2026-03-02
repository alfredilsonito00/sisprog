@ /0100
N K =5
RES K =0
I K =0
MONE K /FFFF



@ =0
SC ROTINA
HM /0000
ROTINA K /0000
LV /0001;  carrega 1 em fatorial
MM RES
LD N
MM I; carrega n em i
LOOP JZ FIM; loop
LD RES; carrega fatorial
ML I; multiplica por i
MM RES; salva
LD MONE; carrega -1
AD I; i-1
MM I; salva novo i
JP LOOP
FIM RS ROTINA