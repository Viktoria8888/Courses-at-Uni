module type OrderedType = sig
  type t
  val compare : t -> t -> int
end

module type S = sig
  type elt
  type t

  type view =
    | Leaf
    | Node of t * elt * t

  val view : t -> view

  val empty : t

  val add : t -> elt -> t

  val mem : t -> elt -> bool
end

module Make(Elt : OrderedType) = struct
  type elt = Elt.t

  type view =
    | Leaf
    | Node of t * Elt.t * t

  and t = view

  let view t = t

  let compare_elt = Elt.compare

  let empty = Leaf

  let rec add t x =
    match t with
    | Leaf -> Node(Leaf, x, Leaf)
    | Node(l, y, r) ->
      begin match compare_elt x y with
      | 0            -> t
      | z when z < 0 -> Node(add l x, y, r)
      | _            -> Node(l, y, add r x)
      end

  let rec mem t x =
    match t with
    | Leaf -> false
    | Node(l, y, r) ->
      begin match compare_elt x y with
      | 0            -> true
      | z when z < 0 -> mem l x
      | _            -> mem r x
      end
end
