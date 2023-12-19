#include "../include/commonFn.h"

// class commonFn
// {
// private:
// public:
// }

SDL_Texture *commonFn::LoadTexture(const char *fileName, SDL_Renderer *renderer)
{
	SDL_Surface *surface = IMG_Load(fileName);
	if (!surface)
		return nullptr;

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void commonFn::close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_CloseAudio();
	SDL_Quit();
}