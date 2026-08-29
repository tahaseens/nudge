# Run schema

Each run has this shape:

```text
runs/<timestamp>_<scenario_id>/
├── manifest.json
├── telemetry.csv
├── events.jsonl
└── rosbag2/
```

`manifest.schema.json` validates static run context. Each line of `events.jsonl`
is independently validated by `event.schema.json`. The CSV header created by
`RunDirectory` covers the telemetry fields in the v0.1 specification.
