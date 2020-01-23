read -p 'n_size=' n_size
read -p 's_size=' s_size
echo $n_size
echo $s_size
g++ 1.cpp
./a.out $n_size
g++ 1opt1.cpp
./a.out $n_size
g++ 1opt2.cpp
./a.out $n_size $s_size
g++ 1opt2swap.cpp
./a.out $n_size $s_size
g++ 1opt3.cpp
./a.out $n_size