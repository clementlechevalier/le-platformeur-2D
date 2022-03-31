#ifndef HITBOXX
#define HITBOXX

std::vector<int> positionMouse();
void affichRect(std::vector<std::vector<int>> *);
void modifHitBox(std::vector<std::vector<int>> *){

void creeHitBox(std::vector<std::vector<int>> *);
/**quand cette fonction est appelée,
il suffit de regarder la ligne de commande et
vous serez guidé afin de créer une hit box.**/
void creeRectangle();
/**quand cette fonction est appelée
regarde la ligne de commande
il sera écrit dans un fichier text nommé decor.txt
les propriété du réctangle crée.
**/


#endif
