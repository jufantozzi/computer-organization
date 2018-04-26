"""Converts text into a single string for use in Assembly code."""
import sys

if (len(sys.argv) < 2):
    print("Usage: stringASM.py text_file")
    exit()

file = open(sys.argv[1], "r")
out = open("converted_string.txt", "w")
text = file.read()
for char in text:
    if (char == '\n'):
        out.write('\\n')
    else:
        out.write(char)
