#include <stdio.h>
#include <windows.h>
#include <string.h>

//Play Mode
int playMode(){

}

//Chord Mode
int chordMode(){
    char chord[4];
    while (TRUE)
    {   
        printf("Press '=' Go to Menu\t'-' Go to Exit\n");
        printf("Chord:");
        scanf("%s",&chord);
        if(strcmp("=",chord) == 0){
            //Menu
            return 0;
        }
        else if(strcmp("-",chord) == 0){
            //Exit
            return 1;
        }
        else if(strcmp("Bb",chord) == 0){
            //Chord Bb
            printf(" ___________________________________________\n"
                "|██|░|█|░|█|▓|██|██|░|▓|░|██|▓▓|░|█|░|█|░|██|\n"
                "|██|░|█|░|█|▓|██|██|░|▓|░|██|▓▓|░|█|░|█|░|██|\n"
                "|██|░|█|░|█|▓|██|██|░|▓|░|██|▓▓|░|█|░|█|░|██|\n"
                "|██|░|█|░|█|▓|██|██|░|▓|░|██|▓▓|░|█|░|█|░|██|\n"
                "|███|███|███|███|███|▓▓▓|███|▓▓▓|███|███|███|\n"
                "|███|███|███|███|███|▓▓▓|███|▓▓▓|███|███|███|\n"
                "|███|███|███|███|███|▓▓▓|███|▓▓▓|███|███|███|\n");
        }
        else if(strcmp("B",chord) == 0){
            //Chord B
            printf(" ___________________________________________\n"
                "|██|▓|█|░|█|░|▓▓|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|██|▓|█|░|█|░|▓▓|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|██|▓|█|░|█|░|▓▓|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|██|▓|█|░|█|░|▓▓|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|███|███|███|▓▓▓|███|███|███|███|███|███|███|\n"
                "|███|███|███|▓▓▓|███|███|███|███|███|███|███|\n"
                "|███|███|███|▓▓▓|███|███|███|███|███|███|███|\n");
        }
    }
}

int main()
{
    int end = 0;
    int mode = 0;
    while(end != 1){
        printf("Mode\n"
               "1.Play Mode\n"
               "2.Chords Mode\n"
               "3.Exit\n"
               "Type in number to choose mode\n"
               "Choose Mode:");
        scanf("%i",&mode);
        if(mode == 1){
            end = playMode();
        }
        else if(mode == 2){
            end = chordMode();
        }
        else if(mode == 3){
            end = 1;
        }
    }
    
    return 0;
}

