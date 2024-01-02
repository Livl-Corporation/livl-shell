<h1 align="center">
  <img src="./img/livl_shell_logo.png" width="224px">

  <b>Livl Shell</b>
</h1>  
<h4 align="center">
  An Intermediate Reimplementation of the Bash Shell in C
</h4>

## Table of Contents

- [📦 Prerequisites](#-prerequisites)
- [🚀 Quick start](#-quick-start)
- [📚 Makefile Guide](#-makefile-guide)
- [📁 Project structure](#-project-structure)
- [📝 List of insane livl-bash commands](#-list-of-insane-livl-bash-commands)
    - [Basic Commands](#basic-commands)
    - [Input/Output Redirection](#inputoutput-redirection)
    - [Pipelines](#pipelines)
    - [Command Sequencing](#command-sequencing)
    - [Batch Mode](#batch-mode)
    - [Background Execution](#background-execution)
    - [History](#history)
    - [Alias](#alias)
- [Working with the documentation](#working-with-the-documentation)
    - [📖 Use the livl-bash man command](#-use-the-livl-bash-man-command)
    - [📜 Doxygen documentation](#-doxygen-documentation)
        - [📦 Prerequisites of Doxygen](#-prerequisites-of-doxygen)
        - [🚀 Generate the Doxygen documentation](#-generate-the-doxygen-documentation)
    - [🧪 GCOV test coverage](#-gcov-test-coverage)
        - [📦 Prerequisites of gcov](#-prerequisites-of-gcov)
        - [🚀 Generate the coverage report](#-generate-the-coverage-report)
- [🛠️ Pipelines](#️-pipelines)
    - [1. C-Make Pipeline](#1-c-make-pipeline)
    - [2. Static Pipeline](#2-static-pipeline)
- [🧍🏽Project team](#-project-team)

## 📦 Prerequisites

This project is developed in C language, so you need to have a C compiler installed on your machine to build it.
It would be better to run it on a Linux distribution, but it has also been tested on macOS.
It is possible to run it on Windows with the WSL (Windows Subsystem for Linux).

- gcc : `sudo apt install gcc`
- make: `sudo apt install make`

> To install the WSL on Windows, follow this [tutorial](https://docs.microsoft.com/en-us/windows/wsl/install-win10).

## 🚀 Quick start

Follow these steps to quickly get started:

1. **Compile the Project**: Run the `make` command. This will compile the project and create an executable file called `livl-shell` in the `bin` folder.

2. **Run the Executable**: You can run the executable by using the command `./bin/livl-shell` or `make run`.

> 😀 **Insane feature**: You can run the executable in batch mode by using the command `./bin/livl-shell -c "ls -l"`.

3. **Clean the Project**: Use the `make clean` command to clean the project.

> 💡 **Tip**: The command `make run` will compile and immediately run the executable. It is equivalent to running `make && ./bin/livl-shell`.

## 📚 Makefile Guide

The project uses a Makefile for managing build tasks. Here are some of the available targets:

- `all`: Compile the project.
- `run`: Run the executable.
- `doc`: Generate documentation using Doxygen.
- `gcov`: Generate code coverage data using gcov and lcov.
- `package`: Package the project into a tar.gz file.
- `clean`: Remove all object files.
- `clean-gcov`: Remove all gcov-related files.
- `mrproper`: Perform a deep clean of the project.
- `clear`: Clear the console.

You can use the `make help` command to display a brief description of each target.

## 📁 Project structure

The project is structured as follows:

```
livl-shell/
├── bin/ # Contains the compiled binary
│   └── livl-shell # Executable
├── doc/ # Contains the Doxygen documentation
│   └── html/
│       └── index.html
├── gcov/ # Contains the coverage report
│   └── report/
│       └── index.html
├── include/ # Contains the header files
│   └── file.h
|   └── ...
├── src/ # Contains the source files
│   └── file.c
|   └── ...
├── livl-shell.1 # Manual of the livl-shell
├── index.html # Static Livl Shell website
├── history.txt # History of your commands
└── Makefile # Makefile
```

## 📝 List of Insane livl-bash features

> 💡 The livl-shell is limited to run a maximum of 3 commands in a row.

### Basic Commands

- `ls`: Lists the files in the current directory.
- `cd`: Changes the current directory.
- `pwd`: Prints the current directory.
- `echo`: Displays a line of text.

### Input/Output Redirection

- `ls -l > output.txt`: Redirects the output of a command to a file.
- `pwd >> output.txt`: Appends the output of a command to a file.
- `wc -l < output.txt`: Counts the number of lines in the file.

### Pipelines

- `ls -l | grep '.txt'`: Redirects the output of a command to another command. You can use single, double, or no quotes.

### Command Sequencing

- `sleep 4 && echo "Second command executed"`: Executes a command after another one.
- `false && echo "This won't be executed"`: Executes a command after another one only if the first one succeeded.
- `false || echo "This will be executed"`: Executes a command after another one only if the first one failed.
- `echo "Command 1"; sleep 3; echo "Command 2"; ls -l`: Executes multiple commands regardless of the success of the previous ones. The `ls -l` won't be executed because the shell is limited to run a maximum of 3 commands in a row.

### Batch Mode

> ⚠️ The command should be enclosed in quotes to ensure it is passed as a single argument

- `./livl-shell -c "ls -l|grep txt && echo heyyy"`: Executes a list of commands from the command line.
- `./livl-shell --command "echo livl"`: Executes a list of commands from the command line.

### Background Execution

- `sleep 3 & echo hey`: Executes a command in the background (the shell will not wait for the command to finish) and it will show you the job id of the background process (ex: `[1] 1234`).
- `pwd`: Running this command will display the job id of the background process terminated (ex: `[1] done sleep 3`).

### History

The livl-shell has an ex history feature that allows you to view the history of your commands.

**Experimental**: Use up and down arrows to navigate through the history. To be able to use this feature, you need to go to the branch  `feat/history`. This feature is not available on the `master` branch because some issues have been detected when using the left and right arrows.

The history is saved in the [`history.txt`](history.txt) file.

### Alias

Livl-shell provide a basic alias support. Alias can be defined only by editing the `alias.txt` file. The syntax is the following:

```
alias_name="command"
```

For example, if you want to create an alias for the `ls -l` command, you can add the following line to the `alias.txt` file:

```
ll="ls -l"
```

Then, you can run the `ll` command to execute the `ls -l` command.

> Note that you can't use alias inside alias, and your input need to be exactly the alias name. You can't add arguments to an alias when using the shell.

## Working with the documentation

### 📖 Use the livl-bash `man` command

> To edit the man you can download a TROFF Syntax Highlighter for Visual Studio Code.

- The `man livl-shell` manual is located in the [`livl-shell.1`](livl-shell.1) file
- To view the manual, run : `man ./livl-shell.1`

### 📜 Doxygen documentation

> ❓ Doxygen is a documentation generator, a tool for writing software reference documentation.

#### 📦 Prerequisites of Doxygen

- Download doxygen : `sudo apt install doxygen`

#### 🚀 Generate the Doxygen documentation

- Run `make doc` to generate the documentation
- To view the documentation, open the [`index.html`](/doc/html/index.html) file in the `doc/html/` folder.

### 🧪 GCOV test coverage

> ❓ GCOV is a test coverage program. It helps you determine how much of your source code is being tested by your test suite. It is a useful tool for finding untested code.

#### 📦 Prerequisites of gcov

- Download gcov : `sudo apt install gcov`
- Download lcov : `sudo apt install lcov`

#### 🚀 Generate the coverage report

- Run `make gcov` to generate the coverage report
- To exit the coverage report, press `exit` two times (one for the shell and one for the coverage report)
- To view the coverage report, open the [`index.html`](/gcov/report/index.html) file in the `gcov/report/` folder or run `gcovr -r .`
- Run `make clean-gcov` to clean the `gcov` folder

## 🛠️ Pipelines

Our pipelines are configured to be triggered on each `push` and `pull request` event on the `master` branch. We have two main pipelines:

### 1. C-Make Pipeline

The `c-make` pipeline compiles the project using the `make` command.

### 2. Static Pipeline

The `static` pipeline hosts the static website on GitHub Pages at the root of the repository. This allows access to the Doxygen documentation and the Coverage report at the following address: https://livl-corporation.github.io/livl-shell/


## 🧍🏽Project team

The Livl team is composed of two members from the CNAM of Strasbourg:

<table align="center">
    <tr>
        <th><img src="https://avatars.githubusercontent.com/u/19238963?v=4?v=4?size=115" width="115"><br><strong>@FranckG28</strong></th>
        <th><img src="https://avatars.githubusercontent.com/u/62793491?v=4?size=115" width="115"><br><strong>@jvondermarck</strong></th>
    </tr>
    <tr align="center">
        <td><b>Franck Gutmann</b></td>
        <td><b>Julien Von Der Marck</b></td>
    </tr>
</table>
