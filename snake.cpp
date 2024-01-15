#include<SDL2/SDL.h>
#include<iostream>
#include<vector>
using namespace std;
struct segment{
    int x,y;
};
 class Game {
    public:
        Game(); 
        ~Game();
        void run();
    private:
        void handleEvents();
        void update();
        void render();
        void reset();
        SDL_Window* window;
        SDL_Renderer* renderer;
        vector<segment>snake;
        int direction,foodx,foody,score;
        bool gameover;

    


    };

Game::Game(){
    SDL_Init(SDL_INIT_VIDEO);
    window=SDL_CreateWindow("ABRAR's Snake Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,980,720,0);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    reset();

}
Game::~Game(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}
void Game::run(){
    while(!gameover){
        handleEvents();
        update();
        render();
        SDL_Delay(100);
    }

}
void Game::handleEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
    if(event.type==SDL_QUIT){
        gameover=true;
    }
    else if(event.type==SDL_KEYDOWN){
        switch(event.key.keysym.sym){
            case SDLK_UP: direction=0;break;
            case SDLK_RIGHT:direction=1;break;
            case SDLK_DOWN:direction=2;break;
            case SDLK_LEFT:direction=3;break;
            default:cout<<"You pressed wrong keay\n";
        }
    }
}
}

void Game::update(){
    for(int i=snake.size()-1;i>0;--i){
        snake[i]=snake[i-1];
    }
    switch (direction)
    {
    case 0:--snake[0].y;break;
    case 1:++snake[0].x;break;
    case 2:++snake[0].y;break;
    case 3:--snake[0].x;break;
    }
    for(size_t i=1;i<snake.size();++i){
        if(snake[i].x==snake[0].x && snake[i].y==snake[0].y){
            gameover=true;
            cout<<"\nGAMEOVER!\nYOUR FINAL SCORE IS: "<<score<<endl;
        }
    }
    if(snake[0].x==foodx && snake[0].y==foody){
        score+=5;
        snake.push_back({-1,-1});
        foodx=rand()%98;
        foody=rand()%72;
        cout<<score<<" ";
    }
      if (snake[0].x < 0 || snake[0].x >= 980 || snake[0].y < 0 || snake[0].y >= 720) {
        gameover = true;
        cout<<"\nGAME OVER!\nYOUR FINAL SCORE IS: "<<score<<endl;
    }

}
void Game::render(){
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,255,0,255);
    for(auto& segment:snake){
        SDL_Rect rect={segment.x*10,segment.y*10,10,10};
        SDL_RenderFillRect(renderer,&rect);

    }

    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_Rect rect={foodx*10,foody*10,10,10};
    SDL_RenderFillRect(renderer,&rect);
    SDL_RenderPresent(renderer);

    
}

void Game::reset(){
    snake={{49,36}};
    direction=0;
    foodx=rand()%98;
    foody=rand()%72;
    score=0;
    gameover=false;
}
int main(int argc,char *argv[]){
    Game game;
    game.run();
    return 0;
}