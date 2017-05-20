
/*

This header file contains miscellaneous functions.

*/

#ifndef _FILE_H_
#define _FILE_H_

// Log file.
void Log()
{
    FILE *f = fopen("log.rtf" , "w");
    int rs = main_box_lower_right_position.X - main_box_upper_left_position.X - 1;
    int cs = main_box_lower_right_position.Y - main_box_upper_left_position.Y - 1;

    fprintf(f , "'object' array:\n");
    for(int i = 0 ; i < cs ; i++)
    {
        for(int j = 0 ; j < rs ; j++) fprintf(f , "%d" , object[i][j]);
        fprintf(f , "\n");
    }

    fprintf(f , "\n");

    fprintf(f , "'object' array adress:\n");
    for(int i = 0 ; i < cs ; i++)
    {
        for(int j = 0 ; j < rs ; j++) fprintf(f , "%8d" , &object[i][j]);
        fprintf(f , "\n");
    }

    fclose(f);
}

// Save 'object' array.
void Save()
{
    char s[1024] , name[1024];
    COORD c = info_position , d = GetCursorPosition();
    FILE *f;
    int rs = main_box_lower_right_position.X - main_box_upper_left_position.X - 1;
    int cs = main_box_lower_right_position.Y - main_box_upper_left_position.Y - 1;

    strcpy(s , "Type file name (without extension) and press enter: ");
    WriteInformation(s);
    c.X += strlen(s);
    SetCursorPosition(c);
    gets(name);

    strcat(name , ".sav");
    f = fopen(name , "w");
    for(int i = 0 ; i < cs ; i++)
    {
        for(int j = 0 ; j < rs ; j++) fprintf(f , "%d" , object[i][j]);
        fprintf(f , "\n");
    }

    fclose(f);

    sprintf(s , "State saved to file: %s" , name);
    WriteInformation(s);

    SetCursorPosition(d);
}

void Load()
{
    char s[1024] , name[1024];
    COORD c = info_position , d = GetCursorPosition();
    FILE *f;
    int rs = main_box_lower_right_position.X - main_box_upper_left_position.X - 1;
    int cs = main_box_lower_right_position.Y - main_box_upper_left_position.Y - 1;

    strcpy(s , "Type file name (without extension) and press enter: ");
    WriteInformation(s);
    c.X += strlen(s);
    SetCursorPosition(c);
    gets(name);

    strcat(name , ".sav");
    if(f = fopen(name , "r"))
    {
        for(int i = 0 ; i < cs ; i++)
        {
            for(int j = 0 ; j < rs ; j++) object[i][j] = (OBJECT)(fgetc(f) - 48);
            fgetc(f);
        }
        for(c.X = starting_position.X ; c.X <= ending_position.X ; c.X++) for(c.Y = starting_position.Y ; c.Y <= ending_position.Y ; c.Y++) SetObject(GetObject(c) , c);
        sprintf(s , "File loaded: %s" , name);
        fclose(f);
    }
    else
        sprintf(s , "No such file: %s" , name);

    WriteInformation(s);

    SetCursorPosition(d);
}
#endif
