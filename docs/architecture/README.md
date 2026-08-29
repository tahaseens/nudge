# Architecture

Nudge separates semantic interpretation from downstream assistance so explicit
and implicit conditions differ only at the interpretation boundary.

```text
sensor_msgs/Joy
      |
      v
nudge_input ---> human motion command
      |
      v
nudge_corrections ---> CorrectionEvent ---> CorrectionInterpretation
                                              |
                 +----------------------------+
                 v
 nudge_autonomy ---> nudge_arbitration ---> independent safety layer ---> /cmd_vel
       ^                    ^
       |                    |
nudge_environment     nudge_operator

nudge_logging observes state and events without controlling behavior.
```

The core packages use standard ROS 2 interfaces wherever possible and contain
no Gazebo APIs. `nudge_sim` owns backend-specific adapters; its `gazebo/` and
future `isaac_sim/` directories make that boundary visible. The physical robot
will be another backend rather than a dependency of the core stack.

## Invariants

- Explicit and heuristic interpretation produce the same
  `CorrectionInterpretation` contract.
- The safety layer may override both autonomous and human commands.
- Debug mode is observable but never drives the authority FSM.
- Repeated unresolved disagreement can force `HUMAN_DOMINANT` regardless of
  correction confidence.
- Recovery from `HUMAN_DOMINANT` passes through `SHARED`; direct recovery to
  `AUTONOMOUS` is invalid.
- Operator context is recorded from v0.1 even before it affects behavior.
- Research thresholds live in YAML and remain null until justified.

The detailed contract is maintained in `docs/specs`.
