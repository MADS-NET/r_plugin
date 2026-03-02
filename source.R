
print("Initializing ARIMA")

N <-  3000
i <- 0

df <- arima.sim(
  model = list(ar = c(0.8897, -0.4858), ma = c(-0.2279, 0.2488), order=c(2, 1, 2)),
  n = N
)

load_data <- function() {
  i <<- i + 1
  if (i > N) i <<- 1
  return(list("arima" = list("i" = i, "value" = df[i])))
}

