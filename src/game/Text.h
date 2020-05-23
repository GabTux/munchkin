#pragma once

#include <string>
#include <SDL2/SDL_ttf.h>

#include "GraphicObject.h"
#include "../Exceptions.h"

class Text : public GraphicObject
{
	private:
		std::string showText;
		SDL_Rect position;
		TTF_Font* font;
		SDL_Color color;
		SDL_Texture* textTexture = nullptr;
		SDL_Renderer* mainRenderer = nullptr;


	public:
		Text(std::string inText, SDL_Rect inPos, TTF_Font* font, SDL_Color color, SDL_Renderer* inRenderer);

		void handleEvent(SDL_Event& event) override { }

		void update() override { }

		void render(SDL_Renderer* renderer) override;

		void setText(std::string inText);

		~Text();
};