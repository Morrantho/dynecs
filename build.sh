g++ -c -Wall -Werror -fpic src/dynecs.cpp
mv *.o ./obj
g++ -shared -o bin/libdynecs.so obj/dynecs.o