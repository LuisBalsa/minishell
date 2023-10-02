# Minishell Project:

# Minishelf
![Minishelf GIF](https://user-images.githubusercontent.com/81270660/272067638-f52afc1d-b27c-44e6-b503-f36e269d5a72.gif)

## Table of Contents
- [Introduction](#introduction)
- [Project Description](#project-description)
- [Features](#features)
- [Authors](#authors) - [Achievement](#achievement)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Usage](#usage)
- [Command Execution Logic (Binary Tree)](#command-execution-logic-binary-tree)
- [Command List for Tests](#command-list-for-tests)
- [Minishell tester](#tester-minishell_tester)

## Introduction
Welcome to the Minishell project repository. This project is a simple shell program developed as a school assignment. It is designed to provide basic shell functionality, including command execution, history management, input/output redirection, and more.

## Project Description
Minishell is a command-line shell that replicates some of the functionality of a typical Unix shell. It is a minimalistic shell designed to be a learning exercise for working with system calls, processes, and various Unix commands.

### Features
- Display a prompt for entering commands.
- Support for command history.
- Execute commands based on the PATH variable or absolute/relative paths.
- Input/output redirection using `<`, `>`, `>>`, and `<<`.
- Pipe (`|`) support for command chaining.
- Handle environment variables (e.g., `$VAR`) and `$?` for exit status.
- Implement built-in commands like `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- Handle signals such as Ctrl-C, Ctrl-D, and Ctrl-\ in interactive mode.


## Authors  - [Luis Balsa](https://github.com/LuisBalsa) - [Adam Kirst](https://github.com/adamckirst)

## Achievement
We are proud to announce that we achieved the maximum score of 125 for this project.

## Getting Started

### Prerequisites
- C compiler (e.g., GCC)
- UNIX-like operating system (Linux or macOS)

### Installation
1. Clone this repository to your local machine.
   ```shell
   git clone https://github.com/yourusername/minishell.git



2. Navigate to the project directory.
   ```shell
   cd minishell
   ```

3. Build the Minishell program.
   ```shell
   make
   ```

### Usage
1. Run Minishell.
   ```shell
   ./minishell
   ```

2. Enter commands at the prompt and press Enter to execute them.

3. Use features like input/output redirection, pipes, and built-in commands as needed.

## Command Execution Logic (Binary Tree)

In this Minishell project, we implemented a binary tree data structure to manage the execution of commands and their associated operations like input/output redirection, piping, and logical operators (&&, ||).

### Parsing Tokens and Building the Command Tree

The heart of our command execution logic lies in the parsing of tokens from the user's input and constructing a binary tree structure that represents the command execution sequence. Here are the key components of this process:

#### Tokenization

We use the `gettoken` and `gettoken_type` functions to tokenize the user's input into different types of tokens. Tokens can be commands, operators, or arguments.

#### Parsing Pipelines

We start by parsing pipelines, which are sequences of commands separated by pipe operators `|`. Each pipeline is represented as a node in the binary tree.

#### Parsing Commands

For each command within a pipeline, we parse the command and its associated elements such as arguments, input/output redirection, and logical operators. The `parseexec` function handles this part.

#### Input/Output Redirection

The `parseredir` function is responsible for detecting and handling input/output redirection operators (`<`, `>`, `>>`, `<<`) and creating nodes in the tree to represent these operations.

#### Logical Operators

We support logical operators `&&` and `||`, which allow for conditional execution of commands based on the success or failure of previous commands. These operators are handled in the `parseline` function.

#### Building the Command Tree

As we parse the input, we construct a binary tree structure where each node represents a command or an operation. The tree structure dictates the order of command execution.

### Executing Commands

Once the binary tree is constructed, we traverse it to execute the commands in the correct order. The `run_cmd` function is responsible for executing individual commands based on their type:

- For regular external commands, we use `execve` to execute them.
- For built-in commands (e.g., `cd`, `echo`), we have dedicated functions to handle their execution.
- For input/output redirection and piping, we manage file descriptors accordingly.
- Logical operators (`&&` and `||`) control the conditional execution of commands.

### Example

Here's an example of how our binary tree logic works for a command like:

```shell
ls -l | grep myfile && echo "File found" || echo "File not found"
```


1. We tokenize the input into commands and operators.
2. We build a binary tree that represents the sequence of commands and operations.
3. The tree structure ensures that `ls -l` is executed first, followed by `grep myfile`. Depending on the success of these commands, either `echo "File found"` or `echo "File not found"` is executed.

This binary tree-based approach allows us to handle complex command sequences and control their execution effectively.

## Additional Resources for Understanding Binary Tree Logic

If you're interested in delving deeper into the binary tree logic used in this Minishell project, we recommend watching the following educational videos. These videos provide detailed explanations and examples of how to build a shell with a similar binary tree-based approach:

1. [# Shell Program Explained](https://www.youtube.com/watch?v=ubt-UjcQUYg)
   - This video tutorial walks you through the process of building a Unix-like shell in the C programming language. It covers various aspects of shell development, including tokenization, parsing, and command execution using a binary tree structure.

2. [Shell Code-- More Detail](https://www.youtube.com/watch?v=ZjzMdsTWF0U&t=1140s)
   - In this video lecture, you'll find an in-depth explanation of creating a Linux shell in C. The video explores the design and implementation of a shell using binary trees, covering topics such as command parsing, redirection, and logical operators.

These videos can be valuable resources for gaining a deeper understanding of the binary tree logic employed in this Minishell project. They provide practical insights and examples that align with the concepts discussed in this README.



## Command List for Tests

```bash
echo ~
```
> Print the home directory of the current user

```bash
cat <<e | grep hello | grep hello | grep world | grep -o l | wc -l
```
> A complex pipeline of text processing commands

```bash
cat /dev/random | head -c 100 | wc -c
```
> Generate random data and count the number of characters

```bash
env -i ./minishell
```
> Run the minishell with a clean environment

```bash
/dev/urandom
```
> You should see: `minishell: /dev/urandom: Permission denied`

```bash
sleep 5 | sleep 5 | sleep 5
```
> Should return in 5 seconds

```bash
"ls > 1 > 2 > 3"
```
> When you don't have the right permissions on file 2

```bash
ls -l | wc -l
```
> Then run `ls -l | wc -l > aqui` (the second command creates a file called 'aqui', and this file counts)

```bash
cat < input.txt | wc
```
> If `input.txt` does not exist
> You should see:
```
minishell: input.txt: No such file or directory
      0       0       0
```
>
```bash
cat << $USER $USER
> $USER
```
> You should see: `cat: luide-so: No such file or directory`

```bash
echo " ' $ ' " don't expand
```
> The text within single quotes is treated literally

```bash
notcmd
```
> Then run `exit`, `echo $?` should return 127

```bash
notexists < input.txt | notexists2 | notexists3
```
> If `input.txt` does not exist

```bash
notcmd1 && (notcmd2 || echo $?)
```
> vs.
```bash
notcmd1 && notcmd2 || echo $?
```
> Check the difference in the logic of these commands

```bash
cat <file
```
> You should see: `minishell: file: No such file or directory`

```bash
touch file
```
> Create a file

```bash
chmod 000 file
```
> Remove all permissions from the file

```bash
cat <file
```
> You should see: `minishell: file: Permission denied`

```bash
asdsad
```
> You should see: `minishell: asdsad: command not found`

```bash
$EMPTYVAR
```
> Show a new prompt line

```bash
echo $?
```
> Should return 0

```bash
sadasdads | $EMPTYVAR
```
> You should see: `minishell: sadasdads: command not found`

```bash
echo $?
```
> Should return 0

```bash
ls | cat -e", setup="touch a b c d
```
> You should see: `cat: invalid option -- ','`

```bash
echo bonjour | | cat -e
```
> You should see: `minishell: syntax error near unexpected token '|'`

```bash
asdf | echo bonjour
```
> You should see: `bonjour` and then `minishell: asdf: command not found`

```bash
cat <$USE*
```
> You should see: `minishell: $USE*: ambiguous redirect`

```bash
echo Hello && echo OK Error: $? && echoHello || echo Not OK Error: $?
```
> You should see:
```
Hello
OK Error: 0
minishell: echoHello: command not found
Not OK Error: 127
```

```bash
echo -"n" hello
```
> You should see: `hello`

```bash
echo -"n -nnnn" -n hello
```
> You should see: `-n -nnnn -n hello`

```bash
echo "|$123USER|" "|$_123USER123|" '"|$_123USER123|"' "|$_123USER?123|"
```
> You should see: `|23USER| || "|$_123USER123|" |?123|`



## Tester: minishell_tester

We utilized the [minishell_tester](https://github.com/kichkiro/minishell_tester) tool to validate our Minishell implementation. This tester is an essential resource for assessing the correctness and functionality of our Minishell program. It includes a suite of test cases and scripts designed to cover various aspects of shell behavior.

