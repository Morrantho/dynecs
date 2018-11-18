g++ \
-Wall \
-Werror \
-ldynecs \
-L$PWD/../bin \
-I$PWD/../include \
-o main main.cpp

export LD_LIBRARY_PATH=$PWD/../bin:$LD_LIBRARY_PATH
./main
unset LD_LIBRARY_PATH