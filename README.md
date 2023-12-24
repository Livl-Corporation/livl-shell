<h1 align="center"><img src="https://user-images.githubusercontent.com/62793491/208452652-71416c5c-8261-4501-a002-afc9e2cf0a0b.png" width="224px"/><br/>
  Livl OS
</h1>  
<p align="center">Livl Shell is an intermediate reimplementation of the bash shell in C language.</p> 

# Table of Contents
- [📦 Prerequisites](#-prerequisites)
- [🚀 Quick start](#-quick-start)
- [📁 Project structure](#-project-structure)
- [📝 List of insane livl-bash commands](#-list-of-insane-livl-bash-commands)
- [📖 Use the livl-bash man command](#📖-use-the-livl-bash-man-command)
- [📜 Use DOXYGEN documentation](#-use-doxygen-documentation)
- [🧪 Use GCOV test coverage](#-use-gcov-test-coverage)
    - [📦 Prerequisites of gcov](#📦-prerequisites-of-gcov)
    - [🚀 Generate the coverage report](#🚀-generate-the-coverage-report)
- [🔧 Pipeline](#-pipeline)
- [🧍🏽Project team](#-project-team)

# 📦 Prerequisites
This project is developed in C language, so you need to have a C compiler installed on your machine. It would be better to run it on a Linux distribution, but it is possible to run it on Windows with the WSL (Windows Subsystem for Linux).

- `gcc` : `sudo apt install gcc`
- `make`: `sudo apt install make`

> To install the WSL, follow this [tutorial](https://docs.microsoft.com/en-us/windows/wsl/install-win10).

# 🚀 Quick start
- In the root folder, go to the lab folder you want to use (ex: `cd 02-proc`)
- Run `make` to compile the project, it will create an executable file in the `bin` folder called `livl-shell`
- Run `./bin/livl-shell` or `make run` to run the executable
- Run `make clean` to clean the project

> 💡 The command `make run` will compile and immediately run the executable. It is equivalent to `make && ./bin/livl-shell`

# 📁 Project structure

The project is structured as follows:

```
livl-shell/
├── bin/
│   └── livl-shell
├── doc/
│   └── html/
│       └── index.html
├── gcov/
│   └── report/
│       └── index.html
├── include/
│   └── file.h
|   └── ...
├── src/
│   └── file.c
|   └── ...
├── livl-shell.1
├── history.txt
└── Makefile
```

# 📝 List of insane livl-bash commands

> 💡 The livl-shell is limited to run max 3 commands in a row. 

- `ls` : list the files in the current directory
- `cd` : change the current directory
- `pwd` : print the current directory
- `cat <<EOF` : let the user enter text until he types `EOF` and display it (thanks to the cat command)
- `echo` : display a line of text
- `ls -l > output.txt` : redirect the output of a command to a file
- `pwd >> output.txt` : redirect the output of a command to a file (append)
- `wc -l < output.txt` : count the number of lines in the file
- `ls -l | grep '.txt'` : redirect the output of a command to another command you can use single, double or without quotes
- `sleep 4 && echo "Second command executed"` : execute a command after another one
- `false && echo "This won't be executed"` : execute a command after another one only if the first one succeeded
- `false || echo "This will be executed"` : execute a command after another one only if the first one failed
- `echo "Command 1"; sleep 3; echo "Command 2"; ls -l` : execute multiple commands regardless of the success of the previous ones
- `sleep 3 & echo hey` : execute a command in the background (the shell will not wait for the command to finish) and it will show you the job id of the background process (ex: `[1] 1234`)
    - `pwd` : running this command will dispkay the job id of the background process terminated (ex: `[1] done sleep 3`)

# 📖 Use the livl-bash `man` command 

> To edit the man you can download a TROFF Syntax Highlighter for Visual Studio Code.

- The `man livl-shell` manual is located in the [`livl-shell.1`](livl-shell.1) file
- To view the manual, run : `man ./livl-shell.1`

# 📜 Use DOXYGEN documentation

> You probably need to install doxygen to generate the documentation : `sudo apt install doxygen`

- Run `make doc` to generate the documentation
- To view the documentation, open the [`index.html`](/doc/html/index.html) file in the `doc` folder

# 🧪 Use GCOV test coverage

> GCOV is a test coverage program. It helps you determine how much of your source code is being tested by your test suite. It is a useful tool for finding untested code.

## 📦 Prerequisites of gcov

- `gcov` : `sudo apt install gcov`
- `lcov` : `sudo apt install lcov`

## 🚀 Generate the coverage report

- Run `make gcov` to generate the coverage report
- To exit the coverage report, press `exit` two times (one for the shell and one for the coverage report)
- To view the coverage report, open the [`index.html`](/gcov/report/index.html) file in the `gcov/report/` folder or run `gcovr -r .`
- Run `make clean-gcov` to clean the `gcov` folder

# 🔧 Pipeline

- The pipeline is configured to run on each push and pull request on the `master` branch

> You can find the pipeline configuration in the [`.github/workflows/c-make.yml`](.github/workflows/c-make.yml) file.

# 🧍🏽Project team

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