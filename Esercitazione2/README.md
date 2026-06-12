# Esercitazione 2

## Overview
Numerical integration of orbital dynamics using custom ODE methods (Euler, RK2, and Velocity Verlet) with ROOT-based visualization.

## Main Files
- `OdeSolver.h`, `OdeSolver.cpp`: ODE solver core and time-stepping logic.
- `Main.cpp`: simulation setup, force callbacks, plotting.
- `fileInput`: input dataset for initial conditions.

## Requirements
- C++ compiler with C++11 support
- CERN ROOT

## Build Hint
Compile linking ROOT and the classes required by `PuntoMateriale` and `Vettore`.

## Notes
The solver is structured around internal (`fInterna`) and external (`fEsterna`) force callbacks to keep the physics model configurable.
