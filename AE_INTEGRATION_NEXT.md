# Augustus Evolution: engine integration checklist

## Confirmed upstream entry points
- `src/window/advisor/chief.c` currently reads food supply, labor, treasury, migration, and defense status.
- `src/building/house_evolution.c` contains the evolution decision logic.
- `src/window/building/house.c` draws house information.

## First native milestone
1. Build unchanged Augustus with its required Caesar III data and record a clean test baseline.
2. Provide read-only `ae_city_snapshot` values from existing Augustus interfaces. `advisor_engine/diagnostics.*` is **not wired to live game data yet**.
3. Verify severity ordering, test no-save-mutation, and replace coarse defense comparisons with gameplay-specific strength estimates.
4. Enumerate each evolution requirement from the actual housing model. Track `met`, `not_met`, and `cannot_verify` states; never guess thresholds.
5. Show minimum corrective action first; recommendations must consider connected roads, workers, storage and distribution before proposing construction.
6. Implement an optional Classic/Strategic/Mentor advisor toggle and a dismiss/snooze facility.
7. Upgrade UI scaling, type legibility, overlays and input responsiveness before attempting wholesale sprite replacement.
8. Add cohort orders, formations, and supply in a separate optional campaign mode only after native advisor/housing functionality is stable.

## Release gates
- No regressions in house evolution or save compatibility.
- Recommendations reproducible from captured city snapshots.
- Minimum-action advice never falsely claims certainty when coverage or routing data are unknown.
- Runs on Windows with native dependencies and lawfully obtained Caesar III game data.
- AGPL-3.0 attribution and source availability maintained.
