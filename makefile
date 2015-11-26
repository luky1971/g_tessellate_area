CC=gcc
GROMACS=/usr/local/gromacs
VGRO=5
GKUT=extern/gkut
INCLUDE=include
SRC=src
BUILD=build
INSTALL=/usr/local/bin

ifeq ($(VGRO),5)
INCGRO=-I$(GROMACS)/include/ \
	-I$(GROMACS)/include/gromacs/utility \
	-I$(GROMACS)/include/gromacs/fileio \
	-I$(GROMACS)/include/gromacs/commandline \
	-I$(GROMACS)/include/gromacs/legacyheaders
LINKGRO=-L$(GROMACS)/lib/i386-linux-gnu
LIBGRO=-lgromacs
DEFV5=-D GRO_V5
else
INCGRO=-I$(GROMACS)/include/gromacs
LINKGRO=-L$(GROMACS)/lib
LIBGRO=-lgmx
endif

.PHONY: install clean

$(BUILD)/lltessellator: $(BUILD)/lltessellator.o $(BUILD)/ll_tessellation.o
	make VGRO=$(VGRO) -C $(GKUT) && $(CC) $(CFLAGS) -o $(BUILD)/lltessellator $(BUILD)/lltessellator.o $(BUILD)/ll_tessellation.o $(GKUT)/build/gkut_io.o $(GKUT)/build/gkut_log.o $(LINKGRO) $(LIBGRO)

install: $(BUILD)/lltessellator
	install $(BUILD)/lltessellator $(INSTALL)

$(BUILD)/lltessellator.o: $(SRC)/lltessellator.c $(INCLUDE)/ll_tessellation.h
	$(CC) $(CFLAGS) -o $(BUILD)/lltessellator.o -c $(SRC)/lltessellator.c $(DEFV5) -I$(INCLUDE) $(INCGRO) -I$(GKUT)/include

$(BUILD)/ll_tessellation.o: $(SRC)/ll_tessellation.c $(INCLUDE)/ll_tessellation.h
	$(CC) $(CFLAGS) -o $(BUILD)/ll_tessellation.o -c $(SRC)/ll_tessellation.c $(DEFV5) -I$(INCLUDE) $(INCGRO) -I$(GKUT)/include

clean:
	make clean -C $(GKUT) && rm -f $(BUILD)/*.o $(BUILD)/lltessellator