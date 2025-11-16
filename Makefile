CC = gcc
CFLAGS = -Wall -I./src

SRC = nn.c ./src/node.c ./src/operation.c ./src/gradient.c ./src/neuron.c ./src/layer.c ./src/mlp.c ./src/common.c ./mnist/reader.c
OBJ = $(SRC:%.c=build/%.o)

TARGET = build/nn

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
