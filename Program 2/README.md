# Program 2 - Command Line Args Parser

## Build

g++ -std=c++17 -Wall -Wextra -O2 main.cpp Args.cpp -o imgtool

## Usage

./imgtool <input_image> <output_image> [options]

## Supported Options

--grayscale (-g)
--blur (-l)
--flipH (-h)
--flipV (-v)
--brighten N (-b N)
--rotate N (-r N)

Also supports:
--brighten=N
--rotate=N
Grouped flags: -glhv

## Example Commands

Valid:
./imgtool in.png out.png --grayscale --brighten 20
./imgtool in.png out.png -g -l -b 20 -r 90
./imgtool in.png out.png --rotate=180

Invalid:
./imgtool in.png
./imgtool in.png out.png --brighten
./imgtool in.png out.png --rotate 45
./imgtool in.png out.png --brighten twenty
