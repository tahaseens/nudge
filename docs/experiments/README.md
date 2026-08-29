# Experiments

The v0.1 evaluation will compare `NUDGE_EXPLICIT` and `NUDGE_IMPLICIT` using a
shared downstream autonomy and assistance stack. `MANUAL`, `AUTO`, and
`FIXED_BLEND` are planned baselines.

No hypotheses, scenario parameters, participant protocol, sample size, metric
definitions, or classifier thresholds are finalized in this foundation. Those
decisions require explicit research review and must be recorded in the system
specification and run manifest before data collection.

Every run follows the schema documented by `nudge_logging` and records operator
context, configuration provenance, assumed and ground-truth goals, semantic
events, telemetry, and a rosbag.
