DEMO math practice for stronghold triangulation.

This is a CLI-only project, and there are no plans to add a GUI. 

This is using 2 chunk axis triangulation, specifically the one explained in this video by Fineberg.


> **Note**: Note that the numbers are randomly generated(within a reasonable range) and independent from each other; as a result, some information given does not follow stronghold rules, as an example, the angle might be -165.00 but show a positive z chord. Unfortunately, there is no quick fix for this; a complete rework is needed. The focus of this demo is to practice the mental math required for axis triangulation, which this demo does accomplish. The rework is currently a WIP.

<img src="example.png">

# Planned features:

- Rework how the info is generated for realistic scenarios.

- ability to set the margin of error

- ability to set axis pressure

## Reach features:
- other triangulation methods (i.e., 4-sprint jump, distance estimation, etc.)

# installation/usage

Download/clone the repo.

cd to the repo

`cd /*REPLACE-WITH-PATH-TO-PROJECT*/AnglePrac`

Run it through your preferred terminal.

`./AP`

To stop use crtl-c, or any other termination signal
