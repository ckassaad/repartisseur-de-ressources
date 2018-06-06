# repartisseur-de-ressources

Le projet consiste à implémenter un répartisseur de ressources c’est à
dire un programme qui sur la donnée d’un certain nombre de ressources
(mémoire, processeurs...) doit les répartir entre les différents programmes.

Pour cela il faut coder un programme qui prend en argument la com-
mande que l’on souhaite lancer et interrogera le programme central,

qui lui sera chargé de la gestion des ressources, pour savoir si il y a des
ressources disponibles. Si il y a suffisament de ressources, le programme
est lancé et les ressources utilisées sont bloquées, sinon il est mis sur
liste d’attente avec une certaine priorité. Lors de la phase de réflexion
préalable à tout projet de ce type nous avons dû considérer plusieurs

problématiques. Premièrement, le choix du langage, ensuite les commu-
nications entre le programme central et le programme chargé de trans-
mettre les commandes au programme central. Dans un troisième temps

nous avons réfléchis au mécanisme de blocage des ressources lorsqu’un

programme qui dispose de suffisamment de ressources s’éxécute. En-
suite nous avons réféléchis à l’implémentation de la file d’attente et

enfin au découpage du projet en module et à la répartition des tâches
au sein du groupe.
