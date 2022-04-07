# level8

# Après réassemblage du code source on remarque plusieurs action possible.

# si on test de auth puis service on remarque que les adresse se suive et qu'on peux donc passer la verif if (auth[32]) en remplissant auth avec service indirectement

$ ./level8 
(nil), (nil) 
auth a
0x804a008, (nil) 
service
0x804a008, 0x804a018 
service
0x804a008, 0x804a028 
login
