# Daniel Davies Modular for VCV Rack
This repo contains the source code for the Daniel Davies VCV rack modules. If you make anything cool with these modules please send youtube links etc. to danieldavies99@gmail.com or @dangerawaits on the VCV rack discord.

I can't wait to see/hear what you come up with!

The manual for all my modules can be found here: 
https://github.com/danieldavies99/sequel/blob/master/manual/daniel_davies_modular_manual.pdf

The manual is released under the GPL3-or-later license.


![All modules (Light)](https://i.imgur.com/jM5JmNR.png)
![All modules (Dark)](https://i.imgur.com/hQmZZfP.png)

# Sequel 8
3 row / 8 step sequencer with built-in clock divider.

![Sequel 8](https://i.imgur.com/LFXTCaE.png?1)

# Sequel 16
3 row / 16 step sequencer with built-in clock divider.

![Sequel 16](https://i.imgur.com/ny7gton.png)

# Sequel Save
Save state expander module for Sequel 8 & Sequel 16.

![Sequel Save](https://i.imgur.com/VmRsBHC.png)

# Quantify
3x Quantizer with attenuverted inputs + nudge and transpose controls.

![Quantify](https://i.imgur.com/hhlliMw.png)

# Samuel
Morse code based rhythm generator.

![Samuel](https://i.imgur.com/jdzElMP.png)

# James
6 row drum sequencer with per-row rush/drag controls.

![James](https://i.imgur.com/CAWooFG.png)

# Bend
Phase modulation oscillator.

![Bend](https://i.imgur.com/LMEtzcI.png)

# Knot
4x4 sequential switch.

![Knot](https://i.imgur.com/v8zWH7Y.gif)

# Blank 3 & Blank 5
3HP and 5HP blank panels.

![Blank 3 & blank 5](https://i.imgur.com/J0giltq.png)

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

If you encounter any issues while using these modules, feel free to open an issue on this repo and I will look into it.

## How to build manual
I create each page of the manual as an individual A4 SVG in inkscape. The Python script found at ./manual/generator/svg2pdf.py can be used to compile all of the SVGs into PDFs and then flatten them into a single manual PDF.

to run:  ```py ./manual/generator/svg2pdf.py```


## How to build and test plugin
There are multiple ways to build and run VCV rack plugins, more can be found here: [https://vcvrack.com/manual/Building](https://vcvrack.com/manual/Building)

I have outlined the simplest way (imo) to get up and running for each OS below. I primarily use windows, if you have any issues building/running this plugin please feel free to open an issue, and I will help you.

<details>
<summary>Windows</summary>

## Setting up your development environment

If you have an anti-virus program running, disable it or it may interfere with the build process or make builds very slow.

Install [MSYS2](https://www.msys2.org/) and launch the MinGW 64-bit shell from the Start menu, not the default MSYS shell. Update the package manager itself:

```pacman -Syu```

Then restart the shell and install packages.

```pacman -Syu git wget make tar unzip zip mingw-w64-x86_64-gcc mingw-w64-x86_64-gdb mingw-w64-x86_64-cmake autoconf automake libtool mingw-w64-x86_64-jq python zstd mingw-w64-x86_64-pkgconf```

## Building DanielDaviesVCV

Download [VCV Rack](https://vcvrack.com/downloads/RackFree-2.6.4-win-x64.exe) and the [windows x64 Rack SDK](https://vcvrack.com/downloads/Rack-SDK-latest-win-x64.zip)

Unzip the Rack SDK folder and set the RACK_DIR environment variable inside the MYSYS2 commandline (you will need to do this every time you launch MYSYS2, unless you add it to your .bashrc file):

```export RACK_DIR=<Rack SDK dir>```

clone the DanielDaviesVCV plugin source code:

```git clone https://github.com/danieldavies99/DanielDaviesVCV.git```

Next, in MYSYS2, cd into the repo, and run the following make command to build the plugin.

```
cd DanielDaviesVCV
make install
```

this will build the plugin from source and output the build into the ./dist directory

Next copy the contents of the dist directory into your rack install plugin director, (probably C:\Users\\<your-user\>\Documents\Rack2\plugins-win-x64)

run VCV rack and you should be able to see the DanielDaviesVCV modules in the module browser.
</details>

<details>
<summary>Mac</summary>

## Setting up your development environment

Install [Homebrew](https://brew.sh/), and install build dependencies.

```
brew install git wget cmake autoconf automake libtool jq python zstd pkg-config
```

## Building DanielDaviesVCV

Download [VCV Rack](https://vcvrack.com/downloads/RackFree-2.6.4-mac-x64+arm64.pkg) and either the [Mac x64 (intel) Rack SDK](https://vcvrack.com/downloads/Rack-SDK-latest-mac-x64.zip) or the [Mac (ARM64) Rack SDK](https://vcvrack.com/downloads/Rack-SDK-latest-mac-arm64.zip)

Unzip the Rack SDK folder and set the RACK_DIR environment variable (you will need to do this every time you open a new terminal instance):

```export RACK_DIR=<Rack SDK dir>```

clone the DanielDaviesVCV plugin source code:

```git clone https://github.com/danieldavies99/DanielDaviesVCV.git```

Next, cd into the repo, and run the following make command to build the plugin.

```
cd DanielDaviesVCV
make install
```

This will build the plugin from source and output the build into the ./dist directory

Copy the contents of the dist directory to your rack plugin directory, then run vcv rack. You should see the DanielDaviesVCV modules in the module brower.
</details>

<details>
<summary>Linux</summary>

## Setting up your development environment

On Ubuntu 16.04+:

```
sudo apt install unzip git gdb curl cmake libx11-dev libglu1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev zlib1g-dev libasound2-dev libgtk2.0-dev libgtk-3-dev libjack-jackd2-dev jq zstd libpulse-dev pkg-config
```

On Arch Linux:
```
pacman -S git wget gcc gdb make cmake tar unzip zip curl jq python zstd libpulse pkgconf
```

## Building DanielDaviesVCV

Download [VCV Rack](https://vcvrack.com/downloads/RackFree-2.6.4-lin-x64.zip) and the [linux x64 Rack SDK](https://vcvrack.com/downloads/Rack-SDK-latest-lin-x64.zip).

Unzip the Rack SDK folder and set the RACK_DIR environment variable (you will need to do this every time you open a new terminal instance):

```export RACK_DIR=<Rack SDK dir>```

clone the DanielDaviesVCV plugin source code:

```git clone https://github.com/danieldavies99/DanielDaviesVCV.git```

Next, cd into the repo, and run the following make command to build the plugin.

```
cd DanielDaviesVCV
make install
```

This will build the plugin from source and output the build into the ./dist directory

Copy the contents of the dist directory to your rack plugin directory, then run vcv rack. You should see the DanielDaviesVCV modules in the module brower.
</details>
