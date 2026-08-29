# Nudge

Nudge is a ROS 2 Jazzy/C++ corrective shared-autonomy research platform for a
USAR-inspired differential-drive unmanned ground vehicle (UGV). The robot is
intended to navigate partially known environments while a human operator gives
sparse corrections with an Xbox controller. The central research question is
whether those corrections convey semantic disagreement about motion, plan,
goal, or authority—not only continuous teleoperation commands.

Version 0.1 compares explicit semantic labels with implicit heuristic
interpretation while keeping the downstream assistance architecture common.
The initial backend is Gazebo; simulator-specific code is isolated so an
NVIDIA Isaac Sim backend and a physical NVIDIA Jetson Orin Nano robot can be
added later. The target completion date for v0.1 is **September 16, 2026**.

This repository currently contains the initial foundation only: interfaces,
configuration contracts, state-machine scaffolds, a minimal robot description,
logging schemas, package boundaries, and tests. Research hypotheses are
provisional, and no experimental results have yet been established.

## Requirements

- ROS 2 Jazzy with `ament_cmake` and `rosidl_default_generators`
- A C++17 compiler
- `colcon`
- `xacro` for inspecting the robot model
- Gazebo and Nav2 only for later integration work; neither is required by the
  unit tests in this foundation

## Build and test

From the repository root:

```bash
cd ros2_ws
colcon build --symlink-install
source install/setup.bash
colcon test
colcon test-result --verbose
```

On Windows, use the ROS-supported developer shell and source the generated
`install/setup.ps1` instead.

## Packages

| Package | Foundation responsibility |
| --- | --- |
| `nudge_interfaces` | Shared messages and enumerated values |
| `nudge_ugv_description` | Parameterized differential-drive URDF/Xacro |
| `nudge_input` | Controller mapping and deadzone/filter primitives |
| `nudge_corrections` | Future event extraction and semantic interpretation boundary |
| `nudge_autonomy` | Future Nav2, assumed-goal, objective, and confidence boundary |
| `nudge_arbitration` | Authority and lifecycle FSM scaffolds |
| `nudge_operator` | Operator context and observable statistics boundary |
| `nudge_environment` | Spatial knowledge/confidence boundary |
| `nudge_logging` | Run-directory and schema scaffolds |
| `nudge_sim` | Simulator-specific backends, currently Gazebo placeholders |
| `nudge_bringup` | Top-level launch and configuration composition |

The authoritative v0.1 design contract is
[`docs/specs/Nudge_v0.1_System_Specification.tex`](docs/specs/Nudge_v0.1_System_Specification.tex).
The architecture overview and proposed GitHub work plan are under `docs/`.

## Scope boundary

The current scaffold intentionally does not implement a heuristic classifier,
corrective Nav2 behavior, a USAR world, learned perception, reinforcement
learning, natural-language interaction, or physical-robot integration. All
unfinalized thresholds remain explicit `null`/TODO values in YAML.
