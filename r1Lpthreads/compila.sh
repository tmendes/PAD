xlc generateRandomMatrix.c -lm MatrixIO.c
mv a.out generateRandomMatrix 

xlc mMatSerial.c -lm readFiles.c
mv a.out mMatSerial

xlc calcPi.c
mv a.out calcPi

xlc mMatThreads.c -lpthread -lm readFiles.c 
mv a.out mMatThreads

xlc calcPit.c -lpthread -lm
mv a.out calcPit
