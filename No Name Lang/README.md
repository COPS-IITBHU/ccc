# No Name Lang

A Compiler for my own programming language written from scratch in C.

> Current Progress: Basic codegen with simple binary operators(precedence works), variable declaration, function declaration, variable reassignment, function call and basic error handling.

### Demo Images:
![Image_1](https://user-images.githubusercontent.com/53043454/230713500-62bd18f0-0d72-4c9e-952f-8046b1dadc9e.jpg)
![Image_2](https://user-images.githubusercontent.com/53043454/230713509-8ce7b834-09fa-4430-867b-7f09a384dbb4.jpg)
![Image_3](https://user-images.githubusercontent.com/53043454/230713513-ee0da819-e2b7-4936-9201-d917075140af.jpg)

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
  - [Terminal](#terminal)
  - [Syntax](#syntax)
- [Author](#author)
- [License](#license)

## Installation

> This guide assumes you have a debian based linux distro installed.

Prior to installing No Name Lang, you must have CMake installed.

```bash
sudo apt-get install cmake
```

Make sure you have git installed on your system.

```bash
sudo apt-get install git
```

Clone the repository and install.

```bash
git clone https://github.com/Harsh1s/No-Name-Lang.git
cd No-Name-Lang
cmake -B bld
cmake --build bld
```

## Usage

Arguements look something like this.

```bash
<No Name Lang Compiler> <Source Code File>
```

>No Name Lang Compiler: The executable that cmake throws in bld folder, nnlc.
>
>Source Code File: The souce code file with the file extension of .nnl written according to No Name Lang syntax.

### Terminal

Run NNL Compiler through the terminal by selecting a souce code file.

```bash
bld/nnlc function.nnl
```

### Syntax

Refer to the three example files given: function.nnl, math.nnl, variable.nnl

## Author

- Harsh Raj
- Contact: harsh.raj.cd.ece21@itbhu.ac.in

## License

This project is open source and available under the [MIT License](LICENSE).
