@ /106
BASE K /3030
COUT K /0A00
MULT K /0100
A K /000A

@ =0
X GD /000; carrega x
SB BASE
MM /100; salva x
GD /000
Y GD /000; carrega y
SB BASE
MM /102; salva y
AD /100
MM /104; salva soma
ML MULT; olha apenas segundo digito
SB COUT
JN SOMA; dig - A < 0 ?
LD /104
SB A ; -A + 10
AD MULT
MM /104
SOMA LD /104; carrega soma
AD BASE
PD /100; print

HM =0