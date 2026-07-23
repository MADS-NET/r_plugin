/*
  ____          _             _           
 |  _ \   _ __ | |_   _  __ _(_)_ __  ___ 
 | |_) | | '_ \| | | | |/ _` | | '_ \/ __|
 |  _ <  | |_) | | |_| | (_| | | | | \__ \
 |_| \_\ | .__/|_|\__,_|\__, |_|_| |_|___/
         |_|            |___/             

Multi-driver plugin for R.
This requires MADS v3.4.x. Previous versions of MADS don't support multi-driver 
plugins.
Author: Paolo Bosetti, University of Trento, Italy
*/
#include <nlohmann/json.hpp>
#include <pugg/Kernel.h>
#include "r_plugin_common.hpp"
#include "r_source.hpp"
#include "r_filter.hpp"
#include "r_sink.hpp"


/*
  ____  _             _             _      _
 |  _ \| |_   _  __ _(_)_ __     __| |_ __(_)_   _____ _ __
 | |_) | | | | |/ _` | | '_ \   / _` | '__| \ \ / / _ \ '__|
 |  __/| | |_| | (_| | | | | | | (_| | |  | |\ V /  __/ |
 |_|   |_|\__,_|\__, |_|_| |_|  \__,_|_|  |_| \_/ \___|_|
                |___/
Enable the class as plugin
*/
MADS_REGISTER_PLUGINS(RSource, RFilter, RSink);


/*
                  _       
  _ __ ___   __ _(_)_ __  
 | '_ ` _ \ / _` | | '_ \ 
 | | | | | | (_| | | | | |
 |_| |_| |_|\__,_|_|_| |_|
                          
*/

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <plugin_type> [args...]" << std::endl;
    std::cerr << "plugin_type: source, filter, sink" << std::endl;
    return 1;
  }
  if (std::string(argv[1]) == "source") {
    return main_source(argc - 1, argv + 1);
  } else if (std::string(argv[1]) == "filter") {
    return main_filter(argc - 1, argv + 1);
  } else if (std::string(argv[1]) == "sink") {
    return main_sink(argc - 1, argv + 1);
  } else {
    std::cerr << "Unknown plugin type: " << argv[1] << std::endl;
    return 1;
  }

  return 0;
}

