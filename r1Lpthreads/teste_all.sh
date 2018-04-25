
./generateRandomMatrix 10 10 10a
./generateRandomMatrix 10 10 10b

./generateRandomMatrix 100 100 100a
./generateRandomMatrix 100 100 100b

./generateRandomMatrix 1000 1000 1000a
./generateRandomMatrix 1000 1000 1000b


./mMatSerial 10 10 10a 10 10 10b
./mMatSerial 100 100 100a 100 100 100b
./mMatSerial 1000 1000 1000a 1000 1000 1000b


./mMatThreads 2 10 10 10a 10 10 10b
./mMatThreads 4 10 10 10a 10 10 10b
./mMatThreads 8 10 10 10a 10 10 10b
./mMatThreads 8 100 100 100a 100 100 100b
./mMatThreads 4 100 100 100a 100 100 100b
./mMatThreads 2 100 100 100a 100 100 100b
./mMatThreads 2 1000 1000 1000a 1000 1000 1000b
./mMatThreads 4 1000 1000 1000a 1000 1000 1000b
./mMatThreads 8 1000 1000 1000a 1000 1000 1000b
