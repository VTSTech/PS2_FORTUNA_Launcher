VERSION = 0.46

EE_BIN = FORTUNA_Launcher.ELF
EE_BIN_PACKED = BOOT-packed.ELF
EE_BIN_STRIPPED = BOOT-stripped.ELF
EE_OBJS = FORTUNA_Launcher.o pad.o OSDInit.o libcdvd_add.o
EE_LIBS = -lc -lcdvd -lpatches -ldebug -lpad

all:
	@echo "Building FORTUNA Launcher $(VERSION) ..."
	$(MAKE) $(EE_BIN_PACKED)

clean:
	@echo "Cleaning ..."
	rm -fr $(EE_BIN) $(EE_BIN_PACKED) $(EE_BIN_STRIPPED) *.o *.bak

run: $(EE_BIN)
	ps2client execee host:$(EE_BIN)

reset:
	ps2client reset

$(EE_BIN_STRIPPED): $(EE_BIN)
	@echo "Stripping ..."
	$(EE_STRIP) -o $@ $<
	
$(EE_BIN_PACKED): $(EE_BIN_STRIPPED)
	@echo "Compressing ..."
	~/ps2homebrew/ps2-packer/ps2-packer -v $< $@
	
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal