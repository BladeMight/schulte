## Shulte Table

A simple Shulte table written in C and WinAPI.
By default running shulte, shows 6x6 matrix, but you can use command line arguments to change matrix and rectangle padding.

Usage:
`shulte.exe <matrix> <rectangle_padding>`
 - matrix            - digit - how big matrix will be, if passed 2 it will be 2x2.
 - rectangle_padding - digit - how big will be padding between number squares, default is 2, also possible to use -1 to make it very tin.

Compilation:

To compile run `make` or `mingw-make` in project folder, and make sure you have MinGW.

