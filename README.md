This C program generates "Hello, World!" code templates in C, Java, Python, or Bash.

How it works:
PrintDefaultCode function: Based on the chosen language, it writes a "Hello, World!" template to a file or displays it on the console.
main function: Interprets command-line arguments:
                          -h: Displays help information.
                          -v: Shows version info.
alap c/java/py/sh [--stdout]: Generates code in the specified language.
                    --stdout: outputs it to the console.
Without --stdout, it saves the code in a file (e.g., file.c for C).

Example commands:
program alap c --stdout → Prints "Hello, World!" in C to the console.
program alap java → Creates a file.java file with a Java "Hello, World!" program.
