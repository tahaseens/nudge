# nudge_ugv_description

Parameterized, simulator-agnostic Xacro for the minimal differential-drive
`nudge_ugv`. It contains no autonomy or Gazebo plugin logic. `map -> odom` and
`odom -> base_footprint` are runtime transforms supplied by localization and
odometry rather than URDF joints.
