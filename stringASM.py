import sys

if (len(sys.argv) < 2):
    print("Usage: stringASM.py text_file")
    exit()

file = open(sys.argv[1], "r")
file.read()
for char in file:
    print(char)
    pass
