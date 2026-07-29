#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

typedef struct {
    char name[20];
    int votes;
    bool eliminated;
} candidate;

candidate candidates[MAX_CANDIDATES];
int preferences[MAX_VOTERS][MAX_CANDIDATES];
int voter_count, candidate_count;

// الدوال الأساسية
bool vote(int voter, int rank, char name[]) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(candidates[i].name, name) == 0) {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

void tabulate(void) {
    for (int i = 0; i < candidate_count; i++) candidates[i].votes = 0;
    for (int i = 0; i < voter_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            int cand_idx = preferences[i][j];
            if (!candidates[cand_idx].eliminated) {
                candidates[cand_idx].votes++;
                break;
            }
        }
    }
}

bool print_winner(void) {
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > voter_count / 2) {
            printf("Winner: %s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

int find_min(void) {
    int min = voter_count;
    for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated && candidates[i].votes < min) min = candidates[i].votes;
    }
    return min;
}

bool is_tie(int min) {
    for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated && candidates[i].votes != min) return false;
    }
    return true;
}

void eliminate(int min) {
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes == min) candidates[i].eliminated = true;
    }
}

int main() {
    printf("Number of candidates: ");
    scanf("%d", &candidate_count);
    for (int i = 0; i < candidate_count; i++) {
        printf("Candidate %d name: ", i + 1);
        scanf("%s", candidates[i].name);
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    printf("Number of voters: ");
    scanf("%d", &voter_count);
    for (int i = 0; i < voter_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            char name[20];
            printf("Rank %d for voter %d: ", j + 1, i + 1);
            scanf("%s", name);
            if (!vote(i, j, name)) { printf("Invalid name!\n"); j--; }
        }
    }
    // حلقة الـ Runoff
    while (true) {
        tabulate();
        if (print_winner()) break;
        int min = find_min();
        if (is_tie(min)) { printf("The election is a tie!\n"); break; }
    }}