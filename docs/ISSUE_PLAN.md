# Proposed GitHub issue and milestone plan

Create one milestone, **Nudge v0.1 — 2026-09-16**, and track these issues in
dependency order. Labels in parentheses are suggestions.

## Foundation

1. Scaffold ROS 2 workspace and packages (`foundation`)
2. Define Nudge ROS interfaces (`interfaces`)
3. Add YAML configuration system (`configuration`)

## Simulation

4. Create minimal Nudge UGV Xacro (`simulation`)
5. Launch UGV in Gazebo (`simulation`, depends on 4)
6. Integrate Nav2 baseline navigation (`autonomy`, depends on 5)

## Control

7. Xbox controller input (`control`)
8. Lifecycle FSM (`control`)
9. Authority FSM (`control`)
10. Manual baseline (`baseline`, depends on 7, 8)
11. Autonomous baseline (`baseline`, depends on 6, 8)
12. Fixed-blend baseline (`baseline`, depends on 9–11)

## Nudge

13. Correction event detector (`nudge`, depends on 3, 7)
14. Explicit Semantic Nudge (`nudge`, depends on 2, 13)
15. Heuristic semantic classifier (`nudge`, depends on 2, 3, 13)
16. Integrate corrective objective/cost updates with Nav2 (`nudge`, depends on 6, 14, 15)

## Confidence

17. Autonomy confidence (`confidence`)
18. Correction confidence (`confidence`)
19. Spatial environmental-confidence model (`confidence`, `environment`)

## Evaluation

20. Parseable run logging (`evaluation`)
21. USAR test world and scenarios (`evaluation`, `simulation`)
22. Explicit-vs-implicit evaluation runner (`evaluation`, depends on 14, 15, 20, 21)
23. Analysis scripts (`evaluation`, depends on 20)

## Release

24. Document v0.1 results and architecture (`documentation`, depends on evaluation)

Issues 1–3 are partially addressed by the foundation scaffold. Each issue
should include acceptance criteria, test evidence, assumptions introduced, and
specification changes. Research-design decisions should be separate, reviewable
issue discussions rather than incidental implementation choices.
