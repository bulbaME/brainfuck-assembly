import sys

file = None
mem = [0] * 65536
ptr = 0
inputStack = ''

def block():
    global ptr, mem, inputStack
    pos = file.tell()
    
    while True:
        c = file.read(1)

        if c == '[':
            block()
        elif c == ']':
            if mem[ptr]:
                file.seek(pos)
            else:
                return
        elif c == '+':
            mem[ptr] += 1
        elif c =='-':
            if mem[ptr] > 0:
                mem[ptr] -= 1
        elif c == '>':
            if ptr < 65535:
                ptr += 1
        elif c == '<':
            if ptr > 0:
                ptr -= 1
        elif c == '.':
            print(chr(mem[ptr]), end = '')
        elif c == ',':
            if not inputStack:
                inputStack = input('')
            mem[ptr] = ord(inputStack[0])
            inputStack = inputStack[1:]

def main():
    global file

    if (len(sys.argv) < 2):
        print('File name was not specified')
        return

    try:
        file = open(sys.argv[1], 'r')
    except:
        print(f"No such file named '{sys.argv[1]}'")
        return

    block()
    file.close()
    print()

if __name__ == '__main__':
    main()