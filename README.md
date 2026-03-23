[![Build Check](https://github.com/MADS-NET/r_plugin/actions/workflows/build-check.yml/badge.svg?branch=main)](https://github.com/MADS-NET/r_plugin/actions/workflows/build-check.yml)

# r_plugin plugin for MADS

This is a Source plugin for [MADS](https://github.com/MADS-NET/MADS). The plugin provides a way to embed an R interpreter in the process, which can act as a source, filter, or sink. It works analogously to the [MADS Python agent](https://github.com/mads-net/python_agent).

*Required MADS version: 2.0.0.*


## Supported platforms

Currently, the supported platforms are:

* **Linux** 
* **MacOS**
* **Windows**


## Installation

Linux and MacOS:

```bash
cmake -Bbuild -DCMAKE_INSTALL_PREFIX="$(mads -p)"
cmake --build build -j4
sudo cmake --install build
```

Windows:

```powershell
cmake -Bbuild -DCMAKE_INSTALL_PREFIX="$(mads -p)"
cmake --build build --config Release
cmake --install build --config Release
```


## INI settings

The plugin supports the following settings in the INI file:

```ini
[r_plugin]
use_renv = false # use renv for package management
init_script = "/path/to/scrip.R" # Mandatory path to the R script
r_output_mode = "stdout" # or "buffer"
```

All settings are optional; if omitted, the default values are used.




## Executable demo

<Explain what happens if the test executable is run>

---