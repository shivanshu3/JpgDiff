#pragma once

#include <optional>

#include "image.h"

std::optional<Image> read_JPEG_file (const char* filename);
