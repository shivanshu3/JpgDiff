#include <cstdint>
#include <iostream>

#include "image.h"

static unsigned char DiffColors(unsigned char color1, unsigned char color2)
{
    int diff = static_cast<int>(color1) - static_cast<int>(color2);

    // 50% grey means there is no difference
    int result = 128 - diff;

    if (result < 0)
        result = 0;

    if (result > 255)
        result = 255;
    
    return static_cast<unsigned char>(result);
}

Pixel Pixel::Subtract(const Pixel& other) const
{
    Pixel result;
    result.red = DiffColors(red, other.red);
    result.green = DiffColors(green, other.green);
    result.blue = DiffColors(blue, other.blue);
    return result;
}

void PrintImage(const Image& image)
{
    for (const auto& row : image)
    {
        for (const auto& pixel : row)
        {
            std::cout << "{" << (unsigned int)pixel.red << "," << (unsigned int)pixel.green << "," << (unsigned int)pixel.blue << "} ";
        }
        std::cout << "\n";
    }
}

Image DiffImages(const Image& image1, const Image& image2)
{
    if (image1.size() != image2.size())
    {
        throw "Images have different heights";
    }

    if (image1.empty() || image2.empty())
    {
        throw "One of the images is empty";
    }

    if (image1[0].size() != image2[0].size())
    {
        throw "Images do not have the same widths";
    }

    if (image1[0].empty() || image2[0].empty())
    {
        throw "One of the images have empty row";
    }

    Image result;
    std::size_t numRows = image1.size();
    std::size_t numCols = image1[0].size();

    for (std::size_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        std::vector<Pixel> resultRow;

        for (std::size_t colIndex = 0; colIndex < numCols; ++colIndex)
        {
            Pixel diffPixel = image1[rowIndex][colIndex].Subtract(image2[rowIndex][colIndex]);
            resultRow.push_back(std::move(diffPixel));
        }

        result.push_back(std::move(resultRow));
    }

    return result;
}
