#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "snakeBack.h"
#include "snakeGraph.h"

void game_tick(void* userdata) {
    Game_Window* window = static_cast<Game_Window*>(userdata);
    snake* p = window->get_player();
    food* meal = window->get_meal();
    int cellsize = window->get_cell_size(); 
    int max_width  = window->w() / cellsize;
    int max_height = window->h() / cellsize;
    
    window->update_pulse();

    p->move();
    if (p->grow(meal)) 
    {
        meal->respawn(max_width, max_height);
    }
    if (p->check_collision(max_width, max_height)){
        printf("GAME OVER\n");
        Fl::remove_timeout(game_tick, userdata);
        return;
    }
    
    window->redraw();
    Fl::repeat_timeout(0.1, game_tick, userdata);
}

int main() {
    const int grid_w = 40;
    const int grid_h = 30;
    const int cell_size = 20;
    const int win_w = grid_w * cell_size;
    const int win_h = grid_h * cell_size;

    snake player(grid_w / 2, grid_h / 2);
    
    Game_Window window(win_w, win_h, &player, cell_size);
    window.show();
    window.take_focus();

    Fl::add_timeout(0.1, game_tick, &window);

    return Fl::run();
}