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
`rci` can install dots from a tar packages as of now. It will eventually support Git repos too.
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
print Installation finished.
```

- Syntax
`location of file in Tar package`=`location of file to move to`
The `rci`\'s Parser provide two builtin functions called `print` and `endl`.
`print <string>` is used to print a string to standard output.
`endl` is used to print a new line to standard output. (`print` function is unable to print newlines via `\n` character. Use this instead).

### Installation?
Nah mate. It's not even in alpha stage.
It cannot create required folders.
It cannot execute required commands to install the rice such as `fc-cache -fv` which required sometimes for installing new fonts.

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

Arigatou.

