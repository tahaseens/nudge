# Contributing to Nudge

Nudge is an early-stage research codebase. Changes should preserve the clean
comparison between explicit and heuristic semantic interpretation and must not
silently introduce research assumptions.

## Development workflow

1. Start from an issue in the proposed v0.1 plan or document the intended scope.
2. Keep simulator-specific dependencies inside `nudge_sim`.
3. Prefer standard ROS 2 messages and services; add a custom interface only
   when the semantic contract is project-specific.
4. Put adjustable thresholds and mappings in YAML. Use a documented TODO/null
   until a value is justified by the system specification or an experiment.
5. Keep safety enforcement independent of autonomous and human command paths.
6. Add focused tests that do not require Gazebo wherever practical.

Use C++17, the repository `.clang-format`, the `nudge` namespace, and the
conventional `include/<package_name>/`, `src/`, and `test/` layout. Public APIs
should use descriptive names and avoid embedding condition-specific behavior.

Before opening a pull request, run:

```bash
cd ros2_ws
colcon build --symlink-install
colcon test
colcon test-result --verbose
```

Pull requests should state any assumptions, new configuration values, interface
changes, test coverage, and whether the system specification needs updating.
