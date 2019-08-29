#ifndef SORTIE_H
#define SORTIE_H

#include "MapElement.h"

class MapProto;
class Sortie : public MapElement
{
    public:
        Sortie(MapProto* destination,int x,int y);
        virtual ~Sortie();

        virtual bool isAWall() const {return false;}
        virtual bool doActionOnEnter() const {return true;}
        virtual bool doActionOnAction() const {return false;}
        virtual bool isACombatZone() const {return false;}

        virtual int action();

        int destX() const {return m_x;}
        int destY() const {return m_y;}

    protected:

    private:
        int m_x;
        int m_y;
        MapProto* m_destination;

};

#endif // SORTIE_H
