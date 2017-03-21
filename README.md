Philosophes
===========

L'objectif de ce projet et d'apprendre l'utilisation de multi-threads en C.

---

Plusieurs philosophes sont autour d'une table et possèdent chacun une baguette. 

Un philosophe peut: 
- Dormir
- Manger								
- Réfléchir
										
En sachant qu'un philosophe peut manger uniquement manger s'il possède deux baguettes, réfléchir avec une seule baguette et dormir avec ou sans baguette.

Chaque philosophe possède un certain nombre de grain de riz qui est défini en argument au démarrage. Lorsqu'un philosophe mange, le nombre de grain de riz -= 1. Lorsqu'un philosophe arrive à 0 grains de riz alors tous les autres doivent arrêter de manger et le programme doit également s'arrêter.

Un philosophe doit manger avant de dormir puis réfléchir. 
On obtient donc l'ordre suivant: [manger -> dormir -> réfléchir] en boucle.

L'objectif principal est d'équilibrer au maximum les actions manger, dormir et penser pour essayer d'obtenir un ratio de 1:1:1.

Utilisation
-----------

```
$> make
$> ./philosophe -p X -e Y
```
X = nombre de philosophes et Y = nombre de grain de riz par philosophe
