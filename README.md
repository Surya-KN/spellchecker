# Spellchecker
A simple spell checker in C using Hash tables And Levenshtein distance algorithm

## Prerequisites

You will need to have the following installed before running the program:

- GCC Compiler
- xxHash Library

### Installing GCC Compiler and xxHash Library

#### Windows

- GCC Compiler: Download and install the MinGW-w64 GCC Compiler from [https://sourceforge.net/projects/mingw-w64/](https://sourceforge.net/projects/mingw-w64/).
- xxHash Library: Download and install the xxHash Library from [https://github.com/Cyan4973/xxHash/releases](https://github.com/Cyan4973/xxHash/releases).

#### Mac

- GCC Compiler: Install GCC using Homebrew by running ``` brew install gcc ```.
- xxHash Library: Install xxHash using Homebrew by running ``` brew install xxhash ```.

#### Linux

- xxHash Library: Install xxHash using your package manager. For example, on Ubuntu, run ``` sudo apt-get install libxxhash-dev ```.

## Getting Started

### Cloning the Repository

You can clone this repository using the following command:

```
git clone https://github.com/Surya-KN/spellchecker.git
```

### Downloading the Zip File

You can download the zip file by clicking on the "Code" button in the repository and selecting "Download ZIP".Then extract it to a new folder.

### Compiling and Running the Program

Once you have the source code(make sure `dict.txt` is in the same directory), you can compile and run the program using the following command:

```
gcc spellcheckerfl.c -o spellcheckerfl -lxxhash; if ($?) { ./spellcheckerfl }
```

This will compile the source code and create an executable file named "spellcheckerfl". The program will then be executed.
