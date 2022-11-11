# Interactive CPP [![CMake](https://github.com/Jxtopher/icpp/actions/workflows/build.yml/badge.svg)](https://github.com/Jxtopher/icpp/actions/workflows/build.yml)


## How to use it

## Installation in Debian/Ubuntu

```bash
bash -c "$(curl -fsSL https://raw.githubusercontent.com/jxtopher/icpp/main/install.sh)"
```

## Lunch ICPP from Docker

```bash
docker pull jxtopher/icpp
docker run -it jxtopher/icpp
```

## ICPP Example

- Print a message

```cpp
[0]: <<"My message";
My message
```

- Initialise a variable and print it

```cpp
[0]: int a = 44;
[1]: <<a;
44
```

- Try your regex

```cpp
[0]: <<std::regex_match ("softwareTesting", std::regex("(xoft)(.*)") );
1
[1]: <<std::regex_match ("softwareTesting", std::regex("(xoft)(.*)") );
0
```

## Features

- [x] Create temporary source file, compile and execute the program
- [x] History of lines write by user
- [x] Count and print nombre of code lines
- [x] Code source colorization
- [x] wildcard for execute external command
- [x] Automatic inclusion
- [ ] Possibility to include external sources

## Keywords

!, ?, exit, reset, reset-on, reset-off
