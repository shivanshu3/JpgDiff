# JpgDiff

`jpg_diff` compares two JPEG images and generates a PNG showing the differences.

## Dependencies

- CMake (3.0 or newer)
- libjpeg development files
- libpng development files
- zlib development files

On Debian/Ubuntu based systems these can be installed with:

```bash
sudo apt-get install cmake build-essential libjpeg-dev libpng-dev zlib1g-dev
```

## Building

1. Create a build directory:

   ```bash
   mkdir build && cd build
   ```

2. Generate the build files with CMake and compile:

   ```bash
   cmake ..
   make
   ```

   The resulting executable `jpg_diff` will be placed in the `build` directory.

## Running

Invoke the program with two JPEG input files and the desired PNG output path:

```bash
./jpg_diff image1.jpg image2.jpg output.png
```

Example (from the `build` directory) using the test images provided in the
repository:

```bash
./jpg_diff ../test_image_1.jpg ../test_image_2.jpg diff.png
```

The file `diff.png` will contain the visual difference between the two input
images.
