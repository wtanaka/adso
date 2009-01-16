The scripts in this directory create the necessary files for the 
compilation of the external MySQL database into the internal Adso
source code. This is useful if you modify the MySQL database and
wish to incorporate the changes in the static software.

Start by typing:

./run

The database dump will take quite a bit of time. When it is done
go into the source directory and type:

./prepare_internal

Then compile the software:

make

The binary produced will be a standard-alone version that does
not need to connect to any external database. Certain features
such as frequency-counting will not work in an independent
compile, as the database will be internal to the software and
entirely static. Because of the way data is stored in the internal
version the software is much slower the first time it is run, although 
there is a significant speed-boost thereafter.


