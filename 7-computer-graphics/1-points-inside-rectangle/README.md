Searches for points inside of the rectangle.

Initialize the environment with 'Run' button, than click in two random places
to set the rectangle.

`O(N^2)` to initialize (once per points set), each query is `O(logN)`.
Uses `O(N^2)` of memory.

Not sure if all `N` points are always drawn correctly (possibly a bug).
