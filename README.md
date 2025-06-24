# BejSnap

A graphical Linux application for taking square screen captures.

## Features

- **Square Region Selection**: Enforces a 1:1 aspect ratio during region selection
- **1:1 Aspect Ratio**: Ensures all captures are perfectly square
- **PNG Output**: Saves high-quality images in PNG format
- **Preview**: Shows the captured image before saving
- **Dark Mode by Default**: Toggle to light theme if desired
- **Square Interface**: The application window itself uses a square ratio
- **Default Save Location**: Set a preferred folder for saving captures
- **Automatic File Naming**: Uses format "BejCap-YYYYMMDD###" for organized file management

## Shortcuts

- **Ctrl+S**: Save the current image in preview mode
- **Esc**: Cancel region selection (when in region selection mode)

## Building from Source

### Prerequisites

- Qt 5 (5.12 or newer recommended)
- CMake 3.10 or newer
- C++17 compatible compiler

#### Installing Qt5 and other dependencies

##### Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential cmake qtbase5-dev qt5-qmake qtbase5-dev-tools libqt5widgets5 libqt5gui5 libqt5core5a
```

For newer Ubuntu/Debian versions:
```bash
sudo apt update
sudo apt install build-essential cmake qtbase5-dev qt5-qmake qtbase5-dev-tools
```

##### Fedora:
```bash
sudo dnf install cmake gcc-c++ qt5-qtbase-devel qt5-qtbase
```

##### Arch Linux:
```bash
sudo pacman -S cmake qt5-base
```

##### openSUSE:
```bash
sudo zypper install cmake gcc-c++ libqt5-qtbase-devel
```

### Build Instructions

1. Clone this repository:
   ```
   git clone https://github.com/taosecurity/BejSnap.git
   cd BejSnap
   ```

2. Create a build directory and navigate to it:
   ```
   mkdir build
   cd build
   ```

3. Run CMake and build:
   ```
   cmake ..
   make
   ```

4. Run the application:
   ```
   ./BejSnap
   ```

## Troubleshooting

- **CMake can't find Qt5**: If you encounter an error like "Could not find a package configuration file provided by Qt5", you can:
  - Install Qt5 using the commands provided above for your distribution
  - Specify the Qt5 installation path manually: `cmake .. -DQt5_DIR=/path/to/qt5/lib/cmake/Qt5`
  - On some systems, you may need to set the CMAKE_PREFIX_PATH: `cmake .. -DCMAKE_PREFIX_PATH=/path/to/qt5`

- **Compilation errors**: Make sure you have a C++17 compatible compiler installed
  - For GCC: `g++ --version` (should be 7.0 or higher)
  - For Clang: `clang++ --version` (should be 5.0 or higher)

## Usage

1. Launch BejSnap
2. Click the "Take Screenshot" button or use the File > Capture menu
3. Select a square region on your screen (the selection will automatically enforce a 1:1 aspect ratio)
4. Preview the captured image
5. Click "Save" (or press Ctrl+S) to save the image or "Cancel" to discard

## Configuration

- **Settings Dialog**: Access via File > Settings menu
- **Save Path**: Set the default location for saving screenshots
- **Theme**: Toggle between dark and light themes

## License

[MIT License](LICENSE)

## Acknowledgments

- Built with Qt and C++
- Created for square aspect ratio enthusiasts
