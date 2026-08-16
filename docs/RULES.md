# RULES.md

## Rules

### Code Style
- C++17 standard.
- camelCase for variables/functions.
- PascalCase for classes.
- Strongly typed enums with domain prefix.
- No magic numbers (use constants).

### Git Workflow
- Feature branches.
- Conventional commits.
- No force-push to main.

### Hardware
- Always run as root when using bcm2835.
- Verify SPI is enabled before running.
- Do not connect 5V devices to Pi GPIO.
