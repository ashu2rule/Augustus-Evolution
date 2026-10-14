#ifndef AUGUSTUS_EVOLUTION_DIAGNOSTICS_H
#define AUGUSTUS_EVOLUTION_DIAGNOSTICS_H
/* Pure deterministic prototype; input values must be populated by Augustus adapters. */
typedef struct {
    int produced_food_monthly;
    int consumed_food_monthly;
    int stored_food;
    int workers_missing;
    int treasury;
    int monthly_balance;
    int enemy_arrives_months; /* -1 if no known invasion */
    int ready_soldiers;
    int estimated_enemy_soldiers;
} ae_city_snapshot;
typedef enum { AE_ISSUE_FOOD, AE_ISSUE_LABOR, AE_ISSUE_TREASURY, AE_ISSUE_DEFENSE } ae_issue_kind;
typedef struct {
    ae_issue_kind kind;
    int severity; /* 1 low, 2 elevated, 3 high */
    int gap; /* units of food/month, workers, currency/month, soldiers */
    int deadline_months; /* -1 if unknown */
} ae_issue;
/* Returns total issues available, writes up to capacity to out. Ordered by severity. */
int ae_diagnose(const ae_city_snapshot *input, ae_issue *out, int capacity);
#endif
