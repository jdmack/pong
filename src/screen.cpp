#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "screen.h"
#include "game_object.h"
#include "sprite.h"
#include "util/logger.h"

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
Screen::Screen()
{
    window_ = nullptr;
    renderer_ = nullptr;
    board_ = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
bool Screen::init()
{
    // Initialize SDL
    // TODO(2013-08-23/JM): Move this elsewhere, init function for whole game
    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        return false;
    }
    if(TTF_Init()==-1) {
        Logger::write(Logger::string_stream << "TTF_Init: " << TTF_GetError());
        return false;
    }

    // Setup screen
    window_ = SDL_CreateWindow(kWindowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN);
    renderer_ = SDL_CreateRenderer(window_, -1, 0);

    // Check screen was setup successfully
    if(window_ == nullptr) {
    	Logger::write("Error: Could not create window");
        return false;
    }
    if(renderer_ == nullptr) {
    	Logger::write("Error: Could not create renderer");
        return false;
    }

    // Create board image
    SDL_Surface * surface = SDL_CreateRGBSurface(0, kScreenWidth, kScreenHeight, 32, kRedMask, kGreenMask, kBlueMask, kAlphaMask);
    if(surface == nullptr) {
    	Logger::write("Error: Could not create board surface");
        return false;
    }

    const int kBorderSpace     = 50;
    const int kBorderWidth     = kScreenWidth - (kBorderSpace * 2);
    const int kBorderHeight    = kScreenHeight - (kBorderSpace * 2);
    const int kBorderThickness = 10;

    SDL_Rect rects[5] = { { kBorderSpace, kBorderSpace, kBorderWidth, kBorderThickness },
    					  { kScreenWidth - kBorderSpace - kBorderThickness, kBorderSpace, kBorderThickness, kBorderHeight },
    					  { kBorderSpace, kBorderSpace, kBorderThickness, kBorderHeight },
    					  { kBorderSpace, kScreenHeight - kBorderSpace - kBorderThickness, kBorderWidth, kBorderThickness },
    					  { (kScreenWidth / 2) - (kBorderThickness / 2), kBorderSpace + kBorderThickness + (kBorderThickness / 2), kBorderThickness / 2, kScreenHeight - (kBorderSpace * 2) - (kBorderThickness * 2) - kBorderThickness },
    };

    SDL_FillRects(surface, rects, 5, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

    board_ = SDL_CreateTextureFromSurface(renderer_, surface);
    if(board_ == nullptr) {
    	Logger::write("Error: Could not create board texture");
        return false;
    }

    return true;
}

void Screen::render_board()
{
	SDL_Rect offset = { 0, 0, kScreenWidth, kScreenHeight };
	render_texture(board_, &offset, nullptr);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::render_texture(SDL_Texture * texture, SDL_Rect * offset, SDL_Rect * clip)
{
    int return_code = SDL_RenderCopy(renderer_, texture, clip, offset);

    if(return_code != 0) {
        Logger::write(Logger::string_stream << "Render Error: " << SDL_GetError());
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::render_texture_rotate(SDL_Texture * texture, SDL_Rect * offset, SDL_Rect * clip, double angle)
{
    int return_code = SDL_RenderCopyEx(renderer_, texture, nullptr, offset, -angle, nullptr, SDL_FLIP_NONE);

    if(return_code != 0) {
        Logger::write(Logger::string_stream << "Render Error: " << SDL_GetError());
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::apply_surface(SDL_Surface * source, SDL_Surface * destination, SDL_Rect * offset, SDL_Rect * clip)
{
    SDL_BlitSurface(source, clip, destination, offset );
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::clear()
{
    SDL_SetRenderDrawColor(renderer_, kDefaultClearColor.red(), kDefaultClearColor.green(), kDefaultClearColor.blue(), 255);
    SDL_RenderClear(renderer_);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::clear(Color clear_color)
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::update()
{
    SDL_RenderPresent(renderer_);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::clean_up()
{
    // TODO(2013-08-23/JM): Move this elsewhere, cleanup function for whole game
    TTF_Quit();
    SDL_Quit();
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Surface * Screen::load_image(std::string filename)
{
    SDL_Surface* loaded_image    = nullptr;

    loaded_image = IMG_Load(filename.c_str());

    if(loaded_image == nullptr) {
        Logger::write(Logger::string_stream << "IMG_Load Error: " << IMG_GetError());
    }
    else {
        Uint32 colorkey = SDL_MapRGB(loaded_image->format, 0xFF, 0, 0xFF);
        SDL_SetColorKey(loaded_image, SDL_TRUE, colorkey);
    }

    return loaded_image;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Surface * Screen::load_image_alpha(std::string filename)
{
    SDL_Surface* loaded_image = nullptr;

    loaded_image = IMG_Load(filename.c_str());
    if(loaded_image == nullptr) {
        Logger::write(Logger::string_stream << "IMG_Load Error: " << IMG_GetError());
    }
    return loaded_image;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Texture * Screen::load_texture(std::string filename)
{
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer_, load_image(filename));

    if(texture == nullptr) {
        Logger::write(Logger::string_stream << "Error creating texture: " << SDL_GetError());
    }

     return texture;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Texture * Screen::load_texture_alpha(std::string filename)
{
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer_, load_image_alpha(filename));

    if(texture == nullptr) {
        Logger::write(Logger::string_stream << "Error creating texture: " << SDL_GetError());
    }

     return texture;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::init_object(GameObject * object)
{
    object->sprite()->set_texture(load_texture_alpha(object->sprite()->art_asset()));
    object->sprite()->set_screen(this);
}

