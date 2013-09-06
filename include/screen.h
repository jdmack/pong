#ifndef PONG_SCREEN_H_
#define PONG_SCREEN_H_

#include "SDL/SDL.h"
#include "constants.h"
#include "color.h"

class GameObject;

//const Color kDefaultClearColor = kColorWhite;
const Color kDefaultClearColor = kColorBlack;

class Screen
{
    private:
        SDL_Window * window_;
        SDL_Renderer * renderer_;
        SDL_Texture * table_;

    public:
        Screen();

        // accessors
        SDL_Window * window() const { return window_; }
        SDL_Renderer * renderer() const { return renderer_; }
        SDL_Texture * table() const { return table_; }

        // mutators

        bool init();
        void update();
        void clear();
        void clear(Color color);
        void clean_up();
        void init_object(GameObject * object);

        void render_texture(SDL_Texture * source, SDL_Rect * offset, SDL_Rect * clip = nullptr);
        void render_texture_rotate(SDL_Texture * source, SDL_Rect * offset, SDL_Rect * clip , double angle);
        void apply_surface(SDL_Surface * source, SDL_Surface * destination, SDL_Rect * offset, SDL_Rect * clip = nullptr);

        void render_table();

        SDL_Surface * load_image(std::string);
        SDL_Surface * load_image_alpha(std::string);
        SDL_Texture * load_texture(std::string);
        SDL_Texture * load_texture_alpha(std::string);
};

#endif
