#include <iostream>

#include "image_loader.h"
#include "image_writer.h"

int main(int argc, char** argv)
{
    std::cout << "Hello JPEG" << std::endl;
    if (argc < 4)
    {
        std::cerr << "Bad usage" << std::endl;
        std::cerr << "exe jpg_1 jpg_2 out_png" << std::endl;
        return 1;
    }

    std::string filePath1{ argv[1] };
    std::string filePath2{ argv[2] };
    std::string outFilePath { argv[3] };

    std::cout << "JPEG file path 1: " << filePath1 << std::endl;
    std::cout << "JPEG file path 2: " << filePath2 << std::endl;
    std::cout << "Output PNG file path: " << outFilePath << std::endl;

    std::optional<Image> image1 = read_JPEG_file(filePath1.c_str());
    std::optional<Image> image2 = read_JPEG_file(filePath2.c_str());

    if (!image1.has_value())
    {
        std::cout << "Failed to read the image 1" << std::endl;
        return 1;
    }

    if (!image2.has_value())
    {
        std::cout << "Failed to read the image 2" << std::endl;
        return 1;
    }

    std::cout << "Processing images..." << std::endl;
    Image resultImage = DiffImages(*image1, *image2);

    std::cout << "Writing image..." << std::endl;
    if (!WritePngFile(outFilePath, resultImage))
    {
        std::cout << "Failed to write PNG image" << std::endl;
        return 1;
    }

    std::cout << "Success!" << std::endl;
    return 0;
}
