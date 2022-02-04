# Rice Installer
A noob\'s rice installer for Linux systems.

## Why something like this?
As a Linux user who likes to hop a lot, I always have to go through the hassle of getting all my dots from Git repos and placing them manually in their place.
One can argue that the same thing can be achieved by shell scripts, but scripts tend to be larger and slower.
This program is written in C++, which is compiled and theoretically runs faster.
Scripts are tedious and larger too. 
Rice Installer aims to provide a better solution for managing and installing dots.

### An insight into working
`rci` is the command line utility to use Rice Installer.

`rci` can install dots from a tar packages and git repos.

It read a file called `index.sc` situated in tar package's root.
A typical `index.sc` looks something like this:
```
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
```

##### Syntax
`location of file in Tar package or git repo`=`location of file to move to`

The `rci`\'s Parser provide three builtin functions called `print`, `endl` and `exec`.

`print <string>` is used to print a string to standard output.

`endl` is used to print a new line to standard output. (`print` function is unable to print newlines via `\n` character. Use this instead).

`exec <command>` is used to execute `<command>`. Note that it can only execute binaries found in `$PATH` variable.

### Installation?
Rice installer is still in alpha stage and heavy development.
Many features are still subject to change.

You can try it out and help me develop it :D

Clone this repository
```sh
git clone https://github.com/clawbhaiya/rci.git
```
And run `make all` in the project's root. The resulting binary is placed in `build/` folder.

### Usage
```
./rci <name-of-tar-package>
```
As `rci` is unable to make folders according to its need, the user themselves have to create folders they specify in `index.sc`.

<b>Arigatou.</b>

