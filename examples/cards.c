#include <tstd.h>

#define MAX_CARDS 13

typedef struct {
    unsigned char cards[MAX_CARDS];
    unsigned char stacks;
    char *label;
} player_t;

typedef enum {
    PLAYER = 0,
    ENEMY = 1,
} player_turn_t;

typedef struct {
    player_t enemy;
    player_t player;
    player_turn_t turn;
} game_state_t;

char card_labels[][MAX_CARDS] = {
    "[A]", "[2]", "[3]", "[4]", "[5]", "[6]", "[7]", "[8]", "[9]", "[10]", "[J]", "[Q]", "[K]"
};

int draw_card(player_t *player) {
    int card = randuint() % MAX_CARDS;
    player->cards[card] += 1;
    return card;
}

void randomize_cards(player_t *player) {
    for (int i = 0; i < 10; i++) {
        draw_card(player);
    }
}

int check_stacks(player_t *player) {
    int count = 0;
    for (int i = 0; i < MAX_CARDS - 1; i++) {
        if (player->cards[i] >= 4) {
            player->stacks += 1;
            player->cards[i] -= 4;
            count += 1;
        }
    }
    return count;
}

int check_cards(player_t *player, player_t *enemy, int card) {
    int taken = 0;
    if (enemy->cards[card] > 0) {
        taken = enemy->cards[card];
        player->cards[card] += enemy->cards[card];
        enemy->cards[card] = 0;
    }
    return taken;
}

void print_deck(player_t *player) {
    char buf[4];

    print(player->label);
    print(" deck:\n | ");

    for (int i = 0; i < MAX_CARDS; i++) {
        if (player->cards[i] > 0) {
            intstr(player->cards[i], buf);
            print(card_labels[i]);
            print(" ");
            print(buf);
            print(" | ");
        }
    }

    print("\n");
}

int main(int argc, char **argv) {
    game_state_t game;
    player_t *active_player, *idle_player;
    int count, card;
    char buf[3];

    game.player.label = "Blaze";
    game.enemy.label = "Alex";
    game.turn = PLAYER;

    randomize_cards(&game.player);
    randomize_cards(&game.enemy);

    while (1) {
        if (game.turn == PLAYER) {
            active_player = &game.player;
            idle_player = &game.enemy;

            print(active_player->label);
            print(" stacks: ");
            intstr(active_player->stacks, buf);
            print(buf);
            print(" | ");
            print(idle_player->label);
            print(" stacks: ");
            intstr(idle_player->stacks, buf);
            print(buf);
            print("\n");

            print_deck(&game.player);
            print("Which card do you want to ask?\n");
            print("> ");

            count = read(buf, 3) - 1;
            if (count == 1) {
                if (buf[0] >= '2' && buf[0] <= '9') {
                    card = buf[0] - '0' - 1;
                } else if (buf[0] == 'A') {
                    card = 0;
                } else if (buf[0] == 'J') {
                    card = 10;
                } else if (buf[0] == 'Q') {
                    card = 11;
                } else if (buf[0] == 'K') {
                    card = 12;
                } else {
                    print("This is not a valid card\n");
                    continue;
                }
            } else if (count == 2) {
                if (buf[0] == '1' && buf[1] == '0') {
                    card = 9;
                }
            } else {
                print("This is not a valid card\n");
                continue;
            }

            if (active_player->cards[card] == 0) {
                print("You dont have such card\n");
                continue;
            }
        } else {
            active_player = &game.enemy;
            idle_player = &game.player;
        }

        // Enemy """AI"""
        if (game.turn == ENEMY) {
            while (1) {
                card = randuint() % MAX_CARDS;
                if (active_player->cards[card] == 0) {
                    continue;
                }
                break;
            }
        }

        count = check_cards(active_player, idle_player, card);
        if (count > 0) {
            print(active_player->label);
            print(" took ");
            intstr(count, buf);
            print(buf);
            print(" ");
            print(card_labels[card]);
            print(" from ");
            print(idle_player->label);
            print("\n");
        } else {
            print(active_player->label);
            print(" asked ");
            print(idle_player->label);
            print(" for ");
            print(card_labels[card]);
            print(", but ");
            print(idle_player->label);
            print(" doesnt have it\n");

            if (game.turn == PLAYER) {
                card = draw_card(active_player);
                print(active_player->label);
                print(" drew ");
                print(card_labels[card]);
                print("\n");
                game.turn = ENEMY;
            } else {
                game.turn = PLAYER;
            }
        }

        count = check_stacks(active_player);
        if (count > 0) {
            print(active_player->label);
            print(" finished a stack\n");

            if (active_player->stacks == 4) {
                print(active_player->label);
                print(" won\n");
                break;
            }
        }
    }

    return 0;
}
