# GBDevCourse

Learning C through GBDK 2020. This is part of the course "Structured Programming", for the 2nd semester of the main track of studies in the Department of Music Technology and Acoustics, Hellenic Mediterranean University. ([mta.hmu.gr](https://mta.hmu.gr/en/home/))

This repository is intended to run on linux - or in WSL for windows. 

### Dependencies

The only dependences in a linux system should be java runtime and make. You can install those dependencies via:

```
sudo apt install default-jre
```
and 
```
sudo apt install make
```

### How to run

Any time you open a terminal, you need to run `./start.sh`, just to add the included GBDK 2020 version in the temporary path of the open terminal. This script also checks if java runtime is installed. You should run `./start.sh` every time you open a new terminal.

For the tutorials, you should run `make` to compile and build the project and `make run` to compile-build and open the emulator directly. You can run `make run` from the get-go (no need to run `make` first). You should run those commands only from a terminal that has been initialized with `./start.sh`. It may still run otherwise, but follow this instruction to be safe.

For making a new project, you can copy the entire `template_project` to a new folder *in the root directory* of the repository. Beware, the path in the `Makefile` of the `template_project` looks at the relative path of GBDK 2020 as if it is placed in the relative path `GBDK = ../tools/gbdk_linux64/gbdk`. Please make sure to change this line in `Makefile` if you intent to put you project on a different directory.