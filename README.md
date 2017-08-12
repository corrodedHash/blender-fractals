# Fractal
###### Generate any fractal that can be described by a [Lindenmayer system](https://en.wikipedia.org/wiki/L-system).

| Master | Develop |
| --- | --- |
| [![Master branch - Build Status](https://travis-ci.org/corrodedHash/blender-fractals.svg?branch=master)](https://travis-ci.org/corrodedHash/blender-fractals) | [![Build Status](https://travis-ci.org/corrodedHash/blender-fractals.svg?branch=develop)](https://travis-ci.org/corrodedHash/blender-fractals) |

<img src="images/sierpinski.png" width="240"></img>
<img src="images/menge.png" width="240"></img>
## How to install and enable an add-on (v.2.78)

### Install add-on

- Download this as a zip file
- Go to `File > User Preferences... > Add-Ons`
- On the Bottom, click on `Install from File...`
- Select the zip file you want to install

### Enable an add-on

Just... Find the add-on in the `User Preferences` somehow, and tick the checkbox

### Draw a fractal

`Add` > `Mesh` > `Fractal`<br>
In the "New entity properties" - toolbox you first have to specify a [Lindenmayer system](https://en.wikipedia.org/wiki/L-system). A few examples are in this repository, in the directory `test_grammars`.<br>
Then, just iterate away.<br>
**Be careful though, these fractals can grow exponentially, iterate away in a _slow_ manner**

## A million thanks to the wonderful people of ANTLR

Who provided the parser generator I used, which made this project a thousand times easier.<br>
Their [project](http://www.antlr.org/).
