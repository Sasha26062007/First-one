# Laboratory Work 7: Computer Vision and Face Detection

## Description
This project implements a modular C++ application using OpenCV for video processing and face detection. It processes a video stream and applies various filters or detects faces using a pre-trained ResNet-10 deep neural network.

## Architecture
* `CameraProvider` - reads the video stream from a file.
* `KeyProcessor` - handles keyboard inputs to switch processing modes.
* `FrameProcessor` - applies filters (Invert, Blur, Canny) and performs Face Detection using `cv::dnn`.
* `Display` - handles the output window and UI elements (Brightness trackbar).

## Build and Run Instructions
1. Run the preinstall script to install dependencies and download the neural network weights:
   `./preinstall.sh`
2. Build the project using CMake:
   `./build.sh`
3. Execute the program:
   `./run.sh`

## Controls
* `0` - Normal mode
* `1` - Invert colors
* `2` - Gaussian Blur
* `3` - Canny edge detection
* `f` or `F` - Face Detection mode
* `q` or `ESC` - Quit
