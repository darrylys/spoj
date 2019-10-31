#include<cstdio>

#define RO 0
#define SC 1
#define PA 2

#define SA 2
#define SB 1
#define TIE 0

char cclang[10][3] = {"cs", "en", "fr", "de", "hu", "it", "jp", "pl", "es"};

char mov[10][5][5] = {  {"1K", "1N", "1P"},  //R, S, P
                        {"1R", "1S", "1P"}, 
                        {"1P", "1C", "1F"}, 
                        {"2St", "2Sc", "1P"}, 
                        {"1K", "1O", "1P"}, 
                        {".", "n", "x"}, //Italian = special case
                        {"1G", "1C", "1P"}, 
                        {"1K", "1N", "1P"}, 
                        {"2Pi", "1T", "2Pa"} };

int get_move(char* lang, char* move) {
    int lc;
    for (int i=0; i<9; i++) {
        if (lang[1] == cclang[i][1] && lang[0] == cclang[i][0]) {
            lc = i;
            break;
        }
    }
    
    if (lc == 5) { //it
        if (move[0] == 'S' || (move[0] == 'R' && move[1] == 'o')) return RO;
        else if (move[0] == 'F') return SC;
        else return PA;
    } else {
        for (int i=0; i<3; i++) {
            for (int j=0; j+'0'<mov[lc][i][0]; j++) {
                if (move[j] != mov[lc][i][j+1]) {
                    goto not_this;
                }
            }
            
            return i;
            
            not_this:
            ;
        }
    }
}

int who_win(int move1, int move2) {
    if (move1 == move2) return TIE;
    int res = move1 - move2;
    if (res == 2) res -= 3;
    else if (res == -2) res += 3;
    
    if (res == -1) return SA;
    else return SB;
}

int main() {
    char langA[5], langB[5];
    char nameA[110], nameB[110];
    char moveA[10], moveB[10];
    int stat[3], codeA, codeB, win, ngame = 1;
    bool f = false;
    while (!f) {
        f = false;
        scanf("%s", langA);
        if (langA[0] == '.') break;
        
        scanf("%s", nameA);
        scanf("%s %s", langB, nameB);
        
        stat[0] = stat[1] = stat[2] = 0;
        
        while (true) {
            scanf("%s", moveA);
            if (moveA[0] == '-') {
                break;
            }
            if (moveA[0] == '.') {
                f = true;
                goto jump;
            }
            scanf("%s", moveB);
            
            codeA = get_move(langA, moveA);
            codeB = get_move(langB, moveB);
            
            win = who_win(codeA, codeB);
            
            stat[win]++;
        }
        
        jump:
        
        printf("Game #%d:\n", ngame++);
        
        if (stat[SA] == 1) {
            printf("%s: 1 point\n", nameA);
        } else {
            printf("%s: %d points\n", nameA, stat[SA]);
        }
        
        if (stat[SB] == 1) {
            printf("%s: 1 point\n", nameB);
        } else {
            printf("%s: %d points\n", nameB, stat[SB]);
        }
        
        if (stat[SA] == stat[SB]) {
            printf("TIED GAME\n");
        } else if (stat[SA] > stat[SB]) {
            printf("WINNER: %s\n", nameA);
        } else {
            printf("WINNER: %s\n", nameB);
        }
        putchar('\n');
    }
    return 0;
}