# Rice Installer
A noob\'s rice installer for Linux systems.

## Why something like this?
As a Linux user who likes to hop a lot, I always have to go through the hassle of getting all my dots from Git repos and placing them manually in their place.
One can argue that the same thing can be achieved by shell scripts, but scripts tend to be larger and slower.
This program is written in C++, which is compiled and theoretically runs faster.

Rice Installer aims to provide a better solution for managing and installing dots.

### An insight into working
`rci` is the command line utility to use Rice Installer.

`rci` can install dots from tar packages and git repos.

It reads a file called `index.rci` situated in root of git repo or tar package.
A typical `index.rci` looks something like this:
```
start i3

print Installing i3 config
i3/config=$HOME/.config/i3/config
endl
print Installing Polybar config
polybar/config=$HOME/.config/polybar/config
endl
print Installing Zsh config and aliases
zshrc=$HOME/.zshrc
aliases=$HOME/.aliases
endl
print Installing fonts
Iosevka.ttf=$HOME/.local/share/fonts/Iosevka.ttf
exec fc-cache -fv
endl
print Installation finished.

stop i3
```

Each and every `index.rci` should and must have atleast one function.

##### Syntax for index.rci
`location of file in Tar package or git repo`=`location of file to move to`

The `rci parser` provides some builtin functions:
- `print`
- `endl`
- `exec`.
- `start`
- `stop`
- `call`


`print <string>` is used to print a string to standard output.

`endl` is used to print a new line to standard output. (`print` function is unable to print newlines via `\n` character. Use this instead).

`exec <command>` is used to execute `<command>`. Note that it can only execute binaries found in `$PATH` variable.

`start <function_name>` is used to define the start of a new function.

`stop <function_name>` is used to close the function started with the `start` function. 

`call <function_name>` is used to call a function from another.

### Installation?
Rice installer is still in alpha stage and heavy development.
Many features are still subject to change.

You can try it out and help me develop it :D

Clone this repository
```sh
git clone https://github.com/clawbhaiya/rci.git
```
Make a `build/` folder in the root directory of project.
And run `make all` in the project's root. The resulting binary is placed in `build/` folder.

### Usage
- Syntax
```sh
rci <installType> <name-of-tar-package or git-repo-url> <function_names>
```

- Example
```sh
rci git https://github.com/clawbhaiya/dotfiles.git common i3
```
The above example runs two functions namely `common` and `i3`.


<b>Arigatou.</b>

