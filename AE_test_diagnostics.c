#include "AE_diagnostics.h"
#include <assert.h>
#include <stdio.h>
int main(void)
{
    ae_issue issues[4];
    ae_city_snapshot city = {100, 150, 50, 20, 500, -100, 4, 40, 90};
    int count = ae_diagnose(&city, issues, 4);
    assert(count == 4);
    assert(issues[0].kind == AE_ISSUE_FOOD && issues[0].gap == 50);
    assert(issues[0].deadline_months == 1);
    assert(issues[1].kind == AE_ISSUE_LABOR);
    assert(issues[3].kind == AE_ISSUE_DEFENSE && issues[3].gap == 50);
    assert(ae_diagnose(&city, issues, 0) == 4);
    puts("diagnostic rules: PASS");
    return 0;
}
