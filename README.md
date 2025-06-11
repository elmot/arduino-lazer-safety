Lazer cutter safety board firmware
===

| Function    | Pin    |
|-------------|--------|
| Relay       | A0     |
| Flow sensor | D2     |
| Cover open  | D3     |
| Speaker     | D4, D5 |

Flow interruption longer than 0.5s OR high level at open cover detector switches off the relay and triggers the alarm sound

Source code compatible with Arduino(unverified) and PlatformIO
