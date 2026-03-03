library(R6)

Source <- R6Class(
  "Source",
  public = list(
    N = NULL,
    i = NULL,
    df = list(),
    
    initialize = function(N = 3000) {
      self$N <- as.numeric(N)
      self$i <- 0
      self$df$x <- as.numeric(arima.sim(
        model = list(
          ar = c(0.8897, -0.4858),
          ma = c(-0.2279, 0.2488),
          order = c(2, 1, 2)
        ),
        n = self$N
      ))
      self$df$y <- as.numeric(arima.sim(
        model = list(
          ar = c(0.8897, -0.4858),
          ma = c(-0.2279, 0.2488),
          order = c(2, 1, 2)
        ),
        n = self$N
      ))
      self$df$z <- as.numeric(arima.sim(
        model = list(
          ar = c(0.8897, -0.4858),
          ma = c(-0.2279, 0.2488),
          order = c(2, 1, 2)
        ),
        n = self$N
      ))
    },
    
    current_data = function() {
      self$i <- self$i + 1
      if (self$i > self$N) self$i <- 1
      list("arima" = list("i" = self$i, "x" = self$df$x[self$i], "y" = self$df$y[self$i], "z" = self$df$z[self$i]))
    }
  )
)

arima <- Source$new(3000)

# Entry point
get_output <- function() arima$current_data()