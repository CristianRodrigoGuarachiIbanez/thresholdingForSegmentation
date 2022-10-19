# Object Detection/segmentation Based On Thresholding 

The current algorithmus was designed to segment images in order to detect the arm of the robot as well as the object on the image [see image](./image_outputs/binocular_view.png)


## Dependencies

To run the algorithmus, the following libraries should be installed:
    
        OpenCV >= 4.6.0 

###  Installing OpenCV on Linux

<html>
<body>

<p>This library can download from the source:</p> 

<ul>
    <li><i>I  *Installing required packages and tools*</i></li>

        sudo apt install -y g++ cmake make git libgtk2.0-dev pkg-config
    
    II  *Download the source*

        1. First of all, we need to clone the correspondently version of OpenCV. To find the all versions, visit this website and click on the GitHub icon of the latest version. 
        2. On the GitHub page, copy the HTTPS link from the code button.
        3. On the terminal, type the following command 

                git clone url 

            paste the link using the shortcut key Ctrl + shift + v
    
    III *Build the sour*
        
        1.  Create the build directory and go into it using the following command:

                    mkdir -p build && cd build
        
        2. Generate the build scripts using cmake:

            cmake ../opencv

        3.  Build the source using make

            make -j4

    IV *Install the OpenCV packa*


        1. After the build process is completed, install the package. You will need sudo privileges to do so:

            sudo make install
    
    If none error ist found, OpenCV is installed successfully on your Linux system. The header files could be found at the location 

            /usr/local/include/opencv4

</body>
</html>

## Run 

Navigate to the file ./ThresholdingForSegmentation/, where the main.cpp file is placed. There, compile the important modules;

        g++ main.cpp objectDetector.cpp -o objectDetector ./directoryWalker/dirWalker.cpp -lstdc++fs `pkg-config --cflags --libs opencv`

Dont forget to use the links for filesystem -> -lstdc++fs und the one for the opencv libs `pkg-config --cflags --libs opencv`.

Once compilated, the file the command ./objectDetector should be excecuted 
    