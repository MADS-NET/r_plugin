last_input <- list()
multiplier <- 2

set_params <- function(params) {
  if (!is.null(params$multiplier)) {
    multiplier <<- params$multiplier
  }
}

load_data <- function(input) {
  last_input <<- input
  TRUE
}

process <- function() {
  result <- last_input
  if (!is.null(result$value)) {
    result$filtered_value <- result$value * multiplier
  }
  result$return_type <- "success"
  result
}
