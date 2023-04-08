# Transcend

A Programming language that transpiles to C++

> [Transpiler](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwjaqKaQkZr-AhVBzzgGHWm-Ah4QmhN6BAhhEAI&url=https%3A%2F%2Fen.wikipedia.org%2Fwiki%2FSource-to-source_compiler&usg=AOvVaw3MvLUf985lJ_iB4i7gTTMt), also known as source-to-source translator, source-to-source compiler or transcompiler is a type of translator that takes the source code of a program written in a programming language as its input and produces an equivalent source code in the same or a different programming language.

## About

Transcend is a general purpose programming language with its own unique syntax that gets converted to C++ using the Transcend tranpiler. You have the option of making an executable file or a C++ source code file using the tanspiler.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
  - [Terminal](#terminal)
  - [Syntax](#syntax)
- [Author](#author)
- [License](#license)

## Installation

> This guide assumes you have a debian based linux distro installed.

Prior to installing Transcend, you must have CMake installed.

```bash
sudo apt-get install cmake
```

Make sure you have git installed on your system.

```bash
sudo apt-get install git
```

Clone the repository and install.

```bash
git clone https://github.com/Harsh1s/Transcend.git
cd Transcend
cmake -B bld
cmake --build bld
```

## Usage

Arguements look something like this.

```bash
<Transpiler executable> <Source Code File> <Compile option>
```

>Transpiler executable: The executable that cmake throws in bld folder, tsc.
>
>Source Code File: The souce code file with the file extension of .ts written according to Transcend syntax.
>
>Compile option: Use arguement c to get a compiled executable and nc to just transpile and get C++ source code.

### Terminal

Run Transpiler through the terminal by selecting a souce code file and providing compile option arguement.

```bash
bld/tsc examples/test.ts c
```

### Syntax

Refer to the test.ts file in examples folder. All the functions are further explained below.

```bash
dec -> auto declare variable
sdec -> declare string
idec -> declare integer
cdec -> declare character
fdec -> declare float
ddec -> declare double
bdec -> declare boolean
mov -> copy a to b
def -> create temp variabler
def -> move old to DEF
conv -> convert to desired datatype
iconv -> convert to int
fconv -> convert to float
dconv -> convert to double
cat -> string 1 += string 2
add -> a += b
sub -> a -= b
mul -> a *= b
div -> a /= b
mod -> a %= b
pow -> Power Calculation
rpow -> a = a^b
ipow -> a = a^b
fpow -> Float Power
dpow -> Double Power
round -> Round a and store in b
defadd -> DEF = a + b
defsub -> DEF = a - b
defmul -> DEF = a * b
defdiv -> DEF = a / b
defmod -> DEF = a % b
defpow -> DEF = a ^ b
io out -> print
io nlout -> print with new line
io in -> input as string
io defin -> input in DEF
io input -> Display message and store in DEF
asserteq -> assert equal
assertlt -> assert smaller
assertgt -> assert greater
assertgteq -> assert greater equal
assertlteq -> assert smaller equal
fasserteq -> formatted assert equal
fassertlt -> formatted assert smaller
fassertgt -> formatted assert greater
fassertgteq -> formatted assert greater equal
fassertlteq -> formatted assert smaller equal
cpp -> C++ code
include -> io
           string
           conv
           math
           type
```

## Author

- Harsh Raj
- Made in [C++](https://en.wikipedia.org/wiki/C%2B%2B)
- Contact: harsh.raj.cd.ece21@itbhu.ac.in

## License

This project is open source and available under the [MIT License](LICENSE).
