type 'a view =
  | Leaf
  | Node of 'a t * 'a * 'a t

and 'a t = 'a view

let view t = t

let compare_elt = compare

let empty = Leaf

let rec add t x =
  match t with
  | Leaf -> Node(Leaf, x, Leaf)
  | Node(l, y, r) ->
    begin match compare x y with
    | 0            -> t
    | z when z < 0 -> Node(add l x, y, r)
    | _            -> Node(l, y, add r x)
    end

let rec mem t x =
  match t with
  | Leaf -> false
  | Node(l, y, r) ->
    begin match compare x y with
    | 0            -> true
    | z when z < 0 -> mem l x
    | _            -> mem r x
    end

