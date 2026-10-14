# Augustus Evolution — Roman City & Legion Strategy

Independent development workspace for a future Augustus fork, building on the AGPL-3.0 Augustus codebase. **These added files currently contain an offline browser design prototype, not a native executable.**

## Try the prototype
Double-click `AE_Prototype.html` in Edge/Chrome on Windows. Explore Chief Advisor issues, housing requirements, and the new Legion Council demonstration with editable simulated army numbers. No network required.

## Feature commitments
1. **Intelligent Chief Advisor:** rank city-wide threats, explain causes and minimum practical fix, compare growth-oriented remedies.
2. **Housing Evolution Tracker:** next level requirements, current blockers, physically highest viable tier and district-wide coverage gaps. Prototype values are illustrative, not Augustus thresholds.
3. **Graphics/UX:** improve readability, DPI-aware presentation, high quality replacement Roman art where appropriately licensed. Do not copy proprietary game art.
4. **Cossacks-inspired Roman tactical depth:** cohorts, formations, cavalry flanks, defensive structures, supply/morale, sieges, provincial campaigns; optional toggle so classic Augustus remains classic. No 17th-century cannons/muskets or unlicensed Cossacks assets.
5. **Game experience first:** slow/fast/pause speed, clear onboarding, actionable diagnostics, low-alert-noise design; advisors remain optional and never spend resources automatically.

## Integration map (upstream Augustus)
- `src/building/house_evolution.c`, `house_service.c`: collect real per-house requirements read-only, respecting original evolution rules.
- `src/window/building/house.c`: future housing UI entry.
- `src/window/advisor/chief.c`: future prioritized actionable advisor entry.
- `src/graphics/`: future DPI, UI and licensed optional HD sprites.
- Military engine requires separate technical feasibility investigation; **Cossacks 3's engine/code is not included**.

## Native fork setup (next stage)
Use GitHub **Fork** on https://github.com/Keriew/augustus to your account, ideally as `augustus-evolution`. Preserve upstream license and attribution. Clone that fork locally and add these design files under the branch root. Build upstream via its documented CMake workflow and required dependencies. Original Caesar III data is still required.

## Review session — Oct 14, 2026 evening
See `AE_TONIGHT_REVIEW.md`.

## Status
- Offline advisor, housing and Legion Council **demo**: available.
- Native engine integration: not implemented.
- Compiled Windows EXE and installer: not built.
- Real tactical combat, hi-res world sprites, live simulation inputs: not implemented.
