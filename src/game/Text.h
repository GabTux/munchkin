#pragma once

#include <string>
#include <SDL2/SDL_ttf.h>

#include "GraphicObject.h"
#include "../Exceptions.h"

/**
 * Class for handling text.
 */
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
		/**
		 * New text object.
		 * It will store renderer, to create texture and save resources.
		 * @param inText Text to show.
		 * @param inPos Position of text.
		 * @param font Which font use.
		 * @param color Which color use.
		 * @param inRenderer Where to render.
		 */
		Text(std::string inText, SDL_Rect inPos, TTF_Font* font, SDL_Color color, SDL_Renderer* inRenderer);

		/**
		 * Do nothing.
		 * @param event
		 */
		void handleEvent(SDL_Event& event) override { }

		/*
		 * Do nothing.
		 */
		void update() override { }

		/**
		 * Render actual text.
		 * @param renderer where to render.
		 */
		void render(SDL_Renderer* renderer) override;

		/**
		 * Set new text.
		 * @param inText which text.
		 */
		void setText(std::string inText);

		~Text();
};