Tout d’abord, les règles de déplacement de chaque pièce :
- Le pion : Il peut se déplacer de 1 ou 2cases lorsqu’il se trouve sur sa ligne de départ, puis
que d’une seule ensuite. Il peut prendre une pièce adverse seulement sur la diagonale et à une
distance de 1 case uniquement. Il ne se déplace sinon qu’en ligne droite. Lorsqu’il arrive à la dernière
colonne de l’échiquier, alors il peut prendre n’importe quelle pièce excepté un pion ou un roi.
- Le fou : Il ne peut se déplacer qu’en diagonale jusqu’à rencontrer une pièce alliée ou
adverse (prise possible dans ce cas là).
- Le cavalier : Il ne se déplace qu’en forme de L (déplacement soit de 1 case latéralement et
2 cases en avant, soit d’une case en avant puis de 2 en latérale). Cela donne donc 8 possibilités si et
seulement si chaque coup est valide (pas de prise alliée ni sortie de l’échiquier).
- La tour : Elle ne se déplace qu’en ligne droite (soit en avançant, soit latéralement) jusqu’à
rencontrée une pièce alliée ou adverse (dans ce cas la prise est donc possible).
- La dame : Elle combine les déplacements du fou et de la tour (peut donc se déplacer en
ligne et droite et en diagonale).
- Le roi : Il ne peut se déplacer que s’il n’est pas en échec après son déplacement et
seulement sur 1 des 8 cases l’entourant (si cela est possible bien entendu). Il ne doit donc pas arriver
sur une case et être en échec (coup refusé). Il peut effectuer un “ROQUE” afin d’échanger la position
de la tour avec celle du roi (coup expliquer plus bas).
Maintenant, les règles de l’échec/mat/roque/promotion(changement de pièce) :
- Echec : Le roi est en échec si et seulement si il est menacé d’une prise. Le roi doit donc alors
immédiatement s’enlever de cet échec. Deux manières sont possibles, la première qui est de
déplacer son roi sur une case ne pouvant être prise par une pièce adverse, lui évitant d’être en
échec. Ou la deuxième solution, est de placer une pièce de telle sorte que la pièce “bloque” le
chemin de la prise. Le roi n’est alors plus en échec dans ce cas-ci. De toute les manières le roi ne doit
plus être en échec après le tour du joueur étant en échec.
- Mat : Le roi est en échec (menace de prise sur le roi) et le roi ne peut pas s’en défaire. Il y a
donc échec et mat. La partie se finie donc et le vainqueur est celui ayant mis en échec et mat le roi
adverse.
- Roque : Ce déplacement est très particulié. En effet, il s’agit du seul coup où déplacer deux
pièces devient possible. Le roi et la tour peuvent échanger de place en se rapprochant. Il existe de
type de roque (le grand et le petit roque) qui diffère que de part la distance entre le roi et la tour
(très peu de différence visuelle). Pour effectuer un ‘roque’ le joueur après avoir cliqué sur le roi doitcliquer sur la tour avec laquelle il veut effectuer le roque. Cependant, cela n’est possible que si
plusieurs conditions sont remplies. Premièrement, le roi ne doit pas être en échec que ce soit sur sa
position de départ ou sur sa position d’arrivée (dans ce cas, le déplacement n’est pas effectué). De
plus, si la tour a bougé alors il n’est pas possible d’effectuer le roque. De même si le roi a déjà bougé
auparavant. Enfin, si vous l’avez bien compris, à titre d’exemple. On ne peut effectivement pas
déplacer une des 4 tours puis le tour suivant la replacée sur sa ligne de départ afin d’effectuer
encore au tour suivant un roque entre le roi et cette tour.
- Promotion : Lorsque un pion arrive à la fin de l’échiquier (sachant qu’il ne se déplace qu’en
avant), il peut être promu en chacune des 4 pièces suivantes. Soit le fou, le cavalier, la tour ou
encore une dame. Le roi peut être mis en échec grâce à la promotion (exemple : pion transformé en
une tour et se trouvant sur la même colonne que le roi), le roi devra donc enlever cet échec, s’il ne
peut pas alors il y a échec et mat.
Les différentes cases possibles sont entourées en bleu et il n’y en a uniquement sur les cases dont le
déplacement est valide (pour chaque type de pièce).
Lorsque la pièce est sélectionné par le joueur à l’aide d’un clic gauche alors la case de la pièce est
surligner en bleu clair.
Il est nécessaire de cliquer de nouveau avec son bouton gauche afin d’effectuer un déplacement (s’il
est valide, il y aura une animation sinon la pièce restera sur sa case de départ).
En cas d’échec et mat, une image apparaitra annonçant l’échec et mat.
A chaque fois qu’une pièce a effectué un déplacement (donc il est validé) alors la couleur du joueur
change. Aux échecs la couleur de départ est blanche. Ensuite, viens le tour des pièces noires, et cela
alterne continuellement.
Pour compiler, tapez la commande (dans le terminal) :
Pour lancer le programme, tapez la commande (dans le terminal) :
make
./Echecs
Vous pouvez vous référrer aux différentes pièces ici (le pion, le fou, le cavalier, la tour, la dame, le
roi) soit pour les règles, sinon si vous ne vous en souvenez plus.
De plus, les déplacements de chaque pièce et du roque vous seront présentées dans le menu ainsi
que les différentes images associées à chacune des pièces.
