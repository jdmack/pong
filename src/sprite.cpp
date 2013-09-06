#include "sprite.h"
#include "screen.h"
#include "game_object.h"
#include "util/logger.h"

Sprite::Sprite(GameObject * object, std::string asset)
{
    object_ = object;
    art_asset_ = asset;
    texture_ = nullptr;
    screen_ = nullptr;
    height_ = object->height();
    width_ = object->width();
}

void Sprite::render()
{
    SDL_Rect offset;
    offset.x = object_->x_position() - (object_->width() / 2);
    offset.y = object_->y_position() - (object_->height() / 2);
    offset.h = height_;
    offset.w = width_;
    screen_->render_texture(texture_, &offset);
}
