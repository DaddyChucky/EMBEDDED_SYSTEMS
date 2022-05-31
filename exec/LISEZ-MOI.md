Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

Identification:
  Travail    : Projet final
  Section #  : 3
  Équipe #   : 109115117


- Make la librairie en premier dans /projet/lib/ avant de Make dans /projet/exec/

- Le circuit à téléverser sur SimulIDE est circuit.simu avec la version .3

- Le voltage de référence devrait être 2.6 V pour le Can interne ET le Can externe. Normalement, cela est déjà ajusté au sein du circuit.

- Les boutons affichent toujours un message lorsqu'ils sont appuyés. Toutefois, ils affichent un second message indiquant qu'une configuration a changé si l'appui cause un changement (par exemple, appuyer deux fois sur le bouton '4' alors que nous nous trouvions déjà à une vitesse de lecture 4 fois/seconde, il n'y aura que 2 messages envoyés - versus - si nous appuyons 2 fois sur le bouton dièse, il y aura 4 messages affichés, peu importe l'état).

- Le main se trouve dans projet.cpp

- Devrait compiler avec c++14

- La documentation du code de la librairie se trouve dans les .h


Bonne compilation !
