#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "include/player.hpp"
#include "include/zombie.hpp"

using namespace std;

int main()
{
    Config *cfg = &Config::instance();
    Player p;// = Player();
    Zombie z;// = Zombie();

    SDL_Init(SDL_INIT_VIDEO); // Init SDL2 (you should check for errors)

    // Create a window. Window mode MUST include SDL_WINDOW_OPENGL for use with OpenGL.
    SDL_Window *window = SDL_CreateWindow(
                "SDL2/OpenGL Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE
                );

    // Create an OpenGL context associated with the window.
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);

    // Now, regular OpenGL functions ...
    glMatrixMode(GL_PROJECTION|GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-320,320,240,-240,0,1);

    // ... can be used alongside SDL2.
    float x = 0.0, y = 30.0;

    SDL_Event event;
    Uint8 done = 0;
    while(!done)  // Enter main loop.
    {
        while(SDL_PollEvent(&event))      // Check for events.
        {
            if(event.type == SDL_QUIT || event.type == SDL_QUIT)
                done = 1;
        }

        // Draw:
        glClearColor(0,0,0,1); // Use OpenGL commands, see the OpenGL reference.
        glClear(GL_COLOR_BUFFER_BIT); // clearing screen
        glRotatef(10.0,0.0,0.0,1.0);  // rotating everything
        // Note that the glBegin() ... glEnd() OpenGL style used below is actually
        // obsolete, but it will do for example purposes. For more information, see
        // SDL_GL_GetProcAddress() or find an OpenGL extension loading library.
        glBegin(GL_TRIANGLES); // drawing a multicolored triangle
        glColor3f(1.0,0.0,0.0); glVertex2f(x, y+90.0);
        glColor3f(0.0,1.0,0.0); glVertex2f(x+90.0, y-90.0);
        glColor3f(0.0,0.0,1.0); glVertex2f(x-90.0, y-90.0);
        glEnd();

        SDL_GL_SwapWindow(window);  // Swap the window/buffer to display the result.
        SDL_Delay(10);              // Pause briefly before moving on to the next cycle.

    }

    // Once finished with OpenGL functions, the SDL_GLContext can be deleted.
    SDL_GL_DeleteContext(glcontext);

    // Done! Close the window, clean-up and exit the program.
    SDL_DestroyWindow(window);
    SDL_Quit();



    p.setX(5);
    p.setY(3);
    z.setX(15);
    z.setY(13);

    cfg->init();

    cout << "Player: x,y: " << p.getX() << "," << p.getY() << endl;
    cout << "Zombie: x,y: " << z.getX() << "," << z.getY() << endl;

    return 0;
}
