OUTDIR = em
OUTPUT=$(OUTDIR)/mtcl.js
CC=em++
CPPFLAGS := -x c++

srcs:= em.cpp $(wildcard mtcl*.c)
hdrs:= em.h $(wildcard mtcl*.h)

all: $(srcs) $(OUTPUT)

.PHONY: all test

$(OUTPUT): $(srcs) $(hdrs)
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(srcs) --std=c++11 --bind -o $(OUTPUT) -s EXPORTED_FUNCTIONS="['_mtclInitInterp','_mtclUninitInterp','_mtclRegisterCoreCommands','_mtclEval']" 
