# Space Data Parser

[![Release CI](https://github.com/michaelwro/space-data-parser/actions/workflows/build-test-release.yml/badge.svg)](https://github.com/michaelwro/space-data-parser/actions/workflows/build-test-release.yml) [![Development CI](https://github.com/michaelwro/space-data-parser/actions/workflows/build-test-main.yml/badge.svg)](https://github.com/michaelwro/space-data-parser/actions/workflows/build-test-main.yml) [![Pre-Commit](https://github.com/michaelwro/space-data-parser/actions/workflows/pre-commit.yml/badge.svg)](https://github.com/michaelwro/space-data-parser/actions/workflows/pre-commit.yml)

**Code By:** Michael Wrona | GitHub: [@michaelwro](https://github.com/michaelwro)

C++11 library for parsing and processing space data files.

* Parse and interpolate [CelesTrak](https://celestrak.org/SpaceData/) earth orientation parameter (EOP) releases.

## Build Instructions

This project gets compiled into a shared library `build/lib/libsdp.so`.

### VS Code Build Tasks

VS Code build tasks are configured for this project. They can be run with `CTRL+SHIFT+B`. Select between debug and release builds.

### Build Scripts

```shell
bash scripts/build-debug.sh
bash scripts/build-release.sh
```

## CelesTrak EOP File Snippet

```txt
DATE,MJD,X,Y,UT1-UTC,LOD,DPSI,DEPS,DX,DY,DAT,DATA_TYPE
2018-01-01,58119,0.059258,0.247585,0.2163567,0.0008094,0.000118,-0.000175,0.041955,0.007790,37,O
```

## Examples (WIP)

Below are my ideas for the interface.

```cpp
sdp::CelesTrakEOP eop_parser("data.csv");

eop_parser.load();  // all
eop_parser.load_range(5000, 5500);  // input mjd -> input mjd
eop_parser.load_range("2020-01-01", "2021-01-01");  // input date -> input date

eop_parser.load_from_begin(5500);  // table begin -> input end mjd
eop_parser.load_from_begin("2021-01-01");  // table begin -> input end date

eop_parser.load_to_end(5000);  // input begin mjd -> end
eop_parser.load_to_end("2020-01-01");  // input begin date -> end

sdp::celestrak_eop_t eop = parser.get_all(5612.6);  // all via struct?
double x = parser.get_dpsi(5612.6);  // one via method?
double x = parser.get(5612.6, sdp::eop::dPsi);  // one via enum?
```

## Resources

* [EOP and Space Weather Data (CelesTrak)](https://celestrak.org/SpaceData/)
* [https://jayemmcee.wordpress.com/cubic-splines/](https://jayemmcee.wordpress.com/cubic-splines/)
* [https://en.wikiversity.org/wiki/Cubic_Spline_Interpolation](https://en.wikiversity.org/wiki/Cubic_Spline_Interpolation)

## Repository

This project can be found [here](https://github.com/michaelwro/space-data-parser).

```shell
git clone https://github.com/michaelwro/space-data-parser.git
```


## Non Affiliation

I am not affiliated with CelesTrak in any way. I'm just a nerd making a tool for other nerds to use :)
