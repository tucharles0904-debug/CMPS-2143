#include "Args.h"
#include "Blur.h"
#include "Brighten.h"
#include "FlipH.h"
#include "FlipV.h"
#include "Grayscale.h"
#include "Image.h"
#include "Pipeline.h"
#include "Rotate.h"

#include <iostream>

int main(int argc, char* argv[]) {
    try {
        Args args = Args::parse(argc, argv);

        if (args.input.empty() || args.output.empty()) {
            return 1;
        }

        args.print();

        Image image = Image::load(args.input);
        std::cout << "\nLoaded: " << image << "\n";

        Pipeline pipeline;

        int brightenIndex = 0;
        int rotateIndex = 0;

        for (const std::string& op : args.order) {
            if (op == "grayscale") {
                pipeline.add(new Grayscale());
            }
            else if (op == "blur") {
                pipeline.add(new Blur());
            }
            else if (op == "flipH") {
                pipeline.add(new FlipH());
            }
            else if (op == "flipV") {
                pipeline.add(new FlipV());
            }
            else if (op == "brighten") {
                pipeline.add(new Brighten(args.brightenAmounts[brightenIndex++]));
            }
            else if (op == "rotate") {
                pipeline.add(new Rotate(args.rotateAngles[rotateIndex++]));
            }
        }

        pipeline.printSteps();
        pipeline.run(image.pixels());

        image.save(args.output);

        std::cout << "Saved: " << args.output << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
