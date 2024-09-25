Tout comme dans les deux exercices precedents, on va devoir jouer avec printf.
Ici on va vouloir rediriger l'execution de la fonction exit vers la fonction 'o'.

En testant je vois que le debut du buffer est au 4eme argument de printf.

Video interessante sur le sujet: [Global Offset Table (GOT) and Procedure Linkage Table (PLT) - Binary Exploitation PWN101](https://www.youtube.com/watch?v=B4-wVdQo040)

En debug avec gdb, on voit que le premier appel de 'exit' renvoie dans la section .plt (RX), 
qui fait un jump vers .got.plt (RW) qui contient l'addresse reelle de la fonction exit.  

INFO: Au premier appel d'une fonction d'une librairie linkee dynamiquement, l'addresse dans .got.plt renvoie vers 
la section .plt qui va appeler le linker dynamiquement pour obtenir l'addresse de la fonction et la stocker dans .got.plt.
Ainsi tous les futurs appels de la fonction iront directement a la bonne addresse et n'appeleront plus le linker.

On va donc vouloir ecraser l'addresse de exit dans .got.plt avec l'addresse de la fonction 'o'.
Et cela en utilisant '%n' de printf pour ecrire un nombre a une addresse donnee.

On peut donc dors et deja convertir l'addresse de 'o' en decimal pour avoir le bon nombre de bytes ecrits.  
0x80484a4 => 134513828 en decimal.

Il nous faut aussi l'addresse ou ecrire ce nombre. Avec gdb je vois que .plt fait un jump vers ds:0x8049838
On va donc ecrire dans cette addresse.
0x8049838 => '\x38\x98\x04\x08'

On peut donc faire notre exploit:
1. [4] Dans le buffer on met l'addresse de 'o'
2. [4 + 8*2 = 20] On print 2 fois '%x' pour utiliser 2 arguments de la stack
3. [20 + 134513808] On print 134513808 characteres + on utilise un argument de la stack
4. [134513828] On print '%n' pour ecrire le nombre de characteres print dans l'addresse de exit

```bash
level5@RainFall:~$ python -c "print '\x38\x98\x04\x08' + '%8x'*2 + '%134513808x' + '%n'" > /tmp/payload5
level5@RainFall:~$ cat /tmp/payload5 - | ./level5
                             200
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```