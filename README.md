
# Visual Representations of Sorting Algorithms



## Overview

A time complexity analysis project in C++, focused on implementing the following common sorting algorithms:
-  Bubble Sort
-  Insertion Sort
- Selection Sort
- Merge Sort
- Quick Sort

An option is avalibale to export a file to ultilize with graphing ultilities like gnuplot and many other API's.

In continuation, the SDL development tool is used to generate a real-time visual representation of each sorting algorithms.
## Acknowledgements

 - [gnuplot](http://www.gnuplot.info/)
 - [SDL](https://www.libsdl.org/)
 

## Getting Started
To get started, make sure you have gnuplot and SDL installed.

### Prerequisites
Using gnuplot:
- Linux:

    ```apt-get install gnuplot```

- MacOs:

    ```sudo port install gnuplot```
    
- Windows

    [Download zip file according to your machine](http://www.gnuplot.info/)

Using SDL:

- All necessary files located in src; however, here is the [link](https://www.libsdl.org/) for those who'd like to download the library.
- The use of SDL adds O(n) to the sort; therefore, is only used for visualization.  ```sort_SDL.cpp``` for SDL use
## Usage
- gnuplot
    - Make sure the file is in your working directory on the gnuplot terminal
    - Command:
        - ```set title "Sorting Algorithms Elapsed Time"```
        - ```set ylabel "seconds"```
        - ```set xlabel "size"```
        - ```plot './<filename>'using 1:2 with linespoints title "bubbleSort", './<filename>' using 1:3 with linespoints title "selectionSort", './<filename>' using 1:4 with linespoints title "insertionSort", './<filename>' using 1:5 with linespoints title "mergeSort", './<filename>' using 1:6 with linespoints title "quickSort", './<filename>' using 1:7 with linespoints title "std::sort()"```


- SDL
    - Linux
        - Command: ```make```
    - MacOs
        - Command: ```make```
    - Windows 
        - Command: ```WinGw32-make```
## Roadmap

- [ ] Refining SDL implementations

- [ ] Consolidate methods into a class


## Contact

- [Sao Thao](https://github.com/sdthao)
- [Contact Me](mailto:sao_thao19@yahoo.com)
- [Project Link:](https://github.com/sdthao/Sorting-Algorithm-Analysis)
