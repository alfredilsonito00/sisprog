@ /106
BASE K /3030
COUT K /0A00
MULT K /0100
A K /000A
MAX K /8000
I K /0001

@ =0
GD /000; carrega x0
MM MAX; salva max 0
GD /000


LOOP LV /005
SUB I
JZ IMPRIME; 5-i = 0?
GD /000; carrega x
SB BASE
SB MAX
JN SKIP ; x - max < 0 ?
AD MAX
MM MAX; max = x
SKIP GD /000
LV /001
AD I
MM I; i = i-1
JP LOOP

IMPRIME LD MAX
ML MULT; olha apenas segundo digito
SB COUT
JN SOMA; dig - A < 0 ?
LD MAX
SB A ; -A + 10
AD MULT
MM MAX
SOMA LD MAX; carrega soma
AD BASE
PD /100; print

HM =0