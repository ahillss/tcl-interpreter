OUTDIR = em
OUTPUT=$(OUTDIR)/mtcl.js
CC=emcc
EXT = c
CPPFLAGS :=

srcs:=$(wildcard mtcl*.$(EXT))
hdrs:=$(wildcard mtcl*.h)

all: $(srcs) $(OUTPUT)

.PHONY: all test

$(OUTPUT): $(srcs) $(hdrs)
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(srcs) -o $(OUTPUT) -s EXPORTED_FUNCTIONS="['mtclInitInterp']"
