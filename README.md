# espaxa-external (ESPHome external component)

AXA Remote 2.0 (UART) integration for ESPHome as an external component.

## Quick start

1. Create a new GitHub repo and push these files (or download the ZIP below and `git init`).
2. In your ESPHome node YAML:

```yaml
external_components:
  - source:
      type: git
      url: https://github.com/<youruser>/espaxa-external
    components: [espaxa]

uart:
  tx_pin: D7      # adjust
  rx_pin: D6
  baud_rate: 9600 # adjust to device

espaxa:
  id: axa_base

cover:
  - platform: espaxa
    id: axa_cover
    name: "AXA Window"
```

## What’s included

- `components/espaxa` base C++ runtime + Python codegen
- `components/espaxa/cover` cover platform (open/close/stop)
- optional sensor stubs

## Notes

- Replace command/status parsing if your AXA variant differs.
- If you have position feedback, publish real position in the cover class.
- Layout follows ESPHome's `components/<name>` discovery for `external_components:`.
