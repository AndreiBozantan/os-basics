---
title: Comenzi Shell
---
@import "../os.less"

## 
\section{Shell Arguments}
- exp2, log2
  - COMUNICARE shell -> program
    - parametrii linia de comanda;
    - env vars; char escaping (echo)
  - EXEMPLU: echo 
    - 1 parametru; 
    - mai multi parametri hardcoded indexes; 
    - ex runtime error hardcoded indexes cu mai putini parametri;
  - EXEMPLU: perimetrul cercului
    - validare input (număr si tip parametrii)
  - TEMA : aria forme geometrice cu argumente in linia de comanda 
    - aria dreptunghi, aria triunghi
  - TEMA : convertor unitati de masura: 
    - conv 1 m to inch; 
    - conv 1 g to pounds


### echo samples
echo hello
echo hello os20
echo hello again os20 !

echo ubuntu linux
echo linus torvalds
echo ana are mere

### echo.py - 00

echo.c - cum tipărim un vector în C folosind printf? nu se poate; tipărim doar prima componentă

### echo.py - 0, 1, 2

#echo0.c (hashtag include vs diez include) / echo0.py
$ gcc -Wall -Werror -o echo0 echo0.c 
./echo1.c

#echo1.c / echo1.py
$ ./echo1 coronavirus
$ ./echo1 corona virus

#echo2 / echo2.py
$ ./echo2 corona virus
#? ce afișează următoarea comandă
$ ./echo2 coronavirus

echolist - list all with messages

echo - echo clone - no messages

echo - official version code
https://github.com/coreutils/coreutils/blob/master/src/echo.c

------
Andrei Bozantan, 2020 
[![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
