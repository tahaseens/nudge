from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, LogInfo
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    condition = LaunchConfiguration("control_condition")
    context = LaunchConfiguration("operator_context")
    return LaunchDescription(
        [
            DeclareLaunchArgument("control_condition", default_value="NUDGE_EXPLICIT"),
            DeclareLaunchArgument("operator_context", default_value="ADJACENT"),
            LogInfo(
                msg=[
                    "Nudge foundation only; no runtime behavior nodes are started. condition=",
                    condition,
                    ", operator_context=",
                    context,
                ]
            ),
        ]
    )
