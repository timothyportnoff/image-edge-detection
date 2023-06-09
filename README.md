# image-edge-detection

This is a program that detects edges in an image using a prewitt kernel operator. Before the Prewitt filter is applied, a slight blur effect is applied to the image to ensure the prewitt filter doesn't apply itself to any parts of the image with artifacts.

## Prewitt Kernel

## Usage

## Directions

## Dependency: CImg Library

This program has a dependency on the CImg library, which is a powerful C++ library for image processing. CImg provides various functionalities to manipulate and process images, making it a valuable tool for image-related projects.

To use this program, you will need to install the CImg library on your system. Please follow the installation instructions provided in the [CImg GitHub repository](https://github.com/dtschump/CImg) to set up the library correctly.

Once you have installed the CImg library, make sure to link it properly when compiling your C++ program. Consult the CImg documentation for more information on how to include and link the library in your build process.

For further details about the CImg library, including usage examples and documentation, please visit the [CImg GitHub page](https://github.com/dtschump/CImg).

Note: If you have already installed the CImg library on your system, ensure that the necessary headers and library files are correctly configured in your project's build settings.

Note: You may need to compile with -lm -lpthread -lX11, as they might be required libraries for CImg
