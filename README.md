**Minishell**
_________________________________________________________________________________________________________________

A lightweight Unix shell implementation created as part of the École 42 curriculum. This project recreates the behavior of bash with essential features including command execution, pipes, redirections, and built-in commands.
Features

_________________________________________________________________________________________________________________

Core Functionality

    Interactive command-line interface with prompt display

    Command history management using readline

    Command execution with PATH resolution using execve

    Multiple command execution with pipes

    Input and output redirections (<, >, <<, >>)

    Here-doc implementation with delimiter support

    Environment variable expansion

    Exit status handling ($?)

_________________________________________________________________________________________________________________

Built-in Commands

    echo with -n option support

    cd with relative and absolute paths

    pwd to display current directory

    export for environment variable management

    unset to remove environment variables

    env to display environment variables

    exit with exit code handling

_________________________________________________________________________________________________________________

Signal Handling

    SIGINT (Ctrl+C) - Interrupts current command

    SIGQUIT (Ctrl+$$ - Ignored in interactive mode

    EOF (Ctrl+D) - Exits the shell properly

_________________________________________________________________________________________________________________

Installation

Clone the repository and compile the project:

<img width="526" height="73" alt="image" src="https://github.com/user-attachments/assets/27168fbd-70af-49b3-884a-6b110d319794" />

_________________________________________________________________________________________________________________

Usage

Launch the shell by running the executable:

<img width="115" height="37" alt="image" src="https://github.com/user-attachments/assets/63979ba0-7bf9-43f0-b1e3-6bcb808d2467" />

_________________________________________________________________________________________________________________

Example Commands:

<img width="317" height="146" alt="image" src="https://github.com/user-attachments/assets/0320319f-e403-443c-b087-bc7755032507" />

_________________________________________________________________________________________________________________

Technical Implementation

    Language: C

    Memory Management: All heap allocations are properly freed with no memory leaks

    File Descriptors: Careful handling to prevent leaks

    Parsing: Tokenization and syntax analysis for command interpretation

    Process Management: Fork and execve for command execution

_________________________________________________________________________________________________________________

Project Structure

<img width="616" height="143" alt="image" src="https://github.com/user-attachments/assets/6642d2ee-00d6-4141-91c8-82b22ee9a264" />

_________________________________________________________________________________________________________________

Compilation

The project uses a Makefile with the following rules:

    make - Compiles the project

    make clean - Removes object files

    make fclean - Removes object files and executable

    make re - Recompiles everything

_________________________________________________________________________________________________________________

Requirements

    GCC compiler

    GNU Readline library

    Make





