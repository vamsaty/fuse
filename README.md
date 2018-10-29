# s3fs
A filesystem using fuse

# STEPS

# go to the directory
Open terminal, then :: 
1)  fusermount -f [ dir_name ]
2)  make
3)  ./fsfs -f [dir_name ]
here dir_name is the name of the directory you want to have as the mount point


# Known issues ::
1) non-trivial disignated initializers not supported

# Solution ::
the order of assigning 'operations' should be the same as in the "fuse operations" structure. So check your 
fuse operations structure