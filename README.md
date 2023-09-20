# Dynamic substring comparison problem: segment tree approach

The paper is in `paper-src/paper.pdf`. The Typst template, Hayagriva bibliography and the paper source can be found alongside.

### Repository structure

Each subproblem considered in the paper has its own folder. Each folder has the Python helper scripts:

1. Test generators (pseudorandom test generation with specified parameters) - `_gen-tests.py`.
2. Mini-test generators (small tests to avoid wasting time on running slow implementations instead of just showing how slow they are on smaller tests) - `_gen-mini-tests.py`.
3. Benchmarking scripts (C++ console invoking, timing, writing to the corresponding CSV) - `_run-tests.py`.
4. Plotters (configured to produce output to be inserted in the paper source) - `_plot-data.py`.

The C++ implementations for the corresponding problem can be found in `implementations`. Note that to run the tests yourself, you will have to compile the executables for your machine from source. Please refer to the source code of `_run-tests.py` to see the folder structure the scripts expect.

The `measurements` folder contains the test results which have been obtained from the generated testset. It has been added here for reference and debugging. The actual results will be different depending on the CPU/OS. Those are the files from which all the plots in the paper have been produced. The format is as follows: `<test-size>,<qp/ln>,<time-in-milliseconds>`.