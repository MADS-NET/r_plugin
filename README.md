[![Build Check](https://github.com/MADS-NET/r_plugin/actions/workflows/build-check.yml/badge.svg?branch=main)](https://github.com/MADS-NET/r_plugin/actions/workflows/build-check.yml)

# r_plugin collection for MADS

This project provides a Source, a Filret and a Sink plugin for [MADS](https://github.com/MADS-NET/MADS). The plugins provide a way to embed an R interpreter in the MADS network. They works analogously to the [MADS Python agent](https://github.com/mads-net/python_agent).

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

# R script details

The R script (loaded by the `init_script` config path), must define a valid R function, whose name and signature depends on the type of plugin:

* a **source**: there must be a `load_data()` function that receives a list of values (converted from JSON) and stores them internally, and a `get_output()` function that takes no arguments and returns a R list (which is automatically converted to JSON object)
* a **filter**: there must be a `process(list)` function that takes a list as a single argument; that list represents the JSON received by the filter agent, and the function must return another list (automatically converted to JSON)
* a **sink**: there must be a `deal_with_data(list)` function that takes a list as a single argument; that list represents the JSON received by the sink agent

---