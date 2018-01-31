This repository contains the scaffold of simple project that aims to help in iteratively develop simple part of code that is referring to constant data that is costly to load/preprocess.

```
mkdir -p build
cd build
cmake ..
make
./CommonData
```

The branch continous-loading implements the simple signal-based method to continuously reload library during development for each build as cmake post-build custom task. Nothing fancy, but can be used efficiently within CLion IDE (also with debugger).
