[![Build Check](https://github.com/MADS-NET/r_plugin/actions/workflows/build-check.yml/badge.svg?branch=main)](https://github.com/MADS-NET/r_plugin/actions/workflows/build-check.yml) ![Dynamic JSON Badge](https://img.shields.io/badge/dynamic/json?url=https%3A%2F%2Fraw.githubusercontent.com%2FMADS-NET%2F.github%2Fmain%2Fprofile%2Fpackages.json&query=%24.packages.%5B'r.plugin'%5D.type&label=mads%20package&logo=C%2B%2B)


# r_plugin collection for MADS

This project provides a Source, a Filret and a Sink plugin for [MADS](https://github.com/MADS-NET/MADS). The plugins provide a way to embed an R interpreter in the MADS network. They works analogously to the [MADS Python agent](https://github.com/mads-net/python_agent).

*Required MADS version: 2.0.0.*


## Supported platforms

Currently, the supported platforms are:

* **Linux** 
* **MacOS**
* **Windows**

## Package install

with MADS v2.1.1 or later, install with:

```bash
mads package --install r.plugin
```

## Install from binaries

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

* a **filter**: there must be a `load_data(list)` function that receives a list of values (converted from JSON) and stores them internally, and a `process()` function that takes no arguments and returns a R list (which is automatically converted to JSON object)
* a **source**: there must be a `get_output()` function that takes no arguments and must return a list (automatically converted to JSON)
* a **sink**: there must be a `load_data(list)` function that takes a list as a single argument; that list represents the JSON received by the sink agent

Regardless its type, the script may **optionally** define a `set_params(list)` function that receives the list corresponding to the JSON ocject passed during plugin startup.

**Notes on functions**:

- `load_data(list)`: in sinks and filters is the function that loads data from network into the R script; it receives a list (generated from the incoming JSON) and it is expected to store it internally in the script. The returned value might be `TRUE` (success), `FALSE` (falure), or a string like `success`, `failure`, `retry`, `error`, `critical`
- `get_output()`: in sources, must return a valid list and takes no arguments. The returned list may contain the field `return_type`, which may be `TRUE` (success), `FALSE` (falure), or a string like `success`, `failure`, `retry`, `error`, `critical`.
- `process()`: in filters, elaborates the data stored by `load_data()` and returns a valid list as result, taking no arguments. The returned list may contain the field `return_type`, which may be `TRUE` (success), `FALSE` (falure), or a string like `success`, `failure`, `retry`, `error`, `critical`.

For the meanings and effects of the return types, see the comments in the source code files `src/r_[source|filter|sink].cpp`.


---