let rec tabulate s ?(a=0) b =
  if a > b then []
  else (s a) :: tabulate s ~a:(a + 1) b
