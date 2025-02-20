module type RandomMonad = sig
  type 'a t
  val return  : 'a -> 'a t
  val bind    : 'a t -> ('a -> 'b t) -> 'b t
  val random  : int t
end

module Shuffle (R : RandomMonad) : sig
  val shuffle : 'a list -> 'a list R.t
end = struct

  let random_range (a : int) (b : int) : int R.t =
      let len = b - a + 1 in
          R.bind R.random
               (fun n -> R.return (a + (((n mod len) + len) mod len)))

  (* deterministyczna funkcja! *)
  let rec insert_at (x : 'a) (xs : 'a list) (ind : int) : 'a list =
      match ind with
      | 0 -> x::xs
      | _ -> let y::ys = xs in y::(insert_at x ys (ind - 1)) 
  
  let insert_random (x : 'a) (xs : 'a list) : 'a list R.t =
      R.bind (random_range 0 (List.length xs + 1))
             (fun ind -> R.return (insert_at x xs ind))
  
  let rec shuffle (xs : 'a list) : 'a list R.t =
      match xs with
      | []    -> R.return []
      | x::xs -> R.bind (shuffle xs) (insert_random x) 

end
