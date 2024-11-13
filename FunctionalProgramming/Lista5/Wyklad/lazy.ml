type 'a mylazy = (unit -> 'a, 'a) Either.t ref

let from_fun f = ref (Either.Left f)

let force x =
  match !x with
  | Either.Right v -> v
  | Either.Left  f -> let v = f () in x := Right v; v

