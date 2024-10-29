let rec scan f a s = fun (x:int) ->
  if x = 0 then f a (s 0)
  else f (scan f a s (x - 1)) (s x)



