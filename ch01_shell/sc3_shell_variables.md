\section{Variable SHELL}

# BASH/environment VARIABLES:
v = "corona virus"
echo $v

# două comenzi pe linie
d = "covid 19"; echo $d
echo 1; echo 2;

# SOME BASH VARIABLES:
echo $BASH_VERSION
echo $HOME
echo $PWD
echo $SHELL
echo $USER
echo $RANDOM
echo $PATH 


#? ce afisează următoarea comanda
v = corona virus

#rezolvare - escape chars - similar cu limbajul C
v = corona\ virus

#? ce afișează următoarea comandă
v = corona$virus

#rezolvare
v = corona\$virus

# ENV VARS in C / Python

#penv.c
# v0 - fail
# v1 - fail again
# v2 - envp main argument
# v2 - try in ipython
# install ipython:
    # sudo apt-get update -y
    # sudo apt-get install -y ipython
# os.environ
# os.environ.get
# os.environ['USER']


# getopt

