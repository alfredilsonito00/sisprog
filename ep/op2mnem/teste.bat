gcc op2mnem.c -o op2mnem
op2mnem.exe ep-exemplo-2.mvn
op2mnem.exe ep-exemplo-2.mvn > ep-exemplo-2-augusto.asm
mnem2op.exe ep-exemplo-2-augusto.asm > ep-exemplo-2-augusto.mvn