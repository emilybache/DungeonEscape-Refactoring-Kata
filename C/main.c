#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>   // stat
#include <stdbool.h>    // bool type
#include <unistd.h>

void cell_choices();
void right_corridor();
void guardroom();

bool file_exists(char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

void write_location(char *location) {
    FILE *fp = fopen("location.txt", "a");
    fprintf(fp, "%s\n", location);
    fclose(fp);
}

void delete_location() {
    remove ("location.txt");
}

void play_again() {
    printf("Play again? y/n\n");
    int command;
    while ((command = getchar()) != EOF) {
        switch (command) {
            case 10:
                break;
            case 'y':
                printf("play again\n");
                cell_choices();
                break;
            case 'n':
                printf("quit\n");
                printf("Thankyou for playing");
                exit(0);
                break;

            case 'q':
                printf("Quit\n");
                exit(0);
                break;

            default:
                printf("Unexpected input %d (0x%.2X) ('%c')\n",
                       command, command, isgraph(command) ? command : '.');
                break;
        }
    }

}

void search() {
    char *scenario = "You are searching the guardroom.";
    printf("%s\n", scenario);
    if (file_exists("location.txt")) {
        scenario = "You have found the escaped prisonor! Take them back to their cell. Contragulations, you have won!";
        printf("%s\n", scenario);
        delete_location();
        play_again();
    } else {
        scenario = "There is no-one here";
        printf("%s\n", scenario);
        guardroom();
    }
}

void hiding_loop() {
    int counter = 0;
    char *scenario;
    while (file_exists("location.txt") && counter < 1) {
        scenario = "The screams are quieter.";
        printf("%s\n", scenario);
        sleep(1);
        counter++;
    }
}

void hide() {

    char *scenario = "You are hiding in the guardroom. Press h to stop hiding.";
    printf("%s\n", scenario);
    write_location("guardroom");
    int command;
    hiding_loop();
    if (file_exists("location.txt")) {
        scenario = "You are hiding in the guardroom.";
        char *choices = "\n\t go back (o)ut of the guardroom\n\t Continue (h)iding\n\n";
        printf("%s. Would you like to:%s", scenario, choices);
        while ((command = getchar()) != EOF) {
            switch (command) {
                case 10:
                    break;
                case 'o':
                    printf("out of the guardroom\n");
                    delete_location();
                    right_corridor();
                    break;
                case 'h':
                    printf("hide\n");
                    hide();
                    break;

                case 'q':
                    printf("Quit\n");
                    exit(0);
                    break;

                default:
                    printf("Unexpected input %d (0x%.2X) ('%c')\n",
                           command, command, isgraph(command) ? command : '.');
                    break;
            }
        }
    } else {
        scenario = "You realize the room is not empty any more. A guard appears and captures you. Soon you find yourself back in your cell, feeling miserable that your escape attempt failed.\n";
        printf("%s", scenario);
        play_again();
    }

}



void guardroom() {
    char *scenario = "You are standing in an empty guard room that looks to have been hastily abandoned. There is no-one here but the screams grow louder. Suddenly the light from the torch outside goes out.\n";
    char *choices = "\n\t go back (o)ut of the guardroom\n\t (h)ide in the guardroom\n\t (s)earch the guardroom\n\n";
    printf("%s. Would you like to:%s", scenario, choices);
    int command;
    while ((command = getchar()) != EOF) {
        switch (command) {
            case 10:
                break;
            case 'o':
                printf("out of the guardroom\n");
                delete_location();
                right_corridor();
                break;
            case 'h':
                printf("hide\n");
                hide();
                break;
            case 's':
                printf("search\n");
                search();
                break;
            case 'q':
                delete_location();
                printf("Quit\n");
                exit(0);
                break;

            default:
                printf("Unexpected input %d (0x%.2X) ('%c')\n",
                       command, command, isgraph(command) ? command : '.');
                break;
        }
    }
}

void upstairs() {
    printf("The stairs lead to the dungeon exit. Your friend Freija the Magnificent Warrior runs towards you and embraces you. 'I am here to rescue you!' she says.\nCongratulations! You have won!!\n\n");
    play_again();
}

void left_corridor() {
    char *scenario = "You are standing at the bottom of some stairs in the dungeon. There is a torch burning on your left and a closed door on your right. You hear screams behind you.";
    char *choices = "\n\t go (u)p the stairs\n\t go (b)ack\n\t go (t)hrough the door\n\n";
    printf("%s. Would you like to:%s", scenario, choices);
    int command;
    while ((command = getchar()) != EOF) {
        switch (command) {
            case 10:
                break;
            case 'u':
                printf("up the stairs\n");
                upstairs();
                break;
            case 'b':
                printf("go back\n");
                right_corridor();
                break;
            case 't':
                printf("go through the door\n");
                guardroom();
                break;

            case 'q':
                printf("Quit\n");
                exit(0);
                break;

            default:
                printf("Unexpected input %d (0x%.2X) ('%c')\n",
                       command, command, isgraph(command) ? command : '.');
                break;
        }
    }

}


void right_corridor() {

    char *scenario = "You are standing in a corridor in the dungeon. It is very dark. A man runs towards you screaming, carrying a big sword";
    char *choices = "\n\t (r)un the other way\n\t (f)ight him\n\n";
    printf("%s. Would you like to:%s", scenario, choices);
    int command;
    while ((command = getchar()) != EOF) {
        switch (command) {
            case 10:
                break;
            case 'r':
                printf("run\n");
                left_corridor();
                break;
            case 'f':
                printf("fight\n");
                printf("Unfortunately you lose the fight and fall to the floor dead.\n");
                play_again();
                break;

            case 'q':
                printf("Quit\n");
                exit(0);
                break;

            default:
                printf("Unexpected input %d (0x%.2X) ('%c')\n",
                       command, command, isgraph(command) ? command : '.');
                break;
        }
    }
}

void door_choices() {
    char *choices = "You are standing in a corridor in the dungeon. To the left you can see a torch burning and some steps. To the right it is dark and you hear screams. Would you like to \n\t go (l)eft\n\t go (r)ight\n\n";
    printf("%s", choices);
    int command;

    while ((command = getchar()) != EOF) {
        switch (command) {
            case 10:
                break;
            case 'l':
                printf("go left\n");
                left_corridor();
                break;
            case 'r':
                printf("go right\n");
                right_corridor();
                break;

            case 'q':
                printf("Quit\n");
                exit(0);
                break;

            default:
                printf("Unexpected input %d (0x%.2X) ('%c')\n",
                       command, command, isgraph(command) ? command : '.');
                break;
        }
    }

}

void cell_choices() {
    char *choices = "You are standing in a cell in the dungeon. The recent earthquake has broken the door. Would you like to \n\t (s)tay in the cell\n\t go through the (d)oor\n\n";
    printf("%s", choices);
    int command;

    while ((command = getchar()) != EOF) {
        switch (command) {
            case 10:
                break;
            case 's':
                printf("stay in the cell\n");
                cell_choices();
                break;
            case 'd':
                printf("go through the door\n");
                door_choices();
                break;

            case 'q':
                printf("Quit\n");
                exit(0);
                break;

            default:
                printf("Unexpected input %d (0x%.2X) ('%c')\n",
                       command, command, isgraph(command) ? command : '.');
                break;
        }
    }

}

int main() {
    printf("Press q to quit at any time.\n\n");

    cell_choices();

    return 0;
}