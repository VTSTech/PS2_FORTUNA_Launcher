EE_BIN = FORTUNA_Launcher.elf
EE_OBJS = FORTUNA_Launcher.o pad.o OSDInit.o libcdvd_add.o
EE_LIBS = -lc -lcdvd -lpatches -ldebug -lpad 

all: $(EE_BIN)
	
clean:
	rm -f $(EE_BIN) $(EE_OBJS)

run: $(EE_BIN)
	ps2client execee host:$(EE_BIN)

reset:
	ps2client reset

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal