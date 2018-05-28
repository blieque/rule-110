CC = clang
OUTPUT = ./rule-110
SRCS    = $(shell find ./src -type f -name *.c -printf "%p ")
HEADERS = $(shell find ./src -type f -name *.h -printf "%p ")

build: $(OUTPUT)

$(OUTPUT): $(SRCS) $(HEADERS) Makefile
	@echo "Building..."
	$(CC) \
	  -g \
	  -Wall \
	  -Wextra \
	  -pedantic \
	  -std=c11 \
	  -pthread \
	  $(SRCS) \
	  -o $(OUTPUT)

install:
	@if [ -e $(OUTPUT) ]; then \
	  echo "Copying executable to /usr/local/bin."; \
	  cp -i rule-110 /usr/local/bin; \
	else \
	  echo "Run \`make\` first."; \
	fi

clean:
	@[ -e $(OUTPUT) ] && rm $(OUTPUT)

#.watch:
#	while true; do \
#		make \
#		inotifywait -qre close_write .; \
#	done
