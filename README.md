# SokoSolver
Sokoban solver.

## Description
SokoSolver is find a solution to a given Sokoban level.
For the puspose of this task PSPACE-compatible problem may be used.
The original source code is "C++ Unordered Set-based Version" of "https://rosettacode.org/wiki/Sokoban".
SokoSolver is customized followed:
- The map management method from std::vector&lt;std::string&gt; to std::string.
- Not used boost library, and used std::unorderd_set.
- Use original hash method of Table.
- Support '*' (box on goal) and '+' (player on goal) characters.
- Check table has '#' (wall).
- Matching goal tuples, and not matching goal map.
- Maps to be checked can be specified with command line options

## Requirement
SokoSolver will run on Windows (Console application).

## Usage
~~~
Usage: SokoSolver.exe [-input {filename} | -stdin] [-verbose]
  -input    Input map from filename.
  -stdin    Input map from stdin.
  -verbose  Enable verbose mode.
~~~

Example:
~~~
SokoSolver.exe -input sample/sample1.txt -verbose
#######
#     #
#     #
#. #  #
#. $$ #
#.$$  #
#.#  @#
#######
100000: open=17115 / 17415 visited=117114
ulULLulDDurrrddlULrruLLrrUruLLLulD
count=168710 open=21565 visited=190098
593 msec.
~~~

| sample map  | runtime    | move count  |
|:------------|-----------:|------------:|
| sample1.txt |  595 msec. |    34 moves |
| sample2.txt | 4868 msec. |   127 moves |
| sample3.txt |    6 msec. |    47 moves |

## Build
The following environment is necessary to build.
- Visual Studio 2017

Please build with Release x64 mode (Speed priority).
Debug mode is very slow.

# License
GNU General Public License v3.0
