import sys

BYTE_LIMIT = 256
MEMORY_SIZE = 4096

if len(sys.argv) < 2:
    print("The source file wasn't provided")
    exit(1)

with open(sys.argv[1], "r") as f:
    source = f.read()

size = len(source)

memory = [0] * MEMORY_SIZE
pointer = 0
index = 0
while index < size:
    if source[index] == '>':
        pointer = (pointer + 1) % MEMORY_SIZE

    elif source[index] == '<':
        pointer = (pointer - 1) % MEMORY_SIZE

    elif source[index] == '+':
        memory[pointer] = (memory[pointer] + 1) % BYTE_LIMIT

    elif source[index] == '-':
        memory[pointer] = (memory[pointer] - 1) % BYTE_LIMIT

    elif source[index] == '.':
        sys.stdout.write(chr(memory[pointer]))

    elif source[index] == ',':
        memory[pointer] = int(sys.stdin.read(1)) % BYTE_LIMIT

    elif source[index] == '[':
        if memory[pointer] == 0:
            scope = 1
            while scope != 0:
                index += 1
                if index == size:
                    break

                if source[index] == '[':
                    scope += 1

                if source[index] == ']':
                    scope -= 1

    elif source[index] == ']':
        if memory[pointer] != 0:
            scope = 1
            while scope != 0:
                index -= 1
                if index == 0:
                    break

                if source[index] == '[':
                    scope -= 1

                if source[index] == ']':
                    scope += 1

    index += 1