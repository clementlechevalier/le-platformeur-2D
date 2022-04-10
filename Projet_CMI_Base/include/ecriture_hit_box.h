#ifndef HITBOXX
#define HITBOXX

void positionMouse(int *,int *);
void affichRect(std::vector<std::vector<int>> *, Map &mapping);
void modifHitBox(std::vector<std::vector<int>> *);
void supppr(std::vector<std::vector<int>> *);

void creeHitBox(std::vector<std::vector<int>> *);
/**quand cette fonction est appelée,
il suffit de regarder la ligne de commande et
vous serez guidé afin de créer une hit box.**/
void ecritDansTxt(std::string,std::vector<std::vector<int>> *);
void getMapData(std::string txtName, Map &mapping,std::vector<std::vector<int>> *vect);

#endif
