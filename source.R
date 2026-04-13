
parameters <- list(N=5, m=0, sd=1)

set_params <- function(params) {
  parameters <<- c(parameters, params)
  print(parameters)
}

# # Entry point
get_output <- function() {
  r <- list(result = round(rnorm(parameters$N, parameters$m, parameters$sd), 2))
  r$mean <- mean(r$result)
  if (r$mean >= 0) {
    r$return_type <- "success"
  } else {
    r$return_type <- "error"
  }
  return(r)
}
