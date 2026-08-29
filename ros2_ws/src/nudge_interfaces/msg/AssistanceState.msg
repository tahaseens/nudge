uint8 AUTHORITY_AUTONOMOUS=0
uint8 AUTHORITY_SHARED=1
uint8 AUTHORITY_HUMAN_DOMINANT=2

uint8 LIFECYCLE_INIT=0
uint8 LIFECYCLE_READY=1
uint8 LIFECYCLE_RUNNING=2
uint8 LIFECYCLE_PAUSED=3
uint8 LIFECYCLE_COMPLETE=4
uint8 LIFECYCLE_ESTOP=5

std_msgs/Header header
uint8 authority_state
uint8 lifecycle_state
float32 human_weight
float32 autonomy_weight
bool safety_override_active
string transition_reason
uint32 unresolved_disagreement_count
