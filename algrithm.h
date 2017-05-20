
/*

This header file contains algorithm functions.

*/

#ifndef _ALGRITHM_H_
#define _ALGRITHM_H_

// Creates random map.
void Random()
{
    COORD c , d = GetCursorPosition();
    char s[1024] , ss[1024];

    do
    {
        strcpy(s , "Enter block infrequency factor (1 < digit): ");
        WriteInformation(s);
        c = info_position;
        c.X += strlen(s);
        SetCursorPosition(c);
        gets(ss);
    } while(strlen(ss) > 1 || !isdigit(ss[0]) || ss[0] < '2');

    block_infrequency_factor = ss[0] - 48;

    for(c.X = starting_position.X ; c.X <= ending_position.X ; c.X++) for(c.Y = starting_position.Y ; c.Y <= ending_position.Y ; c.Y++)
    {
        if(rand() % block_infrequency_factor) SetObject(NOTHING , c);
        else                                  rand() % 2 ? SetObject(RED_BLOCK , c) : SetObject(BLUE_BLOCK , c);
    }

    SetCursorPosition(d);
}

// Calculates Manhattan distance between two points.
int Distance(COORD coordinate1 , COORD coordinate2)
{
    return abs(coordinate1.Y - coordinate2.Y) + abs(coordinate1.X - coordinate2.X);
}

// Starts algorithm.
void Start()
{
    double z; // Normalization constant..
    int rs = main_box_lower_right_position.X - main_box_upper_left_position.X - 1;
    int cs = main_box_lower_right_position.Y - main_box_upper_left_position.Y - 1;
    COORD c , d;
    char s[1024] , _s[1024];
    int ch;
    int correct , wrong;
    bool con = false; // If true, user must push button to stop algorithm.
    bool mx = false; // Maximum speed.
    int update = 0; // If positive, don't update screen.

    // Give every block an equal weight..
    z = 0.;
    for(int i = 0 ; i < cs ; i++) for(int j = 0 ; j < rs ; j++) if(object[i][j] != NOTHING) z += 1.;
    for(int i = 0 ; i < cs ; i++) for(int j = 0 ; j < rs ; j++)
        if(object[i][j] != NOTHING) weight[i][j] = 1. / z;
        else weight[i][j] = 0.;

    classifier = NULL;
    background = NULL;
    step = 0;

    do
    {
        // Allocate space for 'classifier' array..
        classifier = (CLASSIFIER*)realloc(classifier , (step + 1) * sizeof(CLASSIFIER));

        // Classify..
        Classify();

        // Allocate memory for 'background' array...
        background = (COLOUR***)realloc(background , sizeof(COLOUR**) * (step + 1));
        background[step] = (COLOUR**)malloc(sizeof(COLOUR*) * cs);
        for(int i = 0 ; i < cs ; i++) background[step][i] = (COLOUR*)malloc(sizeof(COLOUR) * rs);
        // Fill 'background' array's new dimension with BLACK values...
        for(int i = 0 ; i < cs ; i++) for(int j = 0 ; j < rs ; j++) background[step][i][j] = BLACK;

        // Update 'background' array..
        if(!classifier[step].is_horizontal)
            if(classifier[step].left_up == RED)
            {
                for(int i = 0 ; i < classifier[step].division_place ; i++) for(int j = 0 ; j < rs ; j++) background[step][i][j] = RED;
                for(int i = classifier[step].division_place ; i < cs ; i++) for(int j = 0 ; j < rs ; j++) background[step][i][j] = BLUE;
            }
            else
            {
                for(int i = 0 ; i < classifier[step].division_place ; i++) for(int j = 0 ; j < rs ; j++) background[step][i][j] = BLUE;
                for(int i = classifier[step].division_place ; i < cs ; i++) for(int j = 0 ; j < rs ; j++) background[step][i][j] = RED;
            }
        else
            if(classifier[step].left_up == RED)
            {
                for(int i = 0 ; i < cs ; i++) for(int j = 0 ; j < classifier[step].division_place ; j++) background[step][i][j] = RED;
                for(int i = 0 ; i < cs ; i++) for(int j = classifier[step].division_place ; j < rs ; j++) background[step][i][j] = BLUE;
            }
            else
            {
                for(int i = 0 ; i < cs ; i++) for(int j = 0 ; j < classifier[step].division_place ; j++) background[step][i][j] = BLUE;
                for(int i = 0 ; i < cs ; i++) for(int j = classifier[step].division_place ; j < rs ; j++) background[step][i][j] = RED;
            }

        // Update screen. Screen will show result, not current classification.
        if(!update)
        {
            for(c.X = starting_position.X ; c.X <= ending_position.X ; c.X++) for(c.Y = starting_position.Y ; c.Y <= ending_position.Y ; c.Y++)
            {
                d = CursorToCoordinate(c);
                double s = 0.;
                for(int i = 0 ; i <= step ; i++) background[i][d.X][d.Y] == RED ? s += classifier[i].alpha : s -= classifier[i].alpha;
                if(s > 0.) { if(current_background[d.X][d.Y] != RED)  SetBackground(RED , c);  }
                else       { if(current_background[d.X][d.Y] != BLUE) SetBackground(BLUE , c); }
            }
            correct = wrong = 0;
            for(int i = 0 ; i < cs ; i++) for(int j = 0 ; j < rs ; j++)
                if(object[i][j] != NOTHING) if(object[i][j] == RED_BLOCK && current_background[i][j] == RED || object[i][j] == BLUE_BLOCK && current_background[i][j] == BLUE) correct++;
                                            else wrong++;
        }
        if(con)
        {
            sprintf(_s , "%d steps/sec" , speed);
            sprintf(s , "Step = %d , Epsilon = %.2lf , Alpha = %.2lf , Classified = %d , Not classified = %d , Rate = %.2lf%% , Speed = %s" , step + 1 , classifier[step].epsilon , classifier[step].alpha , correct , wrong , 100. * correct / (correct + wrong) , mx ? "MAX" : _s);
            WriteInformation(s);
            WriteMenu("S = increase speed , D = decrease speed , M = maximum speed , ENTER = stop");
            if(kbhit())
            {
                int i = getch();
                if     (i == 's' || i == 'S') { mx = false; if(speed < 1000) speed++; }
                else if(i == 'd' || i == 'D') { mx = false; if(speed > 1)    speed--; }
                else if(i == 'm' || i == 'M') mx = true;
                else if(i == ENTER_KEY)       con = false;
            }
        }
        else if(!update)
        {
            sprintf(s , "Step = %d , Epsilon = %.2lf , Alpha = %.2lf , Classified = %d , Not classified = %d , Rate = %.2lf%%" , step + 1 , classifier[step].epsilon , classifier[step].alpha , correct , wrong , 100. * correct / (correct + wrong));
            WriteInformation(s);
            WriteMenu("ANY KEY = continue , ESC = stop , C = continue without stopping , Q = go 10 steps , W = go 100 steps , E = go 1000 steps");
            ch = getch();
            if(ch == ESC_KEY)
            {
                free(classifier);
                free(background);
                ResetBackground();
                WriteMenu(main_menu);
                WriteInformation(main_info);
                return;
            }
            else if(ch == 'c' || ch == 'C') con = true;
            else if(ch == 'q' || ch == 'Q') update = 10;
            else if(ch == 'w' || ch == 'W') update = 100;
            else if(ch == 'e' || ch == 'E') update = 1000;
        }

        // Calculate new weights..
        for(int i = 0 ; i < cs ; i++) for(int j = 0 ; j < rs ; j++)
            if(object[i][j] != NOTHING)
                if(object[i][j] == RED_BLOCK && background[step][i][j] == RED || object[i][j] == BLUE_BLOCK && background[step][i][j] == BLUE) weight[i][j] *= exp(-1 * classifier[step].alpha);
                else weight[i][j] *= exp(classifier[step].alpha);
        z = 0.;
        for(int i = 0 ; i < cs ; i++) for(int j = 0 ; j < rs ; j++) if(object[i][j] != NOTHING) z += weight[i][j];
        for(int i = 0 ; i < cs ; i++) for(int j = 0 ; j < rs ; j++)
            if(object[i][j] != NOTHING) weight[i][j] /= z;

        if(con && !mx) Sleep(1000 / speed);

        if(update) --update;
    } while(++step);
}

// Classifier function. Makes horizontal or vertical classify. Always makes best guesses.
void Classify()
{
    int v , h;
    int rs = main_box_lower_right_position.X - main_box_upper_left_position.X - 1;
    int cs = main_box_lower_right_position.Y - main_box_upper_left_position.Y - 1;
    double epsilon , minepsilon = 1;
    int vh; // 0 is vertical, 1 is horizontal.
    int n;
    int lrud; // 0 means left (up) side is red, 1 means right (down) side is red.

    // Vertical..
    for(v = 0 ; v <= cs ; v++)
    {
        // Left is red..
        epsilon = 0.;
        for(int i = 0 ; i < v ; i++) for(int j = 0 ; j < rs ; j++) if(object[i][j] == BLUE_BLOCK) epsilon += weight[i][j];
        for(int i = v ; i < cs ; i++) for(int j = 0 ; j < rs ; j++) if(object[i][j] == RED_BLOCK) epsilon += weight[i][j];
        if(epsilon < minepsilon)
        {
            minepsilon = epsilon;
            vh = 0;
            n = v;
            lrud = 0;
        }
        // Left is blue..
        epsilon = 0.;
        for(int i = 0 ; i < v ; i++) for(int j = 0 ; j < rs ; j++) if(object[i][j] == RED_BLOCK) epsilon += weight[i][j];
        for(int i = v ; i < cs ; i++) for(int j = 0 ; j < rs ; j++) if(object[i][j] == BLUE_BLOCK) epsilon += weight[i][j];
        if(epsilon < minepsilon)
        {
            minepsilon = epsilon;
            vh = 0;
            n = v;
            lrud = 1;
        }
    }

    // Horizontal..
    for(h = 0 ; h <= rs ; h++)
    {
        // Up is red..
        epsilon = 0.;
        for(int i = 0 ; i < cs ; i++) for(int j = 0 ; j < h ; j++) if(object[i][j] == BLUE_BLOCK) epsilon += weight[i][j];
        for(int i = 0 ; i < cs ; i++) for(int j = h ; j < rs ; j++) if(object[i][j] == RED_BLOCK) epsilon += weight[i][j];
        if(epsilon < minepsilon)
        {
            minepsilon = epsilon;
            vh = 1;
            n = h;
            lrud = 0;
        }
        // Up is blue..
        epsilon = 0.;
        for(int i = 0 ; i < cs ; i++) for(int j = 0 ; j < h ; j++) if(object[i][j] == RED_BLOCK) epsilon += weight[i][j];
        for(int i = 0 ; i < cs ; i++) for(int j = h ; j < rs ; j++) if(object[i][j] == BLUE_BLOCK) epsilon += weight[i][j];
        if(epsilon < minepsilon)
        {
            minepsilon = epsilon;
            vh = 1;
            n = h;
            lrud = 1;
        }
    }

    classifier[step].epsilon = minepsilon;
    classifier[step].is_horizontal = vh;
    classifier[step].division_place = n;
    classifier[step].left_up = lrud ? BLUE : RED;
    classifier[step].alpha = classifier[step].epsilon ? .5 * log((1 - minepsilon) / minepsilon) : 1.;
}

#endif
