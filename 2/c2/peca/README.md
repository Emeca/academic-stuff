# peca
Power Explorer CApivara

Use Borland C++ 3.1 to Compile, in installers directory, originally from [here](http://borlandc.org/download-borland-c-3-1/) or this [direct link](http://talentirosit.ro/download/bc31.rar)

This how-to is based on [this link](http://borlandc.org/how-to-download-and-install-borland-c-3-1-on-linux-ubuntu-others/)

## Using dosbox to install bc3.1 compiler

* Install dosbox, in debian system do:

 $ sudo apt-get install dosbox

* Create C: for dosbox:

```
$ export PREFIX=$HOME
$ mkdir -p $PREFIX/c
```

* Extract the file installers/bc31.tar.xz

```
$ tar xJf installers/bc31.tar.xz -C $PREFIX/c
```

* Run dosbox

```
$ dosbox
```

* On dosbox window mount C: and install bc3.1

```
Z:\>mount c ~/c
Z:\>c:
C:\>cd bc31
C:\BC31>INSTALL.EXE
```

## Install BC3.1

Follow the instructions

* When prompted source drive, type C
* Ignore messages about missing windows directory
