type 'a t

type 'a view =
  | Leaf
  | Node of 'a t * 'a * 'a t

val view : 'a t -> 'a view

val empty : 'a t

val add : 'a t -> 'a -> 'a t

val mem : 'a t -> 'a -> bool

