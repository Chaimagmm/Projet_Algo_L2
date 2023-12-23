
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define MAX_RECTANGLES 200

int main(int argc, char *argv[]) {
    int j = 100;
    int n;
    int tab[MAX_RECTANGLES];
    printf("Enter the number of elements for the array: ");
    scanf("%d", &n);
    printf("Enter the elements of the array\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tab[i]);
    }

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *Window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 500, 0);
    SDL_Renderer *Renderer = SDL_CreateRenderer(Window, -1, 0);

    int Running = 1;
    SDL_Event Event = {0};
    ///SDL_Event: SDL_Event is a structure in SDL that represents an event.
    ///Events can be things like keyboard presses, mouse movements, window events, etc.
    ///{0}: This is a C language shorthand for initializing all members of a structure to zero.
    ///It sets the entire structure to zero values, effectively initializing all fields to a default state.

///Event: This is the name given to the instance of the SDL_Event structure.

///{0}: This is a C language shorthand for initializing all members of a structure to zero. It sets the entire structure to zero values, effectively initializing all fields to a default state.

    // Create buttons
    SDL_Rect button1 = {400, 400, 200, 100}; // x, y, width, height
    SDL_Rect button2 = {600, 400, 200, 100}; // x, y, width, height
    SDL_Rect button3 = {800, 400, 200, 100}; // x, y, width, height
    SDL_Rect button4 = {1000, 400, 200, 100}; // x, y, width, height
    int button1Visible = 1; // Flag to control button 1 visibility
    int button4Visible = 1; // Flag to control button 4 visibility
    int rectanglesVisible[MAX_RECTANGLES];
    for (int i = 0; i < MAX_RECTANGLES; i++) {
        rectanglesVisible[i] = 0;
    }
    int rectanglesMoving = 0; // Flag to control rectangles movement

    SDL_Rect rectangles[MAX_RECTANGLES];
    int rectanglesCount = 0;

    while (Running) {
        while (SDL_PollEvent(&Event)) {
            switch (Event.type) {
                case SDL_QUIT:
                    // Handle quit event (window close button clicked)
                    Running = 0;
                    break;
                case SDL_KEYDOWN:
                    // Handle key press event

                    switch (Event.key.keysym.sym) {
                        case SDLK_o:


Running = 0;
                            /*If the 'o' key is pressed, it sets Running to 0.
                            This typically means that the program will exit because
                             the main loop (while (Running)) will exit when Running becomes 0.
                            */
                            break;
                        case SDLK_s:
                            for (int i = 0; i < n; i++) {
                                rectanglesVisible[i] = 1;
                            }
                            button1Visible = 1;  //makes button1Visible true
                            rectanglesMoving = 0;
                            /*If the 's' key is pressed, it sets rectanglesVisible for all rectangles to 1
                             makes button1Visible true, and sets rectanglesMoving to 0.
                            This suggests that pressing 's' is associated with showing rectangles and stopping their movement.
                            */
                            break;
                        case SDLK_m:
                            button1Visible = 1;
                            for (int i = 0; i < n; i++) {
                                rectanglesVisible[i] = 0;
                            }
                            rectanglesMoving = 1;
                            /*If the 'm' key is pressed, it makes button1Visible true and sets rectanglesVisible for all rectangles to 0.
                            It also sets rectanglesMoving to 1.
                            This suggests that pressing 'm' is associated with hiding rectangles and starting their movement.*/
                            break;
                        case SDLK_r:
                            button1Visible = 0;
                            for (int i = 0; i < n; i++) {
                                rectanglesVisible[i] = 0;
                            }
                            rectanglesMoving = 1;

                            // Sorting logic integrated into the main loop
                            static int i = 0;
                            static int min = 0;
                            if (i < n - 1) {
                                if (min == i) {
                                    min = i + 1;
                                }
                                for (int k = i + 1; k < n; k++) {
                                    if (tab[k] < tab[min]) {
                                        min = k;
                                    }
                                }
                                if (min != i) {
                                    int temp = tab[i];
                                    tab[i] = tab[min];
                                    tab[min] = temp;

                                    rectangles[min].y += 1;
                                    rectangles[i].y += 1;
                                }
                                i++;
                            } else {
                                i = 0;
                                min = 0;
                                rectanglesMoving = 0; // Sorting is complete
                            }
                            break;
                        case SDLK_i:
                            button4Visible = 1;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (Event.button.button == SDL_BUTTON_LEFT) {
                        int mouseX, mouseY;
                        SDL_GetMouseState(&mouseX, &mouseY);


if (button1Visible && mouseX >= button1.x && mouseX < button1.x + button1.w &&
                            mouseY >= button1.y && mouseY < button1.y + button1.h) {
                            printf("Button 1 clicked!\n");
                            button1Visible = 0;
                            for (int i = 0; i < n; i++) {
                                rectanglesVisible[i] = 1;
                            }
                            rectanglesMoving = 0;
                            for (int i = 0; i < n; i++) {
                                rectangles[rectanglesCount++] = (SDL_Rect){j, 100, 100, 50};
                                j = j + 110;
                                /*This loop iterates n times, where n is the number of rectangles.
                        For each iteration, a new SDL_Rect structure is created with the following parameters:
                       x: The x-coordinate, initialized with the value of j.
                       y: The y-coordinate, set to 100.
                       w: Width set to 100 pixels.
                       h: Height set to 100 pixels.
                       The new SDL_Rect is added to the rectangles array, and j is incremented by 150 for the next rectangle's x-coordinate.
                       The post-increment (rectanglesCount++) is used to keep track of the number of rectangles in the array.
                                */
                            }
                        } else if (!button1Visible && mouseX >= button2.x && mouseX < button2.x + button2.w &&
                                   mouseY >= button2.y && mouseY < button2.y + button2.h) {
                            printf("Button 2 clicked!\n");
                            Running = 0;
                        } else if (!button1Visible && mouseX >= button3.x && mouseX < button3.x + button3.w &&
                                   mouseY >= button3.y && mouseY < button3.y + button3.h) {
                            printf("Button 3 clicked!\n");
                            button1Visible = 0;
                            for (int i = 0; i < n; i++) {
                                rectanglesVisible[i] = 0;
                            }
                            rectanglesMoving = 1;
                        } else if (button4Visible && mouseX >= button4.x && mouseX < button4.x + button4.w &&
                                   mouseY >= button4.y && mouseY < button4.y + button4.h) {
                            printf("Button 4 clicked!\n");
                            button4Visible = 0;
                            rectanglesMoving = 0;

                            // Sorting logic integrated into the main loop
                            static int i = 0;
                            static int min = 0;
                            if (i < n - 1) {
                                if (min == i) {
                                    min = i + 1;
                                }
                                for (int k = i + 1; k < n; k++) {
                                    if (tab[k] < tab[min]) {
                                        min = k;
                                    }
                                }
                                if (min != i) {
                                    int temp = tab[i];
                                    tab[i] = tab[min];
                                    tab[min] = temp;

                                    rectangles[min].y += 1;
                                    rectangles[i].y += 1;
                                }
                                i++;
                            } else {
                                i = 0;
                                min = 0;
                                rectanglesMoving = 0; // Sorting is complete
                            }
                        }
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(Renderer, 100, 100, 100, 200);
        SDL_RenderClear(Renderer);


// Draw buttons
        if (button1Visible) {
            SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(Renderer, &button1);
        }

        SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(Renderer, &button2);

        SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(Renderer, &button3);

        if (button4Visible) {
            SDL_SetRenderDrawColor(Renderer, 255, 165, 0, 255);
            SDL_RenderFillRect(Renderer, &button4);
        }

        if (!rectanglesMoving) {
            for (int i = 0; i < rectanglesCount; ++i) {
                if (rectanglesVisible[i]) {
                    SDL_SetRenderDrawColor(Renderer, 100, 50, 100, 200);
                    SDL_RenderFillRect(Renderer, &rectangles[i]);
                }
            }
        }

        if (rectanglesMoving) {
            for (int i = 0; i < rectanglesCount; ++i) {
                rectangles[i].y += 1;
                SDL_SetRenderDrawColor(Renderer, 100, 50, 100, 200);
                SDL_RenderFillRect(Renderer, &rectangles[i]);
            }
        }

        SDL_RenderPresent(Renderer);
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();

    return 0;
}
