#include <iostream>
#include "Args.h"
#include "Image.h"
#include "Pipeline.h"

// Filters
#include "Grayscale.h"
#include "Brighten.h"
#include "Blur.h"
#include "FlipH.h"
#include "FlipV.h"
#include "Rotate.h"

/*
Name: Tonne Charles
Class: CMPS 2143
Assignment: Program 3 - Image Filter Pipeline
ID: 10-P03

Description:
Main driver for the image processing pipeline.
Uses Args to determine filter order and applies them using Pipeline.
*/

int main(int argc, char* argv[]) {
try {
// Parse arguments
Args args = Args::parse(argc, argv);

// Print basic info
std::cout << "INPUT : " << args.input << "\n";
std::cout << "OUTPUT : " << args.output << "\n";

std::cout << "ORDER : ";
for (const auto& step : args.order) {
std::cout << step << " ";
}
std::cout << "\n";

if (args.use_brighten) {
std::cout << "BRIGHTEN: " << args.brighten << "\n";
}
if (args.use_rotate) {
std::cout << "ROTATE : " << args.rotate << "\n";
}

// Load image
Image img(args.input);
std::cout << "\nLoaded: " << img.info() << "\n";

// Build pipeline
Pipeline pipeline;

for (const auto& step : args.order) {
if (step == "grayscale") {
pipeline.add(new Grayscale());
}
else if (step == "blur") {
pipeline.add(new Blur());
}
else if (step == "flipH") {
pipeline.add(new FlipH());
}
else if (step == "flipV") {
pipeline.add(new FlipV());
}
else if (step == "brighten") {
pipeline.add(new Brighten(args.brighten));
}
else if (step == "rotate") {
pipeline.add(new Rotate(args.rotate));
}
}

// Print pipeline steps
pipeline.printSteps();

// Run filters
pipeline.run(img.pixels());

// Save output
img.save(args.output);
std::cout << "Saved: " << args.output << "\n";

} catch (const std::exception& e) {
std::cout << "Error: " << e.what() << "\n";
std::cout << "Usage: ./imgtool <input> <output> [options]\n";
return 1;
}

return 0;
}