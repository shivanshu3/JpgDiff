#include <cstdio>
#include <cstddef>
#include <setjmp.h>
#include <iostream>
#include <vector>

#include <png.h>

#include "image.h"

static bool write_png_file(char *filename, png_bytep *row_pointers, unsigned int height, unsigned int width) {
    int y;

    FILE *fp = fopen(filename, "wb");
    if(!fp)
    {
        std::cout << "Failed to open file for writing" << std::endl;
        return false;
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png)
    {
        std::cout << "png_create_write_struct failed" << std::endl;
        return false;
    }

    png_infop info = png_create_info_struct(png);
    if (!info)
    {
        std::cout << "png_create_info_struct failed" << std::endl;
        return false;
    }

    if (setjmp(png_jmpbuf(png)))
    {
        std::cout << "libpng error" << std::endl;
        return false;
    }

    png_init_io(png, fp);

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(
        png,
        info,
        width, height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png, info);

    // To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
    // Use png_set_filler().
    //png_set_filler(png, 0, PNG_FILLER_AFTER);

    if (!row_pointers)
    {
        std::cout << "row_pointers is null" << std::endl;
        return false;
    }

    png_write_image(png, row_pointers);
    png_write_end(png, NULL);

    fclose(fp);

    png_destroy_write_struct(&png, &info);

    return true;
}

bool WritePngFile(const std::string& fileName, const Image& image)
{
    auto height = static_cast<unsigned int>(image.size());
    auto width = static_cast<unsigned int>(image[0].size());

    std::vector<std::vector<png_byte>> pngPixelRows;

    for (const auto& row : image)
    {
        std::vector<png_byte> pngPixelBytes;
        for (const auto& pixel : row)
        {
            pngPixelBytes.push_back(pixel.red);
            pngPixelBytes.push_back(pixel.green);
            pngPixelBytes.push_back(pixel.blue);
            pngPixelBytes.push_back(255);
        }
        pngPixelRows.push_back(std::move(pngPixelBytes));
    }

    std::vector<png_bytep> rowPtrs;
    for (const auto& pngPixelRow : pngPixelRows)
    {
        png_byte* rowPtr = const_cast<png_byte*>(pngPixelRow.data());
        rowPtrs.push_back(rowPtr);
    }

    png_bytepp rawRowPtrs = rowPtrs.data();

    char* fileNamePtr = const_cast<char*>(fileName.c_str());

    return write_png_file(fileNamePtr, rawRowPtrs, height, width);
}
