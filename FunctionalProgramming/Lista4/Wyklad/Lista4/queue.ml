type 'a queue = 'a list * 'a list

let queue (f, r) =
  match f with
  | [] -> (List.rev r, [])
  | _  -> (f, r)

let push (f, r) x = queue (f, x :: r)

let pop (f, r) =
  match f with
  | [] -> None
  | x :: xs -> Some (x, queue (xs, r))
