# Space Data Parser

[![Build & Test](https://github.com/michaelwro/eop-parser/actions/workflows/build-test-main.yml/badge.svg)](https://github.com/michaelwro/eop-parser/actions/workflows/build-test-main.yml) [![Pre-Commit](https://github.com/michaelwro/eop-parser/actions/workflows/pre-commit.yml/badge.svg)](https://github.com/michaelwro/eop-parser/actions/workflows/pre-commit.yml)

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

## CelesTrak EOP File Example

```txt
DATE,MJD,X,Y,UT1-UTC,LOD,DPSI,DEPS,DX,DY,DAT,DATA_TYPE
2018-01-01,58119,0.059258,0.247585,0.2163567,0.0008094,0.000118,-0.000175,0.041955,0.007790,37,O
2018-01-02,58120,0.057424,0.248531,0.2155887,0.0007372,0.000150,-0.000206,0.042005,0.007839,37,O
2018-01-03,58121,0.055761,0.249477,0.2148521,0.0007549,0.000198,-0.000220,0.041868,0.007691,37,O
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

## Repository

This project can be found [here](https://github.com/michaelwro/space-data-parser).

```shell
git clone https://github.com/michaelwro/space-data-parser.git
```

## Non Affiliation

I am not affiliated with CelesTrak in any way. I'm just a nerd making a tool for other nerds to use :)
