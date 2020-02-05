echo "Naive ka chl rha"
g++ -O1 Naive.cpp
./a.out 1024 64
g++ -O2 Naive.cpp
./a.out 1024 64
g++ -O3 Naive.cpp
./a.out 1024 64


echo "Opt1 ka chl rha"
g++ -O1 opt1.cpp
./a.out 1024 64
g++ -O2 opt1.cpp
./a.out 1024 64
g++ -O3 opt1.cpp
./a.out 1024 64

echo "Opt2 ka chl rha"
g++ -O1 opt2.cpp
./a.out 1024 64
g++ -O2 opt2.cpp
./a.out 1024 64
g++ -O3 opt2.cpp
./a.out 1024 64

echo "Opt3 ka chl rha"
g++ -O1 opt3.cpp
./a.out 1024 64
g++ -O2 opt3.cpp
./a.out 1024 64
g++ -O3 opt3.cpp
./a.out 1024 64