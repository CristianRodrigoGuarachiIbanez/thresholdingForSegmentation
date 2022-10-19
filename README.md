# Object Detection/segmentation Based On Thresholding 

<p>The current algorithmus was designed to segment images in order to detect the arm of the robot as well as the object on the image</p>

<img src="./segmented_output/back_1.png" alt="image" style="width:42px;height:42px;">


## Dependencies

<p> To run the algorithmus, the following <strong>libraries should be installed:</strong></p>
    
        <p><mark>OpenCV >= 4.6.0 </mark></p>

###  Installing OpenCV on Linux

<html>
<body>

<p>This library can download from the source:</p> 

<ol>
    <li><i>Installing required packages and tools</i></li>
    <p><mark>sudo apt install -y g++ cmake make git libgtk2.0-dev pkg-config </mark></p>
    <li><i>Download the source</i></li>
    <ul>
        <li> First of all, we need to clone the correspondently version of OpenCV. To find the all versions, visit this website and click on the GitHub icon of the latest version. </li>
        <li> On the GitHub page, copy the HTTPS link from the code button.</li>
        <li> On the terminal, type the following command </liS>
                <p><mark>git clone url</mark></p> 
            <p>paste the link using the shortcut key <mark> Ctrl + shift + v </mark></p>
    </ul>
    <li><i>Build the source</i></li>
    <ul>
        <li> Create the build directory and go into it using the following command: </li>
                    <p><mark> mkdir -p build && cd build </mark></p>
        <li> Generate the build scripts using cmake: </li>
            <p><mark> cmake ../opencv </mark></p>
        <li>  Build the source using make </li>
            <p><mark> make -j4 </p></mark>
    <li><i>Install the OpenCV packages </i></li>
        <p> After the build process is completed, install the package. You will need sudo privileges to do so:</p>
        <pre class="notranslate"><code>  sudo make install </code></pre>
            
</ol>
<p> If none error ist found, OpenCV is installed successfully on your Linux system. The header files could be found at the location </p>
        <p><mark>/usr/local/include/opencv4</p></mark>

</body>
</html>

## Run 

Navigate to the file ./ThresholdingForSegmentation/, where the main.cpp file is placed. There, compile the important modules;

        g++ main.cpp objectDetector.cpp -o objectDetector ./directoryWalker/dirWalker.cpp -lstdc++fs `pkg-config --cflags --libs opencv`

Dont forget to use the links for filesystem -> -lstdc++fs und the one for the opencv libs `pkg-config --cflags --libs opencv`.

Once compilated, the file the command ./objectDetector should be excecuted 
    