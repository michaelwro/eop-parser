# EOP Parser

[![Build & Test](https://github.com/michaelwro/eop-parser/actions/workflows/build-test-main.yml/badge.svg)](https://github.com/michaelwro/eop-parser/actions/workflows/build-test-main.yml) [![Pre-Commit](https://github.com/michaelwro/eop-parser/actions/workflows/pre-commit.yml/badge.svg)](https://github.com/michaelwro/eop-parser/actions/workflows/pre-commit.yml)

**Code By:** Michael Wrona | GitHub: [@michaelwro](https://github.com/michaelwro)

C++ library for parsing and interpolating [CelesTrak](https://celestrak.org/SpaceData/) earth orientation parameter (EOP) releases.

## CelesTrak EOP File Example

```txt
DATE,MJD,X,Y,UT1-UTC,LOD,DPSI,DEPS,DX,DY,DAT,DATA_TYPE
2018-01-01,58119,0.059258,0.247585,0.2163567,0.0008094,0.000118,-0.000175,0.041955,0.007790,37,O
2018-01-02,58120,0.057424,0.248531,0.2155887,0.0007372,0.000150,-0.000206,0.042005,0.007839,37,O
2018-01-03,58121,0.055761,0.249477,0.2148521,0.0007549,0.000198,-0.000220,0.041868,0.007691,37,O
```

## Build Instructions

This project gets compiled into a shared library `build/lib/libeopparser.so`.

### VS Code Build Tasks

VS Code build tasks are configured for this project. They can be run with `CTRL+SHIFT+B`. Select between debug and release builds.

### Build Scripts

```shell
bash scripts/build-debug.sh
bash scripts/build-release.sh
```

## Repository

This project can be found [here](https://github.com/michaelwro/eop-parser).

```shell
git clone https://github.com/michaelwro/eop-parser.git
```

## Brainstorming

```cpp

EopParser parser("data.csv");  

/**
 * parse file for date range, generate spline interpolation polynomials
 */
parser.read(5900);  // MDJ, input -> table end
parser.read(0, 5900);  // MJD range
parser.read("2022-01-01");  // date string, input -> table end
parser.read("2021-01-01", "2022-01-01");  // date string range

// auto [x, y, dut, lod, ... ] = parser.get_all(5801.745);  // C++17 structured binding

// Iau2006Eop eop = parser.get_iau2006(5780.5);  // particular set via class
// double x = eop.X();

EopParser::fk5_t eop = parser.get_fk5(5612.6);  // particular set via struct
double x = eop.X;
```
