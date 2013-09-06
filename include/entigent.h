/* Entity Agent */

#ifndef TLB_ENTIGENT_H_
#define TLB_ENTIGENT_H_

#include <vector>

class Game;
class GameObject;

class Entigent
{
    private:
        Game * game_;
        std::vector<GameObject *> * objects_;

    public:
        void add_object(GameObject * object);
        Entigent();
        GameObject * get_object_at(double x, double y);

        // accessors
        std::vector<GameObject *> * objects() const { return objects_; }

        // mutators
        void set_game(Game * game) { game_ = game; }
};

#endif
