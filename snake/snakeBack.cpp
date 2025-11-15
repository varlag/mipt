
#include "snakeBack.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H> 
#include <ctime>

snake::snake(int x, int y)
{
    int  i = 0; 
    snake_body_x[0] = x;
    snake_body_y[0] = y;
    max_length = 10;
    for (i=1; i<max_length; i++)
    {
        snake_body_x[i] = x-i; 
        snake_body_y[i] = y;
    }
}

void snake::move()
{
    int i = max_length; 
    for (i = max_length-1; i>0; i--)
    {
        snake_body_x[i] = snake_body_x[i-1];
        snake_body_y[i] = snake_body_y[i-1];
    }

    switch (dir)
    {
        case UP   : snake_body_y[0] --; break;
        case DOWN : snake_body_y[0] ++; break;
        case LEFT : snake_body_x[0] --; break;
        case RIGHT: snake_body_x[0] ++; break; 
    }

}

bool snake::check_collision(int max_width, int max_height)
{
    for (int i = 1; i < max_length; i++)
    {
        if (snake_body_x[0] == snake_body_x[i] && snake_body_y[0] == snake_body_y[i])
        {
            return 1;     
        }
    }

    if (snake_body_x[0] >= max_width || snake_body_y[0] >= max_height || snake_body_x[0] < 0 || snake_body_y[0] < 0)
        {
            return 1; 
        }

    return 0; 
}

int snake::len()
{
    return max_length;
}

int snake::get_snake_coordinates_x(int n)
{
    return snake_body_x[n];
}

int snake::get_snake_coordinates_y(int n)
{
    return snake_body_y[n];
}

void snake::set_direction(direction d)
{   
    if (dir == UP && d==DOWN || dir == DOWN && d==UP || dir == LEFT && d ==  RIGHT || dir == RIGHT && d == LEFT){
    }
    else{ 
        dir = d;
    }
}

bool snake::grow(food* meal)
{
    if(meal && snake_body_x[0] == meal->getX() && snake_body_y[0] == meal->getY())
    {
        max_length+=1;
        return 1;
    }
    else
    {
        return 0;
    }
}

SnakeBackground::SnakeBackground(int w, int h, int cell) 
    : width(w), height(h), cellSize(cell)
{
}

void SnakeBackground::draw() {
    
    fl_color(0x100a3a);  
    fl_rectf(0, 0, width, height);
    
    
    fl_color(0x3a4a7a);  
    for (int x = 0; x <= width; x += cellSize) {
        fl_line(x, 0, x, height);
    }
    for (int y = 0; y <= height; y += cellSize) {
        fl_line(0, y, width, y);
    }
}

void food::respawn(int max_width, int max_height)
    {
        x = rand() % max_width;
        y = rand() % max_height;
    }



food::food(int max_width, int max_height)
    {
        srand(time(0));
        respawn(max_width, max_height);
    }

    int food::getX() { return x; }
    int food::getY() { return y; }
