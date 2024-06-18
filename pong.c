#include <stdio.h>
int move_racket(int racket_pos, int player, char movement);
int chng_score_for_player1(int prev_score, int ball_x);
int chng_score_for_player2(int prev_score, int ball_x);
int collision(int ball_ax_coord, int ball_ay_cord, int vector_direction_x, int vector_direction_y,
              int rk1_crd, int rk2_crd, char coll);
int ball_action(int ball_ax_coord, int vector_direction);
void field(int, int, int, int, int, int);
void congrat(int score_1, int score_2);

int main(void) {
    int score_1 = 0;
    int score_2 = 0;
    int ball_x_direction = -1;
    int ball_y_direction = 1;
    int racket1_pos = 12;
    int racket2_pos = 12;
    int ball_y = 13;
    int ball_x = 40;
    int n = 0;
    field(score_1, score_2, ball_x, ball_y, racket1_pos, racket2_pos);  // изначальное поле
    char coll_h = 'h';                                                  // racket collision
    char coll_w = 'w';                                                  // borders collision
    char movement1, movement2, t;
    scanf("%c%c", &movement1, &movement2);
    while (score_1 < 21 && score_2 < 21) {
        int new_score_1, new_score_2;
        racket1_pos = move_racket(racket1_pos, 1, movement1);
        racket2_pos = move_racket(racket2_pos, 2, movement2);
        ball_x_direction =
            collision(ball_x, ball_y, ball_x_direction, ball_y_direction, racket1_pos, racket2_pos, coll_h);
        ball_x = ball_action(ball_x, ball_x_direction);
        ball_y_direction =
            collision(ball_x, ball_y, ball_x_direction, ball_y_direction, racket1_pos, racket2_pos, coll_w);
        ball_y = ball_action(ball_y, ball_y_direction);
        field(score_1, score_2, ball_x, ball_y, racket1_pos, racket2_pos);
        scanf("%c", &t);  // хавает переход на след строку
        scanf("%c%c", &movement1, &movement2);
        new_score_1 = chng_score_for_player1(score_1, ball_x);
        new_score_2 = chng_score_for_player2(score_2, ball_x);
        if ((new_score_1 != score_1) || (new_score_2 != score_2)) {
            if (new_score_1 != score_1) {
                ball_x = 40 - 1;
            } else {
                ball_x = 40 + 1;
            }
            ball_y = 13;
            racket1_pos = 12;
            racket2_pos = 12;
            score_1 = new_score_1;
            score_2 = new_score_2;
            field(new_score_1, new_score_2, ball_x, ball_y, racket1_pos, racket2_pos);
        }
        n++;
    }
    congrat(score_1, score_2);
    return 0;
}

void field(int score_1, int score_2, int ball_x, int ball_y, int racket1_pos, int racket2_pos) {
    int widht = 80;
    int height = 25;
    char gates = '|';
    char border = '-';
    char racket = '*';
    char ball = 'B';
    printf("\033[2J\033[H");

    for (int i = 0; i <= height; i++) {
        for (int j = 0; j <= widht; j++) {
            // top, bottom border
            if ((i == 0) || (i == 25)) {
                printf("%c", border);
                // right, left gates
            } else if ((j == 0) || (j == 80)) {
                printf("%c", gates);
                // ball
            } else if ((i == ball_y) && (j == ball_x)) {
                printf("%c", ball);
                // middle line
            } else if (j == 40) {
                printf("%c", gates);
                // first player score
            } else if ((i == 5) && (j == 20)) {
                printf("%d", score_1);
                // second player score
            } else if ((i == 5) && (j == 60)) {
                printf("%d", score_2);
                // first player racket
            } else if (j == 4) {
                if ((i == racket1_pos) || (i == racket1_pos + 1) || (i == racket1_pos + 2)) {
                    printf("%c", racket);
                } else {
                    printf("%c", ' ');
                }
                // second player racket
            } else if (j == 76) {
                if ((i == racket2_pos) || (i == racket2_pos + 1) || (i == racket2_pos + 2)) {
                    printf("%c", racket);
                } else {
                    printf("%c", ' ');
                }
            } else {
                printf("%c", ' ');
            }
        }
        printf("\n");
    }
}

int ball_action(int ball_ax_coord, int vector_direction) { return ball_ax_coord + vector_direction; }

int move_racket(int racket_pos, int player, char movement) {
    if (player == 1) {
        if ((movement == 'A' || movement == 'a') && (racket_pos != 1)) {
            racket_pos--;
        } else if ((movement == 'Z' || movement == 'z') && (racket_pos != 22)) {
            racket_pos++;
        }
    } else {
        if ((movement == 'K' || movement == 'k') && (racket_pos != 1)) {
            racket_pos--;
        } else if ((movement == 'M' || movement == 'm') && (racket_pos != 22)) {
            racket_pos++;
        }
    }
    return racket_pos;
}

int collision(int ball_ax_coord, int ball_ay_coord, int vector_direction_x, int vector_direction_y,
              int rk1_crd, int rk2_crd, char coll) {
    int v;
    int nxt_chnk_x = ball_ax_coord + vector_direction_x;
    int nxt_chnk_y = ball_ay_coord + vector_direction_y;
    if (coll == 'w') {
        if (((nxt_chnk_y == 0) || (nxt_chnk_y == 25))) {
            v = vector_direction_y * -1;
        } else {
            v = vector_direction_y;
        }
    } else {
        if ((nxt_chnk_x == 4) &&
            ((nxt_chnk_y == rk1_crd) || (nxt_chnk_y == rk1_crd + 1) || (nxt_chnk_y == rk1_crd + 2))) {
            v = vector_direction_x * -1;
        } else if ((nxt_chnk_x == 76) &&
                   ((nxt_chnk_y == rk2_crd) || (nxt_chnk_y == rk2_crd + 1) || (nxt_chnk_y == rk2_crd + 2))) {
            v = vector_direction_x * -1;
        } else {
            v = vector_direction_x;
        }
    }
    return v;
}

int chng_score_for_player1(int prev_score, int ball_x) {
    if (ball_x == 77) {
        prev_score++;
    }
    return prev_score;
}

int chng_score_for_player2(int prev_score, int ball_x) {
    if (ball_x == 3) {
        prev_score++;
    }
    return prev_score;
}

void congrat(int score_1, int score_2) {
    printf("\033[2J\033[H");
    if (score_1 == 21) {
        printf("%d:%d\nPlayer 1 wins!", score_1, score_2);
    } else if (score_2 == 21) {
        printf("%d:%d\nPlayer 2 wins!", score_1, score_2);
    }
}