#include <vector>

struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    Pixel Subtract(const Pixel& other) const;
};

using Image = std::vector<std::vector<Pixel>>;

Image DiffImages(const Image& image1, const Image& image2);
void PrintImage(const Image& image);
