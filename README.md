# Smooth polygon algorithm
## Description
The application demonstates the work of the algorithm for constructing an arbitrary polygon with smoothed vertices. Determination of the points needed to smooth vertices is based on utilizing the de Casteljan algorithm (quadratic Bezier curve). 

The work of the algorithm for smoothing a single vertex of the polygon is schematically shown in Fig. 1. For the algorithm successfull work, it is necessary to know the coordinates of three vertices: the vertex for which the smoothing occurs, the previous and subsequent vertices of the polygon.  

<img src="/img/curve.png" alt="Curve.png" width=40%>&nbsp;&nbsp;&nbsp;
<img src="/img/curve_animation.gif" alt="Curve animation.gif" width=40%>&nbsp;&nbsp;&nbsp;

**Fig. 1.** Schematic view of the de Casteljan algorithm (quadratic Bezier curve) [1].

When tha application is started, two graphic windows are opened: *drawing window* which render a smooth polygon and *control window* which determines settings for the generation of a new polygon. These windows are shown on Fig. 2. GUI windows were created with help of Qt5 framework [2]. C++ language was used for writing the application code. It can successfully be compiled with the Qt Creator and run under different OS.

<img src="/img/drawing_window.png" alt="Drawing window.png" width=60%>&nbsp;&nbsp;&nbsp;
<img src="/img/control_window.png" alt="Control window.png" width=30%>&nbsp;&nbsp;&nbsp;

**Fig. 2.** Drawing and control windows of the program.

## Documentstion
When application is running the result of generation and rendering of a smooth polygon in drawing window can be controlled using control window. Control window has a number of spin box widgets for setting the lower and upper bounds of the following parameters:

`Major points`&nbsp;-&nbsp;Number of major points (vertices) of a polygon.<br>
`Smooth points`&nbsp;-&nbsp;Number of points that defines the quality of smoothing of every particular polygon vertex. It is obvious that more smooth points results to the more smooth surface.<br>
`Round quality`&nbsp;-&nbsp;Parameter showing how close the begining and end poits of a smoothing curve (Bezier curve) to the polygon vertex. Lower value produces more sharp corner.<br>

After pressing the `Generate polygon` button, the polygon is generated and rendered with a set of parameters, the values of which are randomly selected between the defined MIN and MAX values. For example, if `MIN major points = 3` and `MAX major points = 10` are defined for the `Major points` parameter, then only polygons with the number of vertices from 3 to 10 will be generated randomly. The situation is similar for the rest parameters.

## Install from source
Installation, compilation and run of the application occurs when executing commands in a terminal window (The method is described for a UNIX-like terminal, for example, Bash from MSYS2. It also requires a working Mingw-w64 - G++ compiler, Qt5 framework libraries installed and configured paths).

-	Copying the repository to a local directory:
```
$ git clone https://github.com/juvus/Smooth_polygon_algorithm.git
$ cd Circles_packaging_simulation/
```
-	Configuring of the application with qmake:
```
$ 
```


-	Compiling of the application:
```
$ mingw32-make
```
-	Running the application:
```
$ cd build/
$ ./Program
```

## Project Organization
- <img src="/img/folder.png" alt="folder" width=18px> `include/` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Public header files
- <img src="/img/folder.png" alt="folder" width=18px> `data/` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Files necessary for application
- <img src="/img/folder.png" alt="folder" width=18px> `src/` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Source code files
- <img src="/img/folder.png" alt="folder" width=18px> `img/` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Images, necessary for the documentation
















## Licence
Smooth polygon algorithm code in this project is available under the `GPLv3` license. You can find the license file here: [LICENSE](/LICENSE)

## References
[1] https://en.wikipedia.org/wiki/B%C3%A9zier_curve<br>
[2] https://www.qt.io/<br>

