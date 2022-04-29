# pipex
[![dexposit's 42 pipex Score](https://badge42.vercel.app/api/v2/cl2hrwxk3011709jppzcysckf/project/2565211)](https://github.com/JaeSeoKim/badge42)

In this project you should reply the next shell command:
Shell:  <infile command | command >outfile
Pipex:  ./pipex infile command command outfile

In the bonus part of this project we implement the same shell command but with variable number of commands:
Shell:  <infile cmd1 | ... | cmdn >outfile
Pipex:  ./pipex infile cmd1 ... cmdn outfile
And you have to implement the here_doc (<<) functionality of shell with the operators >> for the outfile:
Shell: << limit cmd | ... | cmdn >> outfile
Pipex:  ./pipex here_doc limit cmd ... cmdn outfile
