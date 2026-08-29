uint8 CORRECTION_UNKNOWN=0
uint8 CORRECTION_MOTION=1
uint8 CORRECTION_PLAN=2
uint8 CORRECTION_GOAL=3
uint8 CORRECTION_AUTHORITY=4

uint8 SOURCE_EXPLICIT=0
uint8 SOURCE_HEURISTIC=1

std_msgs/Header header
uint8 correction_type
float32 confidence
uint8 interpretation_source
# Zero denotes no heuristic match (for example, an explicit interpretation).
# H01-H99 map to their numeric suffix when heuristic rules are implemented.
uint32 matched_heuristic_rule_id
nudge_interfaces/CorrectionEvent source_event
