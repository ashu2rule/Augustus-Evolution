#include "AE_diagnostics.h"
#include <stddef.h>

static void push(ae_issue *out, int capacity, int *count, ae_issue issue)
{
    int i = *count;
    (*count)++;
    if (i >= capacity) return;
    /* Keep output ordered by descending severity without mutating the simulation. */
    while (i > 0 && out[i - 1].severity < issue.severity) {
        out[i] = out[i - 1];
        --i;
    }
    out[i] = issue;
}
int ae_diagnose(const ae_city_snapshot *s, ae_issue *out, int capacity)
{
    if (!s || capacity < 0 || (capacity > 0 && !out)) return -1;
    int n = 0;
    int deficit = s->consumed_food_monthly - s->produced_food_monthly;
    if (deficit > 0) {
        int months = s->stored_food > 0 ? s->stored_food / deficit : 0;
        int severity = months <= 1 ? 3 : (months <= 3 ? 2 : 1);
        push(out, capacity, &n, (ae_issue){ AE_ISSUE_FOOD, severity, deficit, months });
    }
    if (s->workers_missing > 0)
        push(out, capacity, &n, (ae_issue){ AE_ISSUE_LABOR, 2, s->workers_missing, -1 });
    if (s->monthly_balance < 0) {
        int months = s->treasury > 0 ? s->treasury / -s->monthly_balance : 0;
        push(out, capacity, &n, (ae_issue){ AE_ISSUE_TREASURY, months <= 2 ? 3 : 2, -s->monthly_balance, months });
    }
    if (s->enemy_arrives_months >= 0 && s->estimated_enemy_soldiers > s->ready_soldiers)
        push(out, capacity, &n, (ae_issue){ AE_ISSUE_DEFENSE,
            s->enemy_arrives_months <= 2 ? 3 : 2,
            s->estimated_enemy_soldiers - s->ready_soldiers, s->enemy_arrives_months });
    return n;
}
