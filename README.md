# Laboratorio 3 - Physics BSc (Course Workspace)

## Overview
This repository collects laboratory exercises developed during the third-year Physics BSc course (Laboratorio 3).
The material spans numerical methods, fitting, Monte Carlo, and experimental data analysis in C++, Python, and MATLAB.

## Folder Index
- [Esercitazione1](Esercitazione1/README.md): C++ OOP basics for vectors, particles, and material points.
- [Esercitazione2](Esercitazione2/README.md): orbital ODE integration with Euler/RK2/Velocity-Verlet + ROOT plots.
- [Esercitazione3](Esercitazione3/README.md): Python numerical methods (including Numerov/Verlet examples).
- [Esercitazione4](Esercitazione4/README.md): MATLAB/Octave PDE schemes (Heat, Laplace, Poisson, CN).
- [Esercitazione5](Esercitazione5/README.md): prism and Gaussian-generation analysis scripts.
- [Esercitazione6](Esercitazione6/README.md): archived drafts and experiment subfolders.
- [Esercitazione7](Esercitazione7/README.md): counting-analysis and fit workflows on high/low-stat data.
- [EsFitI](EsFitI/README.md): linear fit exercises (ROOT and iminuit variants).
- [EsFitII](EsFitII/README.md): exponential and binned likelihood fit exercises.
- [Lez28_09](Lez28_09/README.md): lecture-day examples and analysis scripts.
- [Montecarlo](Montecarlo/README.md): compact Monte Carlo exercises.
- [PrepEsame](PrepEsame/README.md): mixed exam-preparation problem bank.
- [RumoreJ](RumoreJ/README.md): Johnson-noise datasets and analysis scripts.

## Suggested Study Path
1. Start from `Esercitazione1` and `Esercitazione2` for C++ foundations and numerical dynamics.
2. Continue with `Esercitazione3` and `Esercitazione4` for Python and MATLAB numerical schemes.
3. Move to `EsFitI`, `EsFitII`, and `Esercitazione7` for statistical modeling and fitting.
4. Use `Montecarlo` for stochastic-method refresh.
5. Consolidate with `RumoreJ` and `PrepEsame` for complete analysis pipelines and exam training.

## Practical Notes
- Many files with `~` suffix are historical editor backups.
- Several scripts require CERN ROOT and, in some cases, `iminuit`.
- Keep each folder self-contained when running scripts (datasets are usually local to the folder).

## Python Setup
1. Create and activate a Python environment.
2. Install common dependencies from [requirements.txt](requirements.txt).
3. Install CERN ROOT (PyROOT) separately.

Suggested commands:

```bash
pip install -r requirements.txt
```

On Windows, a practical ROOT route is conda-forge:

```bash
conda install -c conda-forge root
```
