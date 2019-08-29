#include "collision.h"
#include <math.h>

bool pointCollision(int x,int y,SDL_Rect box){
    if (x >= box.x
    && x < box.x + box.w
    && y >= box.y
    && y < box.y + box.h)
       return true;
   else
       return false;
}
bool boxCollision(SDL_Rect box1,SDL_Rect box2){
   if((box2.x >= box1.x + box1.w)      // trop à droite
    || (box2.x + box2.w <= box1.x) // trop à gauche
    || (box2.y >= box1.y + box1.h) // trop en bas
    || (box2.y + box2.h <= box1.y))  // trop en haut
          return false;
   else
          return true;
}

bool CollisionDroiteSeg(SDL_Point A,SDL_Point B,SDL_Point O,SDL_Point P)
{
  SDL_Point AO,AP,AB;
  AB.x = B.x - A.x;
  AB.y = B.y - A.y;
  AP.x = P.x - A.x;
  AP.y = P.y - A.y;
  AO.x = O.x - A.x;
  AO.y = O.y - A.y;
  if ((AB.x*AP.y - AB.y*AP.x)*(AB.x*AO.y - AB.y*AO.x)<0)
     return true;
  else
     return false;
}

bool CollisionSegSeg(SDL_Point A,SDL_Point B,SDL_Point O,SDL_Point P)
{
  if (CollisionDroiteSeg(A,B,O,P)==false)
     return false;  // inutile d'aller plus loin si le segment [OP] ne touche pas la droite (AB)
  if (CollisionDroiteSeg(O,P,A,B)==false)
     return false;
  return true;
}

bool CollisionSegSeg(int Ax ,int Ay ,int Bx ,int By,int Ox ,int Oy,int Px ,int Py)
{
    SDL_Point A = {Ax,Ay};
    SDL_Point B = {Bx,By};
    SDL_Point O = {Ox,Oy};
    SDL_Point P = {Px,Py};
    return CollisionSegSeg(A,B,O,P);
}

bool Collision(int x,int y,Cercle C)
{
   int d2 = (x-C.x)*(x-C.x) + (y-C.y)*(y-C.y);
   if (d2>C.rayon*C.rayon)
      return false;
   else
      return true;
}

bool CollisionPointCercle(SDL_Point A,Cercle C)
{
    return Collision(A.x,A.y,C);
}

bool Collision(Cercle C1,Cercle C2)
{
   int d2 = (C1.x-C2.x)*(C1.x-C2.x) + (C1.y-C2.y)*(C1.y-C2.y);
   if (d2 > (C1.rayon + C2.rayon)*(C1.rayon + C2.rayon))
      return false;
   else
      return true;
}

bool CollisionDroite(SDL_Point A,SDL_Point B,Cercle C)
{
   SDL_Point u;
   u.x = B.x - A.x;
   u.y = B.y - A.y;
   SDL_Point AC;
   AC.x = C.x - A.x;
   AC.y = C.y - A.y;
   float numerateur = u.x*AC.y - u.y*AC.x;   // norme du vecteur v
   if (numerateur <0)
      numerateur = -numerateur ;   // valeur absolue ; si c'est négatif, on prend l'opposé.
   float denominateur = sqrt(u.x*u.x + u.y*u.y);  // norme de u
   float CI = numerateur / denominateur;
   if (CI<C.rayon)
      return true;
   else
      return false;
}

bool CollisionSegment(SDL_Point A,SDL_Point B,Cercle C)
{
   if (CollisionDroite(A,B,C) == false)
     return false;  // si on ne touche pas la droite, on ne touchera jamais le segment
   SDL_Point AB,AC,BC;
   AB.x = B.x - A.x;
   AB.y = B.y - A.y;
   AC.x = C.x - A.x;
   AC.y = C.y - A.y;
   BC.x = C.x - B.x;
   BC.y = C.y - B.y;
   float pscal1 = AB.x*AC.x + AB.y*AC.y;  // produit scalaire
   float pscal2 = (-AB.x)*BC.x + (-AB.y)*BC.y;  // produit scalaire
   if (pscal1>=0 && pscal2>=0)
      return true;   // I entre A et B, ok.
   // dernière possibilité, A ou B dans le cercle
   if (CollisionPointCercle(A,C))
     return true;
   if (CollisionPointCercle(B,C))
     return true;
   return false;
}


int ProjectionSurSegment(int Cx,int Cy,int Ax,int Ay,int Bx,int By)
{
   int ACx = Cx-Ax;
   int ACy = Cy-Ay;
   int ABx = Bx-Ax;
   int ABy = By-Ay;
   int BCx = Cx-Bx;
   int BCy = Cy-By;
   int s1 = (ACx*ABx) + (ACy*ABy);
   int s2 = (BCx*ABx) + (BCy*ABy);
   if (s1*s2>0)
     return 0;
   return 1;
}

bool CollisionCercleRect(Cercle C1,SDL_Rect box1)
{
    SDL_Rect boxCercle;
    boxCercle.x=C1.x-C1.rayon;
    boxCercle.y=C1.y-C1.rayon;
    boxCercle.w=boxCercle.h=C1.rayon*2+1;//prendre en condition la facon dont le crcle est construit

    if(!boxCollision(box1,boxCercle))return false;

    if (Collision(box1.x,box1.y,C1)==1
    || Collision(box1.x,box1.y+box1.h,C1)==1
    || Collision(box1.x+box1.w,box1.y,C1)==1
    || Collision(box1.x+box1.w,box1.y+box1.h,C1)==1)
      return true;   // deuxieme test
    if (pointCollision(C1.x,C1.y,box1)==1)
      return true;   // troisieme test
    int projvertical = ProjectionSurSegment(C1.x,C1.y,box1.x,box1.y,box1.x,box1.y+box1.h);
    int projhorizontal = ProjectionSurSegment(C1.x,C1.y,box1.x,box1.y,box1.x+box1.w,box1.y);
    if (projvertical==1 || projhorizontal==1)
      return true;   // cas E
    return false;  // cas B
}
