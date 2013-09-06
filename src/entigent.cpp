/* Entity Agent */

#include "entigent.h"
#include "screen.h"
#include "game.h"
#include "game_object.h"
#include "util/logger.h"

Entigent::Entigent()
{
    game_ = nullptr;
    objects_ = new std::vector<GameObject *>();
}

void Entigent::add_object(GameObject * object)
{
    objects_->push_back(object);
    game_->screen()->init_object(object);

}

GameObject * Entigent::get_object_at(double x, double y)
{
    for(std::vector<GameObject *>::iterator object_iterator = objects_->begin(); object_iterator != objects_->end(); ++object_iterator) {
        if((*object_iterator)->contains_point(x, y)) {
            return *object_iterator;
        }
    }

    return nullptr;
}
