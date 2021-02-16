# Smooth polygon algorithm
## Description
The application demonstates the work of the algorithm for constructing an arbitrary polygon with smoothed vertices. Determination of the points needed to smooth vertices is based on utilizing the de Casteljan algorithm (quadratic Bezier curve). 

Схематически работа алгоритма для сгругления одной вершины многоугольника паказана на рис. 1. Для успешной работы алгоритма необходимо знать координаты трёх вершин: вершины для которой происходит скругление, предыдущей и последующей вершины многоугольника.  

<img src="/img/curve.png" alt="Curve.png" width=60%>&nbsp;&nbsp;&nbsp;
<img src="/img/curve_anumation.gif" alt="Curve animation.gif" width=60%>&nbsp;&nbsp;&nbsp;

**Fig. 1.** Схематическое изображение работы алгоритма по скруглению вершины многоугольника.

When tha application is started, two graphic windows are opened: *drawing window* which render a smooth polygon and *control window* which determines settings for the generation of a new polygon. These windows are shown on Fig. 1.

<img src="/img/drawing_window.png" alt="Drawing window.png" width=60%>&nbsp;&nbsp;&nbsp;
<img src="/img/control_window.png" alt="Control window.png" width=30%>&nbsp;&nbsp;&nbsp;

**Fig. 2.** Drawing and control windows of the program.

## Documentstion
Documentation











## Licence
Circles packaging simulation code in this project is available under the `GPLv3` license. You can find the license file here: [LICENSE](/LICENSE)

## References
[1] https://en.wikipedia.org/wiki/B%C3%A9zier_curve
