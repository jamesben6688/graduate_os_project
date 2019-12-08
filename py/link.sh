#Link the C and Python: Call the Python function from C

gcc spicall.c $(/usr/bin/python2.7-config --ldflags) -o spicall
./spicall
