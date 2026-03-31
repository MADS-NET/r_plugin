#ifndef R_PLUGIN_COMMON_HPP
#define R_PLUGIN_COMMON_HPP

#include <EmbedR.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace RPluginCommon {

using json = nlohmann::json;
using EmbedR::RInterpreter;

inline void apply_common_r_params(json const &params, json &plugin_params) {
  plugin_params["use_renv"] = false;
  plugin_params["r_output_mode"] = "stdout";
  plugin_params.merge_patch(params);
}

inline RInterpreter::OutputMode parse_output_mode(json const &plugin_params) {
  auto const output_mode = plugin_params["r_output_mode"].get<std::string>();
  if (output_mode == "stdout") {
    return RInterpreter::OutputMode::Stdout;
  }
  if (output_mode == "buffer") {
    return RInterpreter::OutputMode::Buffer;
  }
  throw std::runtime_error(
    "Invalid value for r_output_mode. Expected 'stdout' or 'buffer'.");
}

inline void configure_r_options(
  json const &plugin_params,
  RInterpreter::Options &r_options) {
  r_options.auto_load_current_dir_renv = plugin_params.value("use_renv", false);
  r_options.output_mode = parse_output_mode(plugin_params);
}

inline void initialize_r_interpreter(
  json const &plugin_params,
  RInterpreter::Options &r_options,
  std::unique_ptr<RInterpreter> &r_interpreter) {
  configure_r_options(plugin_params, r_options);
  try {
    r_interpreter = std::make_unique<RInterpreter>(r_options);
  } catch (std::exception const &e) {
    throw std::runtime_error(
      "Error initializing R interpreter: " + std::string(e.what()));
  }
}

inline void source_init_script(
  json const &plugin_params,
  RInterpreter &r_interpreter) {
  if (!plugin_params.contains("init_script")) {
    throw std::runtime_error("Missing required parameter: init_script");
  }

  try {
    r_interpreter.source_script(plugin_params["init_script"].get<std::string>());
  } catch (std::exception const &e) {
    throw std::runtime_error(
      "Error sourcing init_script: " + std::string(e.what()));
  }
}

inline void validate_required_function(
  RInterpreter &r_interpreter,
  std::string const &function_name,
  std::string const &agent_type) {
  auto const expression =
    "exists('" + function_name + "') & is.function(" + function_name + ")";
  auto const result = r_interpreter.eval(expression);
  if (!std::holds_alternative<bool>(result) || !std::get<bool>(result)) {
    throw std::runtime_error(
      "The init_script must define a function named " + function_name +
      " with the appropriate signature for the " + agent_type + " type.");
  }
}

template <typename RequiredFunction>
inline void validate_required_functions(
  RInterpreter &r_interpreter,
  RequiredFunction const &required_function,
  std::string const &agent_type) {
  using DecayedType = std::decay_t<RequiredFunction>;

  if constexpr (
    std::is_constructible_v<std::string, RequiredFunction const &>) {
    validate_required_function(
      r_interpreter,
      std::string(required_function),
      agent_type);
  } else if constexpr (
    std::is_same_v<DecayedType, std::vector<std::string>>) {
    for (auto const &function_name : required_function) {
      validate_required_function(r_interpreter, function_name, agent_type);
    }
  } else {
    static_assert(
      std::is_constructible_v<std::string, RequiredFunction const &> ||
        std::is_same_v<DecayedType, std::vector<std::string>>,
      "required_function must be a string-like value or "
      "std::vector<std::string>");
  }
}

template <typename RequiredFunction>
inline void initialize_r_plugin(
  json const &params,
  json &plugin_params,
  RInterpreter::Options &r_options,
  std::unique_ptr<RInterpreter> &r_interpreter,
  RequiredFunction const &required_function,
  std::string const &agent_type) {
  apply_common_r_params(params, plugin_params);
  initialize_r_interpreter(plugin_params, r_options, r_interpreter);
  source_init_script(plugin_params, *r_interpreter);
  validate_required_functions(*r_interpreter, required_function, agent_type);
}

}  // namespace RPluginCommon

#endif
