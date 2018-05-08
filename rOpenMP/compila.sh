xlc generateRandomMatrix.c -lm MatrixIO.c
mv a.out generateRandomMatrix 

xlc mMatSerial.c readFiles.c
mv a.out mMatSerial

xlc mMatOpen.c -q64 -qsmp -qthreaded readFiles.c MatrixIO.c
mv a.out mMatOpen

