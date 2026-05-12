#include "Args.h"

Args Args::parse(int argc, char* argv[]) {
    Args args;

    if (argc < 3) {
        std::cerr << "Usage: ./imgtool input output [filters]\n";
        return args;
    }

    args.input = argv[1];
    args.output = argv[2];

    for (int i = 3; i < argc; i++) {
        std::string op = argv[i];

        if (op == "--grayscale" || op == "-g") {
            args.order.push_back("grayscale");
        }
        else if (op == "--blur" || op == "-l") {
            args.order.push_back("blur");
        }
        else if (op == "--flipH") {
            args.order.push_back("flipH");
        }
        else if (op == "--flipV") {
            args.order.push_back("flipV");
        }
        else if (op == "--brighten" || op == "-b") {
            if (i + 1 < argc) {
                args.order.push_back("brighten");
                args.brightenAmounts.push_back(std::stoi(argv[++i]));
            }
        }
        else if (op == "--rotate" || op == "-r") {
            if (i + 1 < argc) {
                args.order.push_back("rotate");
                args.rotateAngles.push_back(std::stoi(argv[++i]));
            }
        }
    }

    return args;
}

void Args::print() const {
    std::cout << "INPUT   : " << input << "\n";
    std::cout << "OUTPUT  : " << output << "\n";
    std::cout << "ORDER   : ";

    for (const std::string& op : order) {
        std::cout << op << " ";
    }

    std::cout << "\n";
}
