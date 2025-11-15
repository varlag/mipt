#include "snakeGraph.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H>

Game_Window::Game_Window(int w, int h, snake* s, int cell_size_)
    : Fl_Window(w, h, "Snake Game"), player(s), cell_size(cell_size_), meal(new food(w / cell_size_, h / cell_size_))
{
    end();
}

Game_Window::~Game_Window() {
    delete meal;
}

int Game_Window::handle(int event) {
    if(event == FL_KEYDOWN) {
        switch(Fl::event_key()) {
            case 'w': 
            case FL_Up: 
                player->set_direction(snake::UP); 
                break;
            case 's': 
            case FL_Down:
                player->set_direction(snake::DOWN); 
                break;
            case 'a': 
            case FL_Left:
                player->set_direction(snake::LEFT); 
                break;
            case 'd': 
            case FL_Right:
                player->set_direction(snake::RIGHT); 
                break;
            case FL_Escape:
                hide();
                return 1;
            default:
                return 0; 
        }
        return 1;
    }
    return Fl_Window::handle(event);
}

void Game_Window::draw() {
    Fl_Window::draw();
    
    
    fl_color(8, 5, 26);//фон
    fl_rectf(0, 0, w(), h());
    
    // Рисуем сетку
    fl_color(25, 25, 50); 
    for (int x = 0; x <= w(); x += cell_size) {
        fl_line(x, 0, x, h());
    }
    for (int y = 0; y <= h(); y += cell_size) {
        fl_line(0, y, w(), y);
    }
    
    if (meal) {
    static Fl_Color food_colors[] = {
        fl_rgb_color(0, 255, 255),    
        fl_rgb_color(255, 0, 128),    
        fl_rgb_color(0, 255, 128),    
        fl_rgb_color(255, 128, 0),    
        fl_rgb_color(128, 0, 255),    
        fl_rgb_color(255, 255, 128),  
        fl_rgb_color(128, 255, 255),  
        fl_rgb_color(255, 128, 255)   
    };
        
    static int current_color_index = 0;
    static int last_meal_x = -1;
    static int last_meal_y = -1;
    
    if (meal->getX() != last_meal_x || meal->getY() != last_meal_y) {
        current_color_index = (current_color_index + 1) % 8;
        last_meal_x = meal->getX();
        last_meal_y = meal->getY();
    }
    
    fl_color(food_colors[current_color_index]);
    int meal_x = meal->getX() * cell_size;
    int meal_y = meal->getY() * cell_size;
    fl_rectf(meal_x, meal_y, cell_size, cell_size);
    }
    
    fl_color(FL_GRAY);
    for(int i = 0; i < player->len(); ++i) {
        int x = player->get_snake_coordinates_x(i) * cell_size;
        int y = player->get_snake_coordinates_y(i) * cell_size;
        fl_rectf(x, y, cell_size, cell_size);
    }

    if (player->len() > 0) {
        fl_color(FL_WHITE);
        int x = player->get_snake_coordinates_x(0) * cell_size;
        int y = player->get_snake_coordinates_y(0) * cell_size;
        fl_rectf(x, y, cell_size, cell_size);
    }
}

int Game_Window::get_cell_size() {
    return cell_size;
}

snake* Game_Window::get_player() {
    return player;
}

food* Game_Window::get_meal() {
    return meal;
}

BackgroundWindow::BackgroundWindow(int w, int h, const char* title) 
    : Fl_Window(w, h, title), background(w, h)
{
    end();
}

void BackgroundWindow::draw() {
    Fl_Window::draw();
    background.draw();
}

int BackgroundWindow::handle(int event) {
    if (event == FL_KEYDOWN && Fl::event_key() == FL_Escape) {
        hide();
        return 1;
    }
    return Fl_Window::handle(event);  
}