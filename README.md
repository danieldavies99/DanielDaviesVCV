# Daniel Davies Modular for VCV Rack
This repo contains the source code for the Daniel Davies VCV rack modules. If you make anything cool with these modules please send youtube links etc. to danieldavies99@gmail.com or @dangerawaits on the VCV rack discord.

I can't wait to see/hear what you come up with!

The manual for all my modules can be found here (this is very much a WIP): 
https://github.com/danieldavies99/sequel/blob/master/manual/daniel_davies_modular_manual.pdf

The manual is released under the GPL3-or-later license.


![All modules](https://i.imgur.com/NiQAJyR.png)

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

# Blank 3 & Blank 5
3HP and 5HP blank panels.

![Blank 3 & blank 5](https://i.imgur.com/J0giltq.png)

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

If you encounter any issues while using these modules, feel free to open an issue on this repo and I will look into it.

## How to build manual
I build each page of the manual as an individual A4 SVG. The python script found at ./manual/generator/svg2pdf.py can be used to compiled all of the SVGs into pdf's and then flatten them into a single manual PDF.

to run:  ```py ./manual/generator/svg2pdf.py```