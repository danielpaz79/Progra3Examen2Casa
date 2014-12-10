/*
   ****************************************
Creditos: Alver Lopez
   ****************************************
*/

#include "LTexture.h"

using std::endl;

LTexture::LTexture()
{
	mTexture = 0;
	mWidth   = 0;
	mHeight  = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile( std::string path, SDL_Renderer* renderer, std::ofstream& mFile )
{
	// Liberamos cualquier textura pre-existente
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if ( loadedSurface == NULL )
	{
		mFile << "Imposible cargar imagen " << path.c_str() << ", SDL_image Error: " << IMG_GetError() << endl;
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if ( newTexture == NULL )
		{
			mFile << "Imposible crear textura desde " << path.c_str() << ", SDL Error: " << SDL_GetError() << endl;
		}
		else
		{
			mWidth  = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface( loadedSurface );
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText( std::string textTexture, SDL_Color textColor, TTF_Font* mFont, std::ofstream& mFile, SDL_Renderer* renderer )
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid( mFont, textTexture.c_str(), textColor );
	if ( textSurface == NULL )
	{
		mFile << "Imposible renderizar superficie texto, SDL_ttf Error: " << TTF_GetError() << endl;
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
		if ( mTexture == NULL )
		{
			mFile << "Imposible crear una textura desde texto renderizado, SDL Error: " << SDL_GetError() << endl;
		}
		else
		{
			mWidth  = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface( textSurface );
	}

	return mTexture != NULL;
}

void LTexture::free()
{
	if ( mTexture == NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth   = 0;
		mHeight  = 0;
	}
}

void LTexture::render( int x, int y, SDL_Renderer *renderer )
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	SDL_RenderCopy( renderer, mTexture, NULL, &renderQuad );
}

int LTexture::getWidth() const
{
	return mWidth;
}

int LTexture::getHeight() const
{
	return mHeight;
}
