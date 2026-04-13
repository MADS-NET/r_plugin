
parameters <- list(N=5, m=0, sd=1)

set_params <- function(params) {
  parameters <<- c(parameters, params)
  print(parameters)
}

load_data <- function(data) {
  print(paste("Received data:", data))
}