#include <vector>

struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

using Image = std::vector<std::vector<Pixel>>;
