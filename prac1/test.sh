gcc -fPIC -shared -o malw_lib.so malw_lib.c -ldl &&
LD_PRELOAD=$(pwd)/malw_lib.so ps
