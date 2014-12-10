/*
   ****************************************
    Creditos: Alver Lopez
   ****************************************
*/
#include <string>
#include "Game.h"
#include "Config.h"
#include <fstream>
#include <cstdlib>
#include <sstream>


using std::endl;

std::ofstream mFile;

Game::Game()
{
    quit          = false;
    success       = true;
    oneKeyPressed = false;

    time_waiting  = 0;

    textColor.r = 76;
    textColor.g = 255;
    textColor.b = 0;

    //int Puntos = 0;
    str_score = "";

	mFile.open( "Log.txt", std::ios::out );

	mFile << "Iniciando SDL...";
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
    	mFile << "No se pudo iniciar SDL, SDL Error: " << SDL_GetError() << endl;
    	success = false;
    }
    else
    {
    	mFile << "completado!" << endl;
    	mFile << "Estableciendo filtro de textura..." << endl;
    	// Filtro de renderizado
    	if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    	{
    		mFile << "Advertencia: Filtro de textura lineal no esta disponible" << endl;
    		success = false;
    	}

    	mFile << "Creando ventana...";
    	mWindow = SDL_CreateWindow( "Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    	if ( mWindow == NULL )
    	{
    		mFile << "La ventana no se pudo crear, SDL Error: " << SDL_GetError() << endl;
    		success = false;
    	}
    	else
    	{
    		mFile << "completada!" << endl;
    		mFile << "Creando renderizador...";
    		mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED );
    		if ( mRenderer == NULL )
    		{
    			mFile << "No se pudo crear el renderizador, SDL Error: " << SDL_GetError() << endl;
    			success = false;
    		}
    		else
    		{
    			mFile << "completado!" << endl;

    			SDL_SetRenderDrawColor( mRenderer, 0, 0, 0, 255 );

    			// Establecemos que tipo de imagen querremos utilizar, en este caso PNG
    			int imgFlags = IMG_INIT_PNG;
    			if ( !( IMG_Init( imgFlags) & imgFlags ) )
    			{
    				mFile << "SDL_image no se pudo iniciar, SDL_image Error: " << IMG_GetError() << endl;
    				success = false;
    			}

    			if ( TTF_Init() == -1 )
    			{
    				mFile << "SDL_ttf no se pudo inicializar, SDL_ttf Error: " << TTF_GetError() << endl;
    				success = false;
    			}
    		}
    	}
    }
}

Game::~Game()
{
    mFile << "Cerrando TTF...";
    TTF_CloseFont( mFont );
    TTF_Quit();
    mFile << "completado!" << endl;

    mFile << "Quitando renderer...";
    SDL_DestroyRenderer( mRenderer );
    mFile << "completado" << endl;

    mFile << "Quitando ventana...";
    SDL_DestroyWindow( mWindow );
    mFile << "completado" << endl;

    mFile << "Cerrando IMG...";
    IMG_Quit();
    mFile << "completado" << endl;

    mFile << "Cerrando SDL...";
    SDL_Quit();
    mFile << "completado" << endl;

    mFile.close();
}

void Game::execute()
{
    if ( success )
    {
        if ( start() )
        {
            while( !quit )
            {
                think();
                if ( !quit )
                {
                    update();
                    render();
                    update_2();
                }
            }
        }
    }
//    close();
}


bool Game::start()
{
    success = true;

    mFont = TTF_OpenFont( "fonts/consola.ttf", 25 );
    if ( mFont == NULL )
    {
        mFile << "Fallo al cargar fuente consola, SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    }
    else
    {
        if ( !textTexture_1.loadFromRenderedText( "Puntuacion", textColor, mFont, mFile, mRenderer ) )
        {
            mFile << "Fallo al renderizar textura textTexture_1" << endl;
            success = false;
        }
        if ( !textTexture_2.loadFromRenderedText( "FIN DE JUEGO", textColor, mFont, mFile, mRenderer ) )
        {
            mFile << "Fallo al renderizar textura textTexture_2" << endl;
            success = false;
        }
        if ( !textTexture_3.loadFromRenderedText( "Presione Escape para salir", textColor, mFont, mFile, mRenderer ) )
        {
            mFile << "Fallo al renderizar textura textTexture_3" << endl;
            success = false;
        }
        //MOD Alver Lopez
        if ( !textTexture_4.loadFromRenderedText( "Autor: Daniel Paz", textColor, mFont, mFile, mRenderer ) )
        {
            mFile << "Fallo al renderizar textura textTexture_4" << endl;
            success = false;
        }
        if ( !scoreTexture.loadFromRenderedText( "0", textColor, mFont, mFile, mRenderer ) )
        {
            mFile << "Fallo al renderizar textura score" << endl;
            success = false;
        }
    }

    if ( !food.texture.loadFromFile( "images/manzana.png", mRenderer, mFile ) )
        success = false;

    if( !wall.loadFromFile( "images/pared.png", mRenderer, mFile ) )
        success = false;

    return success;
}

void Game::think()
{
    oneKeyPressed = false;
    while( SDL_PollEvent( &event ) )
    {
        if ( event.type == SDL_QUIT )
        {
            quit = true;
        }
        else if ( event.type == SDL_KEYDOWN )
        {
            switch( event.key.keysym.sym )
            {
                case SDLK_LEFT:
                case SDLK_a:
                    if ( snake.get_direction() != RIGHT )
                    {
                        if ( !oneKeyPressed )
                        {
                            snake.set_direction( LEFT );
                            oneKeyPressed = true;
                        }
                    }
                break;
                case SDLK_RIGHT:
                case SDLK_d:
                    if ( snake.get_direction() != LEFT )
                    {
                        if ( !oneKeyPressed )
                        {
                            snake.set_direction( RIGHT );
                            oneKeyPressed = true;
                        }
                    }
                break;
                case SDLK_UP:
                case SDLK_w:
                    if ( snake.get_direction() != DOWN )
                    {
                        if ( !oneKeyPressed )
                        {
                            snake.set_direction( UP );
                            oneKeyPressed = true;
                        }
                    }
                break;
                case SDLK_DOWN:
                case SDLK_s:
                    if ( snake.get_direction() != UP )
                    {
                        if ( !oneKeyPressed )
                        {
                            snake.set_direction( DOWN );
                            oneKeyPressed = true;
                        }
                    }
                break;
                case SDLK_ESCAPE:
                    quit = true;
                break;
            }
        }
    }
}

void Game::update()
{
    if ( snake.get_collision_state() == false )
    {
        // Aqui simplemente evaluamos la siguiente casilla a donde se movera
        // Snake, y procedemos a ejecutar segun el caso
        if( snake.get_direction() == RIGHT )
        {
            if ( snake.get_frontX() + 1 == COL_SIZE )
            {
                snake.set_collision_state( true );
            }
            else if ( ( snake.get_frontX() + 1 == food.get_posX() ) &&
                      ( snake.get_frontY() == food.get_posY() ) )
            {
                food.set_eaten_state( true );
                snake.grow();
            }
            else
                snake.move();
        }
        else if( snake.get_direction() == LEFT )
        {
            if ( snake.get_frontX() - 1 == -1 )
            {
                snake.set_collision_state( true );
            }
            else if ( ( snake.get_frontX() - 1 == food.get_posX() ) &&
                      ( snake.get_frontY() == food.get_posY() ) )
            {
                food.set_eaten_state( true );
                snake.grow();
            }
            else
                snake.move();
        }
        else if( snake.get_direction() == UP )
        {
            if ( snake.get_frontY() - 1 == -1 )
            {
                snake.set_collision_state( true );
            }
            else if ( ( snake.get_frontY() - 1 == food.get_posY() ) &&
                      ( snake.get_frontX() == food.get_posX() ) )
            {
                food.set_eaten_state( true );
                snake.grow();
            }
            else
                snake.move();
        }
        else if( snake.get_direction() == DOWN )
        {
            if ( snake.get_frontY() + 1 == ROW_SIZE )
            {
                snake.set_collision_state( true );
            }
            else if ( ( snake.get_frontY() + 1 == food.get_posY() ) &&
                      ( snake.get_frontX() == food.get_posX() ) )
            {
                food.set_eaten_state( true );
                snake.grow();
            }
            else
                snake.move();
        }
    }


    // str_score = "0";

    //str_score = std::to_string( snake.length() - 1 );
    int i = ( snake.length() - 1 );
    std::string s;
    std::stringstream out;
    out<<i;
    s=out.str();
    str_score = s;
    mFile << s << endl;


    for ( int i = 0; i < snake.length(); ++i )
        myMap.set_symbol( snake.get_posX(i), snake.get_posY(i), SNAKE_SYMBOL );

    time_waiting--;
    // Establecemos nuevas coordenadas a la comida
    food.set_food( &time_waiting, myMap );

    myMap.set_symbol( food.get_posX(), food.get_posY(), FOOD_SYMBOL );
}

void Game::render()
{
    SDL_SetRenderDrawColor( mRenderer, 0, 0, 0, 255 );
    SDL_RenderClear( mRenderer );

    // Render a la primera fila de paredes
    for ( int j = 0; j < COL_SIZE + 2; ++j )
        wall.render( j * wall.getWidth(), 0, mRenderer);

    // Render a las paredes intermedias
    for ( int i = 0; i < ROW_SIZE; ++i )
    {
        wall.render( 0,
                    i * wall.getHeight() + IMAGE_HEIGHT,
                    mRenderer );

        wall.render( COL_SIZE * wall.getWidth() + IMAGE_WIDTH,
                    i * wall.getHeight() + IMAGE_HEIGHT,
                    mRenderer );
    }

    // Render a la ultima fila de paredes
    for ( int j = 0; j < COL_SIZE + 2; ++j )
        wall.render( j * wall.getWidth(),
                    ROW_SIZE * wall.getHeight() + IMAGE_HEIGHT,
                    mRenderer );

    // Render a la fruta
    food.texture.render( food.get_posX() * food.texture.getWidth() + IMAGE_WIDTH,
                food.get_posY() * food.texture.getHeight() + IMAGE_HEIGHT,
                mRenderer );

    // Render al snake
    for ( int i = 0; i < snake.length(); ++i )
    {
        snake.set_body_rect( snake.get_posX(i) * IMAGE_WIDTH + IMAGE_WIDTH,
                            snake.get_posY(i) * IMAGE_HEIGHT + IMAGE_HEIGHT );

        SDL_SetRenderDrawColor( mRenderer, 76, 255, 0, 255 );
        // Ojo verificar si esta instruccion esta correcta en caso de errores
        SDL_RenderFillRect( mRenderer, snake.get_body_ptr() );
    }

    // Render al texto
    textTexture_1.render( SCREEN_WIDTH - ( SCREEN_WIDTH / 3 ),
                            SCREEN_HEIGHT / 10,
                            mRenderer );

    // Render a la puntuacion
    //scoreTexture.loadFromRenderedText( to_string(snake.length() - 1),
    scoreTexture.loadFromRenderedText( str_score.c_str(),
                                        textColor,
                                        mFont,
                                        mFile,
                                        mRenderer );

    scoreTexture.render( SCREEN_WIDTH - ( SCREEN_WIDTH / 3 ),
                        SCREEN_HEIGHT / 10 + ( textTexture_1.getHeight() + 10 ),
                        mRenderer );

    if ( snake.get_collision_state() == true )
    {
        textTexture_2.render( SCREEN_WIDTH - ( SCREEN_WIDTH / 3 ),
                                SCREEN_HEIGHT / 10 + ( textTexture_1.getHeight() + 10 + scoreTexture.getHeight() + 10 ),
                                mRenderer );

        textTexture_3.render( SCREEN_WIDTH - ( SCREEN_WIDTH / 3 ),
                                SCREEN_HEIGHT / 10 + ( textTexture_1.getHeight() + 10 + scoreTexture.getHeight() + 10 + textTexture_3.getHeight() + 10 ),
                                mRenderer );
    }


    textTexture_4.render( SCREEN_WIDTH - ( SCREEN_WIDTH / 3 ),
                            SCREEN_HEIGHT - textTexture_4.getHeight() - 10,
                            mRenderer );

    // Mostrar render
    SDL_RenderPresent( mRenderer );

    SDL_Delay( DELAY );
}

void Game::update_2()
{

    // Esto lo pense a ultima hora y como no consegui como solucionar, lo hice de esta manera
    if ( !oneKeyPressed )
        if ( snake.self_collide() )
            snake.set_collision_state( true );

    myMap.clear_map();
}
