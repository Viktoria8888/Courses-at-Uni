type 'a queue =
  | Empty
  | Queue of 'a * 'a list * 'a list

let queue (f, r) =
  match f with
  | []     ->
    begin match List.rev r with
    | []     -> Empty
    | x :: f -> Queue(x, f, [])
    end
  | x :: f -> Queue(x, f, r)

let push x q =
  match q with
  | Empty          -> Queue(x, [], [])
  | Queue(y, f, r) -> Queue(y, f, x :: r)

let pop q =
  match q with
  | Empty  -> None
  | Queue(x, f, r) -> Some(x, queue (f, r))
